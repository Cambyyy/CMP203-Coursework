#include "Scene.h"

// Scene constructor, initilises OpenGL
// You should add further variables to need initilised.
Scene::Scene(Input *in)
{
	// Store pointer for input class
	input = in;
	initialiseOpenGL();

	// Other OpenGL / render setting should be applied here.
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	// Initialise scene variables
	Camera camera;

	Vector3 earthPosition(0, 0, -1.5)

	myModel.load("models/spaceship.obj", "gfx/checked.png");

	floorTexture = SOIL_load_OGL_texture("gfx/seamlessgrass.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	boxTexture = SOIL_load_OGL_texture("gfx/crate.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	skyboxTop = SOIL_load_OGL_texture("gfx/skyboxtop.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	skyboxLeft = SOIL_load_OGL_texture("gfx/skyboxleft.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	skyboxRight = SOIL_load_OGL_texture("gfx/skyboxright.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	skyboxFront = SOIL_load_OGL_texture("gfx/skyboxfront.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	skyboxBottom = SOIL_load_OGL_texture("gfx/skyboxbot.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	skyboxBack = SOIL_load_OGL_texture("gfx/skyboxback.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	
}

void Scene::handleInput(float dt)
{
	// Handle user input

	// Camera inputs
	// camera movement
	
	if (input->isKeyDown('w')) {
		camera.moveForward(dt);
	}
	
	if (input->isKeyDown('s')) {
		camera.moveBackward(dt);
	}
	
	if (input->isKeyDown('a')) {
		camera.moveLeft(dt);
	}
	if (input->isKeyDown('d')) {
		camera.moveRight(dt);
	}

	if (input->isKeyDown('q')) {
		camera.moveUp(dt);
	}
	if (input->isKeyDown('e')) {
		camera.moveDown(dt);
	}

	// wireframe toggle
	if (input->isKeyDown('v')) {
		if (!wireframe) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			wireframe = true;
			input->setKeyUp('v');
		}
		else if (wireframe) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			wireframe = false;
			input->setKeyUp('v');
		}
	}
	
	// camera rotation
	if (width/2 < input->getMouseX() > width/2 || height/2 < input->getMouseY() < height/2) {
		camera.changeOrientation(dt, input->getMouseX(), input->getMouseY(), width, height);
		glutWarpPointer(width/2, height/2);

	}
	
}

void Scene::update(float dt)
{
	// update scene related variables.

	// Calculate FPS for output
	calculateFPS();
}

void Scene::render() {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(camera.getPosition().x, camera.getPosition().y, camera.getPosition().z, camera.getPosition().x + camera.getForward().x, camera.getPosition().y + camera.getForward().y, camera.getPosition().z + camera.getForward().z, camera.getUp().x, camera.getUp().y, camera.getUp().z);

	// lighting
	glEnable(GL_LIGHTING);
	GLfloat Light_Ambient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat Light_Diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat Light_Position[] = { 3.0f, 2.0f, 3.0f, 1 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, Light_Ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Light_Diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, Light_Position);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.2);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0);
	glEnable(GL_LIGHT0);

	GLfloat Light2_Diffuse[] = { 1, 0, 1, 1 };
	GLfloat Light2_Position[] = { -5.0f, 7.0f, 3.0f, 1.0f };
	GLfloat Light2_Ambient[] = { 0.4, 0.4, 0.4, 1.0f };
	GLfloat Spot2_Direction[] = { 0.0f, -1.0f, 0.0f };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Light2_Diffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, Light2_Position);
	glLightfv(GL_LIGHT1, GL_AMBIENT, Light2_Ambient);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, Spot2_Direction);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 40.0f);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 75.0f);
	glEnable(GL_LIGHT1);


	// Render geometry/scene here -------------------------------------
	
	
	// 
	glBindTexture(GL_TEXTURE_2D, boxTexture);
	
	glBegin(GL_QUADS);
	// front
	glNormal3f(0, 0, 1);
	glTexCoord2f(0, 1);
	glVertex3f(0, 0, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0, 1, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-1, 1, 0);
	glTexCoord2f(0, 0);
	glVertex3f(-1, 0, 0);
	// right
	glNormal3f(1, 0, 0);
	glTexCoord2f(0, 1);
	glVertex3f(0, 0, 1);
	glTexCoord2f(1, 1);
	glVertex3f(0, 1, 1);
	glTexCoord2f(1, 0);
	glVertex3f(0, 1, 0);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, 0);
	// top
	glNormal3f(0, 1, 0);
	glTexCoord2f(0, 1);
	glVertex3f(0, 1, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0, 1, 1);
	glTexCoord2f(1, 0);
	glVertex3f(-1, 1, 1);
	glTexCoord2f(0, 0);
	glVertex3f(-1, 1, 0);
	// left
	glNormal3f(-1, 0, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-1, 0, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 1, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-1, 1, 1);
	glTexCoord2f(0, 0);
	glVertex3f(-1, 0, 1);
	// bottom
	glNormal3f(0, -1, 0);
	glTexCoord2f(0, 1);
	glVertex3f(0, 0, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0, 0, 1);
	glTexCoord2f(1, 0);
	glVertex3f(-1, 0, 1);
	glTexCoord2f(0, 0);
	glVertex3f(-1, 0, 0);

	// back
	glNormal3f(0, 0, -1);
	glTexCoord2f(0, 1);
	glVertex3f(0, 0, 1);
	glTexCoord2f(1, 1);
	glVertex3f(0, 1, 1);
	glTexCoord2f(1, 0);
	glVertex3f(-1, 1, 1);
	glTexCoord2f(0, 0);
	glVertex3f(-1, 0, 1);

	glEnd(); 
	glBindTexture(GL_TEXTURE_2D, NULL);
	
	// drawing sphere
	glPushMatrix();
		glTranslatef(3, 1, 3);
		glColor3f(1, 0.5, 0);
		glutSolidSphere(0.5, 20, 20);
		glPushMatrix();
			glTranslatef(0, 0, -1.5);
			glColor3f(0, 0, 1);
			glutSolidSphere(0.12, 15, 15);
		glPopMatrix();
	glPopMatrix();
	glColor3f(1, 1, 1);

	// drawing skybox;
	glBindTexture(GL_TEXTURE_2D, skyboxFront);

	glBegin(GL_QUADS);
	// front
	glTexCoord2f(1, 1);
	glVertex3f(100, -100, -100);
	glTexCoord2f(1, 0);
	glVertex3f(100, 100, -100);
	glTexCoord2f(0, 0);
	glVertex3f(-100, 100, -100);
	glTexCoord2f(0, 1);
	glVertex3f(-100, -100, -100);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, NULL);
	glBindTexture(GL_TEXTURE_2D, skyboxRight);
	glBegin(GL_QUADS);
	
	// right
	glTexCoord2f(1, 1);
	glVertex3f(100, -100, 100);
	glTexCoord2f(1, 0);
	glVertex3f(100, 100, 100);
	glTexCoord2f(0, 0);
	glVertex3f(100, 100, -100);
	glTexCoord2f(0, 1);
	glVertex3f(100, -100, -100);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, NULL);
	glBindTexture(GL_TEXTURE_2D, skyboxTop);
	glBegin(GL_QUADS);
	// top
	glTexCoord2f(1, 1);
	glVertex3f(100, 100, -100);
	glTexCoord2f(1, 0);
	glVertex3f(100, 100, 100);
	glTexCoord2f(0, 0);
	glVertex3f(-100, 100, 100);
	glTexCoord2f(0, 1);
	glVertex3f(-100, 100, -100);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, NULL);
	glBindTexture(GL_TEXTURE_2D, skyboxLeft);
	glBegin(GL_QUADS);
	// left
	glTexCoord2f(1, 1);
	glVertex3f(-100, -100, -100);
	glTexCoord2f(1, 0);
	glVertex3f(-100, 100, -100);
	glTexCoord2f(0, 0);
	glVertex3f(-100, 100, 100);
	glTexCoord2f(0, 1);
	glVertex3f(-100, -100, 100);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, NULL);
	glBindTexture(GL_TEXTURE_2D, skyboxBottom);
	glBegin(GL_QUADS);
	// bottom
	glTexCoord2f(1, 1);
	glVertex3f(100, -100, -100);
	glTexCoord2f(1, 0);
	glVertex3f(100, -100, 100);
	glTexCoord2f(0, 0);
	glVertex3f(-100, -100, 100);
	glTexCoord2f(0, 1);
	glVertex3f(-100, -100, -100);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, NULL);
	glBindTexture(GL_TEXTURE_2D, skyboxBack);
	glBegin(GL_QUADS);
	// back
	glTexCoord2f(1, 1);
	glVertex3f(-100, -100, 100);
	glTexCoord2f(1, 0);
	glVertex3f(-100, 100, 100);
	glTexCoord2f(0, 0);
	glVertex3f(100, 100, 100);
	glTexCoord2f(0, 1);
	glVertex3f(100, -100, 100);

	glEnd();
	glBindTexture(GL_TEXTURE_2D, NULL);

	glPushMatrix();
	glColor3f(0.7, 0.5, 0.2);
	glTranslatef(-5, 0.5, 3);
	glRotatef(90, 1, 0, 0);
	glutSolidTorus(0.125, 0.25, 30, 30);
	glPopMatrix();

	
	glPushMatrix();
	glColor3f(0.6, 0.4, 0.4);
	glTranslatef(-6, 0.5, 2);
	glRotatef(65, 1, 0, 0);
	glRotatef(-20, 0 , 1, 0);
	glutSolidTorus(0.125, 0.25, 30, 30);
	glPopMatrix();


	// draws the floor
	float startX = -20;
	float startZ = -20;
	float z = startZ;
	glBindTexture(GL_TEXTURE_2D, floorTexture);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	for (int row = 0; row < 80; row++) {
		z += 0.5;
		float x = startX;
		for (int col = 0; col < 80; col++) {
			x += 0.5;
			glTexCoord2f(0, 1);
			glVertex3f(x, 0, z);
			glTexCoord2f(1, 1);
			glVertex3f(x+0.5, 0, z);
			glTexCoord2f(1, 0);
			glVertex3f(x+0.5, 0, z+0.5);
			glTexCoord2f(0, 0);
			glVertex3f(x, 0, z+0.5);
			
		}
	}
	glEnd();
	glBindTexture(GL_TEXTURE_2D, NULL);


	myModel.render();

	// End render geometry --------------------------------------

	// Render text, should be last object rendered.
	renderTextOutput();
	
	// Swap buffers, after all objects are rendered.
	glutSwapBuffers();
}

void Scene::initialiseOpenGL()
{
	//OpenGL settings
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0, 0,0,1);			// Cornflour Blue Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glClearStencil(0);									// Clear stencil buffer
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
}

// Handles the resize of the window. If the window changes size the perspective matrix requires re-calculation to match new window size.
void Scene::resize(int w, int h) 
{
	width = w;
	height = h;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = (float)w / (float)h;
	fov = 45.0f;
	nearPlane = 0.1f;
	farPlane = 200.0f;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(fov, ratio, nearPlane, farPlane);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

// Calculates FPS
void Scene::calculateFPS()
{
	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > 1000) {
		sprintf_s(fps, "FPS: %4.2f", frame*1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}
}

// Compiles standard output text including FPS and current mouse position.
void Scene::renderTextOutput()
{
	// Render current mouse position and frames per second.
	sprintf_s(mouseText, "Mouse: %i, %i", input->getMouseX(), input->getMouseY());
	displayText(-1.f, 0.96f, 1.f, 0.f, 0.f, mouseText);
	displayText(-1.f, 0.90f, 1.f, 0.f, 0.f, fps);
}

// Renders text to screen. Must be called last in render function (before swap buffers)
void Scene::displayText(float x, float y, float r, float g, float b, char* string) {
	// Get Lenth of string
	int j = strlen(string);

	// Swap to 2D rendering
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 5, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Orthographic lookAt (along the z-axis).
	gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Set text colour and position.
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	// Render text.
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
	}
	// Reset colour to white.
	glColor3f(1.f, 1.f, 1.f);

	// Swap back to 3D rendering.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, ((float)width/(float)height), nearPlane, farPlane);
	glMatrixMode(GL_MODELVIEW);
}
