#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "func.h"
#include "menu.h"


void main(int argc, char** argv) {
	InitWindow(argc, argv);
	myCreateMenu();
	guide();

	//获取材质
	LoadGLTextures();

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(changeViewPoint);
	//glutPassiveMotionFunc(changeViewPoint);
	glutIdleFunc(refresh);
	glutMainLoop();
}
