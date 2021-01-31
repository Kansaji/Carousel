#include<Windows.h>
#include<GL/glut.h>
#include<math.h>
#include <iostream>

using namespace std;
GLUquadricObj* qobj;

GLfloat rot = 0;
GLfloat hop = 0;
GLfloat hopChange =1 ;
GLfloat pitch = 0;
GLfloat pitchChange = 10;

GLfloat bulb = 0.0;
GLfloat bulbChange = 0.8;
GLfloat bulbR = 0.0;
GLfloat bulbG = 0.0;
GLfloat bulbB = 0.0;

GLfloat camZ = 100;
GLfloat camX = 0;

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
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	initLighting();
	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE);
	qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);

	
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

//void curtain() {
//	glPushMatrix();
//	glColor3f(0.58, 0.15, 0.16);
//	
//	glTranslatef(-50, 0, 115);
//	for (GLfloat i = 0; i < 5; i++) {
//		glTranslatef(20, 0, 0);
//		glBegin(GL_TRIANGLE_FAN);
//		glVertex3f(0, 0, 0);
//		for (GLfloat j = 0; j < 3.14; j += 0.5) {
//			glVertex3f(10 * cos(j), -10 * sin(j), 0);
//
//		}
//		glEnd();
//	}
//
//	glPopMatrix();
//
//}

void lightBulb() {
	glPushMatrix();
	glutSolidSphere(0.3, 50, 50);
	glTranslatef(0.0,-0.55, 0.0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(qobj, 0.2, 0.2, 0.2, 10, 1);
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
	
	for (GLfloat i = 0; i < 8; i ++) {
		glRotatef(-45, 0, 1, 0);
		glScalef(1, 0.5, 1);
		glRotatef(-22.5, 0, 1, 0);
		glTranslatef(0, -8, 14);
		glRotatef(180, 0, 0, 1);
		glBegin(GL_TRIANGLE_FAN);
		
		glVertex3f(0.0, 0.0, 0.0);
		for (GLfloat j = 0; j < 3.14; j += 0.1) {
			glVertex3f(3.8 * cos(j), 3.8 * sin(j), 0);
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
	gluCylinder(qobj, 4, 2, 18, 8, 1);
	glPopMatrix();
	glEnable(GL_COLOR_MATERIAL);
}

void platformLayer() {
	GLfloat segment = (2 * 3.14) / 8;
	glPushMatrix();
	
	glNormal3f(0, 1, 0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0, 0.0, 0.0);
	for (float i = 0; i < 2 * 3.14; i += segment) {
		glVertex3f(15*cos(i),0.0,15*sin(i));
	}
	glEnd();
	glRotatef(90, 1, 0, 0);
	gluCylinder(qobj, 15, 15, 1, 8, 1);
	glPopMatrix();

	
}

void platform() {
	glPushMatrix();
	glColor3f(0.78, 0.69, 0.53);
	glTranslatef(0.0, -11.0, 0.0);
	platformLayer();
	glColor3f(0.58, 0.15, 0.16);
	glScalef(0.5, 0.5, 0.5);
	glTranslatef(0.0, 2, 0.0);
	platformLayer();
	glPopMatrix();

	glPushMatrix();
	glLoadIdentity();
	//glColor3f(0.78, 0.69, 0.53);
	glTranslatef(0.0, -50.0, 0.0);
	glScalef(5, 5, 5);
	platformLayer();
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
	gluCylinder(qobj, 95, 95, 3, 80, 1); // lower ring
	glRotatef(90, 1, 0, 0);

	glColor3f(0.0, 0.5, 0.25);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0, 0.0, 0.0);
	for (GLfloat i = 0; i < 361; i += 0.5) {
		glVertex3f(95 * cos(i), 0, 95 * sin(i));
	}
	glEnd();

	glColor3f(0.5, 0.5, 0.5);
	glRotatef(11, 0, 1, 0);
	for (GLfloat i = 0; i < 337.5; i += 5.625) { // sticks
		glRotatef(5.625, 0, 1, 0);
		glTranslatef(0, 0, 95);
		glRotatef(-90, 1, 0, 0);
		gluCylinder(qobj, 0.5, 0.5, 15, 40, 1);
		
		glRotatef(90, 1, 0, 0);
		glTranslatef(0, 0, -95);
	}
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glRotatef(-6, 0, 1, 0);
	glTranslatef(0, -40, 0);
	for (GLfloat i = 0; i < 330; i += 5.625) { //upper ring
		glRotatef(-5.625, 0, 1, 0);
		glTranslatef(0, 0, 95);
		glRotatef(-90, 0, 1, 0);
		gluCylinder(qobj, 1, 1, 10, 80, 1);
		glRotatef(90, 0, 1, 0);
		glTranslatef(0, 0, -95);
	}
	glPopMatrix();

	//door
	
	glPushMatrix();
	
	glScalef(2.5, 2, 1);
	glRotatef(0.8, 0, 1, 0);
	glTranslatef(0, -25, 97);
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

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//gluLookAt(45,5,0, 0,0, 0, 0, 1, 0);
	gluLookAt(0,40,150, 0, 0, 0, 0, 1, 0);
	//gluLookAt(-30, 5, 0, 0, 0, 0, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//moon();
	
	glColor3f(0.0, 0.63, 0.90);
	glScalef(0.75, 0.75, 0.75);

	// horse rotation comes here

	glRotatef(rot, 0, 1, 0);
	
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
	glColor3f(bulbR, bulbG, bulbB);
	
	lightBulb();
	for (GLfloat i = 0; i < 361; i+=45) {
		
		glRotatef(i, 0, 1, 0);
		glPushMatrix();
		for (GLfloat j = 0;j < 6; j++) {
			glTranslatef(j, -j / 4, 0);
			if(j>1){
				
				lightBulb();
			}
			
		}
		
		
		glPopMatrix();
	}
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0.0f, 4, 0.0);
	glColor3f(bulbR, bulbG, bulbB);


	for (GLfloat i = 0; i < 361; i += 45) {

		glRotatef(i, 0, 1, 0);
		glPushMatrix();
		for (GLfloat j = 0; j < 6; j++) {
			glTranslatef(j, -j / 4, 0);
			if (j > 1) {
				glRotatef(180, 1, 0, 0);
				lightBulb();
				glRotatef(-180, 1, 0, 0);
			}

		}


		glPopMatrix();
	}
	glPopMatrix();

	roof();

	glPushMatrix();
	glTranslatef(0, 3, 0);
	centerPole();
	glPopMatrix();

	glPopMatrix();
	glPushMatrix();
	glScalef(5, 5, 5);
	platform();
	glPopMatrix();
	
	glPushMatrix();
	glLoadIdentity();
	fence();
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
	gluPerspective(100, aspectRatio, 10, 250);
	
}

void timer(int value) {
	
	rot += -5;
	//pitch+=20;
	hop=hop+ hopChange;
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
	
	bulbR += bulbChange;
	//bulbG += bulbChange;
	bulbB += bulbChange;
	if (bulbR<0 || bulbG < 0 || bulbB < 0) {
		bulbChange = -bulbChange;	
	}
	else if (bulbR >1 || bulbG > 1 || bulbB > 1) {
		bulbChange = -bulbChange;
	}


	glutTimerFunc(130, timer, 1);
	glutPostRedisplay();
}

void keyBoardSpecial() {
	
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
	glutMainLoop();
	return 0;


}