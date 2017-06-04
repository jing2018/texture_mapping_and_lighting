//#include "stdafx.h"

// standard
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <vector>

// glut
#include <GLUT/glut.h>

// source
#include <math/vec3.h>
#include <model.h>

#include <string>
#include <iostream>
#include <fstream>

#define PI 3.1415926
using namespace std;

//================================
// global variables
//================================
// screen size
int g_screenWidth = 0;
int g_screenHeight = 0;

// frame index
int g_frameIndex = 0;

// XZ position of the camera
float x = 0.0f, z = 7.0f;
float y = 3.0f;

float angle = 0.0;

string filename = "/Users/jingsi/Desktop/Lab3/resources/redbrick.bmp";

GLfloat vertices[][3] = { 
	{ -4.0, -1.0, -4.0 },{ 4.0, -1.0, -4.0 },{ 4.0, 4.0, -4.0 },{ -4.0, 4.0, -4.0 },
	{ -4.0, -1.0, 4.0 },{ 4.0, -1.0, 4.0 },{ 4.0, -1.0, -4.0}, { -4.0, -1.0, -4.0 } 
};

//================================
// init
//================================
void init(void) {
	// init something before main loop...
	//define a point light source
	// load model

	glEnable(GL_TEXTURE_2D);

	//define a point light source
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 1.0, 2.0, -2.0, 0.0 };
	GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat lmodel_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

}

//================================
// update
//================================
void update(void) {
	// do something before rendering...
}


GLuint LoadTexture(const char * filename)
{

	GLuint texture;

    NSString *str = [[NSString alloc] initWithCString:fname];
    NSImage *image = [[NSImage alloc] initWithContentsOfFile:str];
    
    
	int width, height;

	unsigned char * data;

	FILE * file;

	file = fopen(filename, "rb");

	if (file == NULL) { cout << "Wrong!!"; return 0; }
	width = 428;
	height = 428;
	data = (unsigned char *)malloc(width * height * 3);

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

	//define texture properties
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	//说明映射方式
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

	//控制滤波
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
	free(data);

	return texture;
}



void polygon(int a, int b, int c, int d)
{
	GLuint texture;
	const char* file = filename.c_str();
	texture = LoadTexture(file);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBegin(GL_POLYGON);
	//v means the parameter is a  array.

	glNormal3fv(vertices[a]);
	glTexCoord2f(0.0, 0.0);
	glVertex3fv(vertices[a]);

	glTranslatef(1.0, 0.0, 0.0);
	glNormal3fv(vertices[b]);
	glTexCoord2f(1.0, 0.0);
	glVertex3fv(vertices[b]);


	glNormal3fv(vertices[c]);
	glTexCoord2f(1.0, 1.0);
	glVertex3fv(vertices[c]);


	glNormal3fv(vertices[d]);
	glTexCoord2f(0.0, 1.0);
	glVertex3fv(vertices[d]);
	glEnd();
}


//================================
// render
//================================
void drawGrids(float height) {
	float step = 0.1f;

	int n = 40;

	float r = step * n;
	GLuint texture;
	const char* file = filename.c_str();
	texture = LoadTexture(file);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_POLYGON);

	for (int i = -n; i <= n; i++) {
		glVertex3f(i * step, height, -r);
		
		glVertex3f(i * step, height, +r);
	}

	for (int i = -n; i <= n; i++) {
		glVertex3f(-r, height, i * step);
		glVertex3f(+r, height, i * step);
	}

	glEnd();
}


void render(void) {

	GLfloat mat_ambient[] = { 0.250000f, 0.250000f, 0.250000f, 1.000000f };
	GLfloat mat_diffuse[] = { 0.400000f, 0.400000f, 0.400000f, 1.000000f };
	GLfloat mat_specular[] = { 0.774597f, 0.774597f, 0.774597f, 1.000000f };
	GLfloat mat_shininess[] = { 76.800003 };




	// clear color and depth buffer
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// enable depth test
	glEnable(GL_DEPTH_TEST);

	// modelview matrix <------------------------------------------
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		x, y, z,
		x+ (0.6*sin(angle)), y-0.1, z-(0.6*cos(angle)),
		0.0f, 1.0f, 0.0f);


	// draw wall
	filename =  "/Users/jingsi/Desktop/Lab3/resources/redbrick.bmp";
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	polygon(0, 1, 2, 3);
	glPopMatrix();

	GLfloat no_mat[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat mat_ambient2[] = { 0.7, 0.7, 0.7, 1.0 };
	GLfloat mat_ambient_color[] = { 0.8f, 0.8f, 0.2f, 1.0f};
	GLfloat mat_diffuse2[] = { 0.1f, 0.5f, 0.8f, 1.0f };
	GLfloat mat_specular2[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat no_shininess[] = { 0.0f };
	GLfloat low_shininess[] = { 5.0f };
	GLfloat high_shininess[] = { 100.0f };
	GLfloat mat_emission[] = { 0.3f, 0.2f, 0.2f, 0.0f };

	// draw floor
	filename =  "/Users/jingsi/Desktop/Lab3/resources/redbrick.bmp";
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	polygon(4, 5, 6, 7);
	glPopMatrix();

	// swap back and front buffers
	glutSwapBuffers();
}

//================================
// keyboard input
//================================
void key_press(unsigned char key, int xx, int yy) {
	switch (key) {
	case 'p':
		break;
	case 'w':
		break;
	case 's':
		break;
	case 'a': angle -= 0.1;
		glutPostRedisplay();
		break;
	case 'd': angle += 0.1;
		glutPostRedisplay();
		break;

	default:
		break;
	}
}

void special_key(int key, int xx, int yy) {
	switch (key) {
	case GLUT_KEY_RIGHT: //right arrow
		x += 0.5;
		glutPostRedisplay();
		break;
	case GLUT_KEY_LEFT: //left arrow
		x -= 0.5;
		glutPostRedisplay();
		break;
	case GLUT_KEY_UP:
		z -= 0.5;
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		z += 0.5;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

//================================
// reshape : update viewport and projection matrix when the window is resized
//================================
void reshape(int w, int h) {
	// screen size
	g_screenWidth = w;
	g_screenHeight = h;

	// viewport
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	// projection matrix <------------------------------------------
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)w / (float)h, 0.1f, 100.0f);
}


//================================
// timer : triggered every 16ms ( about 60 frames per second )
//================================
void timer(int value) {
	// increase frame index
	g_frameIndex++;

	update();

	// render
	glutPostRedisplay();

	// reset timer
	glutTimerFunc(60, timer, 0);
}



//================================
// main
//================================
int main(int argc, char** argv) {
	// create opengL window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);

	// init
	init();

	// set callback functions
	glutDisplayFunc(render);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key_press);
	glutSpecialFunc(special_key);
	//glutTimerFunc(16, timer, 0);
	// main loop
	glutMainLoop();

	return 0;
}
