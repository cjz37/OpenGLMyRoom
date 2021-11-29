#pragma once
#include "param.h"

GLsizei winWidth = 400, winHeight = 400;
GLfloat red = 1.0, green = 1.0, blue = 1.0;
GLenum renderingMode = GL_SMOOTH;

void mainMenu(GLint mainOption) {
	switch (mainOption) {
	case 1:
		wallStyle = 9,
		floorStyle = 0,
		doorStyle = 17,
		wardrobeStyle = 14,
		carpetStyle = 13,
		stairsStyle = 0,
		paintStyle = 6;
		break;
	default:
		break;
	}
}

void textureSubMenu(GLint textureOption) {
	
}

void lightSubMenu(GLint lightOption) {
	switch (lightOption) {
	case 1:
		red = 0.0, green = 0.0, blue = 1.0;
		break;
	case 2:
		red = 0.0, green = 1.0, blue = 0.0;
		break;
	default:
		break;
	}
}

void wallSubMenu(GLint styleIndex) {
	switch (styleIndex)
	{
	case 1:
		wallStyle = 8;
		break;
	case 2:
		wallStyle = 9;
		break;
	case 3:
		wallStyle = 10;
		break;
	case 4:
		wallStyle = 11;
		break;
	default:
		break;
	}
}

void floorSubMenu(GLint styleIndex) {
	switch (styleIndex)
	{
	case 1:
		floorStyle = 0;
		break;
	case 2:
		floorStyle = 1;
		break;
	case 3:
		floorStyle = 2;
		break;
	case 4:
		floorStyle = 3;
		break;
	case 5:
		floorStyle = 4;
		break;
	default:
		break;
	}
}

void doorSubMenu(GLint styleIndex) {
	switch (styleIndex)
	{
	case 1:
		doorStyle = 17;
		break;
	case 2:
		doorStyle = 18;
		break;
	case 3:
		doorStyle = 19;
		break;
	default:
		break;
	}
}

void wardrobeSubMenu(GLint styleIndex) {
	switch (styleIndex)
	{
	case 1:
		wardrobeStyle = 14;
		break;
	case 2:
		wardrobeStyle = 0;
		break;
	case 3:
		wardrobeStyle = 1;
		break;
	case 4:
		wardrobeStyle = 20;
		break;
	default:
		break;
	}
}

void carpetSubMenu(GLint styleIndex) {
	switch (styleIndex)
	{
	case 1:
		carpetStyle = 13;
		break;
	case 2:
		carpetStyle = 16;
		break;
	default:
		break;
	}
}

void stairsSubMenu(GLint styleIndex) {
	switch (styleIndex)
	{
	case 1:
		stairsStyle = 0;
		break;
	case 2:
		stairsStyle = 1;
		break;
	case 3:
		stairsStyle = 2;
		break;
	case 4:
		stairsStyle = 3;
		break;
	case 5:
		stairsStyle = 4;
		break;
	default:
		break;
	}
}

void paintSubMenu(GLint styleIndex) {
	switch (styleIndex)
	{
	case 1:
		paintStyle = 5;
		break;
	case 2:
		paintStyle = 6;
		break;
	case 3:
		paintStyle = 7;
		break;
	default:
		break;
	}
}

void myCreateMenu() {
	GLint subMenu1, subMenu2;
	GLint wall, floor, door, wardrobe, carpet, stairs, paint;

	wall = glutCreateMenu(wallSubMenu);
	glutAddMenuEntry("Style 1", 1);
	glutAddMenuEntry("Style 2", 2);
	glutAddMenuEntry("Style 3", 3);
	glutAddMenuEntry("Style 4", 4);

	floor = glutCreateMenu(floorSubMenu);
	glutAddMenuEntry("Style 1", 1);
	glutAddMenuEntry("Style 2", 2);
	glutAddMenuEntry("Style 3", 3);
	glutAddMenuEntry("Style 4", 4);
	glutAddMenuEntry("Style 5", 5);

	door = glutCreateMenu(doorSubMenu);
	glutAddMenuEntry("Style 1", 1);
	glutAddMenuEntry("Style 2", 2);
	glutAddMenuEntry("Style 3", 3);

	wardrobe = glutCreateMenu(wardrobeSubMenu);
	glutAddMenuEntry("Style 1", 1);
	glutAddMenuEntry("Style 2", 2);
	glutAddMenuEntry("Style 3", 3);
	glutAddMenuEntry("Style 4", 4);

	carpet = glutCreateMenu(carpetSubMenu);
	glutAddMenuEntry("Style 1", 1);
	glutAddMenuEntry("Style 2", 2);

	stairs = glutCreateMenu(stairsSubMenu);
	glutAddMenuEntry("Style 1", 1);
	glutAddMenuEntry("Style 2", 2);
	glutAddMenuEntry("Style 3", 3);
	glutAddMenuEntry("Style 4", 4);
	glutAddMenuEntry("Style 5", 5);

	paint = glutCreateMenu(paintSubMenu);
	glutAddMenuEntry("Style 1", 1);
	glutAddMenuEntry("Style 2", 2);
	glutAddMenuEntry("Style 3", 3);

	subMenu1 = glutCreateMenu(textureSubMenu);
	glutAddSubMenu("Wall", wall);
	glutAddSubMenu("Floor", floor);
	glutAddSubMenu("Door", door);
	glutAddSubMenu("Wardrobe", wardrobe);
	glutAddSubMenu("Carpet", carpet);
	glutAddSubMenu("Stairs", stairs);
	glutAddSubMenu("paint", paint);

	subMenu2 = glutCreateMenu(lightSubMenu);
	glutAddMenuEntry("on", 0);
	glutAddMenuEntry("off", 1);

	glutCreateMenu(mainMenu);
	glutAddSubMenu("Texture", subMenu1);
	glutAddSubMenu("Light", subMenu2);
	glutAddMenuEntry("Reset", 1);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}