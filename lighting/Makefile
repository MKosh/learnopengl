CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic
ROOT_DIR := ..
SRC_DIR = .
RNDR_DIR := $(ROOT_DIR)/utils
TARGET_PROG := lighting
RNDR_BLD := $(RNDR_DIR)/build

RNDR_SRC := $(shell find $(RNDR_DIR) -name '*.cc' -or -name '*.c' -or -name '*.cpp')
RNDR_SRC_FILES := $(RNDR_SRC:../utils/%=%)
RNDR_OBJS := $(RNDR_SRC_FILES:%=../utils/build/%.o)

DEPS := $(RNDR_OBJS:.o=.d)
INC_FLAGS := $(addprefix -I,$(RNDR_DIR))

CPPFLAGS := $(INC_FLAGS) -MMD -MP

$(SRC_DIR)/$(TARGET_PROG): $(RNDR_OBJS) $(SRC_DIR)/lighting.cc
	$(CXX) -I$(ROOT_DIR)/utils $(RNDR_OBJS) $(SRC_DIR)/lighting.cc -o $@ $(LDFLAGS) -lassimp -lglfw

$(RNDR_BLD)/%.c.o: $(RNDR_DIR)/%.c
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(RNDR_BLD)/%.cc.o: $(RNDR_DIR)/%.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(RNDR_BLD)/%.cpp.o: $(RNDR_DIR)/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -r $(RNDR_BLD)

run: $(SRC_DIR)/$(TARGET_PROG)
	./lighting

-include $(DEPS)
