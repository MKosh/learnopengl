CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic
ROOT_DIR := ..
SRC_DIR = ./
RNDR_DIR := $(ROOT_DIR)/utils
TARGET_PROG := gui
RNDR_BLD := $(RNDR_DIR)/build

RNDR_SRC := $(shell find $(RNDR_DIR) -name '*.cc' -or -name '*.c' -or -name '*.cpp')
RNDR_SRC_FILES := $(RNDR_SRC:../utils/%=%)
RNDR_OBJS := $(RNDR_SRC_FILES:%=../utils/build/%.o)

DEPS := $(RNDR_OBJS:.o=.d)
INC_FLAGS := $(addprefix -I,$(RNDR_DIR))

CPPFLAGS := $(INC_FLAGS) -MMD -MP

$(SRC_DIR)/$(TARGET_PROG): $(RNDR_OBJS) $(SRC_DIR)/gui.cc
	$(CXX) $(RNDR_OBJS) $(SRC_DIR)/gui.cc -o $@ $(LDFLAGS) -lglfw3

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
	./gui

-include $(DEPS)



# CXX = g++
# CXXFLAGS = -std=c++20 -Wall -Wextra -Wpedantic

# compile: glad.o stb_image.o texture.o EBO.o VBO.o VAO.o shader.o Renderer.o
# 	${CXX} ${CXXFLAGS} gui.cc ../glad.o ../utils/stb_image.o ../utils/texture.o ../utils/EBO.o ../utils/VAO.o ../utils/VBO.o ../utils/shader.o ../utils/Renderer.o -o gui -ldl -lglfw
# 	./gui

# run:
# 	./gui

# glad.o: ../glad.c
# 	${CXX} ${CXXFLAGS} -c ../glad.c -o ../glad.o

# stb_image.o: ../utils/stb_image.cc
# 	${CXX} ${CXXFLAGS} -c ../utils/stb_image.cc -o ../utils/stb_image.o

# texture.o: ../utils/texture.cc
# 	${CXX} ${CXXFLAGS} -c ../utils/texture.cc -o ../utils/texture.o

# EBO.o: ../utils/EBO.cc
# 	${CXX} ${CXXFLAGS} -c ../utils/EBO.cc -o ../utils/EBO.o

# VBO.o: ../utils/VBO.cc
# 	${CXX} ${CXXFLAGS} -c ../utils/VBO.cc -o ../utils/VBO.o

# VAO.o: ../utils/VAO.cc
# 	${CXX} ${CXXFLAGS} -c ../utils/VAO.cc -o ../utils/VAO.o

# shader.o: ../utils/shader.cc
# 	${CXX} ${CXXFLAGS} -c ../utils/shader.cc -o ../utils/shader.o

# Renderer.o: ../utils/Renderer.cc
# 	${CXX} ${CXXFLAGS} -c ../utils/Renderer.cc -o ../utils/Renderer.o
