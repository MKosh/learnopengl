CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Wpedantic

compile: glad.o stb_image.o texture.o EBO.o VBO.o VAO.o shader.o Renderer.o
	${CXX} ${CXXFLAGS} coordinates.cc ../glad.o ../utils/stb_image.o ../utils/texture.o ../utils/EBO.o ../utils/VAO.o ../utils/VBO.o ../utils/shader.o ../utils/Renderer.o -o coordinates -ldl -lglfw
	./coordinates

run:
	./coordinates

glad.o: ../glad.c
	${CXX} ${CXXFLAGS} -c ../glad.c -o ../glad.o

stb_image.o: ../utils/stb_image.cc
	${CXX} ${CXXFLAGS} -c ../utils/stb_image.cc -o ../utils/stb_image.o

texture.o: ../utils/texture.cc
	${CXX} ${CXXFLAGS} -c ../utils/texture.cc -o ../utils/texture.o

EBO.o: ../utils/EBO.cc
	${CXX} ${CXXFLAGS} -c ../utils/EBO.cc -o ../utils/EBO.o

VBO.o: ../utils/VBO.cc
	${CXX} ${CXXFLAGS} -c ../utils/VBO.cc -o ../utils/VBO.o

VAO.o: ../utils/VAO.cc
	${CXX} ${CXXFLAGS} -c ../utils/VAO.cc -o ../utils/VAO.o

shader.o: ../utils/shader.cc
	${CXX} ${CXXFLAGS} -c ../utils/shader.cc -o ../utils/shader.o

Renderer.o: ../utils/Renderer.cc
	${CXX} ${CXXFLAGS} -c ../utils/Renderer.cc -o ../utils/Renderer.o

