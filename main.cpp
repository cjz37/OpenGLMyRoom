#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <iostream>
#include <string>
#include <GL/glaux.h>
#include <cstdio>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#ifdef GL_VERSION_1_1
static GLuint texName;
#endif

#define GLUT_WHEEL_UP 3
#define GLUT_WHEEL_DOWN 4

#pragma warning(disable:4996)

using namespace std;

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
const char* filepaths[] = { "Res/texture/floor1.bmp", "Res/texture/floor2.bmp", "Res/texture/floor3.bmp", "Res/texture/floor4.bmp", "Res/texture/floor5.bmp", "Res/texture/paint1.bmp", "Res/texture/paint2.bmp", "Res/texture/paint3.bmp", "Res/texture/wall1.bmp", "Res/texture/wall2.bmp", "Res/texture/wall3.bmp", "Res/texture/wall4.bmp", "Res/texture/ball.bmp", "Res/texture/carpet.bmp", "Res/texture/wood1.bmp", "Res/texture/wood2.bmp", "Res/texture/quilt.bmp"};


void axis();
void drawBed(GLfloat x, GLfloat z, int textureIndex1, int textureIndex2, int textureIndex3);
void drawFloor(int fn, int textureIndex);
void display();
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);
void changeView();
void lightInit();
void mouse(int btn, int state, int x, int y);
void myScale();
void drawWall(int textureIndex);
void drawWardrobe(int x, int z, int textureIndex1, int textureIndex2);
void drawBall(int x, int z, int textureIndex);
void drawCarpet(int textureIndex);
void drawStairs(int textureIndex);
void drawEnclosure(int textureIndex);
void drawDesk(int textureIndex);
void drawDoor(int textureIndex);
AUX_RGBImageRec* LoadBMP(const char* Filename);
int LoadGLTextures();
void InitWindow(int argc, char** argv);
void changeViewPoint(int x, int y);

class ObjLoader
{
public:
	struct vertex
	{
		float x;
		float y;
		float z;
	};
	ObjLoader(string filename);//读取函数
	void Draw();//绘制函数
private:
	vector<vector<GLfloat>> v;//存放顶点(x,y,z)坐标
	vector<vector<GLint>> f;//存放面的三个顶点索引
};

ObjLoader::ObjLoader(string filename)
{
	ifstream file(filename);
	string line;
	while (getline(file, line))
	{
		if (line.substr(0, 1) == "v")
		{
			vector<GLfloat> Point;
			GLfloat x, y, z;
			istringstream s(line.substr(2));
			s >> x; s >> y; s >> z;
			Point.push_back(x);
			Point.push_back(y);
			Point.push_back(z);
			v.push_back(Point);

		}
		else if (line.substr(0, 1) == "f")
		{
			vector<GLint> vIndexSets;
			GLint u, v, w;
			istringstream vtns(line.substr(2));
			vtns >> u; vtns >> v; vtns >> w;
			vIndexSets.push_back(u - 1);
			vIndexSets.push_back(v - 1);
			vIndexSets.push_back(w - 1);
			f.push_back(vIndexSets);
		}
	}
	file.close();
}

void ObjLoader::Draw() {
	glBegin(GL_TRIANGLES);//开始绘制
	for (int i = 0; i < f.size(); i++) {
		GLfloat VN[3];//法线
		//三个顶点
		vertex a, b, c, normal;

		if ((f[i]).size() != 3) {
			cout << "ERRER::THE SIZE OF f IS NOT 3!" << endl;
		}
		else {
			GLint firstVertexIndex = (f[i])[0];//取出顶点索引
			GLint secondVertexIndex = (f[i])[1];
			GLint thirdVertexIndex = (f[i])[2];

			a.x = (v[firstVertexIndex])[0];//第一个顶点
			a.y = (v[firstVertexIndex])[1];
			a.z = (v[firstVertexIndex])[2];

			b.x = (v[secondVertexIndex])[0]; //第二个顶点
			b.y = (v[secondVertexIndex])[1];
			b.z = (v[secondVertexIndex])[2];

			c.x = (v[thirdVertexIndex])[0]; //第三个顶点
			c.y = (v[thirdVertexIndex])[1];
			c.z = (v[thirdVertexIndex])[2];


			GLfloat vec1[3], vec2[3], vec3[3];//计算法向量
			//(x2-x1,y2-y1,z2-z1)
			vec1[0] = a.x - b.x;
			vec1[1] = a.y - b.y;
			vec1[2] = a.z - b.z;

			//(x3-x2,y3-y2,z3-z2)
			vec2[0] = a.x - c.x;
			vec2[1] = a.y - c.y;
			vec2[2] = a.z - c.z;

			//(x3-x1,y3-y1,z3-z1)
			vec3[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
			vec3[1] = vec2[0] * vec1[2] - vec2[2] * vec1[0];
			vec3[2] = vec2[1] * vec1[0] - vec2[0] * vec1[1];

			GLfloat D = sqrt(pow(vec3[0], 2) + pow(vec3[1], 2) + pow(vec3[2], 2));

			VN[0] = vec3[0] / D;
			VN[1] = vec3[1] / D;
			VN[2] = vec3[2] / D;

			glNormal3f(VN[0], VN[1], VN[2]);//绘制法向量

			glVertex3f(a.x, a.y, a.z);//绘制三角面
			glVertex3f(b.x, b.y, b.z);
			glVertex3f(c.x, c.y, c.z);
		}
	}
	glEnd();
}


void main(int argc, char** argv) {
	InitWindow(argc, argv);
	//获取材质
	LoadGLTextures();

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(changeViewPoint);
	//glClearColor(0.0, 0.0, 0.0, 1.0);
	//glColor3f(1.0, 1.0, 1.0);
	glutMainLoop();
}

void InitWindow(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(w, h);
	glutCreateWindow("my room");
}

ObjLoader desk = ObjLoader("Res/moudel/desk.obj");

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

	if (1 == viewPos)
		gluLookAt(1.0 * cos(c * degree), 1.0 * sin(c * degree2), 1.0 * sin(c * degree), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	else if (2 == viewPos)
		gluLookAt(0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	else if (3 == viewPos)
		gluLookAt(1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	else if (4 == viewPos)
		gluLookAt(0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0);

	drawFloor(2, 0);
	drawWall(9);
	drawBed(-2.5, -3.0, 15, 1, 16);
	drawWardrobe(-3.6, -4, 14, 1);
	drawBall(1.0, -3.0, 12);
	drawCarpet(13);
	drawStairs(0);
	drawEnclosure(0);
	//drawDesk(0);
	
	axis();

	glFlush();
	glutSwapBuffers();
}

void drawBed(GLfloat x, GLfloat z, int textureIndex1, int textureIndex2, int textureIndex3) {
	//床身
	glBindTexture(GL_TEXTURE_2D, textureIndex1);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	glPushMatrix();
	glTranslated(x, 0.15, z);
	glScalef(3, 0.6, 4);
	glutSolidCube(1);
	glPopMatrix();

	//床头柜
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
	
	//床头
	glBindTexture(GL_TEXTURE_2D, textureIndex2);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	glPushMatrix();
	glTranslated(x, 0.55, z - 1.8);
	glScalef(3.1, 1.5, 0.3);
	glutSolidCube(1);
	glPopMatrix();

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);

	//棉被
	glBindTexture(GL_TEXTURE_2D, textureIndex3);
	clipSize = 8.0;
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-4.0, 0.46, -4.7);
	glTexCoord2f(0.0, clipSize); glVertex3f(-4.0, 0.46, -1.0);
	glTexCoord2f(clipSize, clipSize); glVertex3f(-1.0, 0.46, -1.0);
	glTexCoord2f(clipSize, 0.0); glVertex3f(-1.0, 0.46, -4.7);
	glEnd();

}

void drawFloor(int fn, int textureIndex) {
	glBindTexture(GL_TEXTURE_2D, textureIndex);
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
	else {
		//no floor
	}
	
}

void drawWall(int textureIndex) {
	//left
	glPushMatrix();
	glTranslated(-5.0, 0, 0);
	glScalef(0.2, 10, 10);
	glutSolidCube(1);
	glPopMatrix();
	//right
	glPushMatrix();
	glTranslated(0, 0, -5.0);
	glScalef(10, 10, 0.2);
	glutSolidCube(1);
	glPopMatrix();

	clipSize = 2.0;
	glBindTexture(GL_TEXTURE_2D, textureIndex);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-4.89, -5.0, 5.0);
	glTexCoord2f(0.0, clipSize); glVertex3f(-4.89, 5.0, 5.0);
	glTexCoord2f(clipSize, clipSize); glVertex3f(-4.89, 5.0, -5.0);
	glTexCoord2f(clipSize, 0.0); glVertex3f(-4.89, -5.0, -5.0);
	glEnd();

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-5.0, -5.0, -4.89);
	glTexCoord2f(0.0, clipSize); glVertex3f(-5.0, 5.0, -4.89);
	glTexCoord2f(clipSize, clipSize); glVertex3f(5.0, 5.0, -4.89);
	glTexCoord2f(clipSize, 0.0); glVertex3f(5.0, -5.0, -4.89);
	glEnd();
}

void drawWardrobe(int x, int z, int textureIndex1, int textureIndex2) {
	glBindTexture(GL_TEXTURE_2D, textureIndex1);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	glPushMatrix();
	glTranslated(x, -3.2, z);
	glScalef(1.8, 1.8, 1);
	glutSolidCube(2);
	glPopMatrix();

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);

	glBindTexture(GL_TEXTURE_2D, textureIndex2);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	glPushMatrix();
	glTranslated(-3.1, -3.2, -3.4);
	glScalef(0.08, 0.35, 1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-2.9, -3.2, -3.4);
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
		glTranslated(0.5+i*0.7, -0.5-i, 3.75);
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
		glTranslated(-0.1, 0.75, -4.8+i*1.4);
		glScalef(0.2, 1.5, 0.2);
		glutSolidCube(1);
		glPopMatrix();
	}

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	//围栏
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPushMatrix();
	glTranslated(-0.1, 0.65, -1.4);
	glScalef(0.16, 1.3, 7);
	glColor4f(1.0, 1.0, 1.0, 0.8);
	glutSolidCube(1);
	glPopMatrix();

	glDisable(GL_BLEND);
}

void drawDesk(int textureIndex) {
	glPushMatrix();
	glTranslated(0.0, 0.0, 0.0);
	desk.Draw();
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

	glutPostRedisplay();
}

void mouse(int btn, int state, int x, int y) {
	if (state == GLUT_UP && btn == GLUT_WHEEL_UP && gloSize < 10.0)
		gloSize += stride;
	else if (state == GLUT_UP && btn == GLUT_WHEEL_DOWN && gloSize > 1.0)
		gloSize -= stride;
	else if (state == GLUT_DOWN) {
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

	glutPostRedisplay();
}

void changeViewPoint(int x, int y) {
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

//初始化材质特性、光源、光照模型和深度缓冲区
void lightInit()
{
	GLfloat mat_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat mat_diffuse[] = { 0.8, 0.2, 0.2, 1.0 };
	GLfloat mat_specular[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };

	GLfloat light1_ambient[] = { 0.0, 0.0, 0.0, 1.0 };  //环境光
	GLfloat light1_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };  //漫反射
	GLfloat light1_specular[] = { 0.2, 0.1, 0.1, 1.0 };  //镜面反射
	GLfloat light1_position[] = { -5.0, 5.0, 5.0, 1.0 };

	GLfloat light2_ambient[] = { 0.5, 0.5, 0.5, 1.0 };  //环境光
	GLfloat light2_diffuse[] = { 0.8, 0.2, 0.2, 1.0 };  //漫反射
	GLfloat light2_specular[] = { 1.0, 1.0, 1.0, 1.0 };  //镜面反射
	GLfloat light2_position[] = { 5.0, 0.0, 0.0, 1.0 };

	GLfloat light3_ambient[] = { 0.5, 0.5, 0.1, 1.0 };  //环境光
	GLfloat light3_diffuse[] = { 0.5, 0.5, 0.1, 1.0 };  //漫反射
	GLfloat light3_specular[] = { 0.2, 0.2, 0.1, 1.0 };  //镜面反射
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