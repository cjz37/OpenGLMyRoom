#pragma once
#include <glm/glm.hpp>
#include "objLoader.h"

GLfloat disH = 0.0;
GLfloat disV = 0.0;
GLfloat stride = 1.5;
GLfloat gloSize = 8.5;
int w = 700;
int h = 700;
static GLfloat lightAngle = 90.0;
int viewPos = 1;
GLfloat clipSize = 1.0;
int oldPosX = 0;
int oldPosY = 0;
int degree = 45;
int degree2 = 45;
double c = 3.1415926 / 180.0f;
bool isDown = false;
const char* filepaths[] = { "Res/texture/floor1.bmp", "Res/texture/floor2.bmp", "Res/texture/floor3.bmp", "Res/texture/floor4.bmp", "Res/texture/floor5.bmp", "Res/texture/paint1.bmp", "Res/texture/paint2.bmp", "Res/texture/paint3.bmp", "Res/texture/wall1.bmp", "Res/texture/wall2.bmp", "Res/texture/wall3.bmp", "Res/texture/wall4.bmp", "Res/texture/ball.bmp", "Res/texture/carpet.bmp", "Res/texture/wood1.bmp", "Res/texture/wood2.bmp", "Res/texture/quilt.bmp", "Res/texture/door1.bmp", "Res/texture/door2.bmp", "Res/texture/door3.bmp", "Res/texture/doorframe.bmp", "Res/texture/black.bmp", "Res/texture/tree.bmp" }; //23
string moudelFilepaths[] = { "Res/moudel/moniter.obj", "Res/moudel/computer.obj", "Res/moudel/desk.obj", "Res/moudel/chair.obj", "Res/moudel/curtainoff.obj", "Res/moudel/curtainon.obj", "Res/moudel/floorlamp.obj", "Res/moudel/airconditioner.obj", "Res/moudel/treebottom.obj" }; //9

GLint wallStyle = 9,
floorStyle = 0,
doorStyle = 17,
wardrobeStyle = 14,
carpetStyle = 13,
stairsStyle = 0,
paintStyle = 6;

ObjLoader moniterObj = ObjLoader(moudelFilepaths[0]);
ObjLoader computerObj = ObjLoader(moudelFilepaths[1]);
ObjLoader deskObj = ObjLoader(moudelFilepaths[2]);
ObjLoader chairObj = ObjLoader(moudelFilepaths[3]);
ObjLoader curtainoffObj = ObjLoader(moudelFilepaths[4]);
ObjLoader curtainonObj = ObjLoader(moudelFilepaths[5]);
ObjLoader floorlampObj = ObjLoader(moudelFilepaths[6]);
ObjLoader airconditioner = ObjLoader(moudelFilepaths[7]);
ObjLoader treebottom = ObjLoader(moudelFilepaths[8]);
