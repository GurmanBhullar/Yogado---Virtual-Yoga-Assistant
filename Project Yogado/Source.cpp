#define _USE_MATH_DEFINES
#include<GL/glut.h>
#include<windows.h>
#include<GL/gl.h>
#include<cmath>
#include<iostream>
#include<time.h>
#include <string>
#include <fstream>
// For Mac use
// #include<GLUT/glut.h>
using namespace std;
	
void drawHeading(const char* text, int length, int x, int y) {
	glMatrixMode(GL_PROJECTION);
	double* matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	glOrtho(0, 800, 0, 600, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x, y);
	for (int i = 0; i < length; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)text[i]);
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);
}

void drawText(const char* text, int length, int x, int y) {
	glMatrixMode(GL_PROJECTION);
	double* matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	glOrtho(0, 800, 0, 600, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x, y);
	for (int i = 0; i < length; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)text[i]);
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);
}

// Function for Delay
void delay(unsigned int mseconds)
{
	clock_t goal = mseconds + clock();
	while (goal > clock());
}

void myInit(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0f, 1.0f, 1.0f);
	glPointSize(2.0);
	glLineWidth(2.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 840.0, 0.0, 680.0);
}

void mouse(int, int, int, int);


// Functions for creating Different Postures
void welcome(GLfloat ang, GLfloat x, GLfloat y, GLfloat radius, GLfloat eyeL = 2, GLfloat eyeR = 2, GLfloat eyeV = 4)
{
	// Skull of the Person
	glColor3f(0.63f, 0.4f, 0.37f);
	int i;
	int triangleAmount = 20;
	GLfloat twicePi = 2.0f * M_PI;
	glBegin(GL_TRIANGLE_FAN);
	// center of circle
	glVertex2f(x, y);
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (radius * cos(i * twicePi / triangleAmount)),
			y + (radius * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();
	glFlush();

	// Eyes of the Person
	glColor3f(1.0f, 1.0f, 1.0f);
	glPointSize(15.0);
	glBegin(GL_POINTS);
	glVertex2f(x - radius / 2, y + radius / 4);
	glVertex2f(x + radius / 2, y + radius / 4);
	glEnd();
	glFlush();
	glPointSize(5.0);
	glBegin(GL_POINTS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(x - radius / eyeL, y + radius / eyeV);
	glVertex2f(x + radius / eyeR, y + radius / eyeV);
	glEnd();
	glFlush();

	// Nose of the Person
	glColor3f(1.0f, 1.0f, 1.0f);
	glLineWidth(5.0);
	glBegin(GL_LINES);
	glVertex2f(x, y + radius / 4);
	glVertex2f(x, y - radius / 4);
	glEnd();
	glFlush();

	// Lips of the Person
	glColor3f(1.0f, 0.0f, 0.0f);
	glLineWidth(5.0);
	glBegin(GL_LINES);
	glVertex2f(x - radius / 4, y - radius / 2);
	glVertex2f(x + radius / 4, y - radius / 2);
	glEnd();
	glFlush();


	// Neck
	glColor3f(0.63f, 0.4f, 0.37f);
	glLineWidth(25.0);
	glBegin(GL_LINES);
	glVertex2f(x, y - 0.8 * radius);
	glVertex2f(x, y - 1.2 * radius);
	glEnd();
	glFlush();

	// Trunk
	glColor3f(0.59f, 0.59f, 0.59f);
	glBegin(GL_QUADS);
	glVertex2f(x - 1.1 * radius, y - 4 * radius);
	glVertex2f(x + 1.1 * radius, y - 4 * radius);
	glVertex2f(x + 1.1 * radius, y - 1.1 * radius);
	glVertex2f(x - 1.1 * radius, y - 1.1 * radius);
	glEnd();
	glFlush();


	// Legs
	glColor3f(0.25f, 0.25f, 0.25f);
	glLineWidth(32.0);
	glBegin(GL_LINES);
	glVertex2f(x - 0.7 * radius, y - 4 * radius);
	glVertex2f(x - 0.7 * radius, y - 6 * radius);
	glVertex2f(x + 0.7 * radius, y - 4 * radius);
	glVertex2f(x + 0.7 * radius, y - 6 * radius);
	glEnd();
	glFlush();

	// Rotation of arms
	// Angle of rotation
	float angle = ang * M_PI / 180.0;

	// Rotation of Arms
	glColor3f(0.59f, 0.59f, 0.59f);
	float rx1, rx2, ry1, ry2;
	rx1 = x + 1.1 * radius;
	rx2 = x + 3.3 * radius;
	ry1 = y - 1.4 * radius;
	ry2 = y - 1.4 * radius;
	float rx2_rotated = rx1 + (rx2 - rx1) * cos(angle) - (ry2 - ry1) * sin(angle);
	float ry2_rotated = ry1 + (rx2 - rx1) * sin(angle) + (ry2 - ry1) * cos(angle);

	float lx1, lx2, ly1, ly2;
	lx1 = x - 1.1 * radius;
	lx2 = x - 3.3 * radius;
	ly1 = y - 1.4 * radius;
	ly2 = y - 1.4 * radius;
	float lx2_rotated = lx1 + (lx2 - lx1) * cos(-1 * angle) - (ly2 - ly1) * sin(-1 * angle);
	float ly2_rotated = ly1 + (lx2 - lx1) * sin(-1 * angle) + (ly2 - ly1) * cos(-1 * angle);

	glLineWidth(24.0);
	glBegin(GL_LINES);
	glVertex2f(rx1, ry1);
	glVertex2f(rx2_rotated, ry2_rotated);
	glVertex2f(lx1, ly1);
	glVertex2f(lx2_rotated, ly2_rotated);
	glEnd();
	glFlush();

	// Rotation of wrists
	glColor3f(0.63f, 0.4f, 0.37f);
	float rv1, rv2, rw1, rw2;
	float lv1, lv2, lw1, lw2;
	lv1 = lx2_rotated;
	lw1 = ly2_rotated;
	rv1 = rx2_rotated;
	rw1 = ry2_rotated;
	lv2 = lv1 - 0.4 * radius;;
	lw2 = lw1;// For slope to wrist, add 0.1 * radius;
	rv2 = rv1 + 0.4 * radius;
	rw2 = rw1;// For slope to wrist, add 0.1 * radius;

	float rv2_rotated = rv1 + (rv2 - rv1) * cos(angle) - (rw2 - rw1) * sin(angle);
	float rw2_rotated = rw1 + (rv2 - rv1) * sin(angle) + (rw2 - rw1) * cos(angle);

	float lv2_rotated = lv1 + (lv2 - lv1) * cos(-1 * angle) - (lw2 - lw1) * sin(-1 * angle);
	float lw2_rotated = lw1 + (lv2 - lv1) * sin(-1 * angle) + (lw2 - lw1) * cos(-1 * angle);

	glLineWidth(22.0);
	glBegin(GL_LINES);
	glVertex2f(rv1, rw1);
	glVertex2f(rv2_rotated, rw2_rotated);
	glVertex2f(lv1, lw1);
	glVertex2f(lv2_rotated, lw2_rotated);
	glEnd();
	glFlush();

	
}


void bodyPerson(GLfloat ang, GLfloat x, GLfloat y, GLfloat radius, GLfloat eyeL = 2, GLfloat eyeR = 2, GLfloat eyeV = 4)
{
	// Skull of the Person
	glColor3f(0.63f, 0.4f, 0.37f);
	int i;
	int triangleAmount = 20;
	GLfloat twicePi = 2.0f * M_PI;
	glBegin(GL_TRIANGLE_FAN);
	// center of circle
	glVertex2f(x, y);
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (radius * cos(i * twicePi / triangleAmount)),
			y + (radius * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();
	glFlush();

	// Eyes of the Person
	glColor3f(1.0f, 1.0f, 1.0f);
	glPointSize(15.0);
	glBegin(GL_POINTS);
	glVertex2f(x - radius / 2, y + radius / 4);
	glVertex2f(x + radius / 2, y + radius / 4);
	glEnd();
	glFlush();
	glPointSize(5.0);
	glBegin(GL_POINTS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(x - radius / eyeL, y + radius / eyeV);
	glVertex2f(x + radius / eyeR, y + radius / eyeV);
	glEnd();
	glFlush();

	// Nose of the Person
	glColor3f(1.0f, 1.0f, 1.0f);
	glLineWidth(5.0);
	glBegin(GL_LINES);
	glVertex2f(x, y + radius / 4);
	glVertex2f(x, y - radius / 4);
	glEnd();
	glFlush();

	// Lips of the Person
	glColor3f(1.0f, 0.0f, 0.0f);
	glLineWidth(5.0);
	glBegin(GL_LINES);
	glVertex2f(x - radius / 4, y - radius / 2);
	glVertex2f(x + radius / 4, y - radius / 2);
	glEnd();
	glFlush();


	// Neck
	glColor3f(0.63f, 0.4f, 0.37f);
	glLineWidth(25.0);
	glBegin(GL_LINES);
	glVertex2f(x, y - 0.8 * radius);
	glVertex2f(x, y - 1.2 * radius);
	glEnd();
	glFlush();

	// Trunk
	glColor3f(0.59f, 0.59f, 0.59f);	
	glBegin(GL_QUADS);
	glVertex2f(x - 1.1 * radius, y - 4 * radius);
	glVertex2f(x + 1.1 * radius, y - 4 * radius);
	glVertex2f(x + 1.1 * radius, y - 1.1 * radius);
	glVertex2f(x - 1.1 * radius, y - 1.1 * radius);
	glEnd();
	glFlush();


	// Legs
	glColor3f(0.25f, 0.25f, 0.25f);
	glLineWidth(32.0);
	glBegin(GL_LINES);
	glVertex2f(x - 0.7 * radius, y - 4 * radius);
	glVertex2f(x - 0.7 * radius, y - 6 * radius);
	glVertex2f(x + 0.7 * radius, y - 4 * radius);
	glVertex2f(x + 0.7 * radius, y - 6 * radius);
	glEnd();
	glFlush();


	// Rotation of arms
	// Angle of rotation
	float angle = ang * M_PI / 180.0;

	// Rotation of Arms
	glColor3f(0.59f, 0.59f, 0.59f);
	float rx1, rx2, ry1, ry2;
	rx1 = x + 1.1 * radius;
	rx2 = x + 3.3 * radius;
	ry1 = y - 1.4 * radius;
	ry2 = y - 1.4 * radius;
	float rx2_rotated = rx1 + (rx2 - rx1) * cos(angle) - (ry2 - ry1) * sin(angle);
	float ry2_rotated = ry1 + (rx2 - rx1) * sin(angle) + (ry2 - ry1) * cos(angle);

	float lx1, lx2, ly1, ly2;
	lx1 = x - 1.1 * radius;
	lx2 = x - 3.3 * radius;
	ly1 = y - 1.4 * radius;
	ly2 = y - 1.4 * radius;
	float lx2_rotated = lx1 + (lx2 - lx1) * cos(-1 * angle) - (ly2 - ly1) * sin(-1 * angle);
	float ly2_rotated = ly1 + (lx2 - lx1) * sin(-1 * angle) + (ly2 - ly1) * cos(-1 * angle);

	glLineWidth(24.0);
	glBegin(GL_LINES);
	glVertex2f(rx1, ry1);
	glVertex2f(rx2_rotated, ry2_rotated);
	glVertex2f(lx1, ly1);
	glVertex2f(lx2_rotated, ly2_rotated);
	glEnd();
	glFlush();

	// Rotation of wrists
	glColor3f(0.63f, 0.4f, 0.37f);
	float rv1, rv2, rw1, rw2;
	float lv1, lv2, lw1, lw2;
	lv1 = lx2_rotated;
	lw1 = ly2_rotated;
	rv1 = rx2_rotated;
	rw1 = ry2_rotated;
	lv2 = lv1 - 0.4 * radius;;
	lw2 = lw1;// For slope to wrist, add 0.1 * radius;
	rv2 = rv1 + 0.4 * radius;
	rw2 = rw1;// For slope to wrist, add 0.1 * radius;

	float rv2_rotated = rv1 + (rv2 - rv1) * cos(angle) - (rw2 - rw1) * sin(angle);
	float rw2_rotated = rw1 + (rv2 - rv1) * sin(angle) + (rw2 - rw1) * cos(angle);

	float lv2_rotated = lv1 + (lv2 - lv1) * cos(-1 * angle) - (lw2 - lw1) * sin(-1 * angle);
	float lw2_rotated = lw1 + (lv2 - lv1) * sin(-1 * angle) + (lw2 - lw1) * cos(-1 * angle);

	glLineWidth(22.0);
	glBegin(GL_LINES);
	glVertex2f(rv1, rw1);
	glVertex2f(rv2_rotated, rw2_rotated);
	glVertex2f(lv1, lw1);
	glVertex2f(lv2_rotated, lw2_rotated);
	glEnd();
	glFlush();

	// Land Boundary
	glColor3f(0.0f, 1.0f, 0.0f);
	glLineWidth(10.0);
	glBegin(GL_LINES);
	glVertex2f(0, 150);
	glVertex2f(900, 150);
	glColor3f(0.0f, 0.0f, 1.0f);
	glEnd();
	glFlush();

}

void TrikonasanaLeft(GLfloat x, GLfloat y, GLfloat radius)
{
	// Skull of the Person
	glColor3f(0.63f, 0.4f, 0.37f);
	int i;
	int triangleAmount = 20;
	GLfloat twicePi = 2.0f * M_PI;
	glBegin(GL_TRIANGLE_FAN);
	// center of circle
	glVertex2f(x - 3.3 * radius, y - 3 * radius);
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (radius * cos(i * twicePi / triangleAmount)) - 3.3 * radius,
			y + (radius * sin(i * twicePi / triangleAmount)) - 3 * radius
		);
	}
	glEnd();
	glFlush();

	// Eyes of the Person
	glColor3f(1.0f, 1.0f, 1.0f);
	glPointSize(15.0);
	glBegin(GL_POINTS);
	glVertex2f(x - 3.7 * radius, y - 3.4 * radius);
	glVertex2f(x - 3.7 * radius, y - 2.6 * radius);
	glEnd();
	glFlush();
	glPointSize(5.0);
	glBegin(GL_POINTS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(x - 3.7 * radius, y - 3.25 * radius);
	glVertex2f(x - 3.7 * radius, y - 2.45 * radius);
	glEnd();
	glFlush();

	// Nose of the Person
	glColor3f(1.0f, 1.0f, 1.0f);
	glLineWidth(5.0);
	glBegin(GL_LINES);
	glVertex2f(x - 3.5 * radius, y - 3 * radius);
	glVertex2f(x - 3.0 * radius, y - 3 * radius);
	glEnd();
	glFlush();

	// Lips of the Person
	glColor3f(1.0f, 0.0f, 0.0f);
	glLineWidth(5.0);
	glBegin(GL_LINES);
	glVertex2f(x - 2.6 * radius, y - 2.85 * radius);
	glVertex2f(x - 2.6 * radius, y - 3.05 * radius);
	glEnd();
	glFlush();


	// Neck
	glColor3f(0.63f, 0.4f, 0.37f);
	glLineWidth(25.0);
	glBegin(GL_LINES);
	glVertex2f(x - 2 * radius, y - 3 * radius);
	glVertex2f(x - 2.4 * radius, y - 3 * radius);
	glEnd();
	glFlush();

	
	// Legs
	glColor3f(0.25f, 0.25f, 0.25f);
	glLineWidth(36.0);
	glBegin(GL_LINES);
	glVertex2f(x - 0.5 * radius, y - 4 * radius);
	glVertex2f(x - 2 * radius, y - 6 * radius);
	glVertex2f(x + 0.5 * radius, y - 4 * radius);
	glVertex2f(x + 2 * radius, y - 6 * radius);
	glEnd();
	glFlush();


	// Trunk
	glColor3f(0.59f, 0.59f, 0.59f);
	glBegin(GL_QUADS);
	glVertex2f(x - 2 * radius, y - 4.3 * radius);
	glVertex2f(x + 0.85 * radius, y - 4.1 * radius);
	glVertex2f(x + 0.85 * radius, y - 2.3 * radius);
	glVertex2f(x - 2 * radius, y - 2 * radius);
	glEnd();
	glFlush();


	// Arms
	glColor3f(0.59f, 0.59f, 0.59f);
	float rx1, rx2, ry1, ry2;
	rx1 = x - 1.8 * radius;
	rx2 = x - 1.6 * radius;
	ry1 = y - 2.3 * radius;
	ry2 = y - 0.3 * radius;

	float lx1, lx2, ly1, ly2;
	lx1 = x - 1.8 * radius;
	lx2 = x - 2.1 * radius;
	ly1 = y - 4.2 * radius;
	ly2 = y - 6 * radius;

	glLineWidth(18.0);
	glBegin(GL_LINES);
	glVertex2f(rx1, ry1);
	glVertex2f(rx2, ry2);
	glVertex2f(lx1, ly1);
	glVertex2f(lx2, ly2);
	glEnd();
	glFlush();
		
	// Wrists
	glColor3f(0.63f, 0.4f, 0.37f);
	float rv1, rv2, rw1, rw2;
	float lv1, lv2, lw1, lw2;
	lv1 = lx2 + 0.05 * radius;
	lw1 = ly2 - 0.2 * radius;
	rv1 = rx2 + 0.03 * radius;
	rw1 = ry2 + 0.2 * radius;
	lv2 = lx2;
	lw2 = lw1 + 0.2 * radius;
	rv2 = rv1;
	rw2 = rw1 - 0.2 * radius;



	glLineWidth(18.0);
	glBegin(GL_LINES);
	glVertex2f(rv1, rw1);
	glVertex2f(rv2, rw2);
	glVertex2f(lv1, lw1);
	glVertex2f(lv2, lw2);
	glEnd();
	glFlush();

	// Land Boundary
	glColor3f(0.0f, 1.0f, 0.0f);
	glLineWidth(10.0);
	glBegin(GL_LINES);
	glVertex2f(0, 150);
	glVertex2f(900, 150);
	glColor3f(0.0f, 0.0f, 1.0f);
	glEnd();
	glFlush();
}

void TrikonasanaRight(GLfloat x, GLfloat y, GLfloat radius)
{
	// Skull of the Person
	glColor3f(0.63f, 0.4f, 0.37f);
	int i;
	int triangleAmount = 20;
	GLfloat twicePi = 2.0f * M_PI;
	glBegin(GL_TRIANGLE_FAN);
	// center of circle
	glVertex2f(x + 3.3 * radius, y - 3 * radius);
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (radius * cos(i * twicePi / triangleAmount)) + 3.3 * radius,
			y + (radius * sin(i * twicePi / triangleAmount)) - 3 * radius
		);
	}
	glEnd();
	glFlush();

	// Eyes of the Person
	glColor3f(1.0f, 1.0f, 1.0f);
	glPointSize(15.0);
	glBegin(GL_POINTS);
	glVertex2f(x + 3.7 * radius, y - 3.4 * radius);
	glVertex2f(x + 3.7 * radius, y - 2.6 * radius);
	glEnd();
	glFlush();
	glPointSize(5.0);
	glBegin(GL_POINTS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(x + 3.7 * radius, y - 3.25 * radius);
	glVertex2f(x + 3.7 * radius, y - 2.45 * radius);
	glEnd();
	glFlush();

	// Nose of the Person
	glColor3f(1.0f, 1.0f, 1.0f);
	glLineWidth(5.0);
	glBegin(GL_LINES);
	glVertex2f(x + 3.5 * radius, y - 3 * radius);
	glVertex2f(x + 3.0 * radius, y - 3 * radius);
	glEnd();
	glFlush();

	// Lips of the Person
	glColor3f(1.0f, 0.0f, 0.0f);
	glLineWidth(5.0);
	glBegin(GL_LINES);
	glVertex2f(x + 2.6 * radius, y - 2.85 * radius);
	glVertex2f(x + 2.6 * radius, y - 3.05 * radius);
	glEnd();
	glFlush();


	// Neck
	glColor3f(0.63f, 0.4f, 0.37f);
	glLineWidth(25.0);
	glBegin(GL_LINES);
	glVertex2f(x + 2 * radius, y - 3 * radius);
	glVertex2f(x + 2.4 * radius, y - 3 * radius);
	glEnd();
	glFlush();

	
	// Legs
	glColor3f(0.25f, 0.25f, 0.25f);
	glLineWidth(30.0);
	glBegin(GL_LINES);
	glVertex2f(x - 0.5 * radius, y - 4.0 * radius);
	glVertex2f(x - 2 * radius, y - 6 * radius);
	glVertex2f(x + 0.5 * radius, y - 4.0 * radius);
	glVertex2f(x + 2 * radius, y - 6 * radius);
	glEnd();
	glFlush();

	// Trunk
	glColor3f(0.59f, 0.59f, 0.59f);
	glBegin(GL_QUADS);
	glVertex2f(x + 2 * radius, y - 4.41 * radius);
	glVertex2f(x - 0.85 * radius, y - 4 * radius);
	glVertex2f(x - 0.85 * radius, y - 2.3 * radius);
	glVertex2f(x + 2 * radius, y - 2 * radius);
	glEnd();
	glFlush();


	// Arms
	glColor3f(0.59f, 0.59f, 0.59f);
	float rx1, rx2, ry1, ry2;
	rx1 = x + 1.8 * radius;
	rx2 = x + 1.6 * radius;
	ry1 = y - 2.3 * radius;
	ry2 = y - 0.3 * radius;

	float lx1, lx2, ly1, ly2;
	lx1 = x + 1.8 * radius;
	lx2 = x + 2.1 * radius;
	ly1 = y - 4.2 * radius;
	ly2 = y - 6 * radius;

	glLineWidth(18.0);
	glBegin(GL_LINES);
	glVertex2f(rx1, ry1);
	glVertex2f(rx2, ry2);
	glVertex2f(lx1, ly1);
	glVertex2f(lx2, ly2);
	glEnd();
	glFlush();

	// Wrists
	glColor3f(0.63f, 0.4f, 0.37f);
	float rv1, rv2, rw1, rw2;
	float lv1, lv2, lw1, lw2;
	lv1 = lx2 + 0.05 * radius;
	lw1 = ly2 - 0.2 * radius;
	rv1 = rx2 + 0.03 * radius;
	rw1 = ry2 + 0.2 * radius;
	lv2 = lx2;
	lw2 = lw1 + 0.2 * radius;
	rv2 = rv1;
	rw2 = rw1 - 0.2 * radius;


	glLineWidth(18.0);
	glBegin(GL_LINES);
	glVertex2f(rv1, rw1);
	glVertex2f(rv2, rw2);
	glVertex2f(lv1, lw1);
	glVertex2f(lv2, lw2);
	glEnd();
	glFlush();

	// Land Boundary
	glColor3f(0.0f, 1.0f, 0.0f);
	glLineWidth(10.0);
	glBegin(GL_LINES);
	glVertex2f(0, 150);
	glVertex2f(900, 150);
	glColor3f(0.0f, 0.0f, 1.0f);
	glEnd();
	glFlush();
}

void WideLegForwardFold(GLfloat x, GLfloat y, GLfloat radius)
{
	// Skull of the Person
	glColor3f(0.63f, 0.4f, 0.37f);
	int i;
	int triangleAmount = 20;
	GLfloat twicePi = 2.0f * M_PI;
	glBegin(GL_TRIANGLE_FAN);
	// center of circle
	glVertex2f(x, y - 5.8 * radius);
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (radius * cos(i * twicePi / triangleAmount)),
			y + (radius * sin(i * twicePi / triangleAmount)) - 5.8 * radius
		);
	}
	glEnd();
	glFlush();


	// Neck
	glColor3f(0.63f, 0.4f, 0.37f);
	glLineWidth(25.0);
	glBegin(GL_LINES);
	glVertex2f(x, y - 4.7 * radius);
	glVertex2f(x, y - 5.2 * radius);
	glEnd();
	glFlush();

	// Legs
	glColor3f(0.25f, 0.25f, 0.25f);
	glLineWidth(30.0);
	glBegin(GL_LINES);
	glVertex2f(x - 1 * radius, y - 1.7 * radius);
	glVertex2f(x - 2.8 * radius, y - 6 * radius);
	glVertex2f(x + 1 * radius, y - 1.7 * radius);
	glVertex2f(x + 2.8 * radius, y - 6 * radius);
	glEnd();
	glFlush();


	// Trunk
	glColor3f(0.59f, 0.59f, 0.59f);
	glBegin(GL_QUADS);
	glVertex2f(x - 1.2 * radius, y - 4.7 * radius);
	glVertex2f(x + 1.2 * radius, y - 4.7 * radius);
	glVertex2f(x + 1 * radius, y - 1.7 * radius);
	glVertex2f(x - 1 * radius, y - 1.7 * radius);
	glEnd();
	glFlush();

	
	// Arms
	glColor3f(0.59f, 0.59f, 0.59f);
	float rx1, rx2, ry1, ry2;
	rx1 = x + 1.1 * radius;
	rx2 = x + 2.8 * radius;
	ry1 = y - 4.5 * radius;
	ry2 = y - 6 * radius;

	float lx1, lx2, ly1, ly2;
	lx1 = x - 1.1 * radius;
	lx2 = x - 2.8 * radius;
	ly1 = y - 4.5 * radius;
	ly2 = y - 6 * radius;

	glLineWidth(22.0);
	glBegin(GL_LINES);
	glVertex2f(rx1, ry1);
	glVertex2f(rx2, ry2);
	glVertex2f(lx1, ly1);
	glVertex2f(lx2, ly2);
	glEnd();
	glFlush();

	// Wrists
	glColor3f(0.63f, 0.4f, 0.37f);
	float rv1, rv2, rw1, rw2;
	float lv1, lv2, lw1, lw2;
	lv1 = lx2 + 0.1 * radius;
	lw1 = ly2 + 0.3 * radius;
	rv1 = rx2 - 0.1 * radius;
	rw1 = ry2 + 0.3 * radius;
	lv2 = lv1 - 0.1 * radius;
	lw2 = lw1 - 0.6 * radius;
	rv2 = rv1 + 0.1 * radius;;
	rw2 = rw1 - 0.6 * radius;


	glLineWidth(18.0);
	glBegin(GL_LINES);
	glVertex2f(rv1, rw1);
	glVertex2f(rv2, rw2);
	glVertex2f(lv1, lw1);
	glVertex2f(lv2, lw2);
	glEnd();
	glFlush();

	// Land Boundary
	glColor3f(0.0f, 1.0f, 0.0f);
	glLineWidth(10.0);
	glBegin(GL_LINES);
	glVertex2f(0, 150);
	glVertex2f(900, 150);
	glColor3f(0.0f, 0.0f, 1.0f);
	glEnd();
	glFlush();
}

void bodyPersonJump(GLfloat ang, GLfloat x, GLfloat y, GLfloat radius, GLfloat eyeL = 2, GLfloat eyeR = 2, GLfloat eyeV = 4)
{
	// Skull of the Person
	glColor3f(0.63f, 0.4f, 0.37f);
	int i;
	int triangleAmount = 20;
	GLfloat twicePi = 2.0f * M_PI;
	glBegin(GL_TRIANGLE_FAN);
	// center of circle
	glVertex2f(x, y);
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (radius * cos(i * twicePi / triangleAmount)),
			y + (radius * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();
	glFlush();

	// Eyes of the Person
	glColor3f(1.0f, 1.0f, 1.0f);
	glPointSize(15.0);
	glBegin(GL_POINTS);
	glVertex2f(x - radius / 2, y + radius / 4);
	glVertex2f(x + radius / 2, y + radius / 4);
	glEnd();
	glFlush();
	glPointSize(5.0);
	glBegin(GL_POINTS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(x - radius / eyeL, y + radius / eyeV);
	glVertex2f(x + radius / eyeR, y + radius / eyeV);
	glEnd();
	glFlush();

	// Nose of the Person
	glColor3f(1.0f, 1.0f, 1.0f);
	glLineWidth(5.0);
	glBegin(GL_LINES);
	glVertex2f(x, y + radius / 4);
	glVertex2f(x, y - radius / 4);
	glEnd();
	glFlush();

	// Lips of the Person
	glColor3f(1.0f, 0.0f, 0.0f);
	glLineWidth(5.0);
	glBegin(GL_LINES);
	glVertex2f(x - radius / 4, y - radius / 2);
	glVertex2f(x + radius / 4, y - radius / 2);
	glEnd();
	glFlush();


	// Neck
	glColor3f(0.63f, 0.4f, 0.37f);
	glLineWidth(25.0);
	glBegin(GL_LINES);
	glVertex2f(x, y - 0.8 * radius);
	glVertex2f(x, y - 1.2 * radius);
	glEnd();
	glFlush();

	// Trunk
	glColor3f(0.59f, 0.59f, 0.59f);
	glBegin(GL_QUADS);
	glVertex2f(x - 1.1 * radius, y - 4 * radius);
	glVertex2f(x + 1.1 * radius, y - 4 * radius);
	glVertex2f(x + 1.1 * radius, y - 1.1 * radius);
	glVertex2f(x - 1.1 * radius, y - 1.1 * radius);
	glEnd();
	glFlush();

	// Legs
	glColor3f(0.25f, 0.25f, 0.25f);
	glLineWidth(40.0);
	glBegin(GL_LINES);
	glVertex2f(x - 0.7 * radius, y - 4 * radius);
	glVertex2f(x - 2.2 * radius, y - 6 * radius);
	glVertex2f(x + 0.7 * radius, y - 4 * radius);
	glVertex2f(x + 2.2 * radius, y - 6 * radius);
	glEnd();
	glFlush();

	// Rotation of arms
	// Angle of rotation
	float angle = ang * M_PI / 180.0;

	// Rotation of Arms
	glColor3f(0.59f, 0.59f, 0.59f);
	float rx1, rx2, ry1, ry2;
	rx1 = x + 1.1 * radius;
	rx2 = x + 3.3 * radius;
	ry1 = y - 1.4 * radius;
	ry2 = y - 1.4 * radius;
	float rx2_rotated = rx1 + (rx2 - rx1) * cos(angle) - (ry2 - ry1) * sin(angle);
	float ry2_rotated = ry1 + (rx2 - rx1) * sin(angle) + (ry2 - ry1) * cos(angle);

	float lx1, lx2, ly1, ly2;
	lx1 = x - 1.1 * radius;
	lx2 = x - 3.3 * radius;
	ly1 = y - 1.4 * radius;
	ly2 = y - 1.4 * radius;
	float lx2_rotated = lx1 + (lx2 - lx1) * cos(-1 * angle) - (ly2 - ly1) * sin(-1 * angle);
	float ly2_rotated = ly1 + (lx2 - lx1) * sin(-1 * angle) + (ly2 - ly1) * cos(-1 * angle);

	glLineWidth(24.0);
	glBegin(GL_LINES);
	glVertex2f(rx1, ry1);
	glVertex2f(rx2_rotated, ry2_rotated);
	glVertex2f(lx1, ly1);
	glVertex2f(lx2_rotated, ly2_rotated);
	glEnd();
	glFlush();

	// Rotation of wrists
	glColor3f(0.63f, 0.4f, 0.37f);
	float rv1, rv2, rw1, rw2;
	float lv1, lv2, lw1, lw2;
	lv1 = lx2_rotated;
	lw1 = ly2_rotated;
	rv1 = rx2_rotated;
	rw1 = ry2_rotated;
	lv2 = lv1 - 0.4 * radius;;
	lw2 = lw1;// For slope to wrist, add 0.1 * radius;
	rv2 = rv1 + 0.4 * radius;
	rw2 = rw1;// For slope to wrist, add 0.1 * radius;

	float rv2_rotated = rv1 + (rv2 - rv1) * cos(angle) - (rw2 - rw1) * sin(angle);
	float rw2_rotated = rw1 + (rv2 - rv1) * sin(angle) + (rw2 - rw1) * cos(angle);

	float lv2_rotated = lv1 + (lv2 - lv1) * cos(-1 * angle) - (lw2 - lw1) * sin(-1 * angle);
	float lw2_rotated = lw1 + (lv2 - lv1) * sin(-1 * angle) + (lw2 - lw1) * cos(-1 * angle);

	glLineWidth(22.0);
	glBegin(GL_LINES);
	glVertex2f(rv1, rw1);
	glVertex2f(rv2_rotated, rw2_rotated);
	glVertex2f(lv1, lw1);
	glVertex2f(lv2_rotated, lw2_rotated);
	glEnd();
	glFlush();

	// Land Boundary
	glColor3f(0.0f, 1.0f, 0.0f);
	glLineWidth(10.0);
	glBegin(GL_LINES);
	glVertex2f(0, 150);
	glVertex2f(900, 150);
	glColor3f(0.0f, 0.0f, 1.0f);
	glEnd();
	glFlush();

}

void Cartwheel(GLfloat x, GLfloat y, GLfloat radius)
{
	// Skull of the Person
	glColor3f(0.63f, 0.4f, 0.37f);
	int i;
	int triangleAmount = 20;
	GLfloat twicePi = 2.0f * M_PI;
	glBegin(GL_TRIANGLE_FAN);
	// center of circle
	glVertex2f(x - 3.3 * radius, y - 3 * radius);
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (radius * cos(i * twicePi / triangleAmount)) - 3.3 * radius,
			y + (radius * sin(i * twicePi / triangleAmount)) - 3 * radius
		);
	}
	glEnd();
	glFlush();

	// Eyes of the Person
	glColor3f(1.0f, 1.0f, 1.0f);
	glPointSize(15.0);
	glBegin(GL_POINTS);
	glVertex2f(x - 3.7 * radius, y - 3.4 * radius);
	glVertex2f(x - 3.7 * radius, y - 2.6 * radius);
	glEnd();
	glFlush();
	glPointSize(5.0);
	glBegin(GL_POINTS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(x - 3.7 * radius, y - 3.25 * radius);
	glVertex2f(x - 3.7 * radius, y - 2.45 * radius);
	glEnd();
	glFlush();

	// Nose of the Person
	glColor3f(1.0f, 1.0f, 1.0f);
	glLineWidth(5.0);
	glBegin(GL_LINES);
	glVertex2f(x - 3.5 * radius, y - 3 * radius);
	glVertex2f(x - 3.0 * radius, y - 3 * radius);
	glEnd();
	glFlush();

	// Lips of the Person
	glColor3f(1.0f, 0.0f, 0.0f);
	glLineWidth(5.0);
	glBegin(GL_LINES);
	glVertex2f(x - 2.6 * radius, y - 2.85 * radius);
	glVertex2f(x - 2.6 * radius, y - 3.05 * radius);
	glEnd();
	glFlush();


	// Neck
	glColor3f(0.63f, 0.4f, 0.37f);
	glLineWidth(25.0);
	glBegin(GL_LINES);
	glVertex2f(x - 2 * radius, y - 3 * radius);
	glVertex2f(x - 2.4 * radius, y - 3 * radius);
	glEnd();
	glFlush();

	// Legs
	glColor3f(0.25f, 0.25f, 0.25f);
	glLineWidth(30.0);
	glBegin(GL_LINES);
	glVertex2f(x - 0.5 * radius, y - 4 * radius);
	glVertex2f(x - 2 * radius, y - 6 * radius);
	glVertex2f(x + 0.5 * radius, y - 4 * radius);
	glVertex2f(x + 2 * radius, y - 6 * radius);
	glEnd();
	glFlush();

	// Trunk
	glColor3f(0.59f, 0.59f, 0.59f);
	glBegin(GL_QUADS);
	glVertex2f(x - 2 * radius, y - 4.3 * radius);
	glVertex2f(x + 0.85 * radius, y - 4 * radius);
	glVertex2f(x + 0.85 * radius, y - 2.3 * radius);
	glVertex2f(x - 2 * radius, y - 2 * radius);
	glEnd();
	glFlush();

	// Arms
	glColor3f(0.59f, 0.59f, 0.59f);
	float rx1, rx2, ry1, ry2;
	rx1 = x - 1.8 * radius;
	rx2 = x - 1.6 * radius;
	ry1 = y - 2.3 * radius;
	ry2 = y - 0.3 * radius;

	float lx1, lx2, ly1, ly2;
	lx1 = x - 1.8 * radius;
	lx2 = x - 2.1 * radius;
	ly1 = y - 4.2 * radius;
	ly2 = y - 6 * radius;

	glLineWidth(12.0);
	glBegin(GL_LINES);
	glVertex2f(rx1, ry1);
	glVertex2f(rx2, ry2);
	glVertex2f(lx1, ly1);
	glVertex2f(lx2, ly2);
	glEnd();
	glFlush();

	// Wrists
	glColor3f(0.63f, 0.4f, 0.37f);
	float rv1, rv2, rw1, rw2;
	float lv1, lv2, lw1, lw2;
	lv1 = lx2 - 0.05 * radius;
	lw1 = ly2;
	rv1 = rx2 - 0.03 * radius;
	rw1 = ry2;
	lv2 = lx2;
	lw2 = lw1 + 0.4 * radius;
	rv2 = rv1;
	rw2 = rw1 - 0.4 * radius;


	glLineWidth(15.0);
	glBegin(GL_LINES);
	glVertex2f(rv1, rw1);
	glVertex2f(rv2, rw2);
	glVertex2f(lv1, lw1);
	glVertex2f(lv2, lw2);
	glEnd();
	glFlush();

	// Land Boundary
	glColor3f(0.0f, 1.0f, 0.0f);
	glLineWidth(10.0);
	glBegin(GL_LINES);
	glVertex2f(0, 150);
	glVertex2f(900, 150);
	glColor3f(0.0f, 0.0f, 1.0f);
	glEnd();
	glFlush();
}


// Function for performing different Postures
void performPostures() {
	
	std::string text;
	glClear(GL_COLOR_BUFFER_BIT);
	
	text = "WELCOME TO PROJECT YOGADO";
	drawHeading(text.data(), text.size(), 230, 500);
	
	glColor3f(0.0f, 1.0f, 0.0f);
	text = "For the love of the Yoga";
	drawText(text.data(), text.size(), 300, 450);
	glColor3f(0.0f, 0.0f, 1.0f);
	welcome(30.0f, 400.0f, 300.0f, 40.0f);
	delay(3000);

	// FIRST EXERCISE
	// Arm Movement
	glClear(GL_COLOR_BUFFER_BIT);
	
	for (int i = 0; i < 9; i++) {
		text = "Arm Movement with 30° Angle";
		glColor3f(0.63f, 0.4f, 0.37f);
		drawText(text.data(), text.size(), 280, 500);
		if (i % 4 == 0) {
			bodyPerson(0.0f, 400.0f, 400.0f, 40.0f);
		}
		else if (i % 4 == 1) {
			bodyPerson(30.0f, 400.0f, 400.0f, 40.0f);
		}
		else if (i % 4 == 2) {
			bodyPerson(0.0f, 400.0f, 400.0f, 40.0f);
		}
		else if (i % 4 == 3) {
			bodyPerson(-30.0f, 400.0f, 400.0f, 40.0f);
		}
		Beep(5000, 150);
		delay(1000);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	// SECOND EXERCISE
	for (int i = 0; i < 9; i++) {
		text = "Arm Movement with 90° Angle";
		glColor3f(0.63f, 0.4f, 0.37f);
		drawText(text.data(), text.size(), 280, 500);
		if (i % 4 == 0) {
			bodyPerson(0.0f, 400.0f, 400.0f, 40.0f);
		}
		else if (i % 4 == 1) {
			bodyPerson(90.0f, 400.0f, 400.0f, 40.0f);
		}
		else if (i % 4 == 2) {
			bodyPerson(0.0f, 400.0f, 400.0f, 40.0f);
		}
		else if (i % 4 == 3) {
			bodyPerson(-90.0f, 400.0f, 400.0f, 40.0f);
		}
		Beep(5000, 150);
		delay(1000);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	
	
	// THIRD EXERCISE - Trikonasana Left
	cout << "Trikonasana Left";
	glClear(GL_COLOR_BUFFER_BIT);
	text = "Left Trikonasana";
	glColor3f(0.63f, 0.4f, 0.37f);
	drawText(text.data(), text.size(), 320, 500);
	bodyPerson(0.0f, 400.0f, 400.0f, 40.0f, 2, 2, 4);
	Beep(5000, 150);
	delay(1000);
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < 9; i++) {
		text = "Left Trikonasana";
		glColor3f(0.63f, 0.4f, 0.37f);
		drawText(text.data(), text.size(), 320, 500);
		if (i % 2 == 0) {
			TrikonasanaLeft(400.0f, 400.0f, 40.0f);
		}
		else if (i % 2 == 1) {
			bodyPerson(0.0f, 400.0f, 400.0f, 40.0f);
		}
		Beep(5000, 150);
		delay(1000);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	
	
	// FOURTH EXERCISE - Trikonasana Right
	cout << "Trikonasana Right";
	glClear(GL_COLOR_BUFFER_BIT);
	text = "Right Trikonasana";
	glColor3f(0.63f, 0.4f, 0.37f);
	drawText(text.data(), text.size(), 320, 500);
	bodyPerson(0.0f, 400.0f, 400.0f, 40.0f, 2, 2, 4);
	Beep(5000, 150);
	delay(1000);
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < 9; i++) {
		text = "Right Trikonasana";
		glColor3f(0.63f, 0.4f, 0.37f);
		drawText(text.data(), text.size(), 320, 500);
		if (i % 2 == 0) {
			TrikonasanaRight(400.0f, 400.0f, 40.0f);
		}
		else if (i % 2 == 1) {
			bodyPerson(0.0f, 400.0f, 400.0f, 40.0f);
		}
		Beep(5000, 150);
		delay(1000);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	
	// FIFTH EXERCISE - Trikonasana Left + Right
	cout << "Trikonasana Left + Right";
	glClear(GL_COLOR_BUFFER_BIT);
	text = "Trikonasana";
	glColor3f(0.63f, 0.4f, 0.37f);
	drawText(text.data(), text.size(), 340, 500);
	bodyPerson(-90.0f, 400.0f, 400.0f, 40.0f, 2, 2, 4);
	Beep(5000, 150);
	delay(1000);
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < 9; i++) {
		text = "Trikonasana";
		glColor3f(0.63f, 0.4f, 0.37f);
		drawText(text.data(), text.size(), 340, 500);
		if (i % 4 == 0) {
			TrikonasanaLeft(400.0f, 400.0f, 40.0f);
		}
		else if (i % 4 == 1) {
			bodyPerson(0.0f, 400.0f, 400.0f, 40.0f);
		}
		if (i % 4 == 2) {
			TrikonasanaRight(400.0f, 400.0f, 40.0f);
		}
		else if (i % 4 == 3) {
			bodyPerson(0.0f, 400.0f, 400.0f, 40.0f);
		}
		Beep(5000, 150);
		delay(1000);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	

	// SIXTH EXERCISE - Eye Movement
	glClear(GL_COLOR_BUFFER_BIT);
	text = "Eye Movement";
	glColor3f(0.63f, 0.4f, 0.37f);
	drawText(text.data(), text.size(), 330, 500);
	bodyPerson(0.0f, 400.0f, 400.0f, 40.0f, 2, 2, 4);
	Beep(5000, 150);
	delay(500);
	for (int i = 0; i < 9; i++) {
		text = "Eye Movement";
		glColor3f(0.63f, 0.4f, 0.37f);
		drawText(text.data(), text.size(), 330, 500);
		if (i % 4 == 0) {
			bodyPerson(0.0f, 400.0f, 400.0f, 40.0f, 1.6, 3, 4);
		}
		else if (i % 4 == 1) {
			bodyPerson(0.0f, 400.0f, 400.0f, 40.0f, 2, 2, 6.5);
		}
		else if (i % 4 == 2) {
			bodyPerson(0.0f, 400.0f, 400.0f, 40.0f, 3, 1.5, 4);
		}
		else if (i % 4 == 3) {
			bodyPerson(0.0f, 400.0f, 400.0f, 40.0f, 2, 2, 2.6);
		}
		Beep(5000, 150);
		delay(500);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	text = "Eye Movement";
	glColor3f(0.63f, 0.4f, 0.37f);
	drawText(text.data(), text.size(), 330, 500);
	bodyPerson(-90.0f, 400.0f, 400.0f, 40.0f, 2, 2, 4);
	delay(1000);
	
	
	// SEVENTH EXERCISE - Wide Leg Forward Fold
	cout << "Wide Leg Forward Fold";
	glClear(GL_COLOR_BUFFER_BIT);
	text = "Wide Leg Forward Fold";
	glColor3f(0.63f, 0.4f, 0.37f);
	drawText(text.data(), text.size(), 290, 500);
	bodyPerson(45.0f, 400.0f, 400.0f, 40.0f, 2, 2, 4);
	Beep(5000, 150);
	delay(1000);
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < 9; i++) {
		text = "Wide Leg Forward Fold";
		glColor3f(0.63f, 0.4f, 0.37f);
		drawText(text.data(), text.size(), 290, 500);
		if (i % 2 == 0) {
			WideLegForwardFold(400.0f, 400.0f, 40.0f);
		}
		else if (i % 2 == 1) {
			bodyPerson(45.0f, 400.0f, 400.0f, 40.0f);
		}
		Beep(5000, 150);
		delay(1000);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	bodyPerson(0.0f, 400.0f, 400.0f, 40.0f, 2, 2, 4);
	
	// EIGTH EXERCISE - Jumping
	cout << "Jumping";
	glClear(GL_COLOR_BUFFER_BIT);
	text = "Jumping";
	glColor3f(0.63f, 0.4f, 0.37f);
	drawText(text.data(), text.size(), 350, 500);
	bodyPerson(0.0f, 400.0f, 400.0f, 40.0f, 2, 2, 4);
	Beep(5000, 150);
	delay(1000);
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < 9; i++)
	{
		text = "Jumping";
		glColor3f(0.63f, 0.4f, 0.37f);
		drawText(text.data(), text.size(), 350, 500);
		if (i % 2 == 1)
			bodyPerson(-10.0f, 400.0f, 400.0f, 40.0f, 2, 2, 4);
		if (i % 2 == 0)
			bodyPersonJump(45.0f, 400.0f, 480.0f, 40.0f, 2, 2, 4);
		Beep(5000, 150);
		delay(1000);
		glClear(GL_COLOR_BUFFER_BIT);

	}
	
	// NINTH EXERCISE - Cartwheel
	cout << "Cartwheel";
	glClear(GL_COLOR_BUFFER_BIT);
	text = "Cartwheel";
	glColor3f(0.63f, 0.4f, 0.37f);
	drawText(text.data(), text.size(), 320, 500);
	bodyPerson(0.0f, 550.0f, 400.0f, 40.0f, 2, 2, 4);
	Beep(5000, 150);
	delay(1000);
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < 8; i++) {
		text = "Cartwheel";
		glColor3f(0.63f, 0.4f, 0.37f);
		drawText(text.data(), text.size(), 320, 500);
		if (i % 4 == 0)
			Cartwheel(550.0f, 400.0f, 40.0f);
		
		else if (i % 4 == 1)
			bodyPerson(90.0f, 450.0f, 200.0f, -40.0f);
	
		else if (i % 4 == 2)
			TrikonasanaRight(250.0f, 400.0f, 40.0f);

		else if (i % 4 == 3)
			bodyPerson(-90.0f, 200.0f, 400.0f, 40.0f, 2, 2, 4);
		
		Beep(5000, 150);
		delay(1000);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.63f, 0.4f, 0.37f);
	text = "EXERCISE HARD";
	drawHeading(text.data(), text.size(), 300, 500);
	glColor3f(0.0f, 1.0f, 0.0f);
	text = "THANK YOU";
	drawHeading(text.data(), text.size(), 320, 450);
	
	// Restart Button
	glColor3f(0.63f, 0.4f, 0.37f);
	glBegin(GL_QUADS);
	glVertex2f(650,200);
	glVertex2f(770,200);
	glVertex2f(770,250);
	glVertex2f(650,250);
	glEnd();
	glFlush();
	glColor3f(1.0f, 1.0f, 1.0f);
	text = "RESTART";
	drawHeading(text.data(), text.size(), 625, 190);

	welcome(30.0f, 400.0f, 300.0f, 40.0f);
	delay(5000);

}


void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(840, 680);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Project Yogado");
	glutDisplayFunc(performPostures);
	glutMouseFunc(mouse);
	myInit();
	glutMainLoop();
}


void mouse(int btn, int state, int x, int y)
{
	if ((x < 640 || x>775) || (y < 425 || y>485)) {
		cout << "Invalid Click\n";
	}
	else {
		if ((btn == GLUT_LEFT_BUTTON || btn == GLUT_RIGHT_BUTTON) && state == GLUT_DOWN) {
			performPostures();	
		}
	}
}