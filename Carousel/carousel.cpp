#include<Windows.h>
#include<GL/glut.h>
#include<math.h>


GLUquadricObj* qobj;

void initLighting() {
	GLfloat L0_Ambient[] = { 0.1,0.1,0.1,1.0 };
	GLfloat L0_Diffuse[] = { 1.0,1.0,1.0,1.0 };
	GLfloat L0_Specular[] = { 0.7,0.7,0.7,1.0 };
	GLfloat L0_position[] = { -20,20,20,1.0 };
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
	//glEnable(GL_LIGHT0);
//	glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE);
	qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_SMOOTH);


}

void roofSegment() {
	glPushMatrix();
	glColor3f(0.58, 0.15, 0.16);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(10 * cos(0.393), -4.0, 10 * sin(0.393));
	glVertex3f(10 * cos(0.393), -4.0, -10 * sin(0.393));
	glEnd();
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
		glVertex3f(10.0 * cos(i), -4.0, 10.0 * sin(i));
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glNormal3f(-1.0, 1.0, 0.0);
	glColor3f(0.58, 0.15, 0.16);
	glTranslatef(0, -4.5, 0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(qobj, 10.2, 10.2, 1, 8, 1);
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
	gluCylinder(qobj, 1.5, 1, 15, 8, 1);
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
		glVertex3f(10*cos(i),0.0,10*sin(i));
	}
	glEnd();
	glRotatef(90, 1, 0, 0);
	gluCylinder(qobj, 10, 10, 1, 8, 1);
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
}

void lightBulb() {
	GLfloat L2_Ambient[] = { 0.1,0.1,0.1,1.0 };
	GLfloat L2_Diffuse[] = { 1.0,1.0,1.0,1.0 };
	GLfloat L2_Specular[] = { 0.7,0.7,0.7,1.0 };
	GLfloat L2_position[] = { 0,1,0,1.0 };
	glLightfv(GL_LIGHT2, GL_AMBIENT, L2_Ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, L2_Diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, L2_Specular);
	glLightfv(GL_LIGHT2, GL_POSITION, L2_position);
	glEnable(GL_LIGHT2);

	glPushMatrix();
	glDisable(GL_COLOR_MATERIAL);
	GLfloat Ambient[] = { 1.0,1.0,1.0,1.0 };
	GLfloat Diffuse[] = { 1.0, 1.0, 1.0,1.0 };
	GLfloat Specular[] = { 1.0, 1.0, 1.0,1.0 };
	GLfloat Emmisive =  (1.0, 1.0, 1.0,1.0);

	glMaterialfv(GL_FRONT, GL_AMBIENT, Ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_EMISSION, Emmisive);

	glutSolidSphere(0.5, 50, 50);
	glTranslatef(0.0, -1, 0.0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(qobj, 0.3, 0.3, 0.5,10, 1);
	glPopMatrix();
	glEnable(GL_COLOR_MATERIAL);
}

void horse() {
	//body
	glRotatef(20, 0, 0, 1);
	glPushMatrix();
	glRotatef(-10, 0, 0, 1);
	glRotatef(-90, 0, 1, 0);
	glutSolidSphere(6, 20, 20);
	gluCylinder(qobj, 5, 6, 10, 40, 1);
	glTranslatef(0, 0, 9.5);
	glutSolidSphere(6, 20, 20);
	glPopMatrix();

	//torso
	glPushMatrix();
	glTranslatef(-9.0, 0.0, 0.0);
	glRotatef(-45, 0, 0, 1);
	glRotatef(-90, 0, 1, 0);
	gluCylinder(qobj, 5, 5, 9, 40, 1);
	glPopMatrix();

	//neck
	glPushMatrix();
	glTranslatef(-15.0, 4.0, 0.0);
	glRotatef(-90, 0, 0, 1);
	glRotatef(-90, 0, 1, 0);
	gluCylinder(qobj, 4, 2, 10, 40, 1);
	glPopMatrix();

	//left back limb
	glPushMatrix();
	glTranslatef(2, -1, 3.2);
	glRotatef(45, 0, 0, 1);
	glRotatef(-90, 0, 1, 0);
	glRotatef(45, 1, 0, 0);
	glRotatef(30, 1, 0, 0);
	glutSolidSphere(3,40, 40);
	gluCylinder(qobj, 3, 2, 9.5, 40, 1);
	glTranslatef(0, 0, 10);
	glutSolidSphere(1.9, 6, 2);
	glRotatef(-35, 1, 0, 0);
	gluCylinder(qobj, 1.5, 1, 12, 6, 1);
	glPopMatrix();

	//right back limb
	glPushMatrix();
	glTranslatef(0.0, 0.0, -6.5);
	glTranslatef(2, -1, 3.2);
	glRotatef(45, 0, 0, 1);
	glRotatef(-90, 0, 1, 0);
	glRotatef(45, 1, 0, 0);
	glutSolidSphere(3, 40, 40);
	gluCylinder(qobj, 3, 2, 9.5, 40, 1);
	glTranslatef(0, 0, 10);
	glutSolidSphere(1.9, 6, 2);
	glRotatef(-35, 1, 0, 0);
	gluCylinder(qobj, 1.5, 1, 12, 6, 1);
	glPopMatrix();

	//head
	glPushMatrix();
	glTranslatef(-15.0, 14.0, 0);
	glutSolidSphere(2, 40, 40);
	glRotatef(-15, 0, 0, 1);
	glRotatef(-90, 0, 1, 0);
	glRotatef(40, 1, 0, 0);
	gluCylinder(qobj, 2, 0.75, 5, 40, 1);
	glPopMatrix();

	//ears
	glPushMatrix();
	glTranslatef(-16.0, 16.0, 1.5);
	glRotatef(10,0, 0, 1);
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
	glPopMatrix();

	//tail
	glPushMatrix();
	glTranslatef(5, 0, 0);
	glRotatef(-45, 0, 0, 1);
	glRotatef(90, 0, 1, 0);
	gluCylinder(qobj, 0.5, 3, 12, 8, 1);
	glPopMatrix();


}

//void moon() {
//	glPushMatrix();
//	glDisable(GL_COLOR_MATERIAL);
//	glEnable(GL_LIGHT2);
//	GLfloat L2_Ambient[] = { 0.1,0.1,0.1,1.0 };
//	GLfloat L2_Diffuse[] = { 1.0,1.0,1.0,1.0 };
//	GLfloat L2_Specular[] = { 0.7,0.7,0.7,1.0 };
//	GLfloat L2_position[] = { -40, 30, -15,1.0 };
//	glLightfv(GL_LIGHT2, GL_AMBIENT, L2_Ambient);
//	glLightfv(GL_LIGHT2, GL_DIFFUSE, L2_Diffuse);
//	glLightfv(GL_LIGHT2, GL_SPECULAR, L2_Specular);
//	glLightfv(GL_LIGHT2, GL_POSITION, L2_position);
//
//
//
//	GLfloat Ambient[] = { 1.0,1.0,1.0,1.0 };
//	GLfloat Diffuse[] = { 1.0, 1.0, 1.0,1.0 };
//	GLfloat Specular[] = { 1.0, 1.0, 1.0,1.0 };
//	GLfloat Emmisive = (1.0, 1.0, 1.0, 1.0);
//
//	glMaterialfv(GL_FRONT, GL_AMBIENT, Ambient);
//	glMaterialfv(GL_FRONT, GL_DIFFUSE, Diffuse);
//	glMaterialfv(GL_FRONT, GL_SPECULAR, Specular);
//	glMaterialf(GL_FRONT_AND_BACK, GL_EMISSION, Emmisive);
//	glutSolidSphere(8, 40, 40);
//	glPopMatrix();
//	glEnable(GL_COLOR_MATERIAL);
//}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//gluLookAt(45,5,0, 0,0, 0, -1, 0, 0);
	gluLookAt(-0, -5, 85, 0, 0, 0, 0, 1, 0);
	//gluLookAt(-30, 5, 0, 0, 0, 0, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	lightBulb();
	glPushMatrix();
	glColor3f(0.0, 0.63, 0.90);
	glScalef(0.75, 0.75, 0.75);
	
	//horse1
	glPushMatrix();
	glColor3f(0.0, 0.63, 0.90);
	glTranslatef(0.0, -30.0, 40);
	horse();
	glPopMatrix();

	//horse2
	glPushMatrix();
	glColor3f(0.06, 0.58, 0.10);
	glRotatef(-90, 0, 1, 0);
	glTranslatef(0.0, -30.0, 40);
	horse();
	glPopMatrix();

	//horse3
	glPushMatrix();
	glColor3f(0.0, 0.63, 0.90);
	glRotatef(-180, 0, 1, 0);
	glTranslatef(0.0, -30.0, 40);
	horse();
	glPopMatrix();

	//horse4
	glPushMatrix();
	glColor3f(0.06, 0.58, 0.10);
	glRotatef(-240, 0, 1, 0);
	glTranslatef(0.0, -30.0, 40);
	horse();
	glPopMatrix();
	
	
	glScalef(5,5,5);
	roof();
	glPushMatrix();
	glTranslatef(0.0, 4, 0.0);
	centerPole();
	glPopMatrix();
	platform();

	
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
	gluPerspective(100, aspectRatio, 1, 150);
	
}

int main(int argc, char** args) {
	glutInit(&argc, args);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(150, 150);
	glutCreateWindow("Carousel");
	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	
	glutMainLoop();
	return 0;


}