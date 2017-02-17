/*
 * tetris.c
 *
 *  Created on: 2017. 1. 21.
 *      Author: Yongwoon.jang
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <sys/unistd.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define ROW 14
#define COL 14
#define SPEED 300

// Score
int score;

// Definition of windows half size
GLfloat windowHalfHeight = ROW/2;
GLfloat windowHalfWidth = COL/2;

// Rectangle vertex
float x = 0.0; // up-left
float resize = 1; // size of rectangle
float y = COL/2; // up-left

// Block stype
int type;// Type_A, Type_B, Type_C

// Map to render element of Tetris
bool element[COL][ROW];

// ENUM type definition
// INIT_STOP : If block first faces a bottom.
// STOP : If block faces a bottom.
// PROCEED : If block doesn't face a wall.
enum CHECK{INIT, INIT_END,END,PROCEED,STOP};
enum SHAPE{TYPE_A,TYPE_B,TYPE_C};

// Utility(Logic)
// Check to proceed
int checkProceed(int speed, int direction){
	int result = INIT;
	int diffX;
	int diffY;

	if(direction == GLUT_KEY_DOWN){
		diffX = 0;
		diffY = -speed;

	}else if(direction == GLUT_KEY_LEFT){
		diffX = -speed;
		diffY = 0;

	}else if(direction == GLUT_KEY_RIGHT){
		diffX = +speed;
		diffY = 0;

	}else{
		diffX = 0;
		diffY = 0;
	}

	//Evaluating current algorithm.
	if(type == TYPE_A){ // "--"
		if(y <= - windowHalfHeight){
			result = INIT_END;

		}else if(((x+resize)+diffX) >= windowHalfWidth || (x+diffX) <= -(windowHalfWidth+1)){
			result = STOP;

		}else if(!element[(int)((y+diffY)+windowHalfHeight)][(int)((x+diffX)+windowHalfWidth)]
															 &&!element[(int)((y+diffY)+windowHalfHeight)][(int)(((x+resize)+diffX)+windowHalfWidth)]){
			result = PROCEED;

		}else{
			result = STOP;

		}//end of if

	}else if(type == TYPE_B){
		if(y <= - windowHalfHeight){
					result = INIT_END;

		}else if((x+diffX) >= windowHalfWidth || (x+diffX) <= -(windowHalfWidth+1)){
			result = STOP;

		}else if(!element[(int)((y+diffY)+windowHalfHeight)][(int)((x+diffX)+windowHalfWidth)]
															 &&!element[(int)(((y+resize)+diffY)+windowHalfHeight)][(int)((x+diffX)+windowHalfWidth)]){
			result = PROCEED;

		}else{
			result = STOP;

		}//end of if

	}// end of if

	return result;

}

//check which row is deleted.
void checkRow(){
	for(int i = 0; i < ROW; i++){
		int k = 0;
			for(int j = 0; j < COL; j++){
				if(element[i][j] == true){
					k++;

				}
			}

		//delete 1 line. // from I row.
		if(k == COL){
			for(int l = i; l < ROW; l++){
				if(l == i){
					for(int m = 0; m < COL ; m++){
						element[l][m] = false;
					}

				}

				for(int m = 0; m < COL ; m++){
					element[l][m] = element[l+1][m];
				}

			}//end for

		}//end if
	}//end for
}//end checkRow

// Monitor size and environment setting
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
		glOrtho (-(GLdouble)COL/2, (GLdouble)COL/2, -windowHalfHeight, windowHalfHeight, 1.0, -1.0);
	}else{
		windowHalfWidth = (COL/2) * aspectRatio;
		windowHalfHeight = ROW/2;
		glOrtho (-windowHalfWidth, windowHalfWidth,-(GLdouble)ROW/2, (GLdouble)ROW/2, 1.0, -1.0);
	}

	glMatrixMode(GL_MODELVIEW);
	//do nothing...
	glLoadIdentity();
}

void setupRC(void){

	//set red
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Fill Scene.
}

//controller
//key command receiver
void specialKey(int key, int xi, int yi)
{
	switch(checkProceed(resize, key)){
		case PROCEED:
			switch(key)
				    {
				        case GLUT_KEY_LEFT :
				        	x = x - resize;
							break;

				        case GLUT_KEY_RIGHT :
				        	x = x + resize;
				    		break;

				        case GLUT_KEY_DOWN :
				        	y = y - resize;
				        	break;

				        case GLUT_KEY_UP :
				            break;
				    }
			break;

		default :
			//do nothing.
		break;
	}


	glutPostRedisplay();
}

//Randomly Find Block.
void selectType(){
	int sel = rand()%2;

	if(sel == 0){
		type = TYPE_A;
	}else if(sel == 1){
		type = TYPE_B;
	}

}

//timer ... to proceed and change screen.
void animationTimer(int speed){



	switch(checkProceed(speed, GLUT_KEY_DOWN)){
		case PROCEED:
			//Process to downward
			y = y - (GLfloat)speed;
			break;

		default :
			//End... If block is confronting wall.
			if(type==TYPE_A){
				element[(int)(y+windowHalfHeight)][(int)(x+windowHalfWidth)] = true;
				element[(int)(y+windowHalfHeight)][(int)(x+resize+windowHalfWidth)] = true;
			}else if(type==TYPE_B){
				element[(int)(y+windowHalfHeight)][(int)(x+windowHalfWidth)] = true;
				element[(int)(y+resize+windowHalfHeight)][(int)(x+windowHalfWidth)] = true;
			}
			x = 0;
			y = COL/2;
			selectType();//select block style ;
			break;
	}

	checkRow();
	glutPostRedisplay();
	glutTimerFunc(SPEED, animationTimer, 1);
}

void renderScene(void){

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0,1.0,0.0);

	// Moving object
	if(type == TYPE_A){
		//"けけ" "ぱ" shape
		//draw object using vertex.
		glRectf(x,y,x+resize,y+resize);
		glRectf(x+resize,y,x+2*resize,y+resize);

	}else if(type == TYPE_B){
		//"け"
		//"け" shape
		//draw object using vertext.
		glRectf(x,y,x+resize,y+resize);
		glRectf(x,y+resize,x+resize,y+resize*2);

	}


	// Stacked object
	//Check whether block is stacked
	for(int i = 0; i<ROW; i++){
		for(int j = 0; j<COL; j++){
			if(element[i][j] == true){
				glRectf(j-windowHalfHeight,i-windowHalfWidth,(j-windowHalfHeight)+resize,(i-windowHalfWidth)+resize);
			}
		}
	}

	glutSwapBuffers();
}


int main(int argc, char**argv){

	glutInit(&argc,argv);

	//block initialization
	selectType();//select block style ;

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

