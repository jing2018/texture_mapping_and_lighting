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

//
float angle=0;
float transx=0;
float transy=0;
float transz=0;
float scalex=1.0;

float eyex=6;
float eyey=2;
float eyez=6;

float centerx=0;
float centery=0;
float centerz=0;

float redlight=0.9f;


// frame index
int g_frameIndex = 0;

// model
Model g_model;
Model g_model2;
/*
// XZ position of the camera
float x = 0.0f, z = 7.0f;
float y = 3.0f;
*/

string filename = "/Users/jingsi/Desktop/Lab3/resources/brik.bmp";

GLfloat vertices[][3] = { 
	{ -8.0, -8.0, -8.0 },{ 8.0, -8.0, -8.0 },{ 8.0, 8.0, -8.0 },{ -8.0, 8.0, -8.0 },
	{ -8.0, -8.0, 8.0 },{ 8.0, -8.0, 8.0 },{ 8.0, 8.0, 8.0}, { -8.0, 8.0, 8.0 }
};

//================================
// init
//================================
void init(void) {
	// init something before main loop...
	//define a point light source
	// load model

	glEnable(GL_TEXTURE_2D);
    
    /*
    //define a point light source
    //light source attributes
    GLfloat Ambient	[] = { 0.4f, 0.4f, 0.4f, 1.0f };
    
    GLfloat CeilingDiffuse	[] = { 0.4f, 0.4f, 0.3f, 1.0f };
    GLfloat LightSpecular	[] = { 0.9f, 0.9f, 0.8f, 1.0f };
    GLfloat LightPosition	[] = { 0.0f, 8.0f, 0.0f, 1.0f };
    
    GLfloat CeilingShininess       [] = { 30.0 };
    GLfloat lightcolor      [] = { 1.0, 1.0, 1.0, 1.0 };
    
    glShadeModel(GL_SMOOTH);
    
    glLightfv(GL_LIGHT0, GL_AMBIENT 	, Ambient );
    glLightfv(GL_LIGHT0, GL_DIFFUSE 	, CeilingDiffuse );
    //light color is white
    glLightfv(GL_LIGHT0, GL_SPECULAR	, lightcolor);
    glLightfv(GL_LIGHT0, GL_SHININESS   , CeilingShininess);
    glLightfv(GL_LIGHT0, GL_POSITION	, LightPosition);
    
    //wall reflction attributes
    GLfloat WallDiffuse	[] = { 0.4f, 0.3f, 0.3f, 1.0f };
    GLfloat WallSpecular	[] = { 0.9f, 0.6f, 0.6f, 1.0f };
    GLfloat WallShininess[] = { 50.0 };
	
	glClearColor(0.0, 0.0, 0.0, 0.0);
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, Ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, WallSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, WallShininess);
	
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Ambient);
*/
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
    // load model
    g_model.LoadModel( "/Users/jingsi/Desktop/Lab2/Data/cow.d" );
    g_model2.LoadModel( "/Users/jingsi/Desktop/Lab2/Data/duck.d" );


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
   
    
	int width, height;

	unsigned char * data;

	FILE * file;

	file = fopen(filename, "rb");

	if (file == NULL) { cout << "Wrong!!"; return 0; }
	width = 128;
	height = 128;
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
	//control how texture is applied
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

	//filtering mode
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
    
    //define a point light source
    //light source attributes
    GLfloat Ambient	[] = { 0.4f, 0.4f, 0.4f, 1.0f };
    
    GLfloat CeilingDiffuse	[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    GLfloat LightSpecular	[] = { redlight, 0.9f, 0.8f, 1.0f };
    GLfloat LightPosition	[] = { 0.0f, 8.0f, 0.0f, 1.0f };
    
    GLfloat CeilingShininess       [] = { 30.0 };
    GLfloat lightcolor      [] = { 1.0, 1.0, 1.0, 1.0 };
    
    
    //wall reflction attributes
    GLfloat WallDiffuse	[] = { 0.7f, 0.7f, 0.6f, 1.0f };
    GLfloat WallSpecular	[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    GLfloat WallShininess[] = { 50.0 };
    
    
    glShadeModel(GL_SMOOTH);
    
    glLightfv(GL_LIGHT0, GL_AMBIENT 	, Ambient );
    glLightfv(GL_LIGHT0, GL_DIFFUSE 	, CeilingDiffuse );
    //light color is white
    glLightfv(GL_LIGHT0, GL_SPECULAR	, lightcolor);
    glLightfv(GL_LIGHT0, GL_SHININESS   , CeilingShininess);
    glLightfv(GL_LIGHT0, GL_POSITION	, LightPosition);
    

    glClearColor(0.0, 0.0, 0.0, 0.0);
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, Ambient);
    glMaterialfv(GL_FRONT, GL_SPECULAR, WallSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, WallShininess);
    
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Ambient);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    



	// clear color and depth buffer
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// enable depth test
	glEnable(GL_DEPTH_TEST);

	// modelview matrix <------------------------------------------
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    
    //change the eyes position using keys "w","s","a","d","q","e"
    //change the reference point using keys "1","2","3","4","5","6"
    gluLookAt(
              eyex, eyey, eyez, // eye
              centerx, centery, centerz, // center
              0, 1, 0  // up
              );

    glTranslatef(0.0, 0.0, 0.0);
    glTranslatef(transx, transy, transz);
    glRotatef(angle, 1.0, 0.0, 0.0);
    glScalef(scalex, scalex, scalex);

    

	// draw wall
	filename =  "/Users/jingsi/Desktop/Lab3/resources/brik.bmp";
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, Ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, WallDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, WallSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, WallShininess);
	polygon(0, 1, 2, 3);
	glPopMatrix();
    
    // draw wall2
    filename =  "/Users/jingsi/Desktop/Lab3/resources/brik.bmp";
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT, Ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, WallDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, WallSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, WallShininess);
    polygon(4, 5, 6, 7);
    glPopMatrix();
    
    // draw wall3
    filename =  "/Users/jingsi/Desktop/Lab3/resources/brik.bmp";
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT, Ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, WallDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, WallSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, WallShininess);
    polygon(0, 3, 7, 4);
    glPopMatrix();
    // draw wall3
    filename =  "/Users/jingsi/Desktop/Lab3/resources/brik.bmp";
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT, Ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, WallDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, WallSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, WallShininess);
    polygon(1, 2, 6, 5);
    glPopMatrix();
    

	GLfloat mat_emission[] = { 0.3f, 0.3f, 0.2f, 0.0f };

	// draw floor
	filename =  "/Users/jingsi/Desktop/Lab3/resources/masai.bmp";
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, Ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, CeilingDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, LightSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, CeilingShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	polygon(0, 1, 5, 4);
	glPopMatrix();
    
    // draw top ceiling
    filename =  "/Users/jingsi/Desktop/Lab3/resources/flo.bmp";
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT, Ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, CeilingDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, LightSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, CeilingShininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    polygon(3, 2, 6, 7);
    glPopMatrix();
    
    /*//draw the light
    glPushMatrix();
    glLineWidth( 2 );
    glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
    glTranslatef(0.0, 0.0, 0.0);

    g_model2.DrawEdges();
    glPopMatrix();
    */
    
    // draw the first model
    //push the model
    glPushMatrix();
    
    glLineWidth( 1 );
    glTranslatef( 0.0f, -2.0f, 0.0f );
    glScalef(2.0,2.0,2.0);
    glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
    g_model.DrawTriangleNormal();
    //pop the model, actions after will not inlunence it
    glPopMatrix();
    
    // draw the second model
    //push the model
    glPushMatrix();
    
    glLineWidth( 1 );
    glTranslatef( 6.0f, -6.0f, 0.0f );
    glScalef(2.0,2.0,2.0);
    glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
    g_model.DrawTriangleNormal();
    //pop the model, actions after will not inlunence it
    glPopMatrix();

    // draw the third model
    //push the model
    glPushMatrix();
    
    glLineWidth( 1 );
    glTranslatef( 1.0f, 0.0f, 5.0f );
    glScalef(4.0,4.0,4.0);
    glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
    g_model.DrawTriangleNormal();
    //pop the model, actions after will not inlunence it
    glPopMatrix();

    
    
    
	// swap back and front buffers
	glutSwapBuffers();
}

//================================
// keyboard input
//================================
void key_press(unsigned char key, int xx, int yy) {
	switch (key) {
            //control the eyes position
        case 'w':
            eyey+=0.1;
            break;
        case 'a':
            eyex+=0.1;
            break;
        case 's':
            eyey-=0.1;
            break;
        case 'd':
            eyex-=0.1;
            break;
        case 'q':
            eyez+=0.1;
            break;
        case 'e':
            eyez-=0.1;
            break;
            //to rotate the model/rotate back
        case 'z':
            angle+=10;
            break;
        case 'x':
            angle-=10;
            break;
            //change the reference point
        case '1':
            centerx+=0.3;
            break;
        case '2':
            centerx-=0.3;
            break;
        case '3':
            centery+=0.3;
            break;
        case '4':
            centery-=0.3;
            break;
        case '5':
            centerz+=0.3;
            break;
        case '6':
            centerz-=0.3;
            break;
            
            //scale the model
        case 'r':
            scalex*=1.1;//////////
            break;
        case 'f':
            scalex*=0.9;
        case 'o':
            redlight+=0.2;//////////
            break;
        case 'p':
            redlight-=0.2;
            
            break;
            
        default:
            break;
	}
    //the timer is not needed
    //instead,when press a key, refesh the display,
    //so that the change would show
    glutPostRedisplay();

}

void special_key(int key, int xx, int yy) {
	switch (key) {
        case GLUT_KEY_RIGHT: //right arrow
            transy-=0.1;
            break;
        case GLUT_KEY_LEFT: //left arrow
            transy+=0.1;
            break;
        case GLUT_KEY_UP:
            transx+=0.1;////////
            break;
        case GLUT_KEY_DOWN:
            transx-=0.1;
            break;
        default:
            break;
    }
    //the timer is not needed
    //instead,when press a key, refesh the display,
    //so that the change would show
    glutPostRedisplay();
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
