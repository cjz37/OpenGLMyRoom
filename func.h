#pragma once

#include <stdlib.h>
#include <iostream>
#include <string>
#include <GL/glaux.h>
#include <cstdio>
#include <string>
#include <vector>
#include "param.h"
//#include "objLoader.h"

#pragma warning(disable:4996)

#define GLUT_WHEEL_UP 3
#define GLUT_WHEEL_DOWN 4

using namespace std;

void display();
void reshape(int w, int h);
void lightInit();
void InitWindow(int argc, char** argv);
void refresh();

AUX_RGBImageRec* LoadBMP(const char* Filename);
int LoadGLTextures();

void axis();
void drawBed(GLfloat x, GLfloat z, int textureIndex1, int textureIndex2, int textureIndex3);
void drawFloor(int fn, int textureIndex);
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
//void drawDesk(int textureIndex);
void drawDoor(int textureIndex);
void drawPaint(int textureIndex);
void drawWindow();
void drawCeiling(int textureIndex);

void keyboard(unsigned char key, int x, int y);
void changeView();
void mouse(int btn, int state, int x, int y);
void myScale();
void changeViewPoint(int x, int y);
void reset();

//ObjLoader desk = ObjLoader("Res/moudel/desk.obj");

void InitWindow(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
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
	glShadeModel(GL_FLAT);
	glDepthFunc(GL_LESS);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	//lightInit();

	//�ӽǱ任
	if (1 == viewPos)
		gluLookAt(1.0 * cos(c * degree), 1.0 * sin(c * degree2), 1.0 * sin(c * degree), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	else if (2 == viewPos)
		gluLookAt(0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	else if (3 == viewPos)
		gluLookAt(1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	else if (4 == viewPos)
		gluLookAt(0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0);

	//�� x; �� y; �� z
	axis();
	drawFloor(2, floorStyle);
	drawWall(wallStyle);
	drawBed(-2.5, -2.9, 15, 1, 16);
	drawWardrobe(-3.6, -4.0, wardrobeStyle, 1);
	drawBall(1.0, -3.0, 12);
	drawCarpet(carpetStyle);
	drawStairs(stairsStyle);
	drawEnclosure(0);
	//drawDesk(0);
	drawDoor(doorStyle);
	drawPaint(paintStyle);
	drawWindow();
	

	glFlush();
	glutSwapBuffers();
}

void drawBed(GLfloat x, GLfloat z, int textureIndex1, int textureIndex2, int textureIndex3) {
	//����
	glBindTexture(GL_TEXTURE_2D, textureIndex1);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	glPushMatrix();
	glTranslated(x, 0.15, z);
	glScalef(3, 0.6, 4);
	glutSolidCube(1);
	glPopMatrix();

	//��ͷ��
	glPushMatrix();
	glTranslated(x + 1.9, 0.15, z - 1.55);
	glScaled(0.8, 0.6, 0.8);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x - 1.9, 0.15, z - 1.55);
	glScaled(0.8, 0.6, 0.8);
	glutSolidCube(1);
	glPopMatrix();

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);

	//��ͷ
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

	//�ޱ�
	glBindTexture(GL_TEXTURE_2D, textureIndex3);
	clipSize = 8.0;
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-4.0, 0.46, -4.7);
	glTexCoord2f(0.0, clipSize); glVertex3f(-4.0, 0.46, -0.9);
	glTexCoord2f(clipSize, clipSize); glVertex3f(-1.0, 0.46, -0.9);
	glTexCoord2f(clipSize, 0.0); glVertex3f(-1.0, 0.46, -4.7);
	glEnd();

}

void drawFloor(int fn, int textureIndex) {
	glBindTexture(GL_TEXTURE_2D, textureIndex);
	if (degree2 >= 0) {
		if (1 == fn) {
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
		}
		else if (2 == fn) {
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
	else if (degree2 < 0) {
		//ceiling
		drawCeiling(0);
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
	//����
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
	//����
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
	//����
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-5.0, -5.0, 4.89);
	glTexCoord2f(0.0, clipSize); glVertex3f(-5.0, 5.0, 4.89);
	glTexCoord2f(clipSize, clipSize); glVertex3f(5.0, 5.0, 4.89);
	glTexCoord2f(clipSize, 0.0); glVertex3f(5.0, -5.0, 4.89);
	glEnd();
}

void drawWardrobe(int x, int z, int textureIndex1, int textureIndex2) {
	//����
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

	//����
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
	glBindTexture(GL_TEXTURE_2D, textureIndex);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	glPushMatrix();
	glTranslated(x, -4.7, z);
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
	//����
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
	//Χ��
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//͸��

	glPushMatrix();
	glTranslated(-0.1, 0.65, -1.4);
	glScalef(0.16, 1.3, 7);
	glColor4f(1.0, 1.0, 1.0, 0.8);
	glutSolidCube(1);
	glPopMatrix();

	glDisable(GL_BLEND);
}

//void drawDesk(int textureIndex) {
//	glPushMatrix();
//	glTranslated(0.0, 0.0, 0.0);
//	desk.Draw();
//	glPopMatrix();
//}

void drawDoor(int textureIndex) {
	//�ſ�
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
	
	//������
	glBindTexture(GL_TEXTURE_2D, textureIndex);
	clipSize = 1.0;
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-4.84, -5.0, 4.0);
	glTexCoord2f(0.0, clipSize); glVertex3f(-4.84, -1.5, 4.0);
	glTexCoord2f(clipSize, clipSize); glVertex3f(-4.84, -1.5, 2.0);
	glTexCoord2f(clipSize, 0.0); glVertex3f(-4.84, -5, 2.0);
	glEnd();
	//������
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
		reset();
	case '1':
		viewPos = 1;
		degree = 45;
		degree2 = 45;
		break;
	case '2':
		viewPos = 2;
		break;
	case '3':
		viewPos = 3;
		break;
	case '4':
		viewPos = 4;
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
	//��ֹ�Ҽ��˵��󴥷�λ�Ʋ���
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
		//cout << "degree = " << degree << " " << "k = " << (degree % 360) << endl;
	}
}

void refresh() {
	glutPostRedisplay();//ʵʱ�˶�
}

//��ʼ���������ԡ���Դ������ģ�ͺ���Ȼ�����
void lightInit()
{
	GLfloat mat_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat mat_diffuse[] = { 0.8, 0.2, 0.2, 1.0 };
	GLfloat mat_specular[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };

	GLfloat light1_ambient[] = { 0.0, 0.0, 0.0, 1.0 };  //������
	GLfloat light1_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };  //������
	GLfloat light1_specular[] = { 0.2, 0.1, 0.1, 1.0 };  //���淴��
	GLfloat light1_position[] = { -5.0, 5.0, 5.0, 1.0 };

	GLfloat light2_ambient[] = { 0.5, 0.5, 0.5, 1.0 };  //������
	GLfloat light2_diffuse[] = { 0.8, 0.2, 0.2, 1.0 };  //������
	GLfloat light2_specular[] = { 1.0, 1.0, 1.0, 1.0 };  //���淴��
	GLfloat light2_position[] = { 5.0, 0.0, 0.0, 1.0 };

	GLfloat light3_ambient[] = { 0.5, 0.5, 0.1, 1.0 };  //������
	GLfloat light3_diffuse[] = { 0.5, 0.5, 0.1, 1.0 };  //������
	GLfloat light3_specular[] = { 0.2, 0.2, 0.1, 1.0 };  //���淴��
	GLfloat light3_position[] = { 5.0, -10.0, -6.0, 1.0 };


	GLfloat spot_direction[] = { 5.0, -5.0, -5.0 };


	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

	glLightfv(GL_LIGHT2, GL_AMBIENT, light2_ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light2_specular);
	glLightfv(GL_LIGHT2, GL_POSITION, light2_position);

	glLightfv(GL_LIGHT3, GL_AMBIENT, light3_ambient);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, light3_diffuse);
	glLightfv(GL_LIGHT3, GL_SPECULAR, light3_specular);
	glLightfv(GL_LIGHT3, GL_POSITION, light3_position);


	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, lightAngle);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);


	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
	//glEnable(GL_LIGHT2);
	//glEnable(GL_LIGHT3);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
}

//��ȡ���������
AUX_RGBImageRec* LoadBMP(const char* Filename) //����λͼͼ��
{
	FILE* File = NULL;                             //�ļ����
	if (!Filename)                                //ȷ���ļ������ṩ
	{
		return NULL;
	}
	File = fopen(Filename, "r");                   //���Դ��ļ�
	if (File)
	{
		fclose(File);                            //�ر��ļ�
		return auxDIBImageLoadA(Filename);       //����λͼ������ָ��
	}
	return NULL;                              //�������ʧ�ܣ�����NULL
}

int LoadGLTextures()  //����λͼ��ת��������
{
	int Status = FALSE;                         //״ָ̬ʾ��
	const int filenum = sizeof(filepaths) / sizeof(filepaths[0]);
	AUX_RGBImageRec* TextureImage[filenum];         //��������Ĵ洢�ռ�
	memset(TextureImage, 0, sizeof(void*) * 1);//��ʼ��
//����λͼ��������޴������λͼû�ҵ����˳�
	for (int i = 0; i < filenum; i++) {
		if (TextureImage[i] = LoadBMP(filepaths[i]))
		{
			Status = TRUE;
			//ʹ������λͼ�������ɵ�����
			glBindTexture(GL_TEXTURE_2D, i);
			//ָ����ά����
			glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[i]->sizeX, TextureImage[i]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[i]->data);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
			glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		}

		if (TextureImage[i])               //�����Ƿ����
		{
			if (TextureImage[i]->data)     //����ͼ���Ƿ����
			{
				free(TextureImage[i]->data);      //�ͷ�����ͼ��ռ�õ��ڴ�
			}
			free(TextureImage[i]);        //�ͷ�ͼ��ṹ
		}
	}

	return Status;                   //����Status
}

void reset() {
	degree = 45;
	degree2 = 45;
	disH = 0.0;
	disV = 0.0;
}