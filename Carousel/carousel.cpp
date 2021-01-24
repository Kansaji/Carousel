#include<Windows.h>
#include<GL/glut.h>
#include<math.h>


GLUquadricObj* qobj;

void initLighting() {
	GLfloat L0_Ambient[] = { 0.1,0.1,0.1,1.0 };
	GLfloat L0_Diffuse[] = { 1.0,1.0,1.0,1.0 };
	GLfloat L0_Specular[] = { 0.7,0.7,0.7,1.0 };
	GLfloat L0_position[] = { -5,5,5,1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, L0_Ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, L0_Diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, L0_Specular);
	glLightfv(GL_LIGHT0, GL_POSITION, L0_position);
	

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
	glEnable(GL_NORMALIZE);
	qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_SMOOTH);


}

void roofSegment() {
	glPushMatrix();
	glColor3f(0.98, 0.96, 0.54);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(10 * cos(0.393), -4.0, 10 * sin(0.393));
	glVertex3f(10 * cos(0.393), -4.0, -10 * sin(0.393));
	glEnd();
	glPopMatrix();
}

void roof() {
	glTranslatef(0, 0.5, 0);
	glRotatef(22.5, 0, 1, 0);
	for (GLfloat j = 0; j < 8; j++) {
		glRotatef(90, 0, 1, 0);
		roofSegment();
	}
	
	glPushMatrix();
	glLoadIdentity();
	glColor3f(0.75, 0.0, 0.07);
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
	glLoadIdentity();
	glNormal3f(1.0, 1.0, 0.0);
	glColor3f(0.75, 0.0, 0.07);
	glTranslatef(0, -4.5, 0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(qobj, 10, 10, 1, 8, 1);
	glPopMatrix();
	
}

void centerPole() {
	
}
void platform() {
	
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	gluLookAt(0,10,15, 0, 0, 0, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	roof();
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
	gluPerspective(120, aspectRatio, 1, 25);
	
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