# ENV
EXEC_TARGET := main
EXEC_SRC := main.cpp
EXEC_NV_SRC := main.cu
LIB_TARGET := libsian.a
CC := clang
CXX := c++
NVCC := nvcc
AR := ar

# DIR_STRUCTURE
BUILD_DIR := build
SRC_DIR := src
INC_DIR := include /opt/homebrew/include
LIB_DIR := lib

SRCS := $(shell find $(SRC_DIR) -name "*.cpp" -or -name "*.c" -or -name "*.s" -or -name "*.cu")
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

#INC_DIRS := $(shell find $(INC_DIR) -type d)
INC_DIRS := $(INC_DIR)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# Flags
CFLAGS := $(INC_FLAGS) -MMD -MP
CXXFLAGS := -std=c++20 $(INC_FLAGS) -MMD -MP
NVCCFLAGS := -I/Users/csian/projects/cuda/include
LDFLAGS := -L/Users/csian/projects/sian/lib -lsian
ARFLAGS := crs

$(LIB_DIR)/$(LIB_TARGET): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.cu.o: %.cu
	mkdir -p $(dir $@)
	$(NVCC) $(NVCCFLAGS) -c $< -o $@

.PHONY: exec exec_nv clean
clean:
	rm -r $(BUILD_DIR)/

exec: $(LIB_DIR)/$(LIB_TARGET)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(EXEC_SRC) -o $(EXEC_TARGET)

exec_nv: $(LIB_DIR)/$(LIB_TARGET)
	$(NVCC) $(NVCCFLAGS) $(LDFLAGS) $(EXEC_NV_SRC) -o $(EXEC_TARGET)

-include $(DEPS)
