#include <windows.h>
#include <cmath>
#include <algorithm>
#include <vector>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


void drawRectangle(float x, float y, float width, float height) {
    glBegin(GL_POLYGON);
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height);
    glEnd();
}

void print1(float x, float y) {
    glColor3f(1, 0, 0);
    drawRectangle(x + 0.1, y, 0.1, 0.5);
}

void print2(float x, float y) {
    glColor3f(1, 0, 0);

    drawRectangle(x, y + 0.4, 0.3, 0.1);
    drawRectangle(x, y + 0.2, 0.1, 0.2);
    drawRectangle(x, y + 0.2, 0.3, 0.1);
    drawRectangle(x + 0.2, y, 0.1, 0.2);
    drawRectangle(x, y, 0.3, 0.1);
}

void print5(float x, float y) {
    glColor3f(1, 0, 0);
    drawRectangle(x, y + 0.4, 0.3, 0.1);
    drawRectangle(x + 0.2, y + 0.2, 0.1, 0.2);
    drawRectangle(x, y + 0.2, 0.3, 0.1);
    drawRectangle(x, y, 0.1, 0.2);
    drawRectangle(x, y, 0.3, 0.1);
}

void print6(float x, float y) {
    glColor3f(1, 0, 0);

    drawRectangle(x, y + 0.4, 0.3, 0.1);
    drawRectangle(x, y, 0.1, 0.5);
    drawRectangle(x, y, 0.3, 0.1);
    drawRectangle(x, y + 0.2, 0.3, 0.1);
    drawRectangle(x + 0.2, y, 0.1, 0.2);
}

void print7(float x, float y) {
    glColor3f(1, 0, 0);
    drawRectangle(x, y + 0.4, 0.3, 0.1);
    drawRectangle(x + 0.2, y, 0.1, 0.5);
}



void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(10);
    glLineWidth(20);

    // glBegin(GL_POINT)
    // glTranslatef(2, 2, 0);
    glBegin(GL_POLYGON);
        glVertex2d(3, 3);
        glVertex2d(3, 5);
        glVertex2d(5, 5);
        glVertex2d(5, 3);
    glEnd();

    glScalef(-2, -2, 0);
    glColor3f(1, 0.1, 0);
    glBegin(GL_POLYGON);
        glVertex2d(3, 3);
        glVertex2d(3, 5);
        glVertex2d(5, 5);
        glVertex2d(5, 3);
    glEnd();

	glFlush();
}

void myinit(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 12.7, 8.3, 0);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0,0,0,0);
	glColor3f(0.0,0.0,1.0);
}

int main(int argc, char* argv[]){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(12*50, 7*50);
	//glutInitWindowPosition(100,100);
	glutCreateWindow("Segitiga Titik");
	glutDisplayFunc(display);
	myinit();
	glutMainLoop();

	return 0;
}
