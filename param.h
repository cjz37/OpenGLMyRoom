#pragma once

GLfloat disH = 0.0;
GLfloat disV = 0.0;
GLfloat stride = 1.5;
GLfloat gloSize = 10.0;
int w = 700;
int h = 700;
static GLfloat lightAngle = 90.0;
int viewPos = 1;
GLfloat clipSize = 1.0;
int oldPosX = 0;
int oldPosY = 0;
int degree = 45;
int degree2 = 45;
float c = 3.1415926 / 180.0f;
bool isDown = false;
const char* filepaths[] = { "Res/texture/floor1.bmp", "Res/texture/floor2.bmp", "Res/texture/floor3.bmp", "Res/texture/floor4.bmp", "Res/texture/floor5.bmp", "Res/texture/paint1.bmp", "Res/texture/paint2.bmp", "Res/texture/paint3.bmp", "Res/texture/wall1.bmp", "Res/texture/wall2.bmp", "Res/texture/wall3.bmp", "Res/texture/wall4.bmp", "Res/texture/ball.bmp", "Res/texture/carpet.bmp", "Res/texture/wood1.bmp", "Res/texture/wood2.bmp", "Res/texture/quilt.bmp", "Res/texture/door1.bmp", "Res/texture/door2.bmp", "Res/texture/door3.bmp", "Res/texture/doorframe.bmp" }; //21

GLint wallStyle = 9,
floorStyle = 0,
doorStyle = 17,
wardrobeStyle = 14,
carpetStyle = 13,
stairsStyle = 0,
paintStyle = 6;