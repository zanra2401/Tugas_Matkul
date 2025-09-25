#include <windows.h>
#include<iostream>
#include <cmath>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


float pos[3];
GLdouble viewdir[] = {-1.0, 0.0, 0.0};

void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(pos[0], pos[1], pos[2], pos[0]+viewdir[0], pos[1]+viewdir[1], pos[2]+viewdir[2], 0,1,0);

    glutSolidSphere(1.0, 40, 16);
    glTranslated(0,0,3);
    glutSolidTeapot(1);
    glTranslated(0,0,-6);
    glutSolidTorus(0.3,0.7,12,12);
	glFlush();
}

void reshape(int w, int h){
    glViewport(0,0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(-5,5,-5,5,-5,5);
    gluPerspective(65.0, (GLfloat) w / (GLfloat) h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
}

void myinit(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-2.0,2.0,-2.0,2.0);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.0,0.0,0.0,1.0);
	glColor3f(0.0,0.0,1.0);

	GLfloat light_position_diff[] = { -1.0, 1.0, 1.0, 0.0 };
GLfloat diffuse_light[] = { 0.0, 0.0, 1.0, 1.0 };
GLfloat light_position_spec[] = { 1.0, 1.0, 1.0, 0.0 };
GLfloat specular_light[] = { 0.0, 1.0, 0.0, 1.0 };
GLfloat ambient_light[] = { 0.9, 0.9, 0.9, 1.0 };
glLightfv(GL_LIGHT0, GL_POSITION, light_position_diff);
glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
glLightfv(GL_LIGHT1, GL_POSITION, light_position_spec);
glLightfv(GL_LIGHT1, GL_SPECULAR, specular_light);
glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambient_light);
glEnable(GL_LIGHTING);
glEnable(GL_DEPTH_TEST);
glShadeModel (GL_SMOOTH);
glEnable(GL_LIGHT0);
glEnable(GL_LIGHT1);

    pos[0] = 10.0;
    pos[1] = 0.0;
    pos[2] = 0.0;
}

void mykey(unsigned char key, int mouseX, int mouseY){
    if (key=='g'){
            pos[0] += 0.2 * viewdir[0];
            pos[1] += 0.2 * viewdir[1];
            pos[2] += 0.2 * viewdir[2];
    }
    if (key=='b'){
            pos[0] -= 0.2 * viewdir[0];
            pos[1] -= 0.2 * viewdir[1];
            pos[2] -= 0.2 * viewdir[2];
    }
    if (key=='n'){
        viewdir[0] = viewdir[0] * cos(-0.03) + viewdir[2] * sin(-0.03);
        viewdir[2] = -viewdir[0] * sin(-0.03) + viewdir[2] * cos(-0.03);
    }
    if (key=='v'){
        viewdir[0] = viewdir[0] * cos(0.03) + viewdir[2] * sin(0.03);
        viewdir[2] = -viewdir[0] * sin(0.03) + viewdir[2] * cos(0.03);
    }
    display();
}

int main(int argc, char* argv[]){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500,500);
	//glutInitWindowPosition(100,100);
	glutCreateWindow("Segitiga Titik");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(mykey);
	myinit();
	glutMainLoop();

	return 0;
}
