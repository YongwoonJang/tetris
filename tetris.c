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

#define ROW 18
#define COL 18
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
typedef struct map{
	bool stacked;
	int type;
} Map;

//
Map element[COL][ROW];

// ENUM type definition
// INIT_STOP : If block first faces a bottom.
// STOP : If block faces a bottom.
// PROCEED : If block doesn't face a wall.
enum CHECK{INIT, INIT_END,END,PROCEED,STOP};
enum SHAPE{TYPE_A,TYPE_B,TYPE_C,TYPE_D,TYPE_E,TYPE_F,TYPE_G,TYPE_H,TYPE_I,TYPE_J,TYPE_K,TYPE_L,TYPE_M,TYPE_N,TYPE_O,TYPE_P,TYPE_Q,TYPE_R,TYPE_S};

// Utility(Logic)
// Check to proceed
int checkToProceed(int speed, int direction){
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
	if(type == TYPE_A){
		// "けけけけ"
		if(y+diffY < - windowHalfHeight){
			result = INIT_END;

		}else if(((x+resize*3)+diffX) >= windowHalfWidth || (x+diffX) <= -(windowHalfWidth+1)){
			result = STOP;

		}else if(!element[(int)((y+diffY)+windowHalfHeight)][(int)((x+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)((y+diffY)+windowHalfHeight)][(int)(((x+resize)+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)((y+diffY)+windowHalfHeight)][(int)(((x+resize*2)+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)((y+diffY)+windowHalfHeight)][(int)(((x+resize*3)+diffX)+windowHalfWidth)].stacked){
			result = PROCEED;

		}else{
			result = STOP;

		}//end of if

	}else if(type == TYPE_B){
		//"け" shape
		//"け" shape
		//"け" shape
		//"け" shape
		if(y+diffY < - windowHalfHeight){
					result = INIT_END;

		}else if((x+diffX) >= windowHalfWidth || (x+diffX) <= -(windowHalfWidth+1)){
			result = STOP;

		}else if(!element[(int)((y+diffY)+windowHalfHeight)][(int)((x+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)(((y+resize)+diffY)+windowHalfHeight)][(int)((x+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)(((y+resize*2)+diffY)+windowHalfHeight)][(int)((x+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)(((y+resize*3)+diffY)+windowHalfHeight)][(int)((x+diffX)+windowHalfWidth)].stacked){
			result = PROCEED;

		}else{
			result = STOP;

		}//end of if

	}else if(type == TYPE_C){

		//"け" shape
		//"け  け" shape
		//"  け" shape
		if((y-resize)+diffY < - windowHalfHeight){
					result = INIT_END;

		}else if(((x+resize)+diffX) >= windowHalfWidth || (x+diffX) <= -(windowHalfWidth+1)){
			result = STOP;

		}else if(!element[(int)((y+diffY)+windowHalfHeight)][(int)((x+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)((y+diffY)+windowHalfHeight)][(int)(((x+resize)+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)(((y+resize)+diffY)+windowHalfHeight)][(int)((x+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)(((y-resize)+diffY)+windowHalfHeight)][(int)(((x+resize)+diffX)+windowHalfWidth)].stacked){
			result = PROCEED;

		}else{
			result = STOP;

		}//end of if

	}else if(type == TYPE_D){

		//" けけ" shape
		//"けけ " shape
		if((y-resize)+diffY < - windowHalfHeight){
					result = INIT_END;

		}else if(((x+resize)+diffX) >= windowHalfWidth || ((x-resize)+diffX) <= -(windowHalfWidth+1)){
			result = STOP;

		}else if(!element[(int)((y+diffY)+windowHalfHeight)][(int)((x+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)((y+diffY)+windowHalfHeight)][(int)(((x+resize)+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)(((y-resize)+diffY)+windowHalfHeight)][(int)((x+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)(((y-resize)+diffY)+windowHalfHeight)][(int)(((x-resize)+diffX)+windowHalfWidth)].stacked){
			result = PROCEED;

		}else{
			result = STOP;

		}//end of if

	}else if(type == TYPE_E){
		//"  け" shape
		//"け  け" shape
		//"け     " shape
		if((y-resize)+diffY < - windowHalfHeight){
					result = INIT_END;

		}else if((x+diffX) >= windowHalfWidth || ((x-resize)+diffX) <= -(windowHalfWidth+1)){
			result = STOP;

		}else if(!element[(int)((y+diffY)+windowHalfHeight)][(int)((x+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)(((y-resize)+diffY)+windowHalfHeight)][(int)(((x-resize)+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)((y+diffY)+windowHalfHeight)][(int)(((x-resize)+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)(((y+resize)+diffY)+windowHalfHeight)][(int)((x+diffX)+windowHalfWidth)].stacked){
			result = PROCEED;

		}else{
			result = STOP;

		}//end of if

	}else if(type == TYPE_F){
		//"け  け" shape
		//"  け け   " shape
		if((y-resize)+diffY < - windowHalfHeight){
					result = INIT_END;

		}else if(((x+resize)+diffX) >= windowHalfWidth || ((x-resize)+diffX) <= -(windowHalfWidth+1)){
			result = STOP;

		}else if(!element[(int)((y+diffY)+windowHalfHeight)][(int)((x+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)((y+diffY)+windowHalfHeight)][(int)(((x-resize)+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)(((y-resize)+diffY)+windowHalfHeight)][(int)((x+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)(((y-resize)+diffY)+windowHalfHeight)][(int)(((x+resize)+diffX)+windowHalfWidth)].stacked){
			result = PROCEED;

		}else{
			result = STOP;

		}//end of if

	}else if(type == TYPE_G){
		//"けけ"
		//"けけ"
		if(y+diffY < - windowHalfHeight){
					result = INIT_END;

		}else if(((x+resize)+diffX) >= windowHalfWidth || (x+diffX) <= -(windowHalfWidth+1)){
			result = STOP;

		}else if(!element[(int)((y+diffY)+windowHalfHeight)][(int)((x+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)((y+diffY)+windowHalfHeight)][(int)(((x+resize)+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)(((y+resize)+diffY)+windowHalfHeight)][(int)((x+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)(((y+resize)+diffY)+windowHalfHeight)][(int)(((x+resize)+diffX)+windowHalfWidth)].stacked){
			result = PROCEED;

		}else{
			result = STOP;

		}//end of if

	}else if(type == TYPE_H){
		//"   け"
		//"けけ け"
		if(y+diffY < - windowHalfHeight){
					result = INIT_END;

		}else if((x+diffX) >= windowHalfWidth || ((x-resize*2)+diffX) <= -(windowHalfWidth+1)){
			result = STOP;

		}else if(!element[(int)((y+diffY)+windowHalfHeight)][(int)((x+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)(((y+resize)+diffY)+windowHalfHeight)][(int)((x+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)((y+diffY)+windowHalfHeight)][(int)(((x-resize)+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)((y+diffY)+windowHalfHeight)][(int)(((x-resize*2)+diffX)+windowHalfWidth)].stacked){
			result = PROCEED;

		}else{
			result = STOP;

		}//end of if

	}else if(type == TYPE_I){
		//"け     "
		//"け     "
		//"け け "
		if(y+diffY < - windowHalfHeight){
					result = INIT_END;

		}else if(((x+resize)+diffX) >= windowHalfWidth || (x+diffX) <= -(windowHalfWidth+1)){
			result = STOP;

		}else if(!element[(int)((y+diffY)+windowHalfHeight)][(int)((x+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)((y+diffY)+windowHalfHeight)][(int)(((x+resize)+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)(((y+resize)+diffY)+windowHalfHeight)][(int)((x+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)(((y+(resize*2))+diffY)+windowHalfHeight)][(int)((x+diffX)+windowHalfWidth)].stacked){
			result = PROCEED;

		}else{
			result = STOP;

		}//end of if

	}else if(type == TYPE_J){
		//"けけけ"
		//"け  "
		if((y-resize)+diffY < - windowHalfHeight){
					result = INIT_END;

		}else if(((x+resize*2)+diffX) >= windowHalfWidth || (x+diffX) <= -(windowHalfWidth+1)){
			result = STOP;

		}else if(!element[(int)((y+diffY)+windowHalfHeight)][(int)((x+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)(((y-resize)+diffY)+windowHalfHeight)][(int)((x+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)((y+diffY)+windowHalfHeight)][(int)(((x+resize)+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)((y+diffY)+windowHalfHeight)][(int)(((x+resize*2)+diffX)+windowHalfWidth)].stacked){
			result = PROCEED;

		}else{
			result = STOP;

		}//end of if

	}else if(type == TYPE_K){
		//"けけ"
		//" け"
		//" け"
		if((y-resize*2)+diffY < - windowHalfHeight){
					result = INIT_END;

		}else if((x+diffX) >= windowHalfWidth || ((x-resize)+diffX) <= -(windowHalfWidth+1)){
			result = STOP;

		}else if(!element[(int)((y+diffY)+windowHalfHeight)][(int)((x+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)((y+diffY)+windowHalfHeight)][(int)(((x-resize)+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)(((y-resize)+diffY)+windowHalfHeight)][(int)((x+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)(((y-resize*2)+diffY)+windowHalfHeight)][(int)((x+diffX)+windowHalfWidth)].stacked){
			result = PROCEED;

		}else{
			result = STOP;

		}//end of if

	}else if(type == TYPE_L){
		//"け"
		//"けけ け"
		if(y+diffY < - windowHalfHeight){
					result = INIT_END;

		}else if(((x+2*resize)+diffX) >= windowHalfWidth || (x+diffX) <= -(windowHalfWidth+1)){
			result = STOP;

		}else if(!element[(int)((y+diffY)+windowHalfHeight)][(int)((x+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)(((y+resize)+diffY)+windowHalfHeight)][(int)((x+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)((y+diffY)+windowHalfHeight)][(int)(((x+resize)+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)((y+diffY)+windowHalfHeight)][(int)(((x+resize*2)+diffX)+windowHalfWidth)].stacked){
			result = PROCEED;

		}else{
			result = STOP;

		}//end of if

	}else if(type == TYPE_M){
		//"け け    "
		//"け     "
		//"け  "
		if((y-resize*2)+diffY < - windowHalfHeight){
					result = INIT_END;

		}else if(((x+resize)+diffX) >= windowHalfWidth || (x+diffX) <= -(windowHalfWidth+1)){
			result = STOP;

		}else if(!element[(int)((y+diffY)+windowHalfHeight)][(int)((x+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)((y+diffY)+windowHalfHeight)][(int)(((x+resize)+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)(((y-resize)+diffY)+windowHalfHeight)][(int)((x+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)(((y-(resize*2))+diffY)+windowHalfHeight)][(int)((x+diffX)+windowHalfWidth)].stacked){
			result = PROCEED;

		}else{
			result = STOP;

		}//end of if

	}else if(type == TYPE_N){
		//"けけ け"
		//"   け  "
		if((y-resize)+diffY < - windowHalfHeight){
					result = INIT_END;

		}else if((x+diffX) >= windowHalfWidth || ((x-resize*2)+diffX) <= -(windowHalfWidth+1)){
			result = STOP;

		}else if(!element[(int)((y+diffY)+windowHalfHeight)][(int)((x+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)(((y-resize)+diffY)+windowHalfHeight)][(int)((x+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)((y+diffY)+windowHalfHeight)][(int)(((x-resize)+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)((y+diffY)+windowHalfHeight)][(int)(((x-resize*2)+diffX)+windowHalfWidth)].stacked){
			result = PROCEED;

		}else{
			result = STOP;

		}//end of if

	}else if(type == TYPE_O){
		//"   け"
		//"   け"
		//" け け"
		if(y+diffY < - windowHalfHeight){
					result = INIT_END;

		}else if((x+diffX) >= windowHalfWidth || ((x-resize)+diffX) <= -(windowHalfWidth+1)){
			result = STOP;

		}else if(!element[(int)((y+diffY)+windowHalfHeight)][(int)((x+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)((y+diffY)+windowHalfHeight)][(int)(((x-resize)+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)(((y+resize)+diffY)+windowHalfHeight)][(int)((x+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)(((y+resize*2)+diffY)+windowHalfHeight)][(int)((x+diffX)+windowHalfWidth)].stacked){
			result = PROCEED;

		}else{
			result = STOP;

		}//end of if

	}else if(type == TYPE_P){
		//" け"
		//"けけ け"
		if(y+diffY < - windowHalfHeight){
					result = INIT_END;

		}else if(((x+resize)+diffX) >= windowHalfWidth || ((x-resize)+diffX) <= -(windowHalfWidth+1)){
			result = STOP;

		}else if(!element[(int)((y+diffY)+windowHalfHeight)][(int)((x+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)(((y+resize)+diffY)+windowHalfHeight)][(int)((x+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)(((y+resize)+diffY)+windowHalfHeight)][(int)(((x-resize)+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)(((y+resize)+diffY)+windowHalfHeight)][(int)(((x+resize)+diffX)+windowHalfWidth)].stacked){
			result = PROCEED;

		}else{
			result = STOP;

		}//end of if

	}else if(type == TYPE_Q){
		//"け  "
		//"け け "
		//"け  "
		if((y-resize)+diffY < - windowHalfHeight){
					result = INIT_END;

		}else if(((x+resize)+diffX) >= windowHalfWidth || (x+diffX) <= -(windowHalfWidth+1)){
			result = STOP;

		}else if(!element[(int)((y+diffY)+windowHalfHeight)][(int)((x+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)(((y+resize)+diffY)+windowHalfHeight)][(int)((x+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)((y+diffY)+windowHalfHeight)][(int)(((x+resize)+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)(((y-resize)+diffY)+windowHalfHeight)][(int)((x+diffX)+windowHalfWidth)].stacked){
			result = PROCEED;

		}else{
			result = STOP;

		}//end of if

	}else if(type == TYPE_R){
		//"けけ け"
		//" け     "
		if((y-resize)+diffY < - windowHalfHeight){
					result = INIT_END;

		}else if(((x+resize)+diffX) >= windowHalfWidth || ((x-resize)+diffX) <= -(windowHalfWidth+1)){
			result = STOP;

		}else if(!element[(int)((y+diffY)+windowHalfHeight)][(int)((x+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)((y+diffY)+windowHalfHeight)][(int)(((x-resize)+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)((y+diffY)+windowHalfHeight)][(int)(((x+resize)+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)(((y-resize)+diffY)+windowHalfHeight)][(int)((x+diffX)+windowHalfWidth)].stacked){
			result = PROCEED;

		}else{
			result = STOP;

		}//end of if

	}else if(type == TYPE_S){
		//"   け"
		//" け け"
		//"   け"
		if((y-resize)+diffY < - windowHalfHeight){
					result = INIT_END;

		}else if((x+diffX) >= windowHalfWidth || ((x-resize)+diffX) <= -(windowHalfWidth+1)){
			result = STOP;

		}else if(!element[(int)((y+diffY)+windowHalfHeight)][(int)((x+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)((y+diffY)+windowHalfHeight)][(int)(((x-resize)+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)(((y+resize)+diffY)+windowHalfHeight)][(int)((x+diffX)+windowHalfWidth)].stacked
															 &&!element[(int)(((y-resize)+diffY)+windowHalfHeight)][(int)((x+diffX)+windowHalfWidth)].stacked){
			result = PROCEED;

		}else{
			result = STOP;

		}//end of if

	}

	return result;

}

//check which row is deleted.
void checkRow(){
	for(int i = 0; i < ROW; i++){
		int k = 0;
			for(int j = 0; j < COL; j++){
				if(element[i][j].stacked == true){
					k++;

				}
			}

		//delete 1 line. // from I row.
		if(k == COL){

			for(int l = i; l < ROW; l++){
				if(l == i){
					for(int m = 0; m < COL ; m++){
						element[l][m].stacked = false;
						//--to do
					}

				}

				for(int m = 0; m < COL ; m++){
					element[l][m].stacked = element[l+1][m].stacked;
					element[l][m].type = element[l+1][m].type;
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
//Transform block shape
//Faster block down-warding.
void normalKey(unsigned char key, int xi, int yi)
{
	int i = 0;
	int result = 0;

	switch(key){
		case 32 ://"ISO Spacebar key code"
			//Check how many distance is remained to confront wall...
			do{
				i++;
				result = checkToProceed(i, GLUT_KEY_DOWN);

			}while(!(result==STOP)&&!(result==INIT_END));

			y = y - (float)i +1;

			break;

	}
}

void specialKey(int key, int xi, int yi)
{
	switch(checkToProceed(resize, key)){
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
				        	if(type == TYPE_A){//"ぱ" to "び"
								type = TYPE_B;

							}else if(type == TYPE_B){//"l" to "ぱ"
								//if fronting wall
								if(x == (windowHalfWidth-resize)){
									x = x-resize*3;
									type = TYPE_A;

								}else if(x == (windowHalfWidth-2*resize)){
									x = x-resize*2;
									type = TYPE_A;

								}else if(x == (windowHalfWidth-3*resize)){
									x = x-resize;
									type = TYPE_A;

								}else if(element[(int)(y+windowHalfHeight)][(int)(x+resize*3+windowHalfWidth)].stacked==true
										|| element[(int)(y+windowHalfHeight)][(int)(x+resize*2+windowHalfWidth)].stacked==true
										|| element[(int)(y+windowHalfHeight)][(int)(x+resize+windowHalfWidth)].stacked==true){
									type = TYPE_B;

								}else{
									type = TYPE_A;

								}

							}else if(type == TYPE_C){
								//if fronting wall
								if(x == (-windowHalfWidth)){
									x = x+resize;
									type = TYPE_D;

								}else if(element[(int)((y-resize)+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked==true
										|| element[(int)((y-resize)+windowHalfHeight)][(int)((x-resize)+windowHalfWidth)].stacked==true){
									type = TYPE_C;

								}else{
									type = TYPE_D;

								}

							}else if(type == TYPE_D){
								//if fronting wall
								if(element[(int)((y+resize)+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked==true
										|| element[(int)((y-resize)+windowHalfHeight)][(int)((x+resize)+windowHalfWidth)].stacked==true){
									type = TYPE_D;

								}else{
									type = TYPE_C;

								}

							}else if(type == TYPE_E){
								//if fronting wall
								if(x == (windowHalfWidth-resize)){
									x = x-resize;
									type = TYPE_F;

								}else if(element[(int)((y-resize)+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked==true
										|| element[(int)((y-resize)+windowHalfHeight)][(int)((x+resize)+windowHalfWidth)].stacked==true){
									type = TYPE_E;

								}else{
									type = TYPE_F;

								}
							}else if(type == TYPE_F){
								//if fronting wall
								if(x == (windowHalfWidth)){
									x = x-resize;
									type = TYPE_E;

								}else if(element[(int)((y+resize)+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked==true
										|| element[(int)((y-resize)+windowHalfHeight)][(int)((x-resize)+windowHalfWidth)].stacked==true){
									type = TYPE_F;

								}else{
									type = TYPE_E;

								}
							}else if(type == TYPE_G){
								//No transformation
								type = TYPE_G;

							}else if(type == TYPE_H){
								//if fronting wall
								if(x == (windowHalfWidth-resize)){
									x = x-resize;
									type = TYPE_I;

								}else if(element[(int)(y+windowHalfHeight)][(int)((x+resize)+windowHalfWidth)].stacked==true
										|| element[(int)((y+resize*2)+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked==true){
									type = TYPE_H;

								}else{
									type = TYPE_I;

								}

							}else if(type == TYPE_I){
								//if fronting wall
								if((y == - windowHalfHeight)&&(x == windowHalfWidth - resize*2)){
									y = y+resize;
									x = x-resize;
									type = TYPE_J;

								}else if(y == - windowHalfHeight){
									y = y+resize;
									type = TYPE_J;

								}else if(x == windowHalfWidth - resize*2){
									x = x-resize;
									type = TYPE_J;

								}else if(element[(int)((y-resize)+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked==true
										|| element[(int)(y+windowHalfHeight)][(int)((x+resize*2)+windowHalfWidth)].stacked==true){
									type = TYPE_I;

								}else{
									type = TYPE_J;

								}

							}else if(type == TYPE_J){
								//if fronting wall
								if((y == -windowHalfHeight + resize)&&(x == -windowHalfWidth)){
									y = y+resize;
									x = x+resize;
									type = TYPE_K;

								}else if(y == -windowHalfHeight + resize){
									y = y+resize;
									type = TYPE_K;

								}else if(x == -windowHalfWidth){
									x = x+resize;
									type = TYPE_K;

								}else if(element[(int)(y+windowHalfHeight)][(int)((x-resize)+windowHalfWidth)].stacked==true
										|| element[(int)((y-resize*2)+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked==true){
									type = TYPE_J;

								}else{
									type = TYPE_K;

								}

							}else if(type == TYPE_K){
								//if fronting wall
								if(x == -windowHalfWidth + resize){
									x = x+resize;
									type = TYPE_H;

								}else if(element[(int)((y-resize)+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked==true
										|| element[(int)(y+windowHalfHeight)][(int)((x-resize)+windowHalfWidth)].stacked==true){
									type = TYPE_K;

								}else{
									type = TYPE_H;

								}

							}else if(type == TYPE_L){
								//if fronting wall
								if(x == (windowHalfWidth-resize)){
									x = x-resize;
									type = TYPE_M;

								}else if(element[(int)((y-resize)+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked==true
										|| element[(int)((y-resize*2)+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked==true){
									type = TYPE_L;

								}else{
									type = TYPE_M;

								}

							}else if(type == TYPE_M){
								//if fronting wall
								if(x == - windowHalfWidth){
									x = x+2*resize;
									type = TYPE_N;

								}else if(x == - windowHalfWidth+resize){
									x = x+resize;
									type = TYPE_N;

								}else if(element[(int)(y+windowHalfHeight)][(int)((x-resize)+windowHalfWidth)].stacked==true
										|| element[(int)(y+windowHalfHeight)][(int)((x-resize*2)+windowHalfWidth)].stacked==true){
									type = TYPE_M;

								}else{
									type = TYPE_N;

								}

							}else if(type == TYPE_N){
								//if fronting wall
								if(element[(int)((y+resize)+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked==true
										|| element[(int)((y+resize*2)+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked==true){
									type = TYPE_N;

								}else{
									type = TYPE_O;

								}

							}else if(type == TYPE_O){
								//if fronting wall
								if(x == windowHalfWidth - resize){
									x = x-2*resize;
									type = TYPE_L;

								}else if(x == windowHalfWidth - 2*resize){
									x = x-resize;
									type = TYPE_L;

								}else if(element[(int)(y+windowHalfHeight)][(int)((x+resize)+windowHalfWidth)].stacked==true
											|| element[(int)(y+windowHalfHeight)][(int)((x+2*resize)+windowHalfWidth)].stacked==true){
									type = TYPE_O;

								}else{
									type = TYPE_L;

								}

							}else if(type == TYPE_P){
								//if fronting wall
								if(y == -windowHalfWidth){
									y = y-resize;
									type = TYPE_Q;

								}else if(element[(int)((y-resize)+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked==true){
									type = TYPE_L;

								}else{
									type = TYPE_Q;

								}

							}else if(type == TYPE_Q){
								//if fronting wall
								if(x == - windowHalfWidth){
									x = x+resize;
									type = TYPE_R;

								}else if(element[(int)(y+windowHalfHeight)][(int)((x-resize)+windowHalfWidth)].stacked==true){
									type = TYPE_Q;

								}else{
									type = TYPE_R;

								}

							}else if(type == TYPE_R){
								//if fronting wall
								if(element[(int)((y-resize)+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked==true){
									type = TYPE_R;

								}else{
									type = TYPE_S;

								}

							}else if(type == TYPE_S){
								//if fronting wall
								if(x == windowHalfWidth){
									x = x-resize;
									type = TYPE_P;

								}else if(element[(int)(y+windowHalfHeight)][(int)((x+resize)+windowHalfWidth)].stacked==true){
									type = TYPE_S;

								}else{
									type = TYPE_P;

								}

							}

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
	int sel = rand()%8;

	if(sel == 0){
		type = TYPE_A;

	}else if(sel == 1){
		type = TYPE_B;

	}else if(sel == 2){
		type = TYPE_C;

	}else if(sel == 3){
		type = TYPE_E;

	}else if(sel == 4){
		type = TYPE_G;

	}else if(sel == 5){
		type = TYPE_H;

	}else if(sel == 6){
		type = TYPE_L;

	}else if(sel == 7){
		type = TYPE_P;
	}

}

//timer ... to proceed and change screen.
void animationTimer(int speed){



	switch(checkToProceed(speed, GLUT_KEY_DOWN)){
		case PROCEED:
			//Process to downward
			y = y - (GLfloat)speed;
			break;

		default :
			//End... If block is confronting wall.
			if(type==TYPE_A){
				element[(int)(y+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked = true;
				element[(int)(y+windowHalfHeight)][(int)(x+resize+windowHalfWidth)].stacked = true;
				element[(int)(y+windowHalfHeight)][(int)(x+resize*2+windowHalfWidth)].stacked = true;
				element[(int)(y+windowHalfHeight)][(int)(x+resize*3+windowHalfWidth)].stacked = true;

				element[(int)(y+windowHalfHeight)][(int)(x+windowHalfWidth)].type = TYPE_A;
				element[(int)(y+windowHalfHeight)][(int)(x+resize+windowHalfWidth)].type = TYPE_A;
				element[(int)(y+windowHalfHeight)][(int)(x+resize*2+windowHalfWidth)].type = TYPE_A;
				element[(int)(y+windowHalfHeight)][(int)(x+resize*3+windowHalfWidth)].type = TYPE_A;

			}else if(type==TYPE_B){
				element[(int)(y+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked = true;
				element[(int)(y+resize+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked = true;
				element[(int)(y+resize*2+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked = true;
				element[(int)(y+resize*3+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked = true;

				element[(int)(y+windowHalfHeight)][(int)(x+windowHalfWidth)].type = TYPE_B;
				element[(int)(y+resize+windowHalfHeight)][(int)(x+windowHalfWidth)].type = TYPE_B;
				element[(int)(y+resize*2+windowHalfHeight)][(int)(x+windowHalfWidth)].type = TYPE_B;
				element[(int)(y+resize*3+windowHalfHeight)][(int)(x+windowHalfWidth)].type = TYPE_B;
			}else if(type==TYPE_C){
				element[(int)(y+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked = true;
				element[(int)(y+windowHalfHeight)][(int)((x+resize)+windowHalfWidth)].stacked = true;
				element[(int)((y+resize)+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked = true;
				element[(int)((y-resize)+windowHalfHeight)][(int)((x+resize)+windowHalfWidth)].stacked = true;

				element[(int)(y+windowHalfHeight)][(int)(x+windowHalfWidth)].type = TYPE_C;
				element[(int)(y+windowHalfHeight)][(int)((x+resize)+windowHalfWidth)].type = TYPE_C;
				element[(int)((y+resize)+windowHalfHeight)][(int)(x+windowHalfWidth)].type = TYPE_C;
				element[(int)((y-resize)+windowHalfHeight)][(int)((x+resize)+windowHalfWidth)].type = TYPE_C;

			}else if(type==TYPE_D){
				element[(int)(y+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked = true;
				element[(int)(y+windowHalfHeight)][(int)((x+resize)+windowHalfWidth)].stacked = true;
				element[(int)((y-resize)+windowHalfHeight)][(int)((x-resize)+windowHalfWidth)].stacked = true;
				element[(int)((y-resize)+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked = true;

				element[(int)(y+windowHalfHeight)][(int)(x+windowHalfWidth)].type = TYPE_D;
				element[(int)(y+windowHalfHeight)][(int)((x+resize)+windowHalfWidth)].type = TYPE_D;
				element[(int)((y-resize)+windowHalfHeight)][(int)((x-resize)+windowHalfWidth)].type = TYPE_D;
				element[(int)((y-resize)+windowHalfHeight)][(int)(x+windowHalfWidth)].type = TYPE_D;

			}else if(type==TYPE_E){
				element[(int)(y+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked = true;
				element[(int)(y+windowHalfHeight)][(int)((x-resize)+windowHalfWidth)].stacked = true;
				element[(int)((y-resize)+windowHalfHeight)][(int)((x-resize)+windowHalfWidth)].stacked = true;
				element[(int)((y+resize)+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked = true;

				element[(int)(y+windowHalfHeight)][(int)(x+windowHalfWidth)].type = TYPE_E;
				element[(int)(y+windowHalfHeight)][(int)((x-resize)+windowHalfWidth)].type = TYPE_E;
				element[(int)((y-resize)+windowHalfHeight)][(int)((x-resize)+windowHalfWidth)].type = TYPE_E;
				element[(int)((y+resize)+windowHalfHeight)][(int)(x+windowHalfWidth)].type = TYPE_E;

			}else if(type==TYPE_F){
				element[(int)(y+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked = true;
				element[(int)(y+windowHalfHeight)][(int)((x-resize)+windowHalfWidth)].stacked = true;
				element[(int)((y-resize)+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked = true;
				element[(int)((y-resize)+windowHalfHeight)][(int)((x+resize)+windowHalfWidth)].stacked = true;

				element[(int)(y+windowHalfHeight)][(int)(x+windowHalfWidth)].type = TYPE_F;
				element[(int)(y+windowHalfHeight)][(int)((x-resize)+windowHalfWidth)].type = TYPE_F;
				element[(int)((y-resize)+windowHalfHeight)][(int)(x+windowHalfWidth)].type = TYPE_F;
				element[(int)((y-resize)+windowHalfHeight)][(int)((x+resize)+windowHalfWidth)].type = TYPE_F;

			}else if(type==TYPE_G){
				element[(int)(y+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked = true;
				element[(int)(y+windowHalfHeight)][(int)((x+resize)+windowHalfWidth)].stacked = true;
				element[(int)((y+resize)+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked = true;
				element[(int)((y+resize)+windowHalfHeight)][(int)((x+resize)+windowHalfWidth)].stacked = true;

				element[(int)(y+windowHalfHeight)][(int)(x+windowHalfWidth)].type = TYPE_G;
				element[(int)(y+windowHalfHeight)][(int)((x+resize)+windowHalfWidth)].type = TYPE_G;
				element[(int)((y+resize)+windowHalfHeight)][(int)(x+windowHalfWidth)].type = TYPE_G;
				element[(int)((y+resize)+windowHalfHeight)][(int)((x+resize)+windowHalfWidth)].type = TYPE_G;

			}else if(type==TYPE_H){
				element[(int)(y+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked = true;
				element[(int)((y+resize)+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked = true;
				element[(int)(y+windowHalfHeight)][(int)((x-resize)+windowHalfWidth)].stacked = true;
				element[(int)(y+windowHalfHeight)][(int)((x-resize*2)+windowHalfWidth)].stacked = true;

				element[(int)(y+windowHalfHeight)][(int)(x+windowHalfWidth)].type = TYPE_H;
				element[(int)((y+resize)+windowHalfHeight)][(int)(x+windowHalfWidth)].type = TYPE_H;
				element[(int)(y+windowHalfHeight)][(int)((x-resize)+windowHalfWidth)].type = TYPE_H;
				element[(int)(y+windowHalfHeight)][(int)((x-resize*2)+windowHalfWidth)].type = TYPE_H;

			}else if(type==TYPE_I){
				element[(int)(y+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked = true;
				element[(int)(y+windowHalfHeight)][(int)((x+resize)+windowHalfWidth)].stacked = true;
				element[(int)((y+resize)+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked = true;
				element[(int)((y+resize*2)+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked = true;

				element[(int)(y+windowHalfHeight)][(int)(x+windowHalfWidth)].type = TYPE_I;
				element[(int)(y+windowHalfHeight)][(int)((x+resize)+windowHalfWidth)].type = TYPE_I;
				element[(int)((y+resize)+windowHalfHeight)][(int)(x+windowHalfWidth)].type = TYPE_I;
				element[(int)((y+resize*2)+windowHalfHeight)][(int)(x+windowHalfWidth)].type = TYPE_I;

			}else if(type==TYPE_J){
				element[(int)(y+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked = true;
				element[(int)((y-resize)+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked = true;
				element[(int)(y+windowHalfHeight)][(int)((x+resize)+windowHalfWidth)].stacked = true;
				element[(int)(y+windowHalfHeight)][(int)((x+resize*2)+windowHalfWidth)].stacked = true;

				element[(int)(y+windowHalfHeight)][(int)(x+windowHalfWidth)].type = type;
				element[(int)((y-resize)+windowHalfHeight)][(int)(x+windowHalfWidth)].type = type;
				element[(int)(y+windowHalfHeight)][(int)((x+resize)+windowHalfWidth)].type = type;
				element[(int)(y+windowHalfHeight)][(int)((x+resize*2)+windowHalfWidth)].type = type;

			}else if(type==TYPE_K){
				element[(int)(y+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked = true;
				element[(int)(y+windowHalfHeight)][(int)((x-resize)+windowHalfWidth)].stacked = true;
				element[(int)((y-resize)+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked = true;
				element[(int)((y-resize*2)+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked = true;

				element[(int)(y+windowHalfHeight)][(int)(x+windowHalfWidth)].type = type;
				element[(int)(y+windowHalfHeight)][(int)((x-resize)+windowHalfWidth)].type = type;
				element[(int)((y-resize)+windowHalfHeight)][(int)(x+windowHalfWidth)].type = type;
				element[(int)((y-resize*2)+windowHalfHeight)][(int)(x+windowHalfWidth)].type = type;

			}else if(type==TYPE_L){
				element[(int)(y+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked = true;
				element[(int)((y+resize)+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked = true;
				element[(int)(y+windowHalfHeight)][(int)((x+resize)+windowHalfWidth)].stacked = true;
				element[(int)(y+windowHalfHeight)][(int)((x+resize*2)+windowHalfWidth)].stacked = true;

				element[(int)(y+windowHalfHeight)][(int)(x+windowHalfWidth)].type = type;
				element[(int)((y+resize)+windowHalfHeight)][(int)(x+windowHalfWidth)].type = type;
				element[(int)(y+windowHalfHeight)][(int)((x+resize)+windowHalfWidth)].type = type;
				element[(int)(y+windowHalfHeight)][(int)((x+resize*2)+windowHalfWidth)].type = type;

			}else if(type==TYPE_M){
				element[(int)(y+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked = true;
				element[(int)(y+windowHalfHeight)][(int)((x+resize)+windowHalfWidth)].stacked = true;
				element[(int)((y-resize)+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked = true;
				element[(int)((y-resize*2)+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked = true;

				element[(int)(y+windowHalfHeight)][(int)(x+windowHalfWidth)].type = type;
				element[(int)(y+windowHalfHeight)][(int)((x+resize)+windowHalfWidth)].type = type;
				element[(int)((y-resize)+windowHalfHeight)][(int)(x+windowHalfWidth)].type = type;
				element[(int)((y-resize*2)+windowHalfHeight)][(int)(x+windowHalfWidth)].type = type;

			}else if(type==TYPE_N){
				element[(int)(y+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked = true;
				element[(int)(y+windowHalfHeight)][(int)((x-resize)+windowHalfWidth)].stacked = true;
				element[(int)(y+windowHalfHeight)][(int)((x-resize*2)+windowHalfWidth)].stacked = true;
				element[(int)((y-resize)+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked = true;

				element[(int)(y+windowHalfHeight)][(int)(x+windowHalfWidth)].type = type;
				element[(int)(y+windowHalfHeight)][(int)((x-resize)+windowHalfWidth)].type = type;
				element[(int)(y+windowHalfHeight)][(int)((x-resize*2)+windowHalfWidth)].type = type;
				element[(int)((y-resize)+windowHalfHeight)][(int)(x+windowHalfWidth)].type = type;

			}else if(type==TYPE_O){
				element[(int)(y+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked = true;
				element[(int)(y+windowHalfHeight)][(int)((x-resize)+windowHalfWidth)].stacked = true;
				element[(int)((y+resize)+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked = true;
				element[(int)((y+resize*2)+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked = true;

				element[(int)(y+windowHalfHeight)][(int)(x+windowHalfWidth)].type = type;
				element[(int)(y+windowHalfHeight)][(int)((x-resize)+windowHalfWidth)].type = type;
				element[(int)((y+resize)+windowHalfHeight)][(int)(x+windowHalfWidth)].type = type;
				element[(int)((y+resize*2)+windowHalfHeight)][(int)(x+windowHalfWidth)].type = type;

			}else if(type==TYPE_P){
				element[(int)(y+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked = true;
				element[(int)((y+resize)+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked = true;
				element[(int)(y+windowHalfHeight)][(int)((x-resize)+windowHalfWidth)].stacked = true;
				element[(int)(y+windowHalfHeight)][(int)((x+resize)+windowHalfWidth)].stacked = true;

				element[(int)(y+windowHalfHeight)][(int)(x+windowHalfWidth)].type = type;
				element[(int)((y+resize)+windowHalfHeight)][(int)(x+windowHalfWidth)].type = type;
				element[(int)(y+windowHalfHeight)][(int)((x-resize)+windowHalfWidth)].type = type;
				element[(int)(y+windowHalfHeight)][(int)((x+resize)+windowHalfWidth)].type = type;

			}else if(type==TYPE_Q){
				element[(int)(y+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked = true;
				element[(int)((y+resize)+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked = true;
				element[(int)((y-resize)+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked = true;
				element[(int)(y+windowHalfHeight)][(int)((x+resize)+windowHalfWidth)].stacked = true;

				element[(int)(y+windowHalfHeight)][(int)(x+windowHalfWidth)].type = type;
				element[(int)((y+resize)+windowHalfHeight)][(int)(x+windowHalfWidth)].type = type;
				element[(int)((y-resize)+windowHalfHeight)][(int)(x+windowHalfWidth)].type = type;
				element[(int)(y+windowHalfHeight)][(int)((x+resize)+windowHalfWidth)].type = type;

			}else if(type==TYPE_R){
				element[(int)(y+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked = true;
				element[(int)((y-resize)+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked = true;
				element[(int)(y+windowHalfHeight)][(int)((x-resize)+windowHalfWidth)].stacked = true;
				element[(int)(y+windowHalfHeight)][(int)((x+resize)+windowHalfWidth)].stacked = true;

				element[(int)(y+windowHalfHeight)][(int)(x+windowHalfWidth)].type = type;
				element[(int)((y-resize)+windowHalfHeight)][(int)(x+windowHalfWidth)].type = type;
				element[(int)(y+windowHalfHeight)][(int)((x-resize)+windowHalfWidth)].type = type;
				element[(int)(y+windowHalfHeight)][(int)((x+resize)+windowHalfWidth)].type = type;

			}else if(type==TYPE_S){
				element[(int)(y+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked = true;
				element[(int)(y+windowHalfHeight)][(int)((x-resize)+windowHalfWidth)].stacked = true;
				element[(int)((y+resize)+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked = true;
				element[(int)((y-resize)+windowHalfHeight)][(int)(x+windowHalfWidth)].stacked = true;

				element[(int)(y+windowHalfHeight)][(int)(x+windowHalfWidth)].type = type;
				element[(int)(y+windowHalfHeight)][(int)((x-resize)+windowHalfWidth)].type = type;
				element[(int)((y+resize)+windowHalfHeight)][(int)(x+windowHalfWidth)].type = type;
				element[(int)((y-resize)+windowHalfHeight)][(int)(x+windowHalfWidth)].type = type;
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

//Render Block
void renderScene(void){

	glClear(GL_COLOR_BUFFER_BIT);

	// Moving object
	if(type == TYPE_A){
		//"けけ" "ぱ" shape
		//draw object using vertex.
		glColor3f(1.0,0.0,0.0);
		glRectf(x,y,x+resize,y+resize);
		glRectf(x+resize,y,x+resize*2, y+resize);
		glRectf(x+resize*2,y, x+resize*3, y+resize);
		glRectf(x+resize*3,y, x+resize*4, y+resize);

	}else if(type == TYPE_B){
		//"l" shape
		//draw object using vertext.
		glColor3f(1.0,0.0,0.0);
		glRectf(x,y,x+resize,y+resize);
		glRectf(x,y+resize,x+resize,y+resize*2);
		glRectf(x,y+resize*2,x+resize,y+resize*3);
		glRectf(x,y+resize*3,x+resize,y+resize*4);

	}else if(type == TYPE_C){
		//"L" shape
		//"ぁ" shape
		glColor3f(0.0,1.0,0.0);
		glRectf(x,y,x+resize,y+resize);
		glRectf(x+resize,y,x+resize*2,y+resize);
		glRectf(x,y+resize,x+resize,y+resize*2);
		glRectf(x+resize,y-resize,x+resize*2,y);

	}else if(type == TYPE_D){
		//" けけ" shape
		//"けけ " shape
		glColor3f(0.0,1.0,0.0);
		glRectf(x,y,x+resize,y+resize);
		glRectf(x+resize,y,x+resize*2,y+resize);
		glRectf(x,y-resize,x+resize,y);
		glRectf(x-resize,y-resize,x,y);
	}else if(type == TYPE_E){
		//"  け" shape
		//"け け " shape
		//"け     " shape
		glColor3f(0.0,0.0,1.0);
		glRectf(x,y,x+resize,y+resize);
		glRectf(x-resize,y,x,y+resize);
		glRectf(x,y+resize,x+resize,y+resize*2);
		glRectf(x-resize,y-resize,x,y);
	}else if(type == TYPE_F){
		//"けけ" shape
		//" けけ " shape
		glColor3f(0.0,0.0,1.0);
		glRectf(x,y,x+resize,y+resize);
		glRectf(x-resize,y,x,y+resize);
		glRectf(x,y-resize,x+resize,y);
		glRectf(x+resize,y-resize,x+resize*2,y);

	}else if(type == TYPE_G){
		//"けけ" shape
		//"けけ " shape
		glColor3f(1.0,1.0,0.0);
		glRectf(x,y,x+resize,y+resize);
		glRectf(x+resize,y,x+resize*2,y+resize);
		glRectf(x,y+resize,x+resize,y+resize*2);
		glRectf(x+resize,y+resize,x+resize*2,y+resize*2);

	}else if(type == TYPE_H){
		//"   け" shape
		//"けけ け" shape
		glColor3f(0.0,1.0,1.0);
		glRectf(x,y,x+resize,y+resize);
		glRectf(x,y+resize,x+resize,y+resize*2);
		glRectf(x-resize,y,x,y+resize);
		glRectf(x-resize*2,y,x+resize,y+resize);

	}else if(type == TYPE_I){
		//"け " shape
		//"け " shape
		//"け け" shape
		glColor3f(0.0,1.0,1.0);
		glRectf(x,y,x+resize,y+resize);
		glRectf(x,y+resize,x+resize,y+resize*2);
		glRectf(x,y+resize*2,x+resize,y+resize*3);
		glRectf(x+resize,y,x+resize*2,y+resize);

	}else if(type == TYPE_J){
		//"け け け" shape
		//"け " shape
		glColor3f(0.0,1.0,1.0);
		glRectf(x,y,x+resize,y+resize);
		glRectf(x,y-resize,x+resize,y);
		glRectf(x+resize,y,x+resize*2,y+resize);
		glRectf(x+resize*2,y,x+resize*3,y+resize);

	}else if(type == TYPE_K){
		//"け け" shape
		//"  け " shape
		//"  け " shape
		glColor3f(0.0,1.0,1.0);
		glRectf(x,y,x+resize,y+resize);
		glRectf(x-resize,y,x,y+resize);
		glRectf(x,y-resize,x+resize,y);
		glRectf(x,y-resize*2,x+resize,y-resize);
	}else if(type == TYPE_L){
		//"け       " shape
		//"けけ け" shape
		glColor3f(1.0,0.0,1.0);
		glRectf(x,y,x+resize,y+resize);
		glRectf(x,y+resize,x+resize,y+2*resize);
		glRectf(x+resize,y,x+2*resize,y+resize);
		glRectf(x+2*resize,y,x+3*resize,y+resize);

	}else if(type == TYPE_M){
		//"け け" shape
		//"け    " shape
		//"け    " shape
		glColor3f(1.0,0.0,1.0);
		glRectf(x,y,x+resize,y+resize);
		glRectf(x,y-resize,x+resize,y);
		glRectf(x,y-resize*2,x+resize,y-resize);
		glRectf(x+resize,y,x+resize*2,y+resize);

	}else if(type == TYPE_N){
		//"け け  け" shape
		//"    け " shape
		glColor3f(1.0,0.0,1.0);
		glRectf(x,y,x+resize,y+resize);
		glRectf(x-resize,y,x,y+resize);
		glRectf(x-2*resize,y,x-resize,y+resize);
		glRectf(x,y-resize,x+resize,y);

	}else if(type == TYPE_O){
		//"  け" shape
		//"  け " shape
		//"け  け " shape
		glColor3f(1.0,0.0,1.0);
		glRectf(x,y,x+resize,y+resize);
		glRectf(x-resize,y,x,y+resize);
		glRectf(x,y+resize,x+resize,y+2*resize);
		glRectf(x,y+resize*2,x+resize,y+3*resize);
	}else if(type == TYPE_P){
		//"  け" shape
		//"け  け  け " shape
		glColor3f(1.0,1.0,1.0);
		glRectf(x,y,x+resize,y+resize);
		glRectf(x,y+resize,x+resize,y+2*resize);
		glRectf(x-resize,y,x,y+resize);
		glRectf(x+resize,y,x+2*resize,y+resize);
	}else if(type == TYPE_Q){
		//"け" shape
		//"け け" shape
		//"け " shape
		glColor3f(1.0,1.0,1.0);
		glRectf(x,y,x+resize,y+resize);
		glRectf(x+resize,y,x+2*resize, y+resize);
		glRectf(x,y+resize,x+resize,y+2*resize);
		glRectf(x,y-resize,x+resize,y);
	}else if(type == TYPE_R){
		//"け け け " shape
		//"  け " shape
		glColor3f(1.0,1.0,1.0);
		glRectf(x,y,x+resize,y+resize);
		glRectf(x-resize,y,x,y+resize);
		glRectf(x+resize,y,x+2*resize,y+resize);
		glRectf(x,y-resize,x+resize,y);
	}else if(type == TYPE_S){
		//"  け" shape
		//"け け " shape
		//"  け " shape
		glColor3f(1.0,1.0,1.0);
		glRectf(x,y,x+resize,y+resize);
		glRectf(x-resize,y,x,y+resize);
		glRectf(x,y-resize,x+resize,y);
		glRectf(x,y+resize,x+resize,y+2*resize);
	}



	// Stacked object
	//Check whether block is stacked
	glColor3f(0.0,0.0,1.0);
	for(int i = 0; i<ROW; i++){
		for(int j = 0; j<COL; j++){
			if(element[i][j].stacked == true){
				if(element[i][j].type==TYPE_A||element[i][j].type==TYPE_B){
					glColor3f(1.0,0.0,0.0);

				}else if(element[i][j].type==TYPE_C||element[i][j].type==TYPE_D){
					glColor3f(0.0,1.0,0.0);

				}else if(element[i][j].type==TYPE_E||element[i][j].type==TYPE_F){
					glColor3f(0.0,0.0,1.0);

				}else if(element[i][j].type==TYPE_G){
					glColor3f(1.0,1.0,0.0);

				}else if(element[i][j].type==TYPE_H||element[i][j].type==TYPE_I||element[i][j].type==TYPE_J||element[i][j].type==TYPE_K){
					glColor3f(0.0,1.0,1.0);

				}else if(element[i][j].type==TYPE_L||element[i][j].type==TYPE_M||element[i][j].type==TYPE_N||element[i][j].type==TYPE_O){
					glColor3f(1.0,0.0,1.0);

				}else if(element[i][j].type==TYPE_P||element[i][j].type==TYPE_Q||element[i][j].type==TYPE_R||element[i][j].type==TYPE_S){
					glColor3f(1.0,1.0,1.0);

				}
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
	glutKeyboardFunc(normalKey);
	glutSpecialFunc(specialKey);
	glutReshapeFunc(changeSize);
	setupRC();
	glutMainLoop();
	return 0;

}

