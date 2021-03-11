// Name:Michelle Dozal
// Quarter, Year: Winter, 2021
// Lab:7
//
// This file is to be modified by the student.
// main.cpp
////////////////////////////////////////////////////////////
#ifndef __APPLE__
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif

#include <vector>
#include <cstdio>
#include <math.h>
#include "vec.h"
#include <iostream>

using namespace std;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

//global vector for control points
vector<vec2> cpoints;

float factorial(int n){
 float f = 1;
if(n < 1) {return f;}
for(int i = 1; i <= n; i++){
	f *= i; }
	
 return f;
}

float combination(int n, int i){
  
	return factorial(n) / factorial(i) / factorial(n-i);
}

float polynomial(int n, int i, float t){
   return combination(n,i)*pow(t,i)*pow(1-t,n-i);
}

void GL_render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
/*
    glBegin(GL_LINES);
    glColor3f(1.0f,0.0f,0.0f);

    // TODO: just for example, you will need to change this.
    glVertex2f(-.5f,-.5f);
    glVertex2f(.5f,-.5f);
    glVertex2f(.5f,.5f);
    glVertex2f(-.5f,.5f);
    glEnd();
    glFlush();
*/
	glBegin(GL_LINE_STRIP);
	glColor3f(1.0f,1.0f,1.0f);
	for(float k = 0.0; k < 1.0; k += 0.01){
			vec2 l;
	for(unsigned i = 0; i < cpoints.size(); i++){
		l += polynomial(cpoints.size()-1,i,k)*cpoints.at(i);}
	
	glVertex2f(l[0],l[1]);
	}
	
     glEnd();
    glFlush();
}

void GL_mouse(int button,int state,int x,int y)
{
    y=WINDOW_HEIGHT-y;
    GLdouble mv_mat[16];
    GLdouble proj_mat[16];
    GLint vp_mat[4];
    glGetDoublev(GL_MODELVIEW_MATRIX,mv_mat);
    glGetDoublev(GL_PROJECTION_MATRIX,proj_mat);
    glGetIntegerv(GL_VIEWPORT,vp_mat);

    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
        double px,py,dummy_z; // we don't care about the z-value but need something to pass in
        gluUnProject(x,y,0,mv_mat,proj_mat,vp_mat,&px,&py,&dummy_z);
        // TODO: the mouse click coordinates are (px,py).
       //push back mouseclick into cpoints
	cpoints.push_back(vec2(px,py)); 
	  glutPostRedisplay();
    }
}

//Initializes OpenGL attributes
void GLInit(int* argc, char** argv)
{
    glutInit(argc, argv);
    //glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    //glMatrixMode(GL_PROJECTION_MATRIX);
    //glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1);
    glutCreateWindow("CS 130 - Michelle Dozal Lab7");
    glutDisplayFunc(GL_render);
    glutMouseFunc(GL_mouse);
}

int main(int argc, char** argv)
{
    GLInit(&argc, argv);
    glutMainLoop();
    return 0;
}
