/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

boolean amb = true;
void init(void)
{
glClearColor (0.0, 0.0, 0.0, 0.0);
glColor3f(0.0, 0.0, 0.0);
GLfloat ambient_light[] = { 0.9, 0.9, 0.9, 1.0 };
glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambient_light);
glEnable(GL_LIGHTING);
glEnable(GL_DEPTH_TEST);
glShadeModel (GL_SMOOTH);
}
void display(void)
{
glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glutSolidTeapot(1);
glFlush ();
}
void reshape (int w, int h)
{
glViewport (0, 0, (GLsizei) w, (GLsizei) h);
glMatrixMode (GL_PROJECTION);
glLoadIdentity();
if (w <= h)
glOrtho (-1.5, 1.5, -1.5*(GLfloat)h/(GLfloat)w,
1.5*(GLfloat)h/(GLfloat)w, - 10.0, 10.0);
else
glOrtho (-1.5*(GLfloat)w/(GLfloat)h, 1.5*(GLfloat)w/(GLfloat)h, -
1.5, 1.5, -10.0, 10.0);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
}
void mykey(unsigned char key, int mouseX, int mouseY){
if (key=='1'){
if (amb == true){
GLfloat ambient_light[] = { 0.3, 0.3, 0.3, 1.0 };
glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambient_light);
amb = false;
}
else{
GLfloat ambient_light[] = { 0.9, 0.9, 0.9, 1.0 };
glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambient_light);
amb = true;
}
display();
}
}
int main(int argc, char** argv)
{
glutInit(&argc, argv);
glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
glutInitWindowSize (500, 500); glutInitWindowPosition (100, 100);
glutCreateWindow (argv[0]);
init ();
glutDisplayFunc(display);
glutReshapeFunc(reshape);
glutKeyboardFunc(mykey);
glutMainLoop();
return 0;
}
