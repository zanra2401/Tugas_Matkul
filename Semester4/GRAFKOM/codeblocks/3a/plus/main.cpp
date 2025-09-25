#include <windows.h>
#include <cmath>
#include <algorithm>
#include <vector>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void generateBackground(float size[2], float red, float green, float blue) {
    glColor3f(red, green, blue);
    glBegin(GL_POLYGON);
        glVertex2d(0 + 0.25, 0 + 0.25);
        glVertex2d(0 + 0.25, size[1] + 0.25);
        glVertex2d(size[0] + 0.25, size[1] + 0.25);
        glVertex2d(size[0] + 0.25, 0 + 0.25);
    glEnd();
}

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

void generateMap(int row, int col, float red, float green, float blue)
{
    glColor3f(red, green, blue);

    std::vector<int> valid;
    valid.push_back(1);
    valid.push_back(5);
    valid.push_back(7);
    valid.push_back(2);
    valid.push_back(6);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            int odd = j % 2;
            int pertama = floor((j + 1) / 10);
            int kedua = floor((j + 1) % 10);

            switch (odd) {
                case 0:
                    glColor3f(255, 255, 255);
                    break;
                case 1:
                    glColor3f(0, 0, 1);
                    break;
            }

            glBegin(GL_POLYGON);
                glVertex2d(0 + (j * 1) + 0.1 + 0.25, 0 + (i * 1 + (0.1 * i)) + 0.1 + 0.25);
                glVertex2d(0 + (j * 1) + 0.1 + 0.25, 1 + (i * 1 + (0.1 * i)) + 0.1 + 0.25);
                glVertex2d(1 + (j * 1) + 0.1 + 0.25, 1 + (i * 1 + (0.1 * i)) + 0.1 + 0.25);
                glVertex2d(1 + (j * 1) + 0.1 + 0.25, 0 + (i * 1 + (0.1 * i)) + 0.1 + 0.25);
            glEnd();

            if (std::find(valid.begin(), valid.end(), kedua) != valid.end()) {
                switch (kedua) {
                    case 1:
                        print1(1 + (j * 1) - 0.1, 0 + (i * 1 + (0.1 * i)) + 0.1 + 0.25 + 0.1);
                        break;
                    case 5:
                        print5(1 + (j * 1) - 0.1, 0 + (i * 1 + (0.1 * i)) + 0.1 + 0.25 + 0.1);
                        break;
                    case 7:
                        print7(1 + (j * 1) - 0.1, 0 + (i * 1 + (0.1 * i)) + 0.1 + 0.25 + 0.1);
                        break;
                    case 2:
                        print2(1 + (j * 1)- 0.1 , 0 + (i * 1 + (0.1 * i)) + 0.1 + 0.25 + 0.1);
                        break;
                    case 6:
                        print5(1 + (j * 1) - 0.1, 0 + (i * 1 + (0.1 * i)) + 0.1 + 0.25 + 0.1);
                        break;
                }

            }

            if (pertama != 0) {

            }
        }
    }
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(10);
    glLineWidth(20);

    // glBegin(GL_POINT)
    float size[2] = {12.2, 7.8};
    generateBackground(size, 0, 1, 0);
    generateMap(7, 12, 0, 0, 1);

    print1(0.5, 0.5);
    print5(0.8, 0.5);

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
