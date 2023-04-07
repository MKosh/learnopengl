CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic
SRC_DIR = ./
RNDR_DIR := ../utils/
TARGET_PROG := coordinates
RNDR_BLD := ../utils/build

RNDR_SRC := $(shell find $(RNDR_DIR) -name '*.cc')
RNDR_OBJS := $(RNDR_SRC:%=$(RNDR_BLD)/%.o)

DEPS := $(RNDR_OBJS:.o=.d)
INC_FLAGS := $(addprefix -I,$(RNDR_DIR))

CPPFLAGS := $(INC_FLAGS) -MMD -MP

$(SRC_DIR)/$(TARGET_PROG): $(RNDR_OBJS) $(SRC_DIR)/coordinates.cc
	$(CXX) $(RNDR_OBJS) $(SRC_DIR)/coordinates.cc -o $@ $(LDFLAGS) -lglfw3

$(RNDR_BLD)/%.cc.o: %.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -r $(RNDR_BLD)

-include $(DEPS)
# compile: glad.o stb_image.o texture.o EBO.o VBO.o VAO.o shader.o Renderer.o
# 	${CXX} ${CXXFLAGS} coordinates.cc ../glad.o ../utils/stb_image.o ../utils/texture.o ../utils/EBO.o ../utils/VAO.o ../utils/VBO.o ../utils/shader.o ../utils/Renderer.o -o coordinates -ldl -lglfw3
# 	./coordinates

# compile_windows: w_glad.o w_stb_image.o w_texture.o w_EBO.o w_VBO.o w_VAO.o w_shader.o w_Renderer.o
# 	x86_64-w64-mingw32-g++ ${CXXFLAGS} -I/usr/include/GLFW -I/usr/include/glad -I/usr/include/glm -I/usr/include/asm-generic -I/usr/x86_64-w64-mingw32-g/include coordinates.cc -L../ ../glad.dll ../utils/stb_image.o ../utils/texture.o ../utils/EBO.o ../utils/VAO.o ../utils/VBO.o ../utils/shader.o ../utils/Renderer.o -o coordinates -L/usr/local/lib -lglfw3

# run:
# 	./coordinates

# ###############################################################################
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

# ###############################################################################
# w_glad.o: ../glad.c
# 	${CXX} ${CXXFLAGS} -fPIC -shared ../glad.c -o ../glad

# w_stb_image.o: ../utils/stb_image.cc
# 	${CXX} ${CXXFLAGS} -c ../utils/stb_image.cc -o ../utils/stb_image.o

# w_texture.o: ../utils/texture.cc
# 	${CXX} ${CXXFLAGS} -c ../utils/texture.cc -o ../utils/texture.o

# w_EBO.o: ../utils/EBO.cc
# 	${CXX} ${CXXFLAGS} -c ../utils/EBO.cc -o ../utils/EBO.o

# w_VBO.o: ../utils/VBO.cc
# 	${CXX} ${CXXFLAGS} -c ../utils/VBO.cc -o ../utils/VBO.o

# w_VAO.o: ../utils/VAO.cc
# 	${CXX} ${CXXFLAGS} -c ../utils/VAO.cc -o ../utils/VAO.o

# w_shader.o: ../utils/shader.cc
# 	${CXX} ${CXXFLAGS} -c ../utils/shader.cc -o ../utils/shader.o

# w_Renderer.o: ../utils/Renderer.cc
# 	${CXX} ${CXXFLAGS} -c ../utils/Renderer.cc -o ../utils/Renderer.o

