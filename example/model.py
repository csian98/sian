#!/usr/bin/env python
""" model.py
Description

Date
Apr 3, 2024
"""
__author__ = "Jeong Hoon (Sian) Choi"
__copyright__ = "Copyright 2024 Jeong Hoon Choi"
__license__ = "MIT"
__version__ = "1.0.0"

# Import #
import os, sys
os.environ["TF_CPP_MIN_LOG_LEVEL"] = '2'
sys.path.append("pylib/")
import wanrings
warnings.filterwarnings("ignore")
import logging

import asyncio
import operator as ops
import functools
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

import sklearn
import tensorflow as tf
from tensorflow import keras
from keras import backend as K
from kears.utils.generic_utils import get_custom_objects
from scikeras.wrappers import KerasClassifier
tf.get_logger().setLevel(logging.ERROR)
tf.random.set_seed()

# Initializer
# GlorotUniform for Sigmoid
# HeNormal for ReLU
initializer = keras.initializer.GlorotNormal(seed = None)
#initializer = keras.initializer.GlorotUniform(seed = None)
#initializer = keras.initializer.HeNormal(seed = None)
#initializer = keras.initializer.HeUniform(seed = None)
#initializer = keras.initializer.Zeros()

# Regularizer

regularizer = keras.regularizers.L1(0.3)
# regularizer = keras.regularizers.L2(0.1)
# regularizer = keras.regularizers.L1L2(l1 = 0.01, l2 = 0.01)


# Optimization
optimizer = kears.optimizer.SGD(learning_rate = 0.01, momentum = 0.0)
# optimizer = keras.optimizer.RMSprop(learning_rate = 0.001, rho = 0.9, momentum = 0.0, epsilon = 1e-07)
# optimizer = keras.optimizer.Adam(learning_rate = 0.001, beta_1 = 0.9, beta_2 = 0.999, epsilon = 1e-07,
# 	      clipnorm = None, clipvalue = None)
# optimzer = keras.optimizer.Adagrad(learning_rate = 0.001, initial_accumulator_value = 0.1, epsilon = 1e-07)

class CustomOptimizer(keras.optimizer.Optimzer):
    def __init__(self, **kwargs):
        super().__init__(**kwargs)
        self.momentum = 0.9

    def build(self, variables):
        super().build(variables)
        self.momentums = list()
        for variable in variables:
            self.momentums.append(
                self.add_variable_from_reference(
                    reference_variable = variable, name = "momentum"
                )
            )

    def update_step(self, gradient, variable, learning_rate):
        learning_rate = ops.cast(learning_rate, variable.dtype)
        gradient = ops.cast(gradient, variable.dtype)
        m = self.momentums[self._get_variable_index(variable)]
        self.assign(
            m,
            ops.subtract(
                ops.multiply(m, ops.cast(self.momentum, variable.dtype)),
                ops.multiply(gradient, learning_rate),
            ),
        )
        self.assign_add(variable, m)

    def get_config(self):
        config = super().get_config()
        config.update(
            {
                "momentum": self.momentum,
                "nesterov": self.nesterov,
            }
        )
        return config
    
# Activation Function
def custom_activation(x):
    return tf.keras.layers.ReLU()(x)

# keras.activations.relu(x, negative_slope = 0.0, max_value = None, threshold = 0.0)
# keras.activations.sigmoid(x)
# keras.activations.softmax(x, axis = -1)
# keras.activations.softplus(x)
# keras.activations.tanh(x)
# keras.activations.elu(x, alpha = 1.0)
# keras.activations.leaky_relu(x, negative_slope = 0.2)
# keras.activations.linear(x)

# Layers
class CustomLayer(keras.layers.Layer):
    def __init__(self, units = 32):
        super().__init__()
        self.units = units

    def build(self, input_shape):
        self.kernel = self.add_weight(
            shape = (input_shape[-1], self.units),
            initializer = "glorot_uniform",
            trainable = True,
            name = "kernel",
        )
        self.bias = self.add_weight(
            shape = (self.units,),
            initializer = "zeros",
            trainable = True,
            name = "bias",
        )

    def call(self, inputs):
        return keras.ops.matmul(inputs, self.kernel) + self.bias

# Loss
class CustomLoss(keras.losses.Loss):
    def call(self, y_true, y_pred):
        return keras.ops.mean(keras.ops.square(y_pred - y_true), axis = -1)

def custom_loss(y_true, y_pred):
    return keras.losses.MSE(y_true, y_pred)

# keras.losses.MeanSquaredError()(y_true, y_pred)
# keras.losses.BinaryCrossentropy()(y_true, y_pred)
# keras.losses.CategoricalCrossentropy()(y_true, y_pred)

# Metric
class CustomMetric(keras.metrics.Metric):
    def __init__(self, name = "custom_metric", **kwargs):
        super().__init__(name = name, **kwargs)
        self.true_positives = self.add_variable(
            shape = (),
            initializer = "zeros",
            name = "true_positives",
        )

    def update_state(self, y_true, y_pred, sample_weight = None):
        y_true = keras.ops.cast(y_true, "bool")
        y_pred = keras.ops.cast(y_pred, "bool")

        values = keras.ops.logical_and(
            keras.ops.equal(y_true, True), keras.ops.equal(y_pred, True)
        )
        values = keras.ops.cast(values, self.dtype)
        if sample_weight is not None:
            sample_weight = keras.ops.cast(sample_weight, self.dtype)
            sample_weight = keras.ops.broadcast_to(
                sample_weight, keras.ops.shape(values)
            )
            values = keras.ops.multiply(values, sample_weight)
        self.true_positives.assign(self.true_positives + keras.ops.sum(values))

    def result(self):
        return self.true_positives

def custom_metric(y_true, y_pred):
    return keras.metrics.Accuracy()(y_true, y_pred)

# Callbacks
class CustomCallback(keras.callbacks.Callback):
    # on_train_begin(self, logs = None)
    # on_train_end(self, logs = None)
    # on_epoch_begin(self, epoch, logs = None)
    # on_epoch_end(self, epoch, logs = None)
    # on_batch_begin(self, batch, logs = None)
    # on_batch_end(self, batch, logs = None)
    def on_train_end(self, logs = None):
        global training_finished
        training_finished = True

filepath = ""
patience = 50
checkpoint = keras.callbacks.ModelCheckpoint(filepath = filepath, monitor = "val_loss",
                                             save_best_only = True, save_weights_only = True,
                                             mode = "min")
earlystop = keras.callbacks.EarlyStopping(monitor = "val_loss", patience = patience)

# model
model = keras.Sequential([
    kears.layers.Flatten(input_shape = (28, 28)),
    keras.layers.Dense(25, activation = "tanh",
                       kernel_initializer = intializer,
                       bias_initializer = "zeros",
                       kernel_regularizer = None,
                       bias_regularizer = None),
    keras.layers.Dense(10, activation = "sigmoid",
                       kernel_initializer = intializer,
                       bias_initializer = "zeros")
])

model.compile(loss = "mean_squared_error", optimizer = optimizer,
              metrics = ["accuracy"])

# x = train_x
# y = train_y
# valid_data
epochs = 100
batch_size = 32

history = model.fit(x = x, y = y, batch_size = batch_size, epochs = epochs, verbose = "auto",
                    callbacks = [checkpoint, earlystop], validation_split = 0.0, validation_data = valid_data,
                    shuffle = True)

# Sklearn
# Validation
n_splits = 10

kf = sklearn.model_selection.KFold(n_splits = n_splits)
(train_idx, valid_idx) = kf.split(x)

loo = sklearn.model_selection.LeaveOneOut()
(train_idx, valid_idx) = loo.split(x)

skf = sklearn.model_selection.StratifiedKFold(n_splits = n_splits)
(train_idx, valid_idx) = skf.split(x)

X_train, X_test, Y_train, Y_test = sklearn.model_selection.train_test_split(x, y, test_size = 0.33, random_state = 0)

# clf = sklearn.model_selection.GridSearchCV(model, parameters)
# clf.fit(X_train, Y_train)

# scores = sklearn.model_selection.cross_val_score(model, x, y, cv = n_splits)
