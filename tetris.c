/*
 * tetris.c
 *
 *  Created on: 2017. 1. 21.
 *      Author: USER
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <sys/unistd.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define ROW 50
#define COL 50
#define SPEED 100

// Definition of windows half size
GLfloat windowHalfHeight = ROW/2;
GLfloat windowHalfWidth = COL/2;

// Rectangle vertex
float x = 0.0; // up-left
float resize = 5; // size of rectangle
float y = +(COL/2)-5; // up-left

// Map to render element of Tetris
bool element[ROW][COL];

// Control for change management of window size
void changeSize(GLsizei w, GLsizei h)
{
	GLfloat aspectRatio;

	if(h == 0)
		h = 1;

	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	aspectRatio = (GLfloat)w / (GLfloat)h;

	if(w <= h){
		windowHalfHeight = (ROW/2) / aspectRatio;
		windowHalfWidth = (COL/2);
		glOrtho (-25.0, 25.0, -windowHalfHeight, windowHalfHeight, 1.0, -1.0);
	}else{
		windowHalfWidth = (COL/2) * aspectRatio;
		windowHalfHeight = ROW/2;
		glOrtho (-windowHalfWidth, windowHalfWidth,-25.0, 25.0, 1.0, -1.0);
	}

	glMatrixMode(GL_MODELVIEW);
	//do nothing...
	glLoadIdentity();
}

//key command receiver
void specialKey(int key, int xi, int yi)
{
	switch(key)
	    {
	        case GLUT_KEY_LEFT :
	            if(x > - windowHalfWidth)
	            {
	        		x = x - 5;
	            }
	            break;

	        case GLUT_KEY_RIGHT :
	        	if((x + resize) < windowHalfWidth)
	        	{
	        		x = x + 5;
	    		}
	        	break;

	        case GLUT_KEY_UP :
	            y = y + 5;
	        	break;

	        case GLUT_KEY_DOWN :
				y = y - 5;
	        	break;
	    }

	glutPostRedisplay();
}

//timer
void animationTimer(int speed){

	if(y>-windowHalfHeight){
		y = y - (float)speed;
	}else{
		x = 0;
		y = +(COL/2)-resize;
	}

	glutPostRedisplay();
	glutTimerFunc(SPEED, animationTimer, 1);
}

void renderScene(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	glRectf(x,y,x+resize,y+resize);

	//Check whether block is stacked
	for(int i = 0; i<COL; i++){
		for(int j = 0; j<ROW; j++){
			if(element[i][j] == true){
				glRectf((i-windowHalfWidth),(j-windowHalfHeight),(i-windowHalfWidth)+resize,(j-windowHalfHeight)+resize);
			}
		}
	}

	//Draw check whether to draw
	if(y==(-windowHalfHeight+1)){
		element[(int)(x+windowHalfWidth)][0] = true;
	}

	glutSwapBuffers();

}

void setupRC(void){

	//set red
	glClearColor(0.0f, 0.0f, 0.0f, 0.0); // Fill Scene.
}

int main(int argc, char**argv){

	glutInit(&argc,argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("Tetris");
	glutDisplayFunc(renderScene);
	glutTimerFunc(SPEED, animationTimer, 1);
	glutSpecialFunc(specialKey);
	glutReshapeFunc(changeSize);
	setupRC();

	glutMainLoop();
	return 0;

}

