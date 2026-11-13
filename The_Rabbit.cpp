// The Rabbit - Computer Graphics Story
// --- USER MANUAL ---
// 1- Click the Left Mouse Button to move to the next scene.
// 2- Use Left and Right arrow keys to move the rabbit in Scene 2 and Scene 3.
// 4- Press 'q' or 'ESC' to exit the program.
//////////////////
//  Headers  //
//////////////////
#define _CRT_SECURE_NO_WARNINGS
#ifdef APPLE
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>    
#else
#include <GL/glew.h>
#include <GL/freeglut.h> 
#endif
#include <stdlib.h>
#include <iostream>
using namespace std;
/////////////////////////
// Global variables //
/////////////////////////
int WIN_W = 600, WIN_H = 600;
GLuint texGarden;
GLuint texHome;
char pathGarden[] = "./garden_bg.bmp";
char pathHome[] = "./home_bg.bmp";
// --- Scene Management ---
int currentScene = 1;
// Scene 1
float s1_bunnyX = -0.75f;
bool  s1_arrived = false;
// Scene 2 
float s2_bunnyX = -0.7f;
float s2_bunnyY = -0.35f;
// Scene 3 
float s3_bunnyX = -0.7f;
float s3_bunnyY = -0.35f;
// Scene 4 
float s4_bunnyX = -0.7f;
float s4_bunnyScale = 1.0f;
bool  s4_arrived = false;
// Scene 5 
float s5_bunnyAngle = 0.0f;
float s5_angleDir = 1.0f;
//-------------------------------------
// --- Load BMP Texture ---
GLuint LoadTexture(const char* filename, int width, int height)
{
	GLuint texture;
	unsigned char* data;
	FILE* file;
	file = fopen(filename, "rb");
	if (file == NULL)
	{
		cout << "Unable to open the image file" << endl << "Program will exit :(" << endl;
		exit(0);
		return 0;
	}
	data = (unsigned char*)malloc(width * height * 3);
	fseek(file, 54, SEEK_SET);
	fread(data, width * height * 3, 1, file);
	fclose(file);
	for (int i = 0; i < width * height; ++i)
	{
		int index = i * 3;
		unsigned char B, R;
		B = data[index];
		R = data[index + 2];
		data[index] = R;
		data[index + 2] = B;
	}
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	free(data);
	if (glGetError() != GL_NO_ERROR)
		printf("GLError in genTexture()\n");
	return texture;
}
/////////////////////
// Texture Functions 
/////////////////////
void drawRabbit() {
	// Body
	glColor3f(0.95f, 0.92f, 0.88f);
	glBegin(GL_POLYGON);
	glVertex2f(-0.09f, -0.12f); glVertex2f(0.09f, -0.12f);
	glVertex2f(0.11f, -0.06f);  glVertex2f(0.11f, 0.06f);
	glVertex2f(0.09f, 0.12f);   glVertex2f(-0.09f, 0.12f);
	glVertex2f(-0.11f, 0.06f);  glVertex2f(-0.11f, -0.06f);
	glEnd();
	// Head
	glBegin(GL_POLYGON);
	glVertex2f(-0.07f, 0.08f);  glVertex2f(0.07f, 0.08f);
	glVertex2f(0.10f, 0.14f);   glVertex2f(0.10f, 0.21f);
	glVertex2f(0.07f, 0.27f);   glVertex2f(-0.07f, 0.27f);
	glVertex2f(-0.10f, 0.21f);  glVertex2f(-0.10f, 0.14f);
	glEnd();
	// Left Ear 
	glColor3f(0.95f, 0.92f, 0.88f);
	glBegin(GL_TRIANGLES);
	glVertex2f(-0.07f, 0.26f); glVertex2f(-0.04f, 0.36f); glVertex2f(-0.01f, 0.26f);
	glEnd();

	// Left Inner Ear
	glColor3f(1.0f, 0.75f, 0.8f);
	glBegin(GL_TRIANGLES);
	glVertex2f(-0.06f, 0.27f); glVertex2f(-0.04f, 0.33f); glVertex2f(-0.02f, 0.27f);
	glEnd();
	// Right Ear 
	glColor3f(0.95f, 0.92f, 0.88f);
	glBegin(GL_TRIANGLES);
	glVertex2f(0.01f, 0.26f); glVertex2f(0.04f, 0.36f); glVertex2f(0.07f, 0.26f);
	glEnd();
	// Right Inner Ear
	glColor3f(1.0f, 0.75f, 0.8f);
	glBegin(GL_TRIANGLES);
	glVertex2f(0.02f, 0.27f); glVertex2f(0.04f, 0.33f); glVertex2f(0.06f, 0.27f);
	glEnd();
	// Eyes
	glColor3f(0.2f, 0.1f, 0.1f);
	glPointSize(5.0f);
	glBegin(GL_POINTS);
	glVertex2f(-0.04f, 0.195f); glVertex2f(0.04f, 0.195f);
	glEnd();
	// Nose
	glColor3f(1.0f, 0.6f, 0.7f);
	glBegin(GL_POLYGON);
	glVertex2f(-0.015f, 0.16f); glVertex2f(0.015f, 0.16f);
	glVertex2f(0.0f, 0.18f);
	glEnd();
	// Mouth
	glColor3f(0.5f, 0.3f, 0.3f);
	glBegin(GL_LINE_STRIP);
	glVertex2f(-0.025f, 0.155f); glVertex2f(0.0f, 0.145f); glVertex2f(0.025f, 0.155f);
	glEnd();
	// Left Cheek
	glColor3f(1.0f, 0.75f, 0.8f);
	glBegin(GL_POLYGON);
	glVertex2f(-0.09f, 0.155f); glVertex2f(-0.05f, 0.155f);
	glVertex2f(-0.05f, 0.180f); glVertex2f(-0.09f, 0.180f);
	glEnd();
	// Right Cheek
	glColor3f(1.0f, 0.75f, 0.8f);
	glBegin(GL_POLYGON);
	glVertex2f(0.05f, 0.155f); glVertex2f(0.09f, 0.155f);
	glVertex2f(0.09f, 0.180f); glVertex2f(0.05f, 0.180f);
	glEnd();
	// Left Leg
	glColor3f(0.95f, 0.92f, 0.88f);
	glBegin(GL_POLYGON);
	glVertex2f(-0.075f, -0.12f);
	glVertex2f(-0.025f, -0.12f);
	glVertex2f(-0.018f, -0.13f);
	glVertex2f(-0.028f, -0.138f);
	glVertex2f(-0.072f, -0.138f);
	glVertex2f(-0.082f, -0.13f);
	glEnd();
	// Right Leg 
	glBegin(GL_POLYGON);
	glVertex2f(0.025f, -0.12f);
	glVertex2f(0.075f, -0.12f);
	glVertex2f(0.082f, -0.13f);
	glVertex2f(0.072f, -0.138f);
	glVertex2f(0.028f, -0.138f);
	glVertex2f(0.018f, -0.13f);
	glEnd();
}
//drawSky
void drawSky2() {
	glBegin(GL_QUADS);
	glColor3f(0.75f, 0.88f, 0.94f); glVertex2f(-1.0f, 1.0f);
	glVertex2f(1.0f, 1.0f);
	glColor3f(0.65f, 0.80f, 0.88f);
	glVertex2f(1.0f, -0.45f);
	glVertex2f(-1.0f, -0.45f);
	glEnd();
}
void drawSky3() {
	glBegin(GL_QUADS);
	glColor3f(0.05f, 0.1f, 0.25f);  glVertex2f(-1.0f, 1.0f);
	glColor3f(0.05f, 0.1f, 0.25f);  glVertex2f(1.0f, 1.0f);
	glColor3f(1.0f, 0.8f, 0.4f);    glVertex2f(1.0f, -0.45f);
	glColor3f(0.2f, 0.15f, 0.3f);   glVertex2f(-1.0f, -0.45f);
	glEnd();
}
//drawGround
void drawGround() {
	glBegin(GL_QUADS);
	glColor3f(0.1f, 0.3f, 0.1f); glVertex2f(-1.0f, -0.45f);
	glVertex2f(1.0f, -0.45f);
	glColor3f(0.08f, 0.25f, 0.08f);  glVertex2f(1.0f, -1.0f);
	glVertex2f(-1.0f, -1.0f);
	glEnd();
}
//drawSun
void drawSun() {
	glColor3f(0.9f, 1.0f, 0.9f);
	glBegin(GL_POLYGON);
	glVertex2f(0.77f, 0.82f);
	glVertex2f(0.80f, 0.81f);
	glVertex2f(0.82f, 0.78f);
	glVertex2f(0.83f, 0.75f);
	glVertex2f(0.82f, 0.72f);
	glVertex2f(0.80f, 0.69f);
	glVertex2f(0.77f, 0.68f);
	glVertex2f(0.74f, 0.69f);
	glVertex2f(0.72f, 0.72f);
	glVertex2f(0.71f, 0.75f);
	glVertex2f(0.72f, 0.78f);
	glVertex2f(0.74f, 0.81f);
	glEnd();
}
// drawStar
void drawStar() {
	glColor3f(1.0f, 1.0f, 1.0f);
	glPointSize(1.0f);
	glBegin(GL_POINTS);
	glVertex2f(-0.6f, 0.8f); glVertex2f(-0.3f, 0.65f);
	glVertex2f(0.0f, 0.75f); glVertex2f(0.4f, 0.8f);
	glVertex2f(-0.8f, 0.55f); glVertex2f(0.2f, 0.5f);
	glEnd();
}
//drawTree
void drawTree(float x) {

	glColor3f(0.36f, 0.2f, 0.09f);
	glBegin(GL_QUADS);
	glVertex2f(x - 0.03f, -0.45f); glVertex2f(x + 0.03f, -0.45f);
	glVertex2f(x + 0.03f, -0.2f);  glVertex2f(x - 0.03f, -0.2f);
	glEnd();
	glColor3f(0.1f, 0.3f, 0.1f);
	glBegin(GL_TRIANGLES);
	glVertex2f(x, 0.15f);
	glVertex2f(x - 0.18f, -0.22f);
	glVertex2f(x + 0.18f, -0.22f);
	glEnd();
}
//drawFlower
void drawFlower(float x, float y) {

	glLineWidth(2.0f);
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.3f, 0.0f);
	glVertex2f(x, y); glVertex2f(x, y - 0.08f);
	glEnd();
	glColor3f(1.0f, 0.75f, 0.8f);
	glBegin(GL_TRIANGLES);
	glVertex2f(x, y); glVertex2f(x - 0.02f, y + 0.05f); glVertex2f(x + 0.02f, y + 0.05f);
	glVertex2f(x, y); glVertex2f(x + 0.05f, y + 0.02f); glVertex2f(x + 0.05f, y - 0.02f);
	glVertex2f(x, y); glVertex2f(x - 0.05f, y + 0.02f); glVertex2f(x - 0.05f, y - 0.02f);
	glVertex2f(x, y); glVertex2f(x - 0.02f, y - 0.05f); glVertex2f(x + 0.02f, y - 0.05f);
	glEnd();
	glPointSize(6.0f);
	glBegin(GL_POINTS);
	glColor3f(1.0f, 0.8f, 0.0f);
	glVertex2f(x, y);
	glEnd();
}
/////////////////////
// Texture Functions 
/////////////////////
void drawBackground(GLuint myTex) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, myTex);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.1f, -1.1f);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(1.1f, -1.1f);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(1.1f, 1.1f);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.1f, 1.1f);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}
/////////////////////
//Scene Functions 
/////////////////////
void scene1_draw() {
	drawBackground(texGarden);
	if (!s1_arrived) {
		s1_bunnyX += 0.002f;
	}
	if (s1_bunnyX >= 0.0f) s1_arrived = true;
	glPushMatrix();
	glTranslatef(s1_bunnyX, -0.25f, 0);
	glScalef(1.0f, 1.2f, 1);
	drawRabbit();
	glPopMatrix();
}
void scene2_draw() {
	drawSky2();
	drawGround();
	drawSun();
	drawTree(-0.75f);
	drawTree(0.0f);
	drawTree(0.6f);
	drawFlower(-0.8f, -0.6f);
	drawFlower(-0.4f, -0.75f);
	drawFlower(0.1f, -0.65f);
	drawFlower(0.5f, -0.8f);
	drawFlower(0.8f, -0.7f);
	glPushMatrix();
	glTranslatef(s2_bunnyX, s2_bunnyY, 0); // Movement with Arrow Keys
	glScalef(1.0f, 1.2f, 1);
	drawRabbit();
	glPopMatrix();
}
void scene3_draw() {
	drawSky3();
	drawGround();
	drawSun();
	drawStar();
	drawTree(-0.75f);
	drawTree(0.0f);
	drawTree(0.6f);
	drawFlower(-0.8f, -0.6f);
	drawFlower(-0.4f, -0.75f);
	drawFlower(0.1f, -0.65f);
	drawFlower(0.5f, -0.8f);
	drawFlower(0.8f, -0.7f);
	glPushMatrix();
	glTranslatef(s3_bunnyX, s3_bunnyY, 0.0f);
	glScalef(1.0f, 1.2f, 1);
	drawRabbit();
	glPopMatrix();
}
void scene4_draw() {
	drawBackground(texHome);
	if (!s4_arrived) {
		s4_bunnyX += 0.004f;
		s4_bunnyScale -= 0.0008f;
		if (s4_bunnyX >= 0.55f)
			s4_arrived = true;
	}
	glPushMatrix();
	glTranslatef(s4_bunnyX, -0.42f, 0.0f);
	glScalef(s4_bunnyScale, s4_bunnyScale, 1.0f);
	drawRabbit();
	glPopMatrix();
}
void scene5_draw() {
	drawBackground(texHome);
	s5_bunnyAngle += 0.05f * s5_angleDir;
	if (s5_bunnyAngle > 10.0f) s5_angleDir = -1.0f;
	if (s5_bunnyAngle < -10.0f) s5_angleDir = 1.0f;
	glPushMatrix();
	glTranslatef(0.1f, -0.35f, 0.0f);
	glRotatef(s5_bunnyAngle, 0.0f, 0.0f, 1.0f);
	glScalef(1.3f, 1.3f, 1.0f);
	drawRabbit();
	glPopMatrix();
}
/////////////////////
// System Functions 
/////////////////////
void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION); glLoadIdentity(); gluOrtho2D(-1, 1, -1, 1);
	glMatrixMode(GL_MODELVIEW); glLoadIdentity();
	switch (currentScene) {
	case 1: scene1_draw(); break;
	case 2: scene2_draw(); break;
	case 3: scene3_draw(); break;
	case 4: scene4_draw(); break;
	case 5: scene5_draw(); break;
	}
	glutSwapBuffers();
}
void keyboard(unsigned char k, int x, int y) {
	if (k == 'q' || k == 27) exit(0);
	glutPostRedisplay();
}
void special(int key, int x, int y) {
	float step = 0.05f;
	if (currentScene == 2) {
		if (key == GLUT_KEY_LEFT && s2_bunnyX > -0.9f)  s2_bunnyX -= step;
		if (key == GLUT_KEY_RIGHT && s2_bunnyX < 0.9f)  s2_bunnyX += step;
	}
	if (currentScene == 3) {
		if (key == GLUT_KEY_LEFT && s3_bunnyX > -0.9f)  s3_bunnyX -= step;
		if (key == GLUT_KEY_RIGHT && s3_bunnyX < 0.9f)  s3_bunnyX += step;
	}

	glutPostRedisplay();
}
void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (currentScene == 1) currentScene = 2;
		else if (currentScene == 2) currentScene = 3;
		else if (currentScene == 3) currentScene = 4;
		else if (currentScene == 4 && s4_arrived) currentScene = 5;

		glutPostRedisplay();
	}
}
void idle() { glutPostRedisplay(); }
void reshape(int w, int h) { WIN_W = w; WIN_H = h; glViewport(0, 0, w, h); }

void init() {
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	texGarden = LoadTexture(pathGarden, 800, 600);
	texHome = LoadTexture(pathHome, 800, 600);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(WIN_W, WIN_H);
	glutCreateWindow("The Rabbit- CG Project");
	init();
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutSpecialFunc(special);
	glutMainLoop();
	return 0;
}