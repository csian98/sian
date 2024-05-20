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
INC_DIR := /Users/csian/projects/sian/include /opt/homebrew/include
LIB_DIR := /Users/csian/projects/sian/lib

SRCS := $(shell find $(SRC_DIR) -name "*.cpp" -or -name "*.c" -or -name "*.s" -or -name "*.cu")
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

#INC_DIRS := $(shell find $(INC_DIR) -type d)
INC_DIRS := $(INC_DIR)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# Flags
CFLAGS := $(INC_FLAGS) -MMD -MP
CXXFLAGS := -std=c++20 $(INC_FLAGS) -MMD -MP
NVCCFLAGS := $(INC_FLAGS)
LDFLAGS := -L/Users/csian/projects/sian/lib -lsian
ARFLAGS := crs

$(LIB_DIR)/$(LIB_TARGET): $(OBJS)
	mkdir -p $(dir $@)
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

.PHONY: exec exec_nv clean clean_lib
clean:
	rm -r $(BUILD_DIR)/*

clean_lib:
	rm -r $(LIB_DIR)/*

exec: $(LIB_DIR)/$(LIB_TARGET)
	$(CXX) -o $(EXEC_TARGET) $(EXEC_SRC) $(CXXFLAGS) $(LDFLAGS)
	rm $(EXEC_TARGET).d

exec_nv: $(LIB_DIR)/$(LIB_TARGET)
	$(NVCC) -o $(EXEC_TARGET) $(EXEC_NV_SRC) $(NVCCFLAGS) $(LDFLAGS)
	rm $(EXC_NV_SRC).d

-include $(DEPS)
