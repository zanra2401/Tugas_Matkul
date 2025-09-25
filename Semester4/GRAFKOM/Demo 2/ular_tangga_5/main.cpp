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
#include <cmath>
#include <iostream>
#include <algorithm>
#include <time.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>


// 230411100001 Intan Aulia Majid
// 230411100015 Fatimah Azzahra
// 230411100047 Yunika Lestari
// 230411100087 Zanuar Rikza Aditiya
// 230411100092 Nabiilah Rizqi Amalia
// 230411100096 Tuhu Pangestu

struct Vector2D {
    float x;
    float y;
};


// Demo 3
struct Vector3D {
    float x;
    float y;
    float z;
};

struct Color {
    float r;
    float g;
    float b;
};

// Demo 3
struct data2d  {
    float data[4][3];
};

// Demo 3
struct data3d  {
    float data[6][5][3];
};

bool amb = false;
bool diffuse = false;
bool specular = false;

Vector2D SIZE_GRID = {7, 12};
Vector2D mapCoordinate[7][12];
int player1CoorX = 0;
int player1CoorY = 0;
int player2CoorX = 0;
int player2CoorY = 0;
int player2Langkah = 0;
int player1Langkah = 0;
bool giliran = false;
float observerPos[2] = {1.1f, 1.5f};
float camPos[3] = {1.1f, 1.5f, -15.3f};
float viewdir[3] = {1.0f, 0.0f, 0.0f};

// Demo 3
bool mode3d = false;
bool modeview = false;
float angleX = 0.0f;
float angleY = 0.0f;

float observerAngleX = 0.0f;
float observerAngleY = 0.0f;
float observerAngleZ = 0.0f;
int spinmode = 1;

float batasPagarYatas;
float batasPagarYbawah;
float batasPagarXkiri;
float batasPagarXkanan;

float memX = 340.0f;
float memY = 0.0f;
float memZ = 0.0f;

int langkahUnik[] = {2, 12, 30, 46, 55, 82};
int hasilLangkahUnik[][2] = {{6,0}, {32, 4}, {58, 8}, {9, 1}, {15, 2}, {52, 7}};
bool selesai = false;
float heightNum = 0.3f;

void init();
void printOne();
void display();
void printOne(Color color, Vector2D position);
void printSeven(Color color, Vector2D position);
void printTwo(Color color, Vector2D position);
void printFive(Color color, Vector2D position);
void printSix(Color color, Vector2D position);
void drawMap(Vector2D mapSize, Color firstColor, Color secondColor, float initPos, int sizeBlock, float gap, float initZ);
void drawPagar(Color color, Vector3D position);
void drawVerticalTangga(Vector2D start, Vector2D endPoint, Color color, float gap, float yMinus, float z);
void drawHorizontalTangga(Vector2D start, Vector2D endPoint, Color color, float gap, float xPlus, float z);
void drawDiagonalTangga(Vector2D start, Vector2D endPoint, Color color, float z);
data3d create3dDataDiagonal(data2d data, float depth);
void drawUlar(Vector2D petak[], int length, Color color, float z);
void spawnPlayer(Vector2D player1Coor, Vector2D player2Coor, Color pc1, Color pc2, float z);
void inputHandler(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void movePlayer(int player);
data2d create2dData(Vector3D position, float width, float height);
data3d create3dData(data2d data, float depth);
void drawBlock(data3d data, float color[4]);
int isExist(int arr[], int length, int needle);
void drawNums(Vector2D mapSize, Color numsColor, float initPos, int sizeBlock, float gap, float z);
void make2D();
void make3D();
void resetObserver();
void generateMapCoordinate(Vector2D mapSize, float initPos, int sizeBlock, float gap);
void spinObserver(int mode);
Vector3D crossVector(Vector3D v1, Vector3D v2);
Vector3D diff2Point(Vector3D p1, Vector3D p2);
void reshape(int w, int h);
void makeView();
void handleSpecialKey(int key, int x, int y);

void resetObserver() {
    observerAngleX = 0.0f;
    observerAngleY = 0.0f;
    observerAngleZ = 0.0f;
}

void init() {
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);


    GLfloat ambient_light[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambient_light);

    GLfloat light_position_diff[] = { 1.0, 2.0, 1.0, 0.0 };
    GLfloat diffuse_light[] = { 0.0, 0.0, 1.0, 1.0 };

    GLfloat light_position_spec[] = { 3.0, 3.0, 1.0, 0.2 };
    GLfloat specular_light[] = { 1.0, 1.0, 0.0, 1.0 };

    glLightfv(GL_LIGHT0, GL_POSITION, light_position_diff);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position_spec);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular_light);

    GLfloat mat_specular[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat mat_shininess[] = { 10.0 };
    GLfloat mat_diffuse[] = { 0.7, 0.7, 0.7, 1.0 };

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

    glEnable(GL_BLEND);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glShadeModel (GL_SMOOTH);
}

void spinObserver(int mode, float speed) {
    if (mode == 1) {
        if (observerAngleX > 360.0f) {
            observerAngleX = 0.0f;
        }
        observerAngleX += speed;
    } else if (mode == 2) {
        if (observerAngleY > 360.0f) {
            observerAngleY = 0.0f;
        }
        observerAngleY += speed;
    } else if (mode == 3) {
        if (observerAngleZ > 360.0f) {
            observerAngleZ = 0.0f;
        }
        observerAngleZ += speed;
    }

    glutPostRedisplay();
}

void reshape (int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity ();

    if (modeview) {
        gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 500.0);
    } else {
        glOrtho(0, SIZE_GRID.x * 2 + 1, 0, SIZE_GRID.y * 2 + 3.75, 0, SIZE_GRID.y * 4);
    }

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char* argv[]) {
    std::cout << "Tekan Spasi Untuk Memulai Permainan" << std::endl;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize((SIZE_GRID.x * 2 + 1)*26, (SIZE_GRID.y * 2 + 2.5)*26);
    glutCreateWindow("Ular Tangga");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(inputHandler);
    glutMouseFunc(mouse);
    glutReshapeFunc(reshape);
    glutSpecialFunc(handleSpecialKey);
    glutMainLoop();
    return 0;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    Color warnaUlar = {1, 0, 0};
    Color warnaTangga = {1, 0.6, 0};

    glPushMatrix();

        float centerX = (SIZE_GRID.x * 2 + 1) / 2.0f;
        float centerY = (SIZE_GRID.y * 2 + 3.75) / 2.0f;
        glTranslatef(centerX, centerY, -16.5);
        glRotatef(angleX, 1.0, 0.0, 0.0);
        glRotatef(angleY, 0.0, 1.0, 0.0);
        glTranslatef(-centerX, -centerY, 16.5);


        if (modeview)
        {
            gluLookAt(
                camPos[0],camPos[1], camPos[2],
                camPos[0] + viewdir[0], camPos[1] + viewdir[1], camPos[2] + viewdir[2],
                0.0f,  0.0f,  1.0f
            );
        }

        generateMapCoordinate({7, 12}, 0.5, 2, 0.25);

        drawPagar({0, 1, 0}, {0, 0, -13.99});
        drawNums({7, 12}, {0.9, 0.8, 0},  0.5, 2, 0.25, -15.68);

        drawDiagonalTangga(mapCoordinate[4][4], mapCoordinate[1][1], warnaTangga, -14.5);
        drawVerticalTangga(mapCoordinate[2][8], mapCoordinate[2][4], warnaTangga, 1.85, 0.65, -14.5);
        drawHorizontalTangga(mapCoordinate[2][0], mapCoordinate[6][0], warnaTangga, 2, 0.75, -14.5);

        Vector2D ular1[] = {mapCoordinate[1][11], mapCoordinate[3][9], mapCoordinate[2][8], mapCoordinate[3][7]};
        Vector2D ular2[] = {mapCoordinate[4][6], mapCoordinate[3][5], mapCoordinate[5][3], mapCoordinate[4][1]};
        Vector2D ular3[] = {mapCoordinate[0][7], mapCoordinate[2][5], mapCoordinate[1][4], mapCoordinate[1][2]};

        drawUlar(ular1, 4, warnaUlar, -14.5f);
        drawUlar(ular2, 4, warnaUlar, -14.5f);
        drawUlar(ular3, 4, warnaUlar, -14.5f);


        Vector2D player1Coor = {mapCoordinate[player1CoorX][player1CoorY].x, mapCoordinate[player1CoorX][player1CoorY].y + 0.5};
        Vector2D player2Coor = {mapCoordinate[player2CoorX][player2CoorY].x, mapCoordinate[player2CoorX][player2CoorY].y - 0.5};

        spawnPlayer(player1Coor, player2Coor, {0.0, 1.0, 0.2}, {0.0, 0.0, 0}, -14.5f);

        glPushMatrix();

            glTranslatef(observerPos[0], observerPos[1], -14.5f);
            glRotatef(observerAngleX, 1.0f, 0.0f, 0.0f);
            glRotatef(observerAngleY, 0.0f, 1.0f, 0.0f);
            glRotatef(observerAngleZ, 0.0f, 0.0f, 1.0f);

            glColor3f(1, 0.7, 0.9);
            glutSolidTeapot(0.3);
            if (mode3d && !modeview) {
                spinObserver(spinmode, 0.5f);
            }

        glPopMatrix();

        drawMap({7, 12}, {0, 0, 1}, {1, 1, 1}, 0.5, 2, 0.25, -16.0);
    glPopMatrix();


    glFlush();
}

void mouse(int button, int state, int x, int y)
{
    switch (button)
    {
        case GLUT_LEFT_BUTTON:
            spinmode = 1;
            break;
        case GLUT_MIDDLE_BUTTON:
            spinmode = 2;
            break;
        case GLUT_RIGHT_BUTTON:
            spinmode = 3;
            break;
        default:
            break;
    }
}

// Bagian Menggambar atau Display atau View
void createRectangle(Vector3D position, float width, float height) {
    glBegin(GL_POLYGON);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(position.x, position.y, position.z);
        glVertex3f(position.x, position.y - height, position.z);
        glVertex3f(position.x + width, position.y - height, position.z);
        glVertex3f(position.x + width, position.y, position.z);
    glEnd();
}

// Demo 3
data2d create2dData(Vector3D position, float width, float height) {
    data2d result = {{
        {position.x, position.y, position.z},
        {position.x, position.y - height, position.z},
        {position.x + width, position.y - height, position.z},
        {position.x + width, position.y, position.z}
    }};

    return result;
}

void applyRotationForView(Vector3D pos, float w, float h, float z) {
    if (modeview) {
        float centerX = pos.x + w / 2;
        float centerY = pos.y - h / 2;
        glTranslatef(centerX, centerY, -15.68f);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        glTranslatef(-centerX, -centerY, 15.68f);
    }
}

void printOne(Color color, Vector3D position) {
    if (mode3d) {
        glPushMatrix();
            applyRotationForView(position, 0.1, 0.5, -15.38f);
            float colorSet[4] = {color.r, color.g, color.b, 1.0f};
            data2d vertex2D1 = create2dData(position, 0.1, 0.5);
            data3d vertex3D1 = create3dData(vertex2D1, heightNum);
            drawBlock(vertex3D1, colorSet);
        glPopMatrix();
    } else {
        glColor3f(color.r, color.g, color.b);
        createRectangle(position, 0.1, 0.5);
    }
}

void printSeven(Color color, Vector3D position) {
    if (mode3d) {
        glPushMatrix();
            applyRotationForView(position, 0.1, 0.5, -15.38f);
        float colorSet[4] = {color.r, color.g, color.b, 1.0};

        data2d vertex2D1 = create2dData({position.x - 0.2, position.y, position.z}, 0.2, 0.13);
        data3d vertex3D1 = create3dData(vertex2D1, heightNum);
        drawBlock(vertex3D1, colorSet);

        data2d vertex2D2 = create2dData({position.x,  position.y, position.z}, 0.1, 0.5);
        data3d vertex3D2 = create3dData(vertex2D2, heightNum);
        drawBlock(vertex3D2, colorSet);
        glPopMatrix();
    } else {
        glColor3f(color.r, color.g, color.b);
        createRectangle({position.x - 0.2, position.y, position.z}, 0.2, 0.13);
        createRectangle({position.x,  position.y, position.z}, 0.1, 0.5);
    }
}

void printTwo(Color color, Vector3D position) {
    if (mode3d) {
        glPushMatrix();
            applyRotationForView(position, 0.1, 0.5, -15.38f);
            float colorSet[4] = {color.r, color.g, color.b, 1.0};
            data2d vertex2D1 = create2dData({position.x - 0.2, position.y, position.z}, 0.2, 0.13);
            data3d vertex3D1 = create3dData(vertex2D1, heightNum);
            drawBlock(vertex3D1, colorSet);

            data2d vertex2D2 = create2dData({position.x,  position.y, position.z}, 0.1, 0.35);
            data3d vertex3D2 = create3dData(vertex2D2, heightNum);

            drawBlock(vertex3D2, colorSet);

            data2d vertex2D3 = create2dData({position.x - 0.2, position.y - 0.22, position.z}, 0.2, 0.13);
            data3d vertex3D3 = create3dData(vertex2D3, heightNum);
            drawBlock(vertex3D3, colorSet);


            data2d vertex2D4 = create2dData({position.x - 0.2,  position.y - 0.23, position.z}, 0.1, 0.25);
            data3d vertex3D4 = create3dData(vertex2D4, heightNum);
            drawBlock(vertex3D4, colorSet);

            data2d vertex2D5 = create2dData({position.x - 0.2, position.y - 0.4, position.z}, 0.3, 0.13);
            data3d vertex3D5 = create3dData(vertex2D5, heightNum);
            drawBlock(vertex3D5, colorSet);
        glPopMatrix();
    } else {
        glColor3f(color.r, color.g, color.b);
        createRectangle({position.x - 0.2, position.y, position.z}, 0.2, 0.13);
        createRectangle({position.x,  position.y, position.z}, 0.1, 0.35);
        createRectangle({position.x - 0.2, position.y - 0.22, position.z}, 0.2, 0.13);
        createRectangle({position.x - 0.2,  position.y - 0.23, position.z}, 0.1, 0.25);
        createRectangle({position.x - 0.2, position.y - 0.4, position.z}, 0.3, 0.13);
    }
}

void printFive(Color color, Vector3D position) {
    if (mode3d) {
        glPushMatrix();
            applyRotationForView(position, 0.1, 0.5, -15.38f);
        float colorSet[4] = {color.r, color.g, color.b, 1.0f};

        data2d v1 = create2dData({position.x - 0.2, position.y, position.z}, 0.3, 0.13);
        drawBlock(create3dData(v1, heightNum), colorSet);

        data2d v2 = create2dData({position.x - 0.2, position.y, position.z}, 0.1, 0.25);
        drawBlock(create3dData(v2, heightNum), colorSet);

        data2d v3 = create2dData({position.x - 0.2, position.y - 0.20, position.z}, 0.2, 0.13);
        drawBlock(create3dData(v3, heightNum), colorSet);

        data2d v4 = create2dData({position.x, position.y - 0.20, position.z}, 0.1, 0.30);
        drawBlock(create3dData(v4, heightNum), colorSet);

        data2d v5 = create2dData({position.x - 0.2, position.y - 0.4, position.z}, 0.3, 0.13);
        drawBlock(create3dData(v5, heightNum), colorSet);
        glPopMatrix();
    } else {
        glColor3f(color.r, color.g, color.b);
        createRectangle({position.x - 0.2, position.y, position.z}, 0.3, 0.13);
        createRectangle({position.x - 0.2, position.y, position.z}, 0.1, 0.25);
        createRectangle({position.x - 0.2, position.y - 0.20, position.z}, 0.2, 0.13);
        createRectangle({position.x, position.y - 0.20, position.z}, 0.1, 0.30);
        createRectangle({position.x - 0.2, position.y - 0.4, position.z}, 0.3, 0.13);
    }
}


void printSix(Color color, Vector3D position) {
    if (mode3d) {
        glPushMatrix();
            applyRotationForView(position, 0.1, 0.5, -15.38f);
        float colorSet[4] = {color.r, color.g, color.b, 1.0f};

        data2d v1 = create2dData({position.x - 0.2, position.y, position.z}, 0.3, 0.13);
        drawBlock(create3dData(v1, heightNum), colorSet);

        data2d v2 = create2dData({position.x - 0.2, position.y, position.z}, 0.1, 0.5); // batang kiri penuh
        drawBlock(create3dData(v2, heightNum), colorSet);

        data2d v3 = create2dData({position.x - 0.2, position.y - 0.20, position.z}, 0.2, 0.13);
        drawBlock(create3dData(v3, heightNum), colorSet);

        data2d v4 = create2dData({position.x, position.y - 0.20, position.z}, 0.1, 0.30);
        drawBlock(create3dData(v4, heightNum), colorSet);

        data2d v5 = create2dData({position.x - 0.2, position.y - 0.4, position.z}, 0.3, 0.13);
        drawBlock(create3dData(v5, heightNum), colorSet);
        glPopMatrix();
    } else {
        glColor3f(color.r, color.g, color.b);
        createRectangle({position.x - 0.2, position.y, position.z}, 0.3, 0.13);
        createRectangle({position.x - 0.2, position.y, position.z}, 0.1, 0.5); // batang kiri penuh
        createRectangle({position.x - 0.2, position.y - 0.20, position.z}, 0.2, 0.13);
        createRectangle({position.x, position.y - 0.20, position.z}, 0.1, 0.30);
        createRectangle({position.x - 0.2, position.y - 0.4, position.z}, 0.3, 0.13);
    }
}


void drawPagar(Color color, Vector3D position) {
    batasPagarXkiri = position.x + 0.25 + 0.25;
    batasPagarYbawah = position.y + 0.5 + 0.25;
    batasPagarXkanan = position.x + SIZE_GRID.x * 2 + 0.5;
    batasPagarYatas = position.y + (SIZE_GRID.y * 2 + 3.5) + 0.25;

    if (mode3d) {
        float colorSet[4] = {color.r, color.g, color.b, 1.0};

        data2d vertex2D1 = create2dData({position.x + (0.25f - 0.001f), position.y + (SIZE_GRID.y * 2 + 3.5), position.z - 1.0f}, 0.25, SIZE_GRID.y * 2 + 3.25);
        data3d vertex3D1 = create3dData(vertex2D1, 2.0f);
        drawBlock(vertex3D1, colorSet);

        data2d vertex2D2 = create2dData({position.x + 0.25, position.y + (0.5 - 0.001f), position.z - 1.0f}, SIZE_GRID.x * 2 + 0.5, 0.25);
        data3d vertex3D2 = create3dData(vertex2D2, 2.0f);
        drawBlock(vertex3D2, colorSet);

        data2d vertex2D3 = create2dData({position.x + SIZE_GRID.x * 2 + 0.5 + 0.001f, position.y + (SIZE_GRID.y * 2 + 3.5), position.z - 1.0f}, 0.25, SIZE_GRID.y * 2 + 3.25);
        data3d vertex3D3 = create3dData(vertex2D3, 2.0f);
        drawBlock(vertex3D3, colorSet);

        data2d vertex2D4 = create2dData({position.x + 0.25, position.y + (SIZE_GRID.y * 2 + 3.5) + 0.001f, position.z - 1.0f}, SIZE_GRID.x * 2 + 0.5, 0.25);
        data3d vertex3D4 = create3dData(vertex2D4, 2.0f);
        drawBlock(vertex3D4, colorSet);
    } else {
        glColor3f(color.r, color.g, color.b);
        createRectangle({position.x + 0.25, position.y + (SIZE_GRID.y * 2 + 3.5), position.z}, 0.25, SIZE_GRID.y * 2 + 3.25);
        createRectangle({position.x + 0.25, position.y + 0.5, position.z}, SIZE_GRID.x * 2 + 0.5, 0.25);
        createRectangle({position.x + SIZE_GRID.x * 2 + 0.5, position.y + (SIZE_GRID.y * 2 + 3.5), position.z}, 0.25, SIZE_GRID.y * 2 + 3.25);
        createRectangle({position.x + 0.25, position.y + (SIZE_GRID.y * 2 + 3.5), position.z}, SIZE_GRID.x * 2 + 0.5, 0.25);
    }

    for (int i = 1; i < 12; i++)
    {
        if (mode3d) {
            if (i % 2 == 1) {
                float colorSet[4] ={color.r, color.g, color.b, 1.0};
                data2d vertex2D = create2dData({position.x + 0.5, position.y + 0.5 + (2 * i) + (0.25 * i), position.z - 1.0f}, SIZE_GRID.x * 2 - 2, 0.25);
                data3d vertex3D = create3dData(vertex2D, 1.0f);
                drawBlock(vertex3D, colorSet);
            } else {
                float colorSet[4] = {color.r, color.g, color.b, 1.0};
                data2d vertex2D = create2dData({position.x + 0.5 + 2, position.y + 0.5 + (2 * i) + (0.25 * i), position.z - 1.0f}, SIZE_GRID.x * 2 - 2, 0.25);
                data3d vertex3D = create3dData(vertex2D, 1.0f);
                drawBlock(vertex3D, colorSet);
            }
        } else {
            if (i % 2 == 1)
            {
                createRectangle({position.x + 0.5, position.y + 0.5 + (2 * i) + (0.25 * i), position.z}, SIZE_GRID.x * 2 - 2, 0.25 );
            } else {
                createRectangle({position.x + 0.5 + 2, position.y + 0.5 + (2 * i) + (0.25 * i), position.z}, SIZE_GRID.x * 2 - 2, 0.25 );
            }
        }
    }
}

void drawMap(Vector2D mapSize, Color firstColor, Color secondColor, float initPos, int sizeBlock, float gap, float initZ) {
    int validNumber[] = {1, 2, 5, 6, 7};
    for (int i = 0; i < mapSize.y; i++)
    {
        for (int j = 0; j < mapSize.x; j++)
        {
            float color[4];
            if (mode3d) {
                if ((j % 2 == i % 2) == false) {
                    color[0] = firstColor.r;     color[1] = firstColor.g;
                    color[2] = firstColor.b;     color[3] = 0.4f;
                } else {
                    color[0] = secondColor.r;     color[1] = secondColor.g;
                    color[2] = secondColor.b;     color[3] = 0.4f;
                }


                // if ((i % 2 == 0 && j == 0 || i % 2 != 0 && j == 6) && i > 0) {
                //    data2d vertex2dRect = create2dData({initPos + (j * sizeBlock) + (0.001f * j), initPos + (sizeBlock * (i + 1)) + (gap * (i + 1)) - gap, initZ}, sizeBlock , sizeBlock + gap - (j * 0.0015f));
                //    data3d vertex3dData = create3dData(vertex2dRect, 1.0f);
                //    drawBlock(vertex3dData, color);
                // } else {
                //    data2d vertex2dRect = create2dData({initPos + (j * sizeBlock) + (0.001f * j), initPos + (sizeBlock * (i + 1)) + (gap * (i + 1)) - gap, initZ}, sizeBlock , sizeBlock);
                //    data3d vertex3dData = create3dData(vertex2dRect, 1.0f);
                //    drawBlock(vertex3dData, color);
                // }

                data2d vertex2dRect = create2dData({initPos + (j * sizeBlock) + (0.001f * j), initPos + (sizeBlock * (i + 1)) + (gap * (i + 1)) - gap, initZ}, sizeBlock , sizeBlock + gap - (i * 0.001f));
                data3d vertex3dData = create3dData(vertex2dRect, 1.0f);
                drawBlock(vertex3dData, color);
            } else {

                switch (j % 2 == i % 2) {
                    case false:
                        glColor3f(firstColor.r, firstColor.g, firstColor.b);
                        break;
                    case true:
                        glColor3f(secondColor.r, secondColor.g, secondColor.b);
                        break;
                }

                if (i % 2 == 0 && j == 0 || i % 2 != 0 && j == 6) {
                    createRectangle({initPos + (j * sizeBlock), initPos + (sizeBlock * (i + 1)) + (gap * (i + 1)) - gap, initZ}, sizeBlock , sizeBlock + gap);
                } else {
                    createRectangle({initPos + (j * sizeBlock), initPos + (sizeBlock * (i + 1)) + (gap * (i + 1)) - gap, initZ}, sizeBlock , sizeBlock);
                }
            }
        }
    }
}

void generateMapCoordinate(Vector2D mapSize, float initPos, int sizeBlock, float gap) {
    for (int i = 0; i < mapSize.y; i++)
    {
        for (int j = 0; j < mapSize.x; j++)
        {
            Vector2D centerPos = {(initPos + (j * sizeBlock)) + 1, (initPos + (sizeBlock * (i + 1)) + (gap * i)) - 1};
            mapCoordinate[j][i] = centerPos;
        }
    }
}

void drawNums(Vector2D mapSize, Color numsColor ,float initPos, int sizeBlock, float gap, float z) {
    for (int i = 0; i < mapSize.y; i++)
    {
        for (int j = 0; j < mapSize.x; j++)
        {
            int second;
            int first;
            if ((i + 1) % 2 == 1)
            {
                second = (7 * i + j + 1) % 10;
                first = std::floor((SIZE_GRID.x * i + j + 1) / 10);
            }
            else
            {
                second = ((7 * i + 7) - (j)) % 10;
                first = std::floor(((SIZE_GRID.x * i + SIZE_GRID.x) - (j)) / 10);
            }

            float numberGap = 0.4;

            switch (second) {
                case 1:
                    printOne({numsColor.r, numsColor.g, numsColor.b}, {initPos + ((j + 1) * sizeBlock)- 0.1 - 0.25, initPos + (sizeBlock * (i + 1)) + (gap * i) - 0.25, z});
                    numberGap = 0.2;
                    break;
                case 2:
                    printTwo({numsColor.r, numsColor.g, numsColor.b}, {initPos + ((j + 1) * sizeBlock)- 0.1 - 0.25, initPos + (sizeBlock * (i + 1)) + (gap * i) - 0.25, z});
                    break;
                case 5:
                    printFive({numsColor.r, numsColor.g, numsColor.b}, {initPos + ((j + 1) * sizeBlock)- 0.1 - 0.25, initPos + (sizeBlock * (i + 1)) + (gap * i) - 0.25, z});
                    break;
                case 6:
                    printSix({numsColor.r, numsColor.g, numsColor.b}, {initPos + ((j + 1) * sizeBlock)- 0.1 - 0.25, initPos + (sizeBlock * (i + 1)) + (gap * i) - 0.25, z});
                    break;
                case 7:
                    printSeven({numsColor.r, numsColor.g, numsColor.b}, {initPos + ((j + 1) * sizeBlock)- 0.1 - 0.25, initPos + (sizeBlock * (i + 1)) + (gap * i) - 0.25, z});
                    break;
                default:
                    numberGap = 0.0;
                    break;
            }


            if (first != 0) {
                switch (first) {
                    case 1:
                        printOne({numsColor.r, numsColor.g, numsColor.b}, {initPos + ((j + 1) * sizeBlock)- 0.1 - 0.25- numberGap, initPos + (sizeBlock * (i + 1)) + (gap * i) - 0.25, z});
                        break;
                    case 2:
                        printTwo({numsColor.r, numsColor.g, numsColor.b}, {initPos + ((j + 1) * sizeBlock)- 0.1 - 0.25 - numberGap, initPos + (sizeBlock * (i + 1)) + (gap * i) - 0.25, z});
                        break;
                    case 5:
                        printFive({numsColor.r, numsColor.g, numsColor.b}, {initPos + ((j + 1) * sizeBlock)- 0.1 - 0.25- numberGap, initPos + (sizeBlock * (i + 1)) + (gap * i) - 0.25, z});
                        break;
                    case 6:
                        printSix({numsColor.r, numsColor.g, numsColor.b}, {initPos + ((j + 1) * sizeBlock)- 0.1 - 0.25 - numberGap, initPos + (sizeBlock * (i + 1)) + (gap * i) - 0.25, z});
                        break;
                    case 7:
                        printSeven({numsColor.r, numsColor.g, numsColor.b}, {initPos + ((j + 1) * sizeBlock)- 0.1 - 0.25- numberGap, initPos + (sizeBlock * (i + 1)) + (gap * i) - 0.25, z});
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

void drawVerticalTangga(Vector2D start, Vector2D endPoint, Color color, float gap, float yMinus, float z) {
    if (mode3d) {
        float colorSet[4] = {color.r, color.g, color.b, 1.0f};

        data2d kiri = {{
            {start.x - 0.75, start.y, z},
            {endPoint.x - 0.75, endPoint.y, z},
            {endPoint.x - 0.5, endPoint.y, z},
            {start.x - 0.5, start.y, z}
        }};
        drawBlock(create3dData(kiri, 0.5f), colorSet);

        data2d kanan = {{
            {start.x + 0.5, start.y, z},
            {endPoint.x + 0.5, endPoint.y, z},
            {endPoint.x + 0.75, endPoint.y, z},
            {start.x + 0.75, start.y, z}
        }};
        drawBlock(create3dData(kanan, 0.5f), colorSet);

        int heightLadder = std::floor(start.y - endPoint.y);
        int totalTangga = heightLadder / 1;

        data2d tanggaAwal = create2dData({start.x - 0.5f, start.y - yMinus, z}, 1.0f, 0.25f);
        drawBlock(create3dData(tanggaAwal, 0.25f), colorSet);

        while (gap < heightLadder) {
            data2d tangga = create2dData({start.x - 0.5f, start.y - gap, z}, 1.0f, 0.25f);
            drawBlock(create3dData(tangga, 0.25f), colorSet);
            gap += 1.25f;
        }

        if (!(start.y - gap < endPoint.y + 0.5f)) {
            data2d tanggaAkhir = create2dData({endPoint.x, start.y - gap, z}, 1.0f, 0.25f);
            drawBlock(create3dData(tanggaAkhir, 0.25f), colorSet);
        }

    } else {
        glColor3f(color.r, color.g, color.b);

        glBegin(GL_POLYGON);
            glNormal3f(0.0f, 0.0f, 1.0f);
            glVertex3f(start.x - 0.75, start.y, z + 1);
            glVertex3f(endPoint.x - 0.75, endPoint.y, z + 1);
            glVertex3f(endPoint.x - 0.5, endPoint.y, z + 1);
            glVertex3f(start.x - 0.5, start.y, z + 1);
        glEnd();

        glBegin(GL_POLYGON);
            glNormal3f(0.0f, 0.0f, 1.0f);
            glVertex3f(start.x + 0.5, start.y, z + 1);
            glVertex3f(endPoint.x + 0.5, endPoint.y, z + 1);
            glVertex3f(endPoint.x + 0.75, endPoint.y, z + 1);
            glVertex3f(start.x + 0.75, start.y, z + 1);
        glEnd();

        int heightLadder = std::floor(start.y - endPoint.y);
        int totalTangga = (heightLadder / 1);
        createRectangle({start.x - 0.5, start.y - yMinus, z + 1}, 1, 0.25);

        while (gap < heightLadder)
        {
            createRectangle({start.x - 0.5, start.y - gap, z + 1}, 1, 0.25);
            gap = gap + 1 + 0.25;
        }

        if (!(start.y - gap < endPoint.y + 0.5)) {
            createRectangle({endPoint.x - 0.5, start.y - gap, z + 1}, 1, 0.25);
        }
    }
}

void drawHorizontalTangga(Vector2D start, Vector2D endPoint, Color color, float gap, float xPlus, float z) {
    if (mode3d) {
        float colorSet[4] = {color.r, color.g, color.b, 1.0f};

        data2d vertex2D1 = {{
            {start.x, start.y + 0.75, z},
            {start.x, start.y + 0.5, z},
            {endPoint.x, endPoint.y + 0.5, z},
            {endPoint.x, endPoint.y + 0.75, z},
        }};

        drawBlock(create3dData(vertex2D1, 0.5f), colorSet);

        data2d vertex2D2 = {{
            {start.x, start.y - 0.45, z},
            {start.x, start.y - 0.7, z},
            {endPoint.x, endPoint.y - 0.7, z},
            {endPoint.x, endPoint.y - 0.45, z},
        }};

        drawBlock(create3dData(vertex2D2, 0.5f), colorSet);

        int widthLadder = std::floor(endPoint.x - start.x);

        data2d step1 = create2dData({start.x + xPlus, start.y + 0.5, z}, 0.25, 1.0);
        drawBlock(create3dData(step1, 0.5f), colorSet);

        while (gap < widthLadder) {
            data2d step1 = create2dData({start.x + gap, start.y + 0.5, z}, 0.25, 1.0);
            drawBlock(create3dData(step1, 0.5f), colorSet);
            gap += 1.25f;
        }

        if (!(start.y - gap < endPoint.y + 0.5)) {
            data2d step1 = create2dData({endPoint.x + gap, start.y + 0.5, z}, 0.25, 1.0);
            drawBlock(create3dData(step1, 0.5f), colorSet);
        }

    } else {
        glColor3f(color.r, color.g, color.b);

        glBegin(GL_POLYGON);
            glNormal3f(0.0f, 0.0f, 1.0f);
            glVertex3f(start.x, start.y + 0.75, z);
            glVertex3f(endPoint.x, endPoint.y + 0.75, z);
            glVertex3f(endPoint.x, endPoint.y + 0.5, z);
            glVertex3f(start.x, start.y + 0.5, z);
        glEnd();

        glBegin(GL_POLYGON);
            glNormal3f(0.0f, 0.0f, 1.0f);
            glVertex3f(start.x, start.y - 0.45, z);
            glVertex3f(endPoint.x, endPoint.y - 0.45, z);
            glVertex3f(endPoint.x, endPoint.y - 0.7, z);
            glVertex3f(start.x, start.y - 0.7, z);
        glEnd();

        int widthLadder = std::floor(endPoint.x - start.x);

        createRectangle({start.x + xPlus, start.y + 0.5, z}, 0.25, 1);

        while (gap < widthLadder) {
            createRectangle({start.x + gap, start.y + 0.5, z}, 0.25, 1);
            gap += 1.25f;
        }

        if (!(start.y - gap < endPoint.y + 0.5)) {
            createRectangle({endPoint.x + gap, start.y + 0.5, z}, 0.25, 1);
        }
    }
}


void drawDiagonalTangga(Vector2D start, Vector2D endPoint, Color color, float z) {
    if (mode3d) {
        float colorSet[4] = {color.r, color.g, color.b, 1.0f};

        data2d kiri = {{
            {start.x - 0.35, start.y + 0.35, z},
            {endPoint.x - 0.35, endPoint.y + 0.35, z},
            {endPoint.x - 0.5, endPoint.y + 0.5, z},
            {start.x - 0.5, start.y + 0.5, z}
        }};

        drawBlock(create3dDataDiagonal(kiri, 0.5f), colorSet);

        data2d kanan = {{
            {start.x + 0.5, start.y - 0.5, z},
            {endPoint.x + 0.5, endPoint.y - 0.5, z},
            {endPoint.x + 0.35, endPoint.y - 0.35, z},
            {start.x + 0.35, start.y - 0.35, z}
        }};

        drawBlock(create3dDataDiagonal(kanan, 0.5f), colorSet);


        float gap = 0.5;
        int loop = 0;
        float gap2 = 0;
        float panjangTangga = std::sqrt(pow(start.x - endPoint.x, 2) + pow(start.y - endPoint.y, 2));
        while (gap + 2 + (loop * 0.1) < panjangTangga) {

            data2d anakTangga = {{
                {(start.x + (0.4 + gap2)) - gap, (start.y - (0.4 + gap2)) - gap, z},
                {(start.x + (0.4 + gap2)) - (gap + 0.15), (start.y - (0.4 + gap2)) - (gap + 0.15), z},
                {(start.x - (0.4 - gap2)) - (gap + 0.15), (start.y + (0.4 - gap2)) - (gap + 0.15), z},
                {(start.x - (0.4 - gap2)) - gap, (start.y + (0.4 - gap2)) - gap, z}
            }};

            drawBlock(create3dDataDiagonal(anakTangga, 0.5f), colorSet);

            gap += 1;
            gap2 += 0.07;
            loop += 1;
        }

    } else {
        glColor3f(color.r, color.g, color.b);


        glBegin(GL_POLYGON);
            glVertex3f(start.x - 0.5, start.y + 0.5, z + 1);
            glVertex3f(endPoint.x - 0.5, endPoint.y + 0.5, z + 1);
            glVertex3f(endPoint.x - 0.35, endPoint.y + 0.35, z + 1);
            glVertex3f(start.x - 0.35, start.y + 0.35, z + 1);
        glEnd();

        glBegin(GL_POLYGON);
            glVertex3f(start.x + 0.5, start.y - 0.5, z + 1);
            glVertex3f(endPoint.x + 0.5, endPoint.y - 0.5, z + 1);
            glVertex3f(endPoint.x + 0.35, endPoint.y - 0.35, z + 1);
            glVertex3f(start.x + 0.35, start.y - 0.35, z + 1);
        glEnd();

        float gap = 0.5;
        int loop = 0 ;
        float gap2 = 0;
        float panjangTangga = std::sqrt(pow(start.x - endPoint.x, 2) + pow(start.y - endPoint.y, 2));
        while (gap + 2 + (loop * 0.1) < panjangTangga) {
            glBegin(GL_POLYGON);
                glVertex3f((start.x - (0.4 - gap2)) - gap, (start.y + (0.4 - gap2)) - gap, z);
                glVertex3f((start.x - (0.4 - gap2)) - (gap + 0.15), (start.y + (0.4 - gap2)) - (gap + 0.15), z);
                glVertex3f((start.x + (0.4 + gap2)) - (gap + 0.15), (start.y - (0.4 + gap2)) - (gap + 0.15), z);
                glVertex3f((start.x + (0.4 + gap2)) - gap , (start.y - (0.4 + gap2)) - gap, z);
            glEnd();
            gap += 1;
            gap2 += 0.07;
            loop += 1;
        }
    }
}

void drawUlar(Vector2D petak[], int length, Color color, float z) {
    for (int i = 0; i < length - 1; i++)
    {
        if (mode3d) {
            float colorSet[4] = {color.r, color.g, color.b, 1.0f};

            data2d vertex2D1 = {{
                {petak[i].x + 0.15, petak[i].y, z},
                {petak[i + 1].x + 0.15, petak[i + 1].y, z},
                {petak[i + 1].x - 0.15, petak[i + 1].y, z},
                {petak[i].x - 0.15, petak[i].y, z}
            }};

            data3d vertex3D1 = create3dDataDiagonal(vertex2D1, 0.5f);
            drawBlock(vertex3D1, colorSet);

        } else {
            glColor3f(color.r, color.g, color.b);

            glBegin(GL_POLYGON);
                glNormal3f(0.0f, 0.0f, 1.0f);
                glVertex3f(petak[i].x - 0.15, petak[i].y, z + 1);
                glVertex3f(petak[i + 1].x - 0.15, petak[i + 1].y, z + 1);
                glVertex3f(petak[i + 1].x + 0.15, petak[i + 1].y, z + 1);
                glVertex3f(petak[i].x + 0.15, petak[i].y, z + 1);
            glEnd();
        }

    }
}

void spawnPlayer(Vector2D player1Coor, Vector2D player2Coor, Color pc1, Color pc2, float z)
{
    if (mode3d) {
        float colorSet1[4] = {pc1.r, pc1.g, pc1.b, 1.0f};

        float colorSet2[4] = {pc2.r, pc2.g, pc2.b, 1.0f};

        data2d vertex2D1 = create2dData({player1Coor.x - 0.2, player1Coor.y + 0.2, z}, 0.4, 0.4);
        data3d vertex3D1 = create3dData(vertex2D1, 0.5f);
        drawBlock(vertex3D1, colorSet1);

        glPushMatrix();
            glColor4f(pc2.r, pc2.g, pc2.b, 1.0f);
            glTranslatef(player2Coor.x, player2Coor.y, z);
            glutSolidSphere(0.3f, 50, 50);
        glPopMatrix();


    } else {
        glColor3f(pc1.r, pc1.g, pc1.b);
        createRectangle({player1Coor.x - 0.2, player1Coor.y + 0.2, z}, 0.4, 0.4);

        glPushMatrix();
            glColor4f(pc2.r, pc2.g, pc2.b, 1.0f);
            glTranslatef(player2Coor.x, player2Coor.y, z);
            glutSolidSphere(0.3f, 50, 50);
        glPopMatrix();
    }

}

// Bagian INPUT atau bagian Controller
void inputHandler(unsigned char key, int x, int y) {
    if (key == ' ' && selesai == false) {
        if (giliran == true)
        {
            movePlayer(2);
            giliran = false;
        } else {
            movePlayer(1);
            giliran = true;
        }
    } else if (key == 'v' || key == 'V') {
        if (modeview) {
            make2D();
            mode3d = false;
            modeview = false;
        } else if (mode3d) {
            makeView();
            modeview = true;
            mode3d = true;
        } else {
            make3D();
            mode3d = true;
        }

        reshape((SIZE_GRID.x * 2 + 1)*26, (SIZE_GRID.y * 2 + 2.5)*26);
        glutPostRedisplay();
    } else if ((key == 'l' || key == 'L') && mode3d && !modeview) {
        if (angleY >= 360.0f) {
            angleY = 0;
        } else {
            angleY += 1.0f;
        }

    } else if ((key == 'j' || key == 'J') && mode3d&& !modeview) {
        if (angleY <= 0.0f) {
            angleY = 360.0f;
        } else {
            angleY -= 1.0f;
        }
    } else if ((key == 'k' || key == 'K') && mode3d && !modeview) {
        if (angleX >= 360.0f) {
            angleX = 0.0f;
        } else {
            angleX += 1.0f;
        }
    }  else if ((key == 'i' || key == 'I') && mode3d && !modeview) {
        if (angleX <= 0.0f) {
            angleX = 360.0f;
        } else {
            angleX -= 1.0f;
        }
    } else if ((key == 'a' || key == 'A' ) && observerPos[0] - 0.5f >= batasPagarXkiri) {
        observerPos[0] -= 0.1f;
    } else if ((key == 'd' || key == 'D') && observerPos[0] + 0.5f  <= batasPagarXkanan) {
        observerPos[0] += 0.1f;
    } else if ((key == 's' || key == 'S') && observerPos[1] - 0.20f >= batasPagarYbawah) {
        observerPos[1] -= 0.1f;
    } else if ((key == 'w' || key == 'W') && observerPos[1] + 1.0f <= batasPagarYatas) {
        observerPos[1] += 0.1f;
    }

    if (key=='1'){
        if (amb == true){
            GLfloat ambient_light[] = { 0.9f, 0.9f, 0.9f, 1.0f };
            glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambient_light);
            amb = false;
        } else {
            GLfloat ambient_light[] = { 0.3f, 0.3f, 0.3f, 1.0f };
            glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambient_light);
            amb = true;
        }
    }

    if (key == '2') {
        if (diffuse == true) {
            glDisable(GL_LIGHT0);
            diffuse = false;
        } else {
            glEnable(GL_LIGHT0);
            diffuse = true;
        }
    }

    if (key == '3') {
        if (specular == true) {
            glDisable(GL_LIGHT1);
            specular = false;
        } else {
            glEnable(GL_LIGHT1);
            specular = true;
        }
    }



    display();
}


void handleSpecialKey(int key, int x, int y) {
    if (modeview) {
        switch (key) {
            case GLUT_KEY_UP:
                camPos[0] += 0.2 * viewdir[0];
                camPos[1] += 0.2 * viewdir[1];
                camPos[2] += 0.2 * viewdir[2];
                break;
            case GLUT_KEY_DOWN:
                camPos[0] -= 0.2 * viewdir[0];
                camPos[1] -= 0.2 * viewdir[1];
                camPos[2] -= 0.2 * viewdir[2];
                break;
            case GLUT_KEY_LEFT:
                viewdir[0] = viewdir[0] * cos(0.03) - viewdir[1] * sin(0.03);
                viewdir[1] = viewdir[0] * sin(0.03) + viewdir[1] * cos(0.03);
                break;
            case GLUT_KEY_RIGHT:
                viewdir[0] = viewdir[0] * cos(-0.03) - viewdir[1] * sin(-0.03);
                viewdir[1] = viewdir[0] * sin(-0.03) + viewdir[1] * cos(-0.03);
                break;
        }
    }

    display();
}

void movePlayer(int player) {
    srand(time(NULL));
    int angkaDadu = rand() % 6 + 1;
    if (player == 2)
    {
        std::cout << "Player 2 main. Dadu dapat " << angkaDadu << std::endl;
        player2Langkah += angkaDadu;

        if (player2Langkah % 7 == 0 || (player2CoorY + 1) * 7 <= player2Langkah) {
            player2CoorY += 1;
        }
        int adaTangga = isExist(langkahUnik, 6, player2Langkah);
        if (adaTangga != -1) {
            player2Langkah = hasilLangkahUnik[adaTangga][0];
            player2CoorY = hasilLangkahUnik[adaTangga][1];
        }

        if (player2Langkah >= 83)
        {
            player2Langkah = 83;
            player2CoorY = 11;
        }

        if (player2CoorY % 2 == 0)
        {
            player2CoorX = player2Langkah % 7;
        }else {
            player2CoorX = 6 - (player2Langkah % 7);
        }

        if (player2Langkah == 83) {
            selesai = true;
            std::cout << "Player 2 Menang!!!" << std::endl;
        }

    } else {
        player1Langkah += angkaDadu;
        std::cout << "Player 1 main. Dadu dapat " << angkaDadu << std::endl;

        if (player1Langkah % 7 == 0 || (player1CoorY + 1) * 7 <= player1Langkah) {
            player1CoorY += 1;
        }

        int adaTangga = isExist(langkahUnik, 6, player1Langkah);
        if (adaTangga != -1) {
            player1Langkah = hasilLangkahUnik[adaTangga][0];
            player1CoorY = hasilLangkahUnik[adaTangga][1];
        }

        if (player1Langkah >= 83)
        {
            player1Langkah = 83;
            player1CoorY = 11;
        }


        if (player1CoorY % 2 == 0)
        {
            player1CoorX = player1Langkah % 7;
        }else {
            player1CoorX = 6 - (player1Langkah % 7);
        }

        if (player1Langkah == 83)
        {
            selesai = true;
            std::cout << "Player 1 Menang!!!" << std::endl;
        }
    }
}

int isExist(int arr[], int length, int needle)
{
    for (int i = 0; i < length; i++)
    {
        if (arr[i] == needle)
        {
            return i;
        }
    }
    return -1;
}

// FUNGSI TAMBAHAN DEMO 3 3D
data3d create3dData(data2d data, float depth) {
    data3d result = {{
        {
            {0.0f, 0.0f, 1.0f},
            {data.data[0][0], data.data[0][1], data.data[0][2]},
            {data.data[1][0], data.data[1][1], data.data[1][2]},
            {data.data[2][0], data.data[2][1], data.data[2][2]},
            {data.data[3][0], data.data[3][1], data.data[3][2]}
        },
        {
            {-1.0f, 0.0f, 0.0f},
            {data.data[0][0], data.data[0][1], data.data[0][2] - depth},
            {data.data[0][0], data.data[1][1], data.data[1][2] - depth},
            {data.data[0][0], data.data[2][1], data.data[2][2]},
            {data.data[0][0], data.data[3][1], data.data[3][2]}
        },
        {
            {1.0f, 0.0f, 0.0f},
            {data.data[3][0], data.data[0][1], data.data[0][2]},
            {data.data[3][0], data.data[1][1], data.data[1][2]},
            {data.data[3][0], data.data[2][1], data.data[2][2] - depth},
            {data.data[3][0], data.data[3][1], data.data[3][2] - depth}
        },
        {
            {0.0f, 1.0f, 0.0f},
            {data.data[0][0], data.data[0][1], data.data[0][2] - depth},
            {data.data[1][0], data.data[0][1], data.data[1][2]},
            {data.data[2][0], data.data[0][1], data.data[2][2]},
            {data.data[3][0], data.data[0][1], data.data[3][2] - depth}
        },
        {
            {0.0f, -1.0f, 0.0f},
            {data.data[0][0], data.data[1][1], data.data[0][2]},
            {data.data[1][0], data.data[1][1], data.data[1][2] - depth},
            {data.data[2][0], data.data[1][1], data.data[2][2] - depth},
            {data.data[3][0], data.data[1][1], data.data[3][2]}
        },
        {
            {0.0f, 0.0f, -1.0f},
            {data.data[0][0], data.data[0][1], data.data[0][2] - depth},
            {data.data[1][0], data.data[1][1], data.data[1][2] - depth},
            {data.data[2][0], data.data[2][1], data.data[2][2] - depth},
            {data.data[3][0], data.data[3][1], data.data[3][2] - depth}
        }
    }};
    return result;
}


data3d create3dDataDiagonal(data2d data, float depth) {

    Vector3D cross1 = crossVector(
                                  diff2Point(
                                                {data.data[0][0], data.data[0][1], data.data[0][2]},
                                                {data.data[3][0], data.data[3][1], data.data[3][2]}
                                             ),
                                  diff2Point(
                                                {data.data[0][0], data.data[0][1], data.data[0][2]},
                                                {data.data[1][0], data.data[1][1], data.data[1][2]}
                                             )
                                  );

    Vector3D cross2 = crossVector(
                                  diff2Point(
                                                {data.data[0][0], data.data[0][1], data.data[0][2] - depth},
                                                {data.data[0][0], data.data[0][1], data.data[3][2]}
                                             ),
                                  diff2Point(
                                                {data.data[0][0], data.data[0][1], data.data[0][2] - depth},
                                                {data.data[1][0], data.data[1][1], data.data[1][2] - depth}
                                             )
                                  );
    Vector3D cross3 = crossVector(diff2Point(
                                                {data.data[3][0], data.data[3][1], data.data[0][2]},
                                                {data.data[2][0], data.data[2][1], data.data[1][2]}
                                             ),
                                  diff2Point(
                                                {data.data[3][0], data.data[3][1], data.data[0][2]},
                                                {data.data[3][0], data.data[3][1], data.data[3][2] - depth}
                                            ));

    Vector3D cross4 = crossVector(
                              diff2Point(
                                         {data.data[0][0], data.data[0][1], data.data[0][2] - depth},
                                         {data.data[0][0], data.data[0][1], data.data[1][2]}
                                         ),
                              diff2Point(
                                         {data.data[0][0], data.data[0][1], data.data[0][2] - depth},
                                         {data.data[3][0], data.data[3][1], data.data[2][2]}
                                         )
                              );

    Vector3D cross5 = crossVector(
                                  diff2Point(
                                             {data.data[1][0], data.data[1][1], data.data[0][2]},
                                             {data.data[1][0], data.data[1][1], data.data[1][2] - depth}
                                             ),
                                  diff2Point(
                                             {data.data[1][0], data.data[1][1], data.data[0][2]},
                                             {data.data[2][0], data.data[2][1], data.data[2][2] - depth}
                                             )
                                  );


    Vector3D cross6 = crossVector(
                                  diff2Point(
                                             {data.data[0][0], data.data[0][1], data.data[0][2]},
                                             {data.data[1][0], data.data[1][1], data.data[1][2]}),
                                diff2Point(
                                           {data.data[0][0], data.data[0][1], data.data[0][2]},
                                           {data.data[3][0], data.data[3][1], data.data[3][2]}));


    data3d result = {{
        {
            {cross1.x, cross1.y, cross1.z},
            {data.data[0][0], data.data[0][1], data.data[0][2]},
            {data.data[1][0], data.data[1][1], data.data[1][2]},
            {data.data[2][0], data.data[2][1], data.data[2][2]},
            {data.data[3][0], data.data[3][1], data.data[3][2]}
        },
        {
            {cross2.x, cross2.y, cross2.z},
            {data.data[0][0], data.data[0][1], data.data[0][2] - depth},
            {data.data[1][0], data.data[1][1], data.data[1][2] - depth},
            {data.data[1][0], data.data[1][1], data.data[2][2]},
            {data.data[0][0], data.data[0][1], data.data[3][2]}
        },
        {
            {cross3.x, cross3.y, cross3.z},
            {data.data[3][0], data.data[3][1], data.data[0][2]},
            {data.data[2][0], data.data[2][1], data.data[1][2]},
            {data.data[2][0], data.data[2][1], data.data[2][2] - depth},
            {data.data[3][0], data.data[3][1], data.data[3][2] - depth}
        },
        {
            {cross4.x, cross4.y, cross4.z},
            {data.data[0][0], data.data[0][1], data.data[0][2] - depth},
            {data.data[0][0], data.data[0][1], data.data[1][2]},
            {data.data[3][0], data.data[3][1], data.data[2][2]},
            {data.data[3][0], data.data[3][1], data.data[3][2] - depth}
        },
        {
            {cross5.x, cross5.y, cross5.z},
            {data.data[1][0], data.data[1][1], data.data[0][2]},
            {data.data[1][0], data.data[1][1], data.data[1][2] - depth},
            {data.data[2][0], data.data[2][1], data.data[2][2] - depth},
            {data.data[2][0], data.data[2][1], data.data[3][2]}
        },
        {
            {cross6.x, cross6.y, cross6.z},
            {data.data[0][0], data.data[0][1], data.data[0][2] - depth},
            {data.data[1][0], data.data[1][1], data.data[1][2] - depth},
            {data.data[2][0], data.data[2][1], data.data[2][2] - depth},
            {data.data[3][0], data.data[3][1], data.data[3][2] - depth}
        }
    }};

    return result;
}

void make2D() {
    angleX = 0.0f;
    angleY = 0.0f;
    resetObserver();
}

void make3D() {
    angleX = memX;
    angleY = memY;
}

void makeView() {
    memX = angleX;
    memY = angleY;
    angleX = 0.0f;
    angleY = 0.0f;
    resetObserver();
}

void drawBlock(data3d data, float color[4]) {
    for (int i = 0; i < 6; i++) {
        glBegin(GL_POLYGON);
        glNormal3f(data.data[i][0][0], data.data[i][0][1], data.data[i][0][2]);
        for (int j = 1; j < 5; j++) {
            glColor4f(color[0], color[1], color[2], color[3]);
            glVertex3f(
                data.data[i][j][0],
                data.data[i][j][1],
                data.data[i][j][2]
            );
        }
        glEnd();
    }
}

Vector3D crossVector(Vector3D v1, Vector3D v2) {
    Vector3D cross;

    cross.x = v1.y * v2.z - v1.z * v2.y;
    cross.y = v1.z * v2.x - v1.x * v2.z;
    cross.z = v1.x * v2.y - v1.y * v2.x;

    float besar = std::sqrt(std::pow(cross.x, 2) + std::pow(cross.y, 2) + std::pow(cross.z, 2));

    cross.x = cross.x / besar;
    cross.y = cross.y / besar;
    cross.z = cross.z / besar;

    return cross;
}


Vector3D diff2Point(Vector3D p1, Vector3D p2) {
    Vector3D v;

    v.x = p2.x - p1.x;
    v.y = p2.y - p1.y;
    v.z = p2.z - p1.z;

    return v;
}



