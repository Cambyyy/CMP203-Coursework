// Below ifdef required to remove warnings for unsafe version of fopen and fscanf.
// Secure version won't work cross-platform, forcing this small hack.
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "Model.h"

bool Model::load(char* modelFilename, char* textureFilename)
{
	bool result;

	// Load in the model data,
	result = loadModel(modelFilename);
	if (!result)
	{
		//MessageBox(NULL, "Model failed to load", "Error", MB_OK);
		return false;
	}

	// Load the texture for this model.
	loadTexture(textureFilename);

	return true;
}

void Model::render()
{
	// TODO: Need to add code here to render the loaded model
	// How this is done is based on how you stored and sorted the data
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertexArray);
	glDrawArrays(GL_TRIANGLES, 0, n);
	glDisableClientState(GL_VERTEX_ARRAY);
	

}

void Model::vertexArrayConv() {
	for (int i = 0; i < n; i++) {
		vertexArray[i] = vertex[i];
	}
}


// Modified from a mulit-threaded version by Mark Ropper.
bool Model::loadModel(char* filename)
{
	vector<Vector3> verts;
	vector<Vector3> norms;
	vector<Vector3> texCs;
	vector<unsigned int> faces;

	FILE* file = fopen(filename, "r");
	if (file == NULL)
	{
		return false;
	}
	while (true)
	{
		char lineHeader[128];

		// Read first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
		{
			break; // exit loop
		}
		else // Parse
		{
			if (strcmp(lineHeader, "v") == 0) // Vertex
			{
				Vector3 vertex;
				fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				verts.push_back(vertex);
			}
			else if (strcmp(lineHeader, "vt") == 0) // Tex Coord
			{
				Vector3 uv;
				fscanf(file, "%f %f\n", &uv.x, &uv.y);
				texCs.push_back(uv);
			}
			else if (strcmp(lineHeader, "vn") == 0) // Normal
			{
				Vector3 normal;
				fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				norms.push_back(normal);
			}
			else if (strcmp(lineHeader, "f") == 0) // Face
			{
				unsigned int face[9];
				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &face[0], &face[1], &face[2],
					&face[3], &face[4], &face[5],
					&face[6], &face[7], &face[8]);
				if (matches != 9)
				{
					// Parser error, or not triangle faces
					return false;
				}

				for (int i = 0; i < 9; i++)
				{
					faces.push_back(face[i]);
				}


			}
		}
	}

#pragma region unroll_data
	// "Unroll" the loaded obj information into a list of triangles.
	// TODO: By this point all model has been read from the file, but is not in the correct order.
	// You NEED to loop over all the data and sort it into a render ready order/format.
	
	int noFaces = faces.size();
	bool complete = true;
	while (!complete) {
		int i = 0;
		float vert = verts[faces[i]].x;
		vertex.push_back(vert);
		vert = verts[faces[i]].y;
		vertex.push_back(vert);
		vert = verts[faces[i]].z;
		vertex.push_back(vert);
		float tex = texCs[faces[i + 1]].x;
		texCoords.push_back(tex);
		tex = texCs[faces[i + 1]].y;
		texCoords.push_back(tex);
		float norm = norms[faces[i + 2]].x;
		normals.push_back(norm);
		norm = norms[faces[i + 2]].y;
		normals.push_back(norm);
		norm = norms[faces[i + 2]].z;
		normals.push_back(norm);
		if (i + 1 == noFaces) {
			complete = true;
		}
		//else if ((i + 1 == noFaces))
		i += 3;
	}
	n = vertex.size();


#pragma endregion unroll_data

	// Once data has been sorted clear read data (which has been copied and are not longer needed).
	verts.clear();
	norms.clear();
	texCs.clear();
	faces.clear();

	return true;
}

void Model::loadTexture(char* filename)
{
	texture = SOIL_load_OGL_texture
	(
		filename,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_INVERT_Y // Depending on texture file type some need inverted others don't.
	);

	//check for an error during the load process
	if (texture == 0)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}

}