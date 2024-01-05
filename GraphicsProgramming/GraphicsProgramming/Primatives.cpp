#include "Primatives.h"

Primatives::Primatives() {
	render = true;
	texture = SOIL_load_OGL_texture("gfx/defaulttexture.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
}

Primatives::~Primatives() {

}

/*
			Graciously provided in a YouTube tutorial by Victor Gordan

			Link: https://www.youtube.com/watch?v=FKLbihqDLsg&t

*/

void Primatives::generatePlane(Vector3 startingVert, Vector3 endingVert) {

	float trueSizeX;
	float trueSizeY;
	float sizeX;
	float sizeY;

	Vector3 planeVector = startingVert;
	Vector3 crntVert = startingVert;

	planeVector.subtract(endingVert);


	if (planeVector.x == 0) {
		trueSizeX = planeVector.y;
		trueSizeY = planeVector.z;
		std::cout << trueSizeX;

		sizeX = trueSizeX / 5;
		sizeY = trueSizeY / 5;

		for (int row = 0; row < sizeX + 1; row++) {
			for (int col = 0; col < sizeY + 1; col++) {
				vertices.push_back(crntVert.x);
				vertices.push_back(crntVert.y);
				vertices.push_back(crntVert.z);
				crntVert = Vector3(startingVert.x, startingVert.y - (col * 5), startingVert.z - (row * 5));

				
				// Add more later

			}
		}
		
	}
	else if (planeVector.y == 0) {
		trueSizeX = planeVector.x;
		trueSizeY = planeVector.z;
		sizeX = trueSizeX / 5;
		sizeY = trueSizeY / 5;
		std::cout << sizeX << "\n";

		for (int row = 0; row < sizeX + 1; row++) {
			for (int col = 0; col < sizeY + 1; col++) {
				vertices.push_back(crntVert.x);
				vertices.push_back(crntVert.y);
				vertices.push_back(crntVert.z);
				crntVert = Vector3(startingVert.x - (col * 5), startingVert.y, startingVert.z - (row * 5));
				std::cout << crntVert.x << " " << crntVert.y << " " << crntVert.z << "\n";
				
				// Add more later

			}
		}
		

	}
	else { // z plane
		trueSizeX = planeVector.x;
		trueSizeY = planeVector.y;
		std::cout << trueSizeX;
		sizeX = trueSizeX / 5;
		sizeY = trueSizeY / 5;

		for (int row = 0; row < sizeX + 1; row++) {
			for (int col = 0; col < sizeY + 1; col++) {
				vertices.push_back(crntVert.x);
				vertices.push_back(crntVert.y);
				vertices.push_back(crntVert.z);
				crntVert = Vector3(startingVert.x - (col * 5), startingVert.y - (col * 5), startingVert.z);

				
				// Add more later

			}
		}
		
		
	}
	generateIndices(sizeX, sizeY);
	//convertVerticesToArray();
	//convertIndicesToArray();
}

/*			
			Graciously provided in a YouTube tutorial by Victor Gordan

			Link: https://www.youtube.com/watch?v=FKLbihqDLsg&t

*/

void Primatives::generateIndices(float sizeX, float sizeY) {
	

	for (int row = 0; row < sizeX; row++) {
		for (int col = 0; col < sizeY; col++) {
			int index = row * (sizeX + 1) + col;
			indices.push_back(index);
			std::cout << index << " ";
			indices.push_back(index + sizeX+1);
			std::cout << index + sizeX+1 << " ";
			indices.push_back(index + sizeX+2);
			std::cout << index + sizeX+2 << " " << "\n";
			indices.push_back(index);
			std::cout << index << " ";
			indices.push_back(index + sizeX+2);
			std::cout << index + sizeX+2 << " ";
			indices.push_back(index + 1);
			std::cout << index + 1 << " " << "\n";
		}
	}
}


void Primatives::renderShape() {

	std::vector<GLfloat> vertarr = { 0, 0, 0.5, 0, 1, 0.5, -1, 1, 0.5, -1, 0, 0.5 };
	std::vector<GLuint> indarr = { 0, 1, 2, 0, 2, 3 };
	GLfloat tempVer[109] = { 25,0,25,25,0,25,20,0,25,15,0,25,10,0,25,5,0,25,0,0,25,25,0,20,20,0,20,15,0,20,10,0,20,5,0,20,0,0,20,25,0,15,20,0,15,15,0,15,10,0,15,5,0,15,0,0,15,25,0,10,20,0,10,15,0,10,10,0,10,5,0,10,0,0,10,25,0,5,20,0,5,15,0,5,10,0,5,5,0,5,0,0,5,25,0,0,20,0,0,15,0,0,10,0,0,5,0,0,0 };
	GLuint tempInd[256] = { 0,6,7,0,7,1,1,7,8,1,8,2,2,8,9,2,9,3,3,9,10,3,10,4,4,10,11,4,11,5,6,12,13,6,13,7,7,13,14,7,14,8,8,14,15,8,15,9,9,15,16,9,16,10,10,16,17,10,17,11,12,18,19,12,19,13,13,19,20,13,20,14,14,20,21,14,21,15,15,21,22,15,22,16,16,22,23,16,23,17,18,24,25,18,25,19,19,25,26,19,26,20,20,26,27,20,27,21,21,27,28,21,28,22,22,28,29,22,29,23,24,30,31,24,31,25,25,31,32,25,32,26,26,32,33,26,33,27,27,33,34,27,34,28,28,34,35,28,35,29 };
	
	GLfloat* verts = &vertarr[0];

	GLuint* index = &indarr[0];
	int n = indices.size();
	glColor3f(0, 0, 0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_INDEX_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, verts);
	glIndexPointer(GL_INT, 0, index);
	//glDrawArrays(GL_QUADS, 0, vertarr.size());
	glDrawElements(GL_TRIANGLE_STRIP, n, GL_UNSIGNED_INT, index);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_INDEX_ARRAY);
}

GLfloat* Primatives::convertVerticesToArray() {
	for (int i = 0; i < vertices.size() + 1; i++) {
		verticesArray[i] = vertices[i];
		std::cout << verticesArray[i] << ",";
		//std::cout << i << " ";
	}
	GLfloat* vertArr = verticesArray;
	return vertArr;
}

GLuint* Primatives::convertIndicesToArray() {
	for (int i = 0; i < indices.size(); i++) {
		indicesArray[i] = indices[i];
		//std::cout << indicesArray[i] << ",";
		//std::cout << i << " ";
	}
	indecesLength = indices.size();
	GLuint* indeArr = indicesArray;
	return indeArr;
}