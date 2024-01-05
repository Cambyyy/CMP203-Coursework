#pragma once

#include "Vector3.h"
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <iostream>
#include "SOIL.h"
#include <vector>
#include <fstream>


class Primatives
{

public:

	Primatives();
	
	~Primatives();

	std::vector<float> getVerticesArray() { return vertices; }
	std::vector<float> getNormalsArray() { return normals; }
	std::vector<float> getTextureArray() { return textures; }
	std::vector<int> getIndicesArray() { return indices; }

	int getIndicesLength() { return indecesLength; }

	GLfloat* convertVerticesToArray();
	GLuint* convertIndicesToArray();

	void renderShape();


	void changeTextureMap(GLuint);
	void setRender(bool);

	void generatePlane(Vector3, Vector3);

private:

	//void generateVertices(Vector3, Vector3, float, float);

	void generateIndices(float, float);
	GLfloat verticesArray[2048]; // 3 values per point
	float normalsArray[2048]; // 3 values per point
	float texturesArray[2048]; // 2  values per point
	GLuint indicesArray[2048]; // 3 values per point

	int verticesLength = 0;
	int normalsLength = 0;
	int textureLength = 0;
	int indecesLength = 0;

	std::vector<float> vertices; // 3 values per point
	std::vector<float> normals; // 3 values per point
	std::vector<float> textures; // 2  values per point
	std::vector<int> indices; // 3  values per point

	bool render;

	GLuint texture;

};