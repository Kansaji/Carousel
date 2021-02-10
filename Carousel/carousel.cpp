#include<Windows.h>
#include<GL/glut.h>
#include<math.h>
#include <iostream>
#include<fstream>

using namespace std;
GLUquadricObj* qobj;

GLfloat rot = 0;
GLfloat rotChange = 0.0;
GLfloat hop = 0;
GLfloat hopChange =0 ;
GLfloat pitch = 0;
GLfloat pitchChange = 10;

GLfloat bulbChange = 0;
GLfloat bulbR = 0.1;
GLfloat bulbG = 0.1;
GLfloat bulbB = 0.1;
GLfloat lightingMode = 2;

GLfloat camX = -60.0;
GLfloat camY = 40.0;
GLfloat camZ = 150.0;

GLfloat sway = 0;
GLfloat swayChange = 0.2;

struct BitMapFile {
	int sizeX;
	int sizeY;
	unsigned char* data;
};

BitMapFile* getbmp(string filename)
{
	int offset, headerSize;

	// Initialize bitmap files for RGB (input) and RGBA (output).
	BitMapFile* bmpRGB = new BitMapFile;
	BitMapFile* bmpRGBA = new BitMapFile;

	// Read input bmp file name.
	ifstream infile(filename.c_str(), ios::binary);

	// Get starting point of image data in bmp file.
	infile.seekg(10);
	infile.read((char*)&offset, 4);

	// Get header size of bmp file.
	infile.read((char*)&headerSize, 4);

	// Get image width and height values from bmp file header.
	infile.seekg(18);
	infile.read((char*)&bmpRGB->sizeX, 4);
	infile.read((char*)&bmpRGB->sizeY, 4);

	// Determine the length of zero-byte padding of the scanlines 
	// (each scanline of a bmp file is 4-byte aligned by padding with zeros).
	int padding = (3 * bmpRGB->sizeX) % 4 ? 4 - (3 * bmpRGB->sizeX) % 4 : 0;

	// Add the padding to determine size of each scanline.
	int sizeScanline = 3 * bmpRGB->sizeX + padding;

	// Allocate storage for image in input bitmap file.
	int sizeStorage = sizeScanline * bmpRGB->sizeY;
	bmpRGB->data = new unsigned char[sizeStorage];

	// Read bmp file image data into input bitmap file.
	infile.seekg(offset);
	infile.read((char*)bmpRGB->data, sizeStorage);

	// Reverse color values from BGR (bmp storage format) to RGB.
	int startScanline, endScanlineImageData, temp;
	for (int y = 0; y < bmpRGB->sizeY; y++)
	{
		startScanline = y * sizeScanline; // Start position of y'th scanline.
		endScanlineImageData = startScanline + 3 * bmpRGB->sizeX; // Image data excludes padding.
		for (int x = startScanline; x < endScanlineImageData; x += 3)
		{
			temp = bmpRGB->data[x];
			bmpRGB->data[x] = bmpRGB->data[x + 2];
			bmpRGB->data[x + 2] = temp;
		}
	}

	// Set image width and height values and allocate storage for image in output bitmap file.
	bmpRGBA->sizeX = bmpRGB->sizeX;
	bmpRGBA->sizeY = bmpRGB->sizeY;
	bmpRGBA->data = new unsigned char[4 * bmpRGB->sizeX * bmpRGB->sizeY];

	// Copy RGB data from input to output bitmap files, set output A to 1.
	for (int j = 0; j < 4 * bmpRGB->sizeY * bmpRGB->sizeX; j += 4)
	{
		bmpRGBA->data[j] = bmpRGB->data[(j / 4) * 3];
		bmpRGBA->data[j + 1] = bmpRGB->data[(j / 4) * 3 + 1];
		bmpRGBA->data[j + 2] = bmpRGB->data[(j / 4) * 3 + 2];
		bmpRGBA->data[j + 3] = 0xFF;
	}

	return bmpRGBA;
}

static unsigned int texture[4];

void loadExternalTextures() {
	BitMapFile* image[4];
	image[0] = getbmp("C:/Users/ABC/Downloads/tex1.bmp");
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[0]->sizeX, image[0]->sizeY, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, image[0]->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

}


void initLighting() {
	GLfloat L0_Ambient[] = { 0.1,0.1,0.1,1.0 };
	GLfloat L0_Diffuse[] = { 1.0,1.0,1.0,1.0 };
	GLfloat L0_Specular[] = { 0.7,0.7,0.7,1.0 };
	GLfloat L0_position[] = { -20,20,100,1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, L0_Ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, L0_Diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, L0_Specular);
	glLightfv(GL_LIGHT0, GL_POSITION, L0_position);

	GLfloat L1_Ambient[] = { 0.1,0.1,0.1,1.0 };
	GLfloat L1_Diffuse[] = { 1.0,1.0,1.0,1.0 };
	GLfloat L1_Specular[] = { 0.7,0.7,0.7,1.0 };
	GLfloat L1_position[] = { -5,5,0,1.0 };
	glLightfv(GL_LIGHT1, GL_AMBIENT, L1_Ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, L1_Diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, L1_Specular);
	glLightfv(GL_LIGHT1, GL_POSITION, L1_position);
	

}
void init() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	GLfloat globalAmbient[] = { 0.1,0.1,0.1,1.0 };
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
	initLighting();
	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE);
	qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);

	glGenTextures(2, texture);
	loadExternalTextures();

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	
}

void roofSegment() {
	glPushMatrix();
	glColor3f(0.58, 0.15, 0.16);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(15 * cos(0.393), -4.0, 15 * sin(0.393));
	glVertex3f(15 * cos(0.393), -4.0, -15 * sin(0.393));
	glEnd();
	glPopMatrix();
}

void lightBulb(GLfloat r, GLfloat g, GLfloat b) {
	glPushMatrix();
	glDisable(GL_COLOR_MATERIAL);
	GLfloat Ambient[] = { r, g, b,1.0 };
	GLfloat Diffuse[] = { r, g, b,1.0 };
	GLfloat Specular[] = { r, g, b,1.0 };
	GLfloat Emmision[] = { b/10, g/10, b/10,1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, Ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, Emmision);

	glutSolidSphere(0.3, 50, 50);
	glTranslatef(0.0,-0.29, 0.0);
	glRotatef(90, 1, 0, 0);
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(0.5, 0.5, 0.5);
	gluCylinder(qobj, 0.2, 0.2, 0.5, 10, 1);

	glPopMatrix();	
}

void roof() {
	glPushMatrix();
	glTranslatef(0, 5, 0);

	glPushMatrix();
	glNormal3f(1.0, 1.0, 0.0);
	glTranslatef(0, 0.3, 0);
	glRotatef(22.5, 0, 1, 0);
	for (GLfloat j = 0; j < 8; j++) {
		glRotatef(90, 0, 1, 0);
		roofSegment();
	}
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.78, 0.69, 0.53);
	glNormal3f(1.0, 1.0, 0.0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0, 0.0, 0.0);
	float segments = (2 * 3.14) / 8;
	for (GLfloat i = 0; i <= 2 * 3.14; i += segments ) {
		glVertex3f(15.0 * cos(i), -4.0, 15.0 * sin(i));
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glNormal3f(-1.0, 1.0, 0.0);
	glColor3f(0.58, 0.15, 0.16);
	glTranslatef(0, -4.5, 0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(qobj, 15.2, 15.2, 1, 8, 1);
	glPopMatrix();
	
	glPushMatrix();
	glColor3f(0.58, 0.15, 0.16);
	for (GLfloat i = 0; i < 8; i ++) {			//curtains
		glRotatef(-45, 0, 1, 0);
		glScalef(1, 0.5, 1);
		glRotatef(-22.5, 0, 1, 0);
		glTranslatef(0, -8, 14);
		glRotatef(180, 0, 0, 1);
		glBegin(GL_TRIANGLE_FAN);
		
		glVertex3f(0.0, 0.0, 0.0);
		for (GLfloat j = 0; j < 3.14; j += 0.1) {
			glVertex3f(5.8 * cos(j), 5.8 * sin(j), 0);
		}
		glEnd();
		
		glRotatef(-180, 0, 0, 1);
		glTranslatef(0, 8, -14);
		glRotatef(22.5, 0, 1, 0);
		glScalef(1, 2, 1);
	}
	glPopMatrix();

	glPopMatrix();
}

void centerPole() {
	glPushMatrix();
	glNormal3f(0, 0, 1);
	glDisable(GL_COLOR_MATERIAL);
	GLfloat Ambient[] = { 0.5,0.0,0.0,1.0 };
	GLfloat Diffuse[] = { 0.58, 0.15, 0.16,1.0 };
	GLfloat Specular[] = { 0.58, 0.15, 0.16,1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, Ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 3.14);

	glRotatef(90, 1, 0, 0);
	gluCylinder(qobj, 5, 2.5, 8, 8, 1);
	glTranslatef(0.0,0,8);
	gluCylinder(qobj, 2.5, 2, 10, 8, 1);
	glPopMatrix();
	glEnable(GL_COLOR_MATERIAL);

	
}

void platformLayer(GLfloat sides , GLfloat radius) {
	GLfloat segment = (2 * 3.14) / sides;

	glPushMatrix();
	glNormal3f(0, 1, 0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0, 0.0, 0.0);
	for (float i = 0; i < 2 * 3.14; i += segment) {
		glVertex3f(radius*cos(i),0.0,radius*sin(i));
	}
	glEnd();
	glRotatef(90, 1, 0, 0);
	gluCylinder(qobj, radius, radius, 1, sides, 1);
	glPopMatrix();	
}

void platform() {
	glPushMatrix();
	glColor3f(0.58, 0.15, 0.16);
	platformLayer(8, 4);
	glColor3f(0.78, 0.69, 0.53);
	glTranslatef(0, -1, 0);
	platformLayer(8, 15);
	glColor3f(0.58, 0.15, 0.16);
	glTranslatef(0, -1, 0);
	platformLayer(32, 18);
	glPopMatrix();

}

void horse() {	
	//body
	glRotatef(10, 0, 0, 1);
	glPushMatrix();
	glRotatef(-10, 0, 0, 1);
	glRotatef(-90, 0, 1, 0);
	glutSolidSphere(5, 20, 20);
	gluCylinder(qobj, 5, 5, 10, 40, 1);
	glTranslatef(0, 0, 9.5);
	glutSolidSphere(4.7, 20, 20);
	glPopMatrix();

	//torso
	glPushMatrix();
	glTranslatef(-9.0, 0.0, 0.0);
	glRotatef(-45, 0, 0, 1);
	glRotatef(-90, 0, 1, 0);
	gluCylinder(qobj, 4.5, 4.5, 9, 40, 1);
	glPopMatrix();

	//neck
	glPushMatrix();
	glTranslatef(-15.0, 4.0, 0.0);
	glRotatef(-90, 0, 0, 1);
	glRotatef(-90, 0, 1, 0);
	gluCylinder(qobj, 4, 2, 12, 40, 1);
	glPopMatrix();

	//left back limb
	glPushMatrix();
	glTranslatef(1.75, -1.0, 2.0);
	glRotatef(0, 0, 0, 1);
	glRotatef(-90, 0, 1, 0);
	glRotatef(80, 1, 0, 0);
	glutSolidSphere(3,40, 40);
	gluCylinder(qobj, 3, 2, 8.0, 40, 1);
	

	glTranslatef(0, 0, 7.5);
	glutSolidSphere(1.9, 6, 2);
	glRotatef(-80, 1, 0, 0);

	gluCylinder(qobj, 1.5, 1, 10, 6, 1);
	glTranslatef(0.0, -1.0, 10.0);
	glRotatef(20, 1, 0, 0);
	gluCylinder(qobj, 1.23, 1.75, 2, 40, 1);
	glPopMatrix();

	//right back limb
	glPushMatrix();
	glRotatef(25, 0, 0, 1);
	glTranslatef(-1.0, -2.5, -5);
	glTranslatef(1.75, -1.0, 2.0);
	glRotatef(0, 0, 0, 1);
	glRotatef(-90, 0, 1, 0);
	glRotatef(80, 1, 0, 0);
	glutSolidSphere(3, 40, 40);
	gluCylinder(qobj, 3, 2, 8.0, 40, 1);


	glTranslatef(0, 0, 7.5);
	glutSolidSphere(1.9, 6, 2);
	glRotatef(-80, 1, 0, 0);

	gluCylinder(qobj, 1.5, 1, 10, 6, 1);
	glTranslatef(0.0, -1.0, 10.0);
	glRotatef(20, 1, 0, 0);
	gluCylinder(qobj, 1.23, 1.75, 2, 40, 1);
	glPopMatrix();

	//head
	glPushMatrix();
	glTranslatef(-15.0, 17.0, 0);
	glutSolidSphere(2.5, 40, 40);
	glRotatef(-15, 0, 0, 1);
	glRotatef(-90, 0, 1, 0);
	glRotatef(30, 1, 0, 0);
	gluCylinder(qobj, 2.5, 1.25, 5, 40, 1);
	glTranslatef(0, 0, 4.5);
	glutSolidSphere(1.5, 40, 40);
	glPopMatrix();

	//ears
	glPushMatrix();
	glTranslatef(-15.0, 20.0, 1.5);
	glRotatef(5,0, 0, 1);
	glutSolidOctahedron();
	glTranslatef(-0.0, 0.0, -3.0);
	glutSolidOctahedron();
	glPopMatrix();
	
	//front left limb
	glPushMatrix();
	glTranslatef(-15, 5, 3.2);
	glRotatef(-90, 0, 1, 0);
	glutSolidSphere(2.2,40,40);
	gluCylinder(qobj, 2.5, 1.2, 6, 40, 1);
	glTranslatef(0, 0, 6);//joint
	glRotatef(45, 1, 0, 0);
	gluCylinder(qobj, 0.95, 0.95, 2, 6, 1);
	glTranslatef(-0.0, -0.1, 2);
	glRotatef(40, 1, 0, 0);
	gluCylinder(qobj, 1.2, 0.75, 6, 40, 1);
	glTranslatef(-0.0, 0.0, 6.0);
	glRotatef(60,1,0,0);
	gluCylinder(qobj, 1., 1.25, 2, 40, 1);
	glPopMatrix();

	//front right limb
	glPushMatrix();
	glTranslatef(-15, 5, -3.2);
	glRotatef(-90, 0, 1, 0);
	glRotatef(45, 1, 0, 0);
	glutSolidSphere(2.2, 40, 40);
	gluCylinder(qobj, 2.5, 1.2, 6, 40, 1);
	glTranslatef(0, 0, 6);//joint
	glRotatef(45, 1, 0, 0);
	gluCylinder(qobj, 0.95, 0.95, 2, 6, 1);
	glTranslatef(-0.0, -0.1, 2);
	glRotatef(10, 1, 0, 0);
	gluCylinder(qobj, 1.2, 0.75, 6, 40, 1);
	glTranslatef(-0.0, 0.0, 6.0);
	glRotatef(60, 1, 0, 0);
	gluCylinder(qobj, 1., 1.25, 2, 40, 1);
	glPopMatrix();

	//tail
	glPushMatrix();
	glTranslatef(5, 0, 0);
	glRotatef(-45, 0, 0, 1);
	glRotatef(90, 0, 1, 0);
	gluCylinder(qobj, 0.5, 3, 12, 8, 1);
	glPopMatrix();

	
	
}

void dropRod() {
	glPushMatrix();
	glColor3f(0.78, 0.35, 0.36);
	glRotatef(90, 1, 0, 0);
	gluCylinder(qobj, 0.5, 0.5, 80, 40, 40);
	glTranslatef(0, 0, 80);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, 0, 0);
	for (GLfloat i = 0; i < 360; i += 1) {
		glVertex3f(5 * cos(i),  5 * sin(i),0);
	}
	glEnd();
	glPopMatrix();
}

void fence(){

	glPushMatrix();
	glColor3f(0.5,0.5,0.5);
	glTranslatef(0, -55, 0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(qobj, 100, 100, 3, 80, 1); // lower ring
	glRotatef(90, 1, 0, 0);

	glColor3f(0.0, 0.5, 0.25);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0, 0.0, 0.0);
	for (GLfloat i = 0; i < 361; i += 0.5) {
		glVertex3f(100 * cos(i), 0, 100 * sin(i));
	}
	glEnd();

	glColor3f(0.5, 0.5, 0.5);
	glRotatef(11, 0, 1, 0);
	for (GLfloat i = 0; i < 337.5; i += 5.625) { // sticks
		glRotatef(5.625, 0, 1, 0);
		glTranslatef(0, 0, 100);
		glRotatef(-90, 1, 0, 0);
		gluCylinder(qobj, 0.5, 0.5, 20, 40, 1);
		glTranslatef(0, 0, 21);
		glutSolidSphere(1, 40, 40);
		glTranslatef(0, 0, -21);
		glRotatef(90, 1, 0, 0);
		glTranslatef(0, 0, -100);
	}
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glRotatef(-6, 0, 1, 0);
	glTranslatef(0, -40, 0);
	for (GLfloat i = 0; i < 330; i += 5.625) { //upper ring
		glRotatef(-5.625, 0, 1, 0);
		glTranslatef(0, 0, 100);
		glRotatef(-90, 0, 1, 0);
		gluCylinder(qobj, 1, 1, 10, 80, 1);
		glRotatef(90, 0, 1, 0);
		glTranslatef(0, 0, -100);
	}
	glPopMatrix();

	//door
	glPushMatrix();
	glScalef(2.5, 2, 1);
	glRotatef(0.8, 0, 1, 0);
	glTranslatef(0, -25, 100);
	glRotatef(-90, 1, 0, 0);
	glTranslatef(-7.5, 0, 0);
	gluCylinder(qobj, 0.75, 0.75, 15, 40, 1);
	glTranslatef(15, 0, 0);
	gluCylinder(qobj, 0.75, 0.75, 15, 40, 1);
	glTranslatef(-7.5, 0, 0);
	glRotatef(90, 1, 0, 0);
	glTranslatef(0, 15, 0);
	glRotatef(-90, 0, 1, 0);
	for (GLfloat i = 0; i < 180; i+=1) {
		glRotatef(-i, 1, 0, 0);
		glTranslatef(0, 0, 7.5);
		glRotatef(-90, 1, 0, 0);
		gluCylinder(qobj, 0.75, 0.75, 1, 40,1);
		glRotatef(90, 1, 0, 0);
		glTranslatef(0, 0, -7.5);
		glRotatef(i, 1, 0, 0);	
	}
	glPopMatrix();
}

void moon() {
	glPushMatrix();
	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT2);
	GLfloat L2_Ambient[] = { 0.1,0.1,0.1,1.0 };
	GLfloat L2_Diffuse[] = { 1.0,1.0,1.0,1.0 };
	GLfloat L2_Specular[] = { 0.7,0.7,0.7,1.0 };
	GLfloat L2_position[] = { -40, 30, -15,1.0 };
	glLightfv(GL_LIGHT2, GL_AMBIENT, L2_Ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, L2_Diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, L2_Specular);
	glLightfv(GL_LIGHT2, GL_POSITION, L2_position);



	GLfloat Ambient[] = { 1.0,1.0,1.0,1.0 };
	GLfloat Diffuse[] = { 1.0, 1.0, 1.0,1.0 };
	GLfloat Specular[] = { 1.0, 1.0, 1.0,1.0 };
	GLfloat Emmisive = (1.0, 1.0, 1.0, 1.0);

	glMaterialfv(GL_FRONT, GL_AMBIENT, Ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_EMISSION, Emmisive);
	glutSolidSphere(8, 40, 40);
	glPopMatrix();
	glEnable(GL_COLOR_MATERIAL);
}

void pineTree(GLfloat red, GLfloat green, GLfloat blue, GLboolean isSwaing, GLfloat swayOffset) {
	//trunk
	glPushMatrix();
	glColor3f(0.54, 0.22, 0.21);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(qobj, 1.75, 0.5, 25, 5, 1);
	//crown
	glTranslatef(0, 0, 3);
	for (GLfloat i = 0; i < 8; i++) {
		glColor3f(red, green+(i*0.1), blue);
		glTranslatef(0, 0, 5);
		if (isSwaing) {

			glRotatef(sway*swayOffset, 0, 1, 0);
			glRotatef(sway*swayOffset, 0, 0, 1);
		}
		glRotatef(i*10, 0, 0, 1);
		gluCylinder(qobj, 12-(i*2.0), 0, 10, 8, 1);
	}
	glPopMatrix();

}

void Tree(GLfloat red, GLfloat green, GLfloat blue) {
	glPushMatrix();
	glColor3f(0.47, 0.19, 0.0);
	glRotatef(-90, 1, 0, 0);
	//trunk
	gluCylinder(qobj, 1.5, 0.75, 25, 5, 5);
	//1st crown
	glTranslatef(0, 0, 12);
	glPushMatrix();
	for (GLfloat i = 0; i < 5; i++) {
		//leaves
		glColor3f(red, green+(i/10), blue);
		glRotatef(65,0,0,1);
		glRotatef(-45, 1, 0, 0);
		glPushMatrix();
		glTranslatef(0, 0, 5+(i*2.5));
		glScalef(5, 5, 5);
		glutSolidIcosahedron();

		//fruits
		glTranslatef(0, 0, 1);
		glColor3f(0.78, 0.02, 0.10);
		glutSolidSphere(0.1, 5, 5);
		glTranslatef(0.5, 0, -0.9);
		glutSolidSphere(0.1, 5, 5);
		glPopMatrix();
		//branch
		glColor3f(0.47, 0.19, 0.0);
		gluCylinder(qobj, 0.6, 0.7, 8, 6, 1);
		glRotatef(45, 1, 0, 0);
	
	}
	glPopMatrix();
	//2nd crown
	glPushMatrix();
	glRotatef(45, 0, 0, 1);
	glTranslatef(0, 0, 10);
	for (GLfloat i = 0; i < 3; i++) {
		//leaves
		glColor3f(red+0.2+(i/10), green+0.3, blue);
		glRotatef(120, 0, 0, 1);
		glRotatef(-45, 1, 0, 0);
		glPushMatrix();
		glTranslatef(0, 0, 8);
		glScalef(4, 4, 4);
		glutSolidIcosahedron();
		//fruits
		glTranslatef(0, 0, 1);
		glColor3f(0.78, 0.02, 0.10);
		glutSolidSphere(0.1, 5, 5);
		glTranslatef(0.5, 0, -0.9);
		glutSolidSphere(0.1, 5, 5);
		glPopMatrix();
		//branch
		glColor3f(0.47, 0.19, 0.0);
		gluCylinder(qobj, 0.75, 0.75, 10, 6, 1);
		glRotatef(45, 1, 0, 0);

	}
	glPopMatrix();

	//3rd crown
	glPushMatrix();
	glRotatef(60, 0, 0, 1);
	glTranslatef(0, 0, 12);
	for (GLfloat i = 0; i < 3; i++) {
		//leaves
		glColor3f(red + 0.4 + (i / 10), green + 0.3, blue);
		glRotatef(120, 0, 0, 1);
		glRotatef(-15, 1, 0, 0);
		glPushMatrix();
		glTranslatef(0, 0, 8);
		glScalef(3, 3, 3);
		glutSolidIcosahedron();
		glPopMatrix();
		//branch
		glColor3f(0.47, 0.19, 0.0);
		gluCylinder(qobj, 0.4, 0.4, 10.5, 6, 1);
		glRotatef(-15, 1, 0, 0);

	}
	glPopMatrix();
	glPopMatrix();

}



void ground() {
	
	//ground
	
	glEnable(GL_TEXTURE_2D);
	//ground
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_POLYGON);

	glTexCoord2f(0.0, 0.0); glVertex3f(-15, 0.0, 15);
	glTexCoord2f(1.0, 0.0); glVertex3f(15, 0.0, 15);
	glTexCoord2f(1.0, 1.0); glVertex3f(15, 0.0, -15);
	glTexCoord2f(0.0, 1.0); glVertex3f(-15, 0.0, -15);
	glEnd();
	glDisable(GL_TEXTURE_2D);

}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//gluLookAt(45,5,0, 0,0, 0, 0, 1, 0);
	
	//gluLookAt(-30, 5, 0, 0, 0, 0, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//glPushMatrix();
	
	
	

	
	
	//gluLookAt(distanceToOrigin*cos(cameraRotationAngle), 0, distanceToOrigin*sin(cameraRotationAngle), 0, 0, 0, 0, 1, 0);
	gluLookAt(camX,camY,camZ, 0, 0, 0, 0, 1, 0);

	//glPopMatrix();
	//moon();
	
	
	glScalef(0.75, 0.75, 0.75);
	glPushMatrix();
	// horse rotation comes here
	glRotatef(rot, 0, 1, 0);
	glColor3f(0.0, 0.63, 0.90);
	glPushMatrix();
	glTranslatef(-5.0, 30.0, 60);
	dropRod();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-60, 0, 1, 0);
	glTranslatef(-5.0, 30.0, 60);
	dropRod();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-120, 0, 1, 0);
	glTranslatef(-5.0, 30.0, 60);
	dropRod();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-180, 0, 1, 0);
	glTranslatef(-5.0, 30.0, 60);
	dropRod();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-240, 0, 1, 0);
	glTranslatef(-5.0, 30.0, 60);
	dropRod();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-300, 0, 1, 0);
	glTranslatef(-5.0, 30.0, 60);
	dropRod();
	glPopMatrix();

	//horse1
	glPushMatrix();
	glTranslatef(0, hop, 0);
	glColor3f(0.0, 0.63, 0.90);
	glTranslatef(0.0, -30.0, 60);
	glRotatef(pitch, 0, 0, 1);
	horse();
	glPopMatrix();

	//horse2
	glPushMatrix();
	glTranslatef(0, -hop, 0);
	glColor3f(0.8, 0.0, 0.8);
	glRotatef(-60, 0, 1, 0);
	glTranslatef(0.0, -30.0, 60);
	glRotatef(-pitch, 0, 0, 1);
	horse();
	glPopMatrix();

	//horse3
	glPushMatrix();
	glTranslatef(0, hop, 0);
	glColor3f(0.0, 0.63, 0.90);
	glRotatef(-120, 0, 1, 0);
	glTranslatef(0.0, -30.0, 60);
	glRotatef(pitch, 0, 0, 1);
	horse();
    glPopMatrix();

	//horse4
	glPushMatrix();
	glTranslatef(0, -hop, 0);
	glColor3f(0.8, 0.0, 0.8);
	glRotatef(-180, 0, 1, 0);
	glTranslatef(0.0, -30.0, 60);
	glRotatef(-pitch, 0, 0, 1);
	horse();
	glPopMatrix();

	//horse5
	glPushMatrix();
	glTranslatef(0, hop, 0);
	glColor3f(0.0, 0.63, 0.90);
	glRotatef(-240, 0, 1, 0);
	glTranslatef(0.0, -30.0, 60);
	glRotatef(pitch, 0, 0, 1);
	horse();
	glPopMatrix();

	//horse6
	glPushMatrix();
	glTranslatef(0, -hop, 0);
	glColor3f(0.8, 0.0, 0.8);
	glRotatef(-300, 0, 1, 0);
	glTranslatef(0.0, -30.0, 60);
	glRotatef(-pitch, 0, 0, 1);
	horse();
	glPopMatrix();
	
	glPushMatrix();
	glScalef(5, 5, 5);
	glTranslatef(0.0, 4, 0.0);

	glPushMatrix();
	glTranslatef(0.0f, 6, 0.0);
	lightBulb(bulbR, bulbG, bulbB);
	for (GLfloat i = 0; i < 361; i+=45) {
		
		glRotatef(i, 0, 1, 0);
		glPushMatrix();
		for (GLfloat j = 0;j < 6; j++) {
			glTranslatef(j, -j / 4, 0);
			if(j>1){
				lightBulb(bulbR, bulbG, bulbB);
			}
		}
		glPopMatrix();
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 4, 0.0);
	for (GLfloat i = 0; i < 361; i += 45) {
		glRotatef(i, 0, 1, 0);
		glPushMatrix();
		for (GLfloat j = 0; j < 6; j++) {
			glTranslatef(j, -j / 4, 0);
			if (j > 1) {
				glRotatef(180, 1, 0, 0);
				lightBulb(bulbR,bulbG,bulbB);
				glRotatef(-180, 1, 0, 0);
			}
		}
		glPopMatrix();
	}
	glPopMatrix();

	glPushMatrix();
	roof();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 3, 0);
	centerPole();
	glPopMatrix();

	glPopMatrix();

	glPushMatrix();
	
	glScalef(5, 5, 5);
	glTranslatef(0, -9.1, 0);
	platform();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -12.1, 0);
	fence();
	glPopMatrix();
	//glScalef(4, 1, 4);
	//glTranslatef(0.0,-20, 0);
	//ground();

	glPushMatrix();
	
	glScalef(3, 3, 3);
	glTranslatef(0, -20, 0);
	
	glTranslatef(-50, 0, 0);
	Tree(0, 0.1, 0); 
	
	glTranslatef(0, 0, 10);
	Tree(0.4, 0.5, 0);
	
	glTranslatef(20, 0, -55);
	pineTree(0.5, 0.5, 0.0, true,1);
	
	glTranslatef(40, 0, 0.0);
	pineTree(0.5, 0.2, 0.0, true, 1);
	
	glTranslatef(35, 0, 50.0);
	pineTree(0.7, 0.1, 0.0,true,-1);
	
	glTranslatef(20, 0, 0);
	pineTree(0.7, 0.1, 0.0, true, 1);

	glTranslatef(-30, 0, 25.0);
	pineTree(0.7, 0.3, 0.0, true, 0.75);
	
	glPopMatrix();
	glFlush();
}

void reshape(GLsizei width, GLsizei height) {
	if (height == 0) {
		height = 1;
	}
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat aspectRatio = (GLfloat)width / (GLfloat)height;
	gluPerspective(100, aspectRatio, 10, 300);	
}

void timer(int value) {
	rot += -rotChange;
	//pitch+=20;
	hop = hop + hopChange;
	//pitch = pitch + pitchChange;

	if (hop >= 6) {
		hopChange = -hopChange;
	}
	else if (hop <= 5) {
		hopChange = -hopChange;
	}

	if (pitch >= 5) {
		pitchChange = -pitchChange;
	}
	else if (pitch <= -5) {
		pitchChange = -pitchChange;
	}

	if (lightingMode < 2 && lightingMode > 0) {
		bulbR += bulbChange;
		bulbG += bulbChange;
		bulbB += bulbChange;
	}
	else if (lightingMode < 3 && lightingMode > 1) {
		bulbR += bulbChange;
		bulbG += bulbChange;
		bulbB =0.0;
	}
	else if (lightingMode <4 && lightingMode > 2) {
		bulbR += bulbChange;
		bulbG =0.0;
		bulbB += bulbChange;
	}
	
	if (bulbR<0 || bulbG < 0 || bulbB < 0) {
		bulbChange = -bulbChange;	
	}
	else if (bulbR >1 || bulbG > 1 || bulbB > 1) {
		bulbChange = -bulbChange;
	}

	sway += swayChange;
	if (sway > 3) {
		swayChange = -swayChange;
	}
	else if (sway <-3) {
		swayChange = -swayChange;
	}

	glutTimerFunc(130, timer, 1);
	glutPostRedisplay();
}

void keyBoardSpecial(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT) {
		camX -= 1;
	}
	if (key == GLUT_KEY_RIGHT) {
		camX += 1;
	}
	if (key == GLUT_KEY_UP) {
		camY+= 1;
	}
	if (key == GLUT_KEY_DOWN) {
		camY-=1;
	}
	glutPostRedisplay();
}

void keyBoard(unsigned char key,int x, int y) {
	if (key == 'Z') {
		camZ -= 1;
	}
	if (key == 'z') {
		camZ += 1;
	}
	if (key == 's') {
		if (rotChange < 5) {
			rotChange = 5;
			hopChange = 1;
		}
		else if (rotChange > 0) {
			rotChange = 0;
			hopChange = 0;
		}
	}

	if (key == '0') {	
		bulbChange = 0.0;
		bulbR = 0.1;
		bulbG = 0.1;
		bulbB = 0.1;
	}
	if (key == '1') {
		lightingMode = 1;
		bulbChange = 0.8;
		bulbR = 0.1;
		bulbG = 0.1;
		bulbB = 0.1;
	}

	if (key == '2') {
		lightingMode = 2;
		bulbChange = 0.8;
		bulbR = 0.1;
		bulbG = 0.1;
		bulbB = 0.1;
	}
	if (key == '3') {
		lightingMode = 3;
		bulbChange = 0.8;
		bulbR = 0.1;
		bulbG = 0.1;
		bulbB = 0.1;
	}
	if (key == '4') {
		lightingMode = 4;
		bulbChange = 0.8;
		bulbR = 0.1;
		bulbG = 0.1;
		bulbB = 0.1;
	}

	
	glutPostRedisplay();
}

int main(int argc, char** args) {
	glutInit(&argc, args);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(150, 150);
	glutCreateWindow("Carousel");
	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutTimerFunc(1000, timer, 1);
	glutSpecialFunc(keyBoardSpecial);
	glutKeyboardFunc(keyBoard);
	glutMainLoop();
	return 0;


}