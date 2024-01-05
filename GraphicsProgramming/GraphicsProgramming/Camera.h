#pragma once

#include "Vector3.h"

class Camera
{
public:
	
	Camera();
	Camera(Vector3, Vector3);
	~Camera();

	void setOrientation(Vector3 rotation) { orientation = rotation; }
	void setPosition(Vector3 pos) { position = pos; }

	Vector3 getPosition() { return position; }
	Vector3 getOrientation() { return orientation; }
	Vector3 getUp() { return up; }
	Vector3 getForward() { return forward; }
	Vector3 getRight() { return right; }




	void vectorsUpdate();
	void moveForward(float);
	void moveBackward(float);
	void moveLeft(float);
	void moveRight(float);
	void moveUp(float);
	void moveDown(float);
	void changeOrientation(float, float, float, int, int);


private:

	Vector3 forward;
	Vector3 up;
	Vector3 right;
	Vector3 position;
	Vector3 orientation;

};

