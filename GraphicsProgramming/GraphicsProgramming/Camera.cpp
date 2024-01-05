#include "Camera.h"


Camera::Camera() {
	position = Vector3(0.0f, 0.5f, -2.0f);
	orientation = Vector3(180.0f, -89.0f, 0.0f);
	// Calculate up right and forward
	this->vectorsUpdate();
	up = Vector3(0.0f, 1.0f, 0.0f);
	forward = Vector3(0.0f, 0.0f, 1.0f);
	right = Vector3(1.0f, 0.0f, 0.0f);
}

Camera::Camera(Vector3 pos, Vector3 rotation) {
	position = pos;
	orientation = rotation; // Change later to correct calculation

	// Calculate Up and right
	this->vectorsUpdate();
}

Camera::~Camera() {

}

void Camera::vectorsUpdate() {

	float cosR, cosP, cosY;
	float sinR, sinP, sinY;


	// Getting data for Forward and Up Vectors Calculations
	cosY = cosf(orientation.x*3.1415/180);
	cosP = cosf(orientation.y*3.1415/180);
	cosR = cosf(orientation.z*3.1415/180);
	sinY = sinf(orientation.x*3.1415/180);
	sinP = sinf(orientation.y*3.1415/180);
	sinR = sinf(orientation.z*3.1415/180);

	//Forward Vector Calculations
	forward.x = sinY * cosP;
	forward.y = sinP;
	forward.z = cosP * -cosY;
	// For lookAt add forward to the position

	// Up Vector Calculations
	up.x = -cosY * sinR - sinY * sinP * cosR;
	up.y = cosP * cosR;
	up.z = -sinY * sinR - sinP * cosR * -cosY;

	// Right vector will have to be figured out at a later point, apparently it is a cross between the Up and Forward vectors (p-l) (u-p)

	right = forward.cross(up);

}


void Camera::moveForward(float dt) {
	position.add(forward, dt);
}

void Camera::moveBackward(float dt) {
	position.subtract(forward, dt);
}

void Camera::moveLeft(float dt) {
	position.subtract(right, dt);
}

void Camera::moveRight(float dt) {
	position.add(right, dt);
}

void Camera::moveUp(float dt) {
	position.y += 2 * dt;
}

void Camera::moveDown(float dt) {
	position.y -= 2 * dt;
}

void Camera::changeOrientation(float dt, float mx, float my, int w, int h) {

	orientation.x += ((mx - w/2) * 4) * dt;
	orientation.y += ((h/2 - my) * 4) * dt;
	if (orientation.y > 89) {
		orientation.y = 89;
	}
	else if (orientation.y < -89) {
		orientation.y = -89;
	}
	this->vectorsUpdate();
}

