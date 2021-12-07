
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <random>
#include <ctime>
#include <iostream>
#include <Windows.h>
#include <glut.h>


using namespace std;
int x = 1;
int y = 2;
int z = 3;

float circleX = 255;
float circleY = 15;

int lives = 3;
int coins = 0;

int val[3] = { 20, 180, 350 };
int r = rand() % 2;
float obsX = val[r];
float obsY = 450 + (rand() % 500);

int val2[3] = { 255, 415, 95 };
int r2 = rand() % 3;
float coinX = val2[r2];
float coinY = 500 + (rand() % 550);

int test = 0;

int cum_obstacles = 0;

float laneR1 = 0.2f;
float laneG1 = 0.1f;
float laneB1 = 0.0f;

float laneR2 = 0.4f;
float laneG2 = 0.2f;
float laneB2 = 0.0f;

void init()
{
	glClearColor(0, 0, 0, 1); 	
	glMatrixMode(GL_PROJECTION); 	
	glLoadIdentity(); 	
	gluOrtho2D(0, 500, 0, 500);
}

void drawLane() {
	glColor3f(laneR1, laneG1, laneB1);
	glBegin(GL_QUADS);
	glVertex2f(160, 0); 
	glVertex2f(180, 0);
	glVertex2f(180, 125);
	glVertex2f(160, 125);
	glEnd();
	glColor3f(laneR2, laneG2, laneB2);
	glBegin(GL_QUADS);
	glVertex2f(160, 125);
	glVertex2f(180, 125);
	glVertex2f(180, 250);
	glVertex2f(160, 250);
	glEnd();
	glColor3f(laneR1, laneG1, laneB1);
	glBegin(GL_QUADS);
	glVertex2f(160, 250);
	glVertex2f(180, 250);
	glVertex2f(180, 375);
	glVertex2f(160, 375);
	glEnd();
	glColor3f(laneR2, laneG2, laneB2);
	glBegin(GL_QUADS);
	glVertex2f(160, 375);
	glVertex2f(180, 375);
	glVertex2f(180, 500);
	glVertex2f(160, 500);
	glEnd();
	glColor3f(laneR1, laneG1, laneB1);
	glPushMatrix();
	glTranslated(160, 0, 0);
	glBegin(GL_QUADS);
	glVertex2f(160, 0); 
	glVertex2f(180, 0);
	glVertex2f(180, 125);
	glVertex2f(160, 125);
	glEnd();
	glPopMatrix();
	glColor3f(laneR2, laneG2, laneB2);
	glPushMatrix();
	glTranslated(160, 0, 0);
	glBegin(GL_QUADS);
	glVertex2f(160, 125);
	glVertex2f(180, 125);
	glVertex2f(180, 250);
	glVertex2f(160, 250);
	glEnd();
	glPopMatrix();
	glColor3f(laneR1, laneG1, laneB1);
	glPushMatrix();
	glTranslated(160, 0, 0);
	glBegin(GL_QUADS);
	glVertex2f(160, 250);
	glVertex2f(180, 250);
	glVertex2f(180, 375);
	glVertex2f(160, 375);
	glEnd();
	glPopMatrix();
	glColor3f(laneR2, laneG2, laneB2);
	glPushMatrix();
	glTranslated(160, 0, 0);
	glBegin(GL_QUADS);
	glVertex2f(160, 375);
	glVertex2f(180, 375);
	glVertex2f(180, 500);
	glVertex2f(160, 500);
	glEnd();
	glPopMatrix();
}

void drawObstacle() {
		glColor3f(1, 0.25, 0.25);
		glPushMatrix();
		glTranslated(obsX, obsY, 0);
		glBegin(GL_TRIANGLES);
		glVertex3f(50, 50.0f, 0.0f);
		glVertex3f(75, 60.0f, 0.0f);
		glVertex3f(100, 50.0f, 0.0f);
		glEnd();
		glColor3f(0.6, 1, 0.2);
		glBegin(GL_QUADS);
		glVertex2f(50, 50);
		glVertex2f(50, 10);
		glVertex2f(100, 10);
		glVertex2f(100, 50);
		glEnd();
		glPopMatrix();
		glutSwapBuffers();
}

void drawCoin()
{
	float theta;
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		theta = i * 3.141592653589793238 / 180;
		glVertex2f(coinX + 10 * cos(theta), coinY + 10 * sin(theta));
	}
	glEnd();
}

void slideCoin() {
	if (coinY <= 15) {
		coinY = 500 + (rand() % 550);
		int val2[3] = { 255, 415, 95};
		int r = rand() % 3;
		coinX = val2[r];
	}
}

void laneAnimate(int x) {
	
	glutPostRedisplay();
	glutTimerFunc(100, laneAnimate, 0);
}

void slideObstacle(int val) {

		if (obsY <= -30) {
			obsY = 450 + (rand() % 500);
			int val[3] = { 20, 180, 350 };
			int r = rand() % 3;
			cout << r;
			obsX = val[r];
			cum_obstacles = cum_obstacles + 1;
		}
		obsY -= 1;
		if (cum_obstacles == 6) {
			slideCoin();
			cum_obstacles = 0;
			test = 1;
		}
		coinY -= 1;
		if (coinX == circleX && coinY == circleY) {
			coins = coins + 1;
		}
	glutPostRedisplay();
	glutTimerFunc(10, slideObstacle, 0);
}

void shiftChar(int key, int x, int y) {
	if (key == GLUT_KEY_RIGHT) {
		if (circleX <= 255) {
			circleX += 160;
		}

	}
	if (key == GLUT_KEY_LEFT) {
		if (circleX >= 255) {
			circleX -= 160;
		}
	}
}


void print(int x, int y, char* string)
{
	int len, i;
	glRasterPos2f(x, y);
	len = (int)strlen(string);
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawCoin();
	drawLane();
	drawObstacle();
	glColor3f(1, 1, 0.6);
	glBegin(GL_TRIANGLES);
	glVertex3f(circleX - 5, circleY + 5, 0.0f);
	glVertex3f(circleX - 5, circleY - 5, 0.0);
	glVertex3f(circleX - 15, circleY + 5, 0.0);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex3f(circleX + 5, circleY + 5, 0.0f);
	glVertex3f(circleX + 5, circleY - 5, 0.0);
	glVertex3f(circleX + 15, circleY + 5, 0.0);
	glEnd();
	float theta;
	glColor3f(1, 0.5, 0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		theta = i * 3.141592653589793238 / 180;
		glVertex2f(circleX + 10 * cos(theta), circleY + 10 * sin(theta));
	}
	glEnd();
	glColor3f(1, 1, 1);
	char* p0s[20];
	sprintf((char*)p0s, "Lives: %d", lives);
	print(400, 450, (char*)p0s);
	sprintf((char*)p0s, "Coins: %d", coins);
	print(50, 450, (char*)p0s);
	glFlush();

}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(433, 116);
	srand(time(NULL));
	//obsY = 450 + (rand() % 500);
	int val[3] = { 20, 180, 350 };
	int r = rand() % 2;
	//obsX = val[r];
	//coinY = 500;
	int val2[3] = { 255, 415, 95};
	int r2 = rand() % 3;
	//coinX = 255;
	glutCreateWindow("Assignment1");
	init();
	glutSpecialFunc(shiftChar);
	glutDisplayFunc(display);
	glutTimerFunc(10, slideObstacle, 0);
	glutTimerFunc(100, laneAnimate, 0);
	glutMainLoop();

	return 1;
}