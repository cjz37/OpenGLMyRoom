#pragma once

#include <stdlib.h>
#include <iostream>
#include <string>
#include <GL/glut.h>
#include <GL/glaux.h>
#include <cstdio>
#include <string>
#include <vector>
#include "param.h"
#include "objLoader.h"

#pragma warning(disable:4996)

#define GLUT_WHEEL_UP 3
#define GLUT_WHEEL_DOWN 4

using namespace std;

void display();
void reshape(int w, int h);
void lightInit();
void InitWindow(int argc, char** argv);
void refresh();
void guide();

AUX_RGBImageRec* LoadBMP(const char* Filename);
int LoadGLTextures();

void axis();
void drawFloor(int textureIndex);
void drawBed(GLfloat x, GLfloat z, int textureIndex1, int textureIndex2, int textureIndex3);
void drawWall(int textureIndex);
void drawWall0();
void drawWall1();
void drawWall2();
void drawWall3();
void drawWardrobe(int x, int z, int textureIndex1, int textureIndex2);
void drawBall(int x, int z, int textureIndex);
void drawCarpet(int textureIndex);
void drawStairs(int textureIndex);
void drawEnclosure(int textureIndex);
void drawComputer(int textureIndex);
void drawDesk(int textureIndex);
void drawDoor(int textureIndex);
void drawPaint(int textureIndex);
void drawWindow();
void drawCeiling(int textureIndex);
void drawCurtain(int textureIndex);
void drawFloorlamp(int textureIndex);
void drawAirconditioner(int textureIndex);
void drawTree(int textureIndex1, int textureIndex2);
void drawClock(int textureIndex);
void drawBookshelf(int textureIndex);

void keyboard(unsigned char key, int x, int y);
void changeView();
void mouse(int btn, int state, int x, int y);
void myScale();
void changeViewPoint(int x, int y);
void reset(GLfloat gs);

void InitWindow(int argc, char** argv) {
	glutInit(&argc, argv);
	glShadeModel(GL_SMOOTH);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(w, h);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("my room");
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	//是否开灯
	if (isLighton) {
		glEnable(GL_LIGHT0);
	}
	else {
		glDisable(GL_LIGHT0);
	}
	//视角变换
	if (1 == viewPos)
		gluLookAt(1.0 * cos(c * degree), 1.0 * sin(c * degree2), 1.0 * sin(c * degree), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	else if (2 == viewPos)
		gluLookAt(0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	else if (3 == viewPos)
		gluLookAt(1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	else if (4 == viewPos)
		gluLookAt(0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0);
	else if (5 == viewPos) {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(90.0, 1.0, 1.0, 25.0);
		gluLookAt(10.0 * cos(c * degree), 10.0 * sin(c * degree2), 10.0 * sin(c * degree), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	}
	//红 x; 绿 y; 蓝 z
	//axis();
	drawBed(-2.5, -2.9, 15, 1, 16);
	drawWardrobe(-3.6, -4.0, wardrobeStyle, 1);
	drawBall(0, -4.0, 12);
	drawCarpet(carpetStyle);
	drawStairs(stairsStyle);
	drawComputer(21);
	drawDesk(20);
	drawDoor(doorStyle);
	drawPaint(paintStyle);
	drawCurtain(20);
	drawFloorlamp(20);
	drawAirconditioner(11);
	drawTree(20, 22);
	drawFloor(floorStyle);
	drawWall(wallStyle);
	drawClock(14);
	drawBookshelf(20);
	//透明
	drawEnclosure(0);
	drawWindow();

	glFlush();
	glutSwapBuffers();
}

void drawBed(GLfloat x, GLfloat z, int textureIndex1, int textureIndex2, int textureIndex3) {
	//床身
	glBindTexture(GL_TEXTURE_2D, textureIndex1);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	glPushMatrix();
	glTranslated(x, 0.30, z);
	glScalef(3, 0.6, 4);
	glutSolidCube(1);
	glPopMatrix();

	//床头柜
	glPushMatrix();
	glTranslated(x + 1.9, 0.30, z - 1.55);
	glScaled(0.8, 0.6, 0.8);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x - 1.9, 0.30, z - 1.55);
	glScaled(0.8, 0.6, 0.8);
	glutSolidCube(1);
	glPopMatrix();

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);

	//床头
	glBindTexture(GL_TEXTURE_2D, textureIndex2);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	glPushMatrix();
	glTranslated(x, 0.95, z - 1.8);
	glScalef(3.1, 1.0, 0.3);
	glutSolidCube(1);
	glPopMatrix();

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);

	//棉被
	glBindTexture(GL_TEXTURE_2D, textureIndex3);
	clipSize = 8.0;
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-4.0, 0.61, -4.7);
	glTexCoord2f(0.0, clipSize); glVertex3f(-4.0, 0.61, -0.9);
	glTexCoord2f(clipSize, clipSize); glVertex3f(-1.0, 0.61, -0.9);
	glTexCoord2f(clipSize, 0.0); glVertex3f(-1.0, 0.61, -4.7);
	glEnd();
}

void drawFloor(int textureIndex) {
	glBindTexture(GL_TEXTURE_2D, textureIndex);
	if (1 == viewPos) {
		if (degree2 >= 0) {
			//f2
			glPushMatrix();
			glTranslated(-2.5, -0.1, 0);
			glScalef(5, 0.2, 10);
			glutSolidCube(1);
			glPopMatrix();

			//f1
			glPushMatrix();
			glTranslated(0, -5.1, 0);
			glScalef(10, 0.2, 10);
			glutSolidCube(1);
			glPopMatrix();

			clipSize = 1.5;
			glBegin(GL_QUADS);
			glTexCoord2f(clipSize, 0.0); glVertex3f(-5.0, 0.01, 5.0);
			glTexCoord2f(0.0, 0.0); glVertex3f(-5.0, 0.01, -5.0);
			glTexCoord2f(0.0, clipSize); glVertex3f(0, 0.01, -5.0);
			glTexCoord2f(clipSize, clipSize); glVertex3f(0, 0.01, 5.0);
			glEnd();
			clipSize = 3.0;
			glBegin(GL_QUADS);
			glTexCoord2f(clipSize, 0.0); glVertex3f(-5.0, -4.99, 5.0);
			glTexCoord2f(0.0, 0.0); glVertex3f(-5.0, -4.99, -5.0);
			glTexCoord2f(0.0, clipSize); glVertex3f(5.0, -4.99, -5.0);
			glTexCoord2f(clipSize, clipSize); glVertex3f(5.0, -4.99, 5.0);
			glEnd();
		}
		else if (degree2 < 0) {
			//ceiling
			drawCeiling(0);
		}
	}
	else {
		//f2
		glPushMatrix();
		glTranslated(-2.5, -0.1, 0);
		glScalef(5, 0.2, 10);
		glutSolidCube(1);
		glPopMatrix();

		//f1
		glPushMatrix();
		glTranslated(0, -5.1, 0);
		glScalef(10, 0.2, 10);
		glutSolidCube(1);
		glPopMatrix();

		clipSize = 1.5;
		glBegin(GL_QUADS);
		glTexCoord2f(clipSize, 0.0); glVertex3f(-5.0, 0.01, 5.0);
		glTexCoord2f(0.0, 0.0); glVertex3f(-5.0, 0.01, -5.0);
		glTexCoord2f(0.0, clipSize); glVertex3f(0, 0.01, -5.0);
		glTexCoord2f(clipSize, clipSize); glVertex3f(0, 0.01, 5.0);
		glEnd();
		clipSize = 3.0;
		glBegin(GL_QUADS);
		glTexCoord2f(clipSize, 0.0); glVertex3f(-5.0, -4.99, 5.0);
		glTexCoord2f(0.0, 0.0); glVertex3f(-5.0, -4.99, -5.0);
		glTexCoord2f(0.0, clipSize); glVertex3f(5.0, -4.99, -5.0);
		glTexCoord2f(clipSize, clipSize); glVertex3f(5.0, -4.99, 5.0);
		glEnd();
	}
}

void drawWall(int textureIndex) {
	int state = 0;
	int td = degree;
	int k = 0;
	if (1 == viewPos) {
		if (td < 0) {
			k = -td / 360 + 1;
			td += k * 360;
		}
		if (td > 360) {
			k = td / 360;
			td -= k * 360;
		}

		if (td >= 0 && td < 90)
			state = 0;
		else if (td >= 90 && td < 180)
			state = 1;
		else if (td >= 180 && td < 270)
			state = 2;
		else if (td >= 270 && td < 360)
			state = 3;
	}

	clipSize = 2.0;
	if (10 == textureIndex || 11 == textureIndex)
		clipSize = 1.0;
	glBindTexture(GL_TEXTURE_2D, textureIndex);

	switch (state) {
	case 0:
		drawWall0();
		drawWall1();
		break;
	case 1:
		drawWall1();
		drawWall2();
		break;
	case 2:
		drawWall2();
		drawWall3();
		break;
	case 3:
		drawWall3();
		drawWall0();
		break;
	default:
		break;
	}
}

void drawWall0() {
	glPushMatrix();
	glTranslated(-5.0, 0, 0);
	glScalef(0.2, 10, 10);
	glutSolidCube(1);
	glPopMatrix();
	//纹理
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-4.89, -5.0, 5.0);
	glTexCoord2f(0.0, clipSize); glVertex3f(-4.89, 5.0, 5.0);
	glTexCoord2f(clipSize, clipSize); glVertex3f(-4.89, 5.0, -5.0);
	glTexCoord2f(clipSize, 0.0); glVertex3f(-4.89, -5.0, -5.0);
	glEnd();
}

void drawWall1() {
	glPushMatrix();
	glTranslated(0, 0, -5.0);
	glScalef(10, 10, 0.2);
	glutSolidCube(1);
	glPopMatrix();
	//纹理
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-5.0, -5.0, -4.89);
	glTexCoord2f(0.0, clipSize); glVertex3f(-5.0, 5.0, -4.89);
	glTexCoord2f(clipSize, clipSize); glVertex3f(5.0, 5.0, -4.89);
	glTexCoord2f(clipSize, 0.0); glVertex3f(5.0, -5.0, -4.89);
	glEnd();
}

void drawWall2() {
	glPushMatrix();
	glTranslated(5.0, 0, -4.0);
	glScalef(0.2, 10, 2);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(5.0, 3.5, 0);
	glScalef(0.2, 3, 6);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(5.0, 0, 4.0);
	glScalef(0.2, 10, 2);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(5.0, -3.5, 0);
	glScalef(0.2, 3, 6);
	glutSolidCube(1);
	glPopMatrix();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(4.89, -5.0, -5.0);
	glTexCoord2f(0.0, clipSize); glVertex3f(4.89, 5.0, -5.0);
	glTexCoord2f(clipSize * 0.2, clipSize); glVertex3f(4.89, 5.0, -3.0);
	glTexCoord2f(clipSize * 0.2, 0.0); glVertex3f(4.89, -5.0, -3.0);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, clipSize * 0.7); glVertex3f(4.89, 2.0, -3.0);
	glTexCoord2f(0.0, clipSize); glVertex3f(4.89, 5.0, -3.0);
	glTexCoord2f(clipSize * 0.6, clipSize); glVertex3f(4.89, 5.0, 3.0);
	glTexCoord2f(clipSize * 0.6, clipSize * 0.7); glVertex3f(4.89, 2.0, 3.0);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(4.89, -5.0, 3.0);
	glTexCoord2f(0.0, clipSize); glVertex3f(4.89, 5.0, 3.0);
	glTexCoord2f(clipSize * 0.2, clipSize); glVertex3f(4.89, 5.0, 5.0);
	glTexCoord2f(clipSize * 0.2, 0.0); glVertex3f(4.89, -5.0, 5.0);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(4.89, -5.0, -3.0);
	glTexCoord2f(0.0, clipSize * 0.3); glVertex3f(4.89, -2.0, -3.0);
	glTexCoord2f(clipSize * 0.6, clipSize * 0.3); glVertex3f(4.89, -2.0, 3.0);
	glTexCoord2f(clipSize * 0.6, 0.0); glVertex3f(4.89, -5.0, 3.0);
	glEnd();
}

void drawWall3() {
	glPushMatrix();
	glTranslated(0, 0, 5.0);
	glScalef(10, 10, 0.2);
	glutSolidCube(1);
	glPopMatrix();
	//纹理
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-5.0, -5.0, 4.89);
	glTexCoord2f(0.0, clipSize); glVertex3f(-5.0, 5.0, 4.89);
	glTexCoord2f(clipSize, clipSize); glVertex3f(5.0, 5.0, 4.89);
	glTexCoord2f(clipSize, 0.0); glVertex3f(5.0, -5.0, 4.89);
	glEnd();
}

void drawWardrobe(int x, int z, int textureIndex1, int textureIndex2) {
	//柜子
	glBindTexture(GL_TEXTURE_2D, textureIndex1);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	glPushMatrix();
	glTranslated(x, -3.2, z);
	glScalef(1.8, 1.8, 0.8);
	glutSolidCube(2);
	glPopMatrix();

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);

	//把手
	glBindTexture(GL_TEXTURE_2D, textureIndex2);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	glPushMatrix();
	glTranslated(-3.1, -3.2, -3.6);
	glScalef(0.08, 0.35, 1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-2.9, -3.2, -3.6);
	glScalef(0.08, 0.35, 1);
	glutSolidCube(1);
	glPopMatrix();

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
}

void drawBall(int x, int z, int textureIndex) {
	//篮球跳动动画
	timecnt++;
	if (timecnt % intervel == 0) {
		if (v <= -initV)
			v = initV;
		ballH += v;
		v -= rV;
	}

	glBindTexture(GL_TEXTURE_2D, textureIndex);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	glPushMatrix();
	glTranslated(x, -4.7 + ballH, z);
	glutSolidSphere(0.3, 36.0, 36.0);
	glPopMatrix();

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
}

void drawCarpet(int textureIndex) {
	glBindTexture(GL_TEXTURE_2D, textureIndex);
	clipSize = 1.0;
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-5.0, 0.02, -5.0);
	glTexCoord2f(0.0, clipSize); glVertex3f(-5.0, 0.02, 0.0);
	glTexCoord2f(clipSize, clipSize); glVertex3f(0.0, 0.02, 0.0);
	glTexCoord2f(clipSize, 0.0); glVertex3f(0.0, 0.02, -5.0);
	glEnd();
}

void drawStairs(int textureIndex) {
	glBindTexture(GL_TEXTURE_2D, textureIndex);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	for (int i = 0; i < 5; i++) {
		glPushMatrix();
		glTranslated(0.5 + i * 0.7, -0.5 - i, 3.75);
		glScaled(1.0, 1.0, 2.5);
		glutSolidCube(1);
		glPopMatrix();
	}

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
}

void drawEnclosure(int textureIndex) {
	//柱子
	glBindTexture(GL_TEXTURE_2D, textureIndex);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	for (int i = 0; i < 6; i++) {
		glPushMatrix();
		glTranslated(-0.1, 0.75, -4.8 + i * 1.4);
		glScalef(0.2, 1.5, 0.2);
		glutSolidCube(1);
		glPopMatrix();
	}

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	//围栏
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//透明

	glPushMatrix();
	glTranslated(-0.1, 0.65, -1.4);
	glScalef(0.16, 1.3, 7);
	glColor4f(1.0, 1.0, 1.0, 0.8);
	glutSolidCube(1);
	glPopMatrix();

	glDisable(GL_BLEND);
}

void drawComputer(int textureIndex) {
	glBindTexture(GL_TEXTURE_2D, textureIndex);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	glPushMatrix();
	glTranslated(3.93, -3.4, -2.1);
	glRotated(-90.0, 0, 1.0, 0);
	glScalef(0.1, 0.1, 0.1);
	computerObj.Draw();
	glPopMatrix();

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
}

void drawDesk(int textureIndex) {
	glBindTexture(GL_TEXTURE_2D, textureIndex);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	glPushMatrix();
	glTranslated(3.93, -4.2, -1.5);
	glRotated(-90.0, 0, 1.0, 0);
	glScalef(0.1, 0.1, 0.1);
	deskObj.Draw();
	glTranslated(-10.0, 2, 20.0);
	chairObj.Draw();
	glPopMatrix();

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
}

void drawDoor(int textureIndex) {
	//门框
	glBindTexture(GL_TEXTURE_2D, 20);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	glPushMatrix();
	glTranslated(-5.0, -3.25, 3.0);
	glScalef(0.3, 3.5, 2.0);
	glutSolidCube(1);
	glPopMatrix();

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);

	//门面里
	glBindTexture(GL_TEXTURE_2D, textureIndex);
	clipSize = 1.0;
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-4.84, -5.0, 4.0);
	glTexCoord2f(0.0, clipSize); glVertex3f(-4.84, -1.5, 4.0);
	glTexCoord2f(clipSize, clipSize); glVertex3f(-4.84, -1.5, 2.0);
	glTexCoord2f(clipSize, 0.0); glVertex3f(-4.84, -5, 2.0);
	glEnd();
	//门面外
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-5.16, -5.0, 4.0);
	glTexCoord2f(0.0, clipSize); glVertex3f(-5.16, -1.5, 4.0);
	glTexCoord2f(clipSize, clipSize); glVertex3f(-5.16, -1.5, 2.0);
	glTexCoord2f(clipSize, 0.0); glVertex3f(-5.16, -5, 2.0);
	glEnd();
}

void drawPaint(int textureIndex) {
	glBindTexture(GL_TEXTURE_2D, 20);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	glPushMatrix();
	glTranslated(2.5, 1, -4.9);
	glScalef(1, 1, 0.05);
	glutSolidCube(3);
	glPopMatrix();

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);

	glBindTexture(GL_TEXTURE_2D, textureIndex);
	clipSize = 1.0;
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(1, -0.5, -4.82);
	glTexCoord2f(0.0, clipSize); glVertex3f(1, 2.5, -4.82);
	glTexCoord2f(clipSize, clipSize); glVertex3f(4, 2.5, -4.82);
	glTexCoord2f(clipSize, 0.0); glVertex3f(4, -0.5, -4.82);
	glEnd();
}

void drawWindow() {
	glEnable(GL_BLEND);
	glColor4f(0.6, 0.6, 0.8, 0.3);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPushMatrix();
	glTranslated(5.0, 0.0, 0.0);
	glScaled(0.2, 4, 6);
	glutSolidCube(1);
	glPopMatrix();

	glDisable(GL_BLEND);
}

void drawCeiling(int textureIndex) {
	glPushMatrix();
	glTranslated(0, 5.0, 0);
	glScalef(10, 0.2, 10);
	glutSolidCube(1);
	glPopMatrix();
}

void drawCurtain(int textureIndex) {
	glBindTexture(GL_TEXTURE_2D, textureIndex);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	glPushMatrix();
	glTranslated(5.28, -1.5, 0.15);
	glScalef(0.2, 0.2, 0.2);
	//deskObj.Draw();
	curtainoffObj.Draw();
	glPopMatrix();

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
}

void drawFloorlamp(int textureIndex) {
	glBindTexture(GL_TEXTURE_2D, textureIndex);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	glPushMatrix();
	glTranslated(-4, 0, 4);
	glScalef(0.1, 0.1, 0.1);
	floorlampObj.Draw();
	glPopMatrix();

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
}

void drawAirconditioner(int textureIndex) {
	glBindTexture(GL_TEXTURE_2D, textureIndex);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	glPushMatrix();
	glTranslated(2.5, 4.0, -4.7);
	glScalef(0.1, 0.1, 0.1);
	airconditioner.Draw();
	glPopMatrix();

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
}

void drawTree(int textureIndex1, int textureIndex2) {
	glBindTexture(GL_TEXTURE_2D, textureIndex1);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	glPushMatrix();
	glTranslated(0, -5.05, 3);
	glScalef(0.1, 0.1, 0.1);
	treebottom.Draw();
	glPopMatrix();

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);

	//植物
	glBindTexture(GL_TEXTURE_2D, textureIndex2);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	glPushMatrix();
	glTranslated(0, -3, 3);
	glScalef(0.5, 0.8, 0.5);
	glutSolidSphere(1, 10, 10);
	glPopMatrix();

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
}

void drawClock(int textureIndex) {
	glBindTexture(GL_TEXTURE_2D, textureIndex);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	glPushMatrix();
	glTranslated(3.0, 1.5, 4.8);
	glRotatef(90, 0, 1, 0);
	glScalef(0.1, 0.1, 0.1);
	myClock.Draw();
	glPopMatrix();

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
}

void drawBookshelf(int textureIndex) {
	glPushMatrix();
	//bookshelf
	glBindTexture(GL_TEXTURE_2D, textureIndex);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	glTranslated(-4.6, 2.0, 0.0);
	glRotatef(90, 0, 1, 0);
	glScalef(0.1, 0.1, 0.1);
	bookshelf.Draw();

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	//books1
	glBindTexture(GL_TEXTURE_2D, 23);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	books1.Draw();

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	//books2
	glBindTexture(GL_TEXTURE_2D, 24);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	books2.Draw();

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	//books3
	glBindTexture(GL_TEXTURE_2D, 25);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	books3.Draw();

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);

	glPopMatrix();
}

void axis() {
	glPushMatrix();
	glTranslated(0, 0, 0);
	glLineWidth(2);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(2.0, 0.0, 0.0);
	glEnd();
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 2.0, 0.0);
	glEnd();
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 2.0);
	glEnd();
	glPopMatrix();
	glutSolidSphere(0.1, 36.0, 36.0);
	glColor3f(1.0, 1.0, 1.0);
}



void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-gloSize, gloSize, -gloSize * (GLfloat)h / (GLfloat)w, gloSize * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
	else
		glOrtho(-gloSize * (GLfloat)w / (GLfloat)h, gloSize * (GLfloat)w / (GLfloat)h, -gloSize, gloSize, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'd':
		disH += stride;
		break;
	case 'a':
		disH -= stride;
		break;
	case 'w':
		disV += stride;
		break;
	case 's':
		disV -= stride;
		break;
	case 'r':
		if (1 == viewPos)
			reset(8.5);
		else
			reset(5.5);
		break;
	case 'l':
		if (lightOpen) {
			glDisable(GL_LIGHTING);
			lightOpen = false;
		}
		else if (!lightOpen) {
			glEnable(GL_LIGHTING);
			lightOpen = true;
		}
		break;
	case '1':
		viewPos = 1;
		reset(8.5);
		break;
	case '2':
		viewPos = 2;
		reset(5.5);
		break;
	case '3':
		viewPos = 3;
		reset(5.5);
		break;
	case '4':
		viewPos = 4;
		reset(5.5);
		break;
	case '5':
		viewPos = 5;
		break;
	default:
		break;
	}
	changeView();
}

void changeView() {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat a = -gloSize + disH;
	GLfloat b = gloSize + disH;
	GLfloat c = -gloSize + disV;
	GLfloat d = gloSize + disV;
	if (w <= h)
		glOrtho(a, b, c * (GLfloat)h / (GLfloat)w, d * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
	else
		glOrtho(a * (GLfloat)w / (GLfloat)h, b * (GLfloat)w / (GLfloat)h, -2.0, 2.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
}

void mouse(int btn, int state, int x, int y) {
	//防止右键菜单后触发位移操作
	if (state == GLUT_DOWN)
		isDown = true;
	else if (state == GLUT_UP)
		isDown = false;

	if (state == GLUT_UP && btn == GLUT_WHEEL_UP && gloSize < 10.0)
		gloSize += stride;
	else if (state == GLUT_UP && btn == GLUT_WHEEL_DOWN && gloSize > 1.0)
		gloSize -= stride;
	else if (state == GLUT_DOWN && btn == GLUT_LEFT_BUTTON) {
		oldPosX = x;
		oldPosY = y;
	}
	myScale();
}

void myScale() {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat a = -gloSize + disH;
	GLfloat b = gloSize + disH;
	GLfloat c = -gloSize + disV;
	GLfloat d = gloSize + disV;
	if (w <= h)
		glOrtho(a, b, c * (GLfloat)h / (GLfloat)w, d * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
	else
		glOrtho(a * (GLfloat)w / (GLfloat)h, b * (GLfloat)w / (GLfloat)h, -2.0, 2.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
}

void changeViewPoint(int x, int y) {
	if (isDown) {
		int temp = x - oldPosX;
		degree += temp;
		temp = y - oldPosY;
		if (degree2 <= 90 && degree2 >= -45)
			degree2 += temp;
		if (degree2 > 90)
			degree2 = 90;
		else if (degree2 < -45)
			degree2 = -45;
		oldPosX = x;
		oldPosY = y;
	}
}

void refresh() {
	glutPostRedisplay();//实时运动
}

//初始化材质特性、光源、光照模型和深度缓冲区
void lightInit()
{
	GLfloat light0_postion[] = { 10.0, 50.0, -10.0, 1.0 };
	GLfloat light0_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light0_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light0_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat amb[] = { 0.6, 0.6, 0.6, 1.0 };

	GLfloat spot_direction[] = { -10.0, -50.0 , 10.0 };

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);

	glLightfv(GL_LIGHT0, GL_POSITION, light0_postion);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);

	GLfloat gray[] = { 0.80f, 0.80f, 0.80f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);

	/*glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 50.0);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);*/

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

//读取导入的纹理
AUX_RGBImageRec* LoadBMP(const char* Filename) //载入位图图像
{
	FILE* File = NULL;                             //文件句柄
	if (!Filename)                                //确保文件名已提供
	{
		return NULL;
	}
	File = fopen(Filename, "r");                   //尝试打开文件
	if (File)
	{
		fclose(File);                            //关闭文件
		return auxDIBImageLoadA(Filename);       //载入位图并返回指针
	}
	return NULL;                              //如果载入失败，返回NULL
}

int LoadGLTextures()  //载入位图并转换成纹理
{
	int Status = FALSE;                         //状态指示器
	const int filenum = sizeof(filepaths) / sizeof(filepaths[0]);
	AUX_RGBImageRec* TextureImage[filenum];         //创建纹理的存储空间
	memset(TextureImage, 0, sizeof(void*) * 1);//初始化
//载入位图，检查有无错误，如果位图没找到则退出
	for (int i = 0; i < filenum; i++) {
		if (TextureImage[i] = LoadBMP(filepaths[i]))
		{
			Status = TRUE;
			//使用来自位图数据生成的纹理
			glBindTexture(GL_TEXTURE_2D, i);
			//指定二维纹理
			glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[i]->sizeX, TextureImage[i]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[i]->data);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
			glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		}

		if (TextureImage[i])               //纹理是否存在
		{
			if (TextureImage[i]->data)     //纹理图像是否存在
			{
				free(TextureImage[i]->data);      //释放纹理图像占用的内存
			}
			free(TextureImage[i]);        //释放图像结构
		}
	}

	return Status;                   //返回Status
}

void reset(GLfloat gs) {
	degree = 45;
	degree2 = 45;
	disH = 0.0;
	disV = 0.0;
	gloSize = gs;
}

void guide() {
	cout << "___________________操作指南___________________" << endl << endl;
	cout << " 1.转换视角: 1 2 3 4 5" << endl;
	cout << " 2.重置视角: R" << endl;
	cout << " 3.开启光照: L" << endl;
	cout << " 4.调整位置: W A S D" << endl;
	cout << " 5.鼠标调整视角" << endl;
	cout << " 6.右键呼出菜单调整材质和灯光效果以及重置材质" << endl;
	cout << "______________________________________________" << endl;

}
