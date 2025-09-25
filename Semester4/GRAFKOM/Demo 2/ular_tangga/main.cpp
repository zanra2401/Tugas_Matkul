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

struct Color {
    float r;
    float g;
    float b;
};

Vector2D SIZE_GRID = {7, 12};
Vector2D mapCoordinate[7][12];
int player1CoorX = 0;
int player1CoorY = 0;
int player2CoorX = 0;
int player2CoorY = 0;
int player2Langkah = 0;
int player1Langkah = 0;
bool giliran = false;

int langkahUnik[] = {2, 12, 30, 46, 55, 82};
int hasilLangkahUnik[][2] = {{6,0}, {32, 4}, {58, 8}, {9, 1}, {15, 2}, {52, 7}};
bool selesai = false;

void init();
void printOne();
void createRectangle(int width, int height);
void display();
void printOne(Color color, Vector2D position);
void printSeven(Color color, Vector2D position);
void printTwo(Color color, Vector2D position);
void printFive(Color color, Vector2D position);
void printSix(Color color, Vector2D position);
void drawMap(Vector2D mapSize, Color firstColor, Color secondColor, float initPos, int sizeBlock, float gap);
void drawPagar(Color color, Vector2D position);
void drawVerticalTangga(Vector2D start, Vector2D endPoint, Color color, float gap, float yMinus);
void drawHorizontalTangga(Vector2D start, Vector2D endPoint, Color color, float gap, float xPlus);
void drawDiagonalTangga(Vector2D start, Vector2D endPoint, Color color);
void drawUlar(Vector2D petak[], int length, Color color);
void spawnPlayer(Vector2D player1Coor, Vector2D player2Coor, Color pc1, Color pc2);
void inputHandler(unsigned char key, int x, int y);
void movePlayer(int player);
int isExist(int arr[], int length, int needle);
void drawNums(Vector2D mapSize, Color numsColor, float initPos, int sizeBlock, float gap);


int main(int argc, char* argv[]) {
    std::cout << "Tekan Spasi Untuk Memulai Permainan" << std::endl;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize((SIZE_GRID.x * 2 + 1)*26, (SIZE_GRID.y * 2 + 2.5)*26);
    glutCreateWindow("Ular Tangga");
    glutDisplayFunc(display);
    glutKeyboardFunc(inputHandler);
    init();
    glutMainLoop();
    return 0;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    Color warnaUlar = {1, 0, 0};
    Color warnaTangga = {1, 0.6, 0};

    drawMap({7, 12}, {0, 0, 1}, {1, 1, 1}, 0.5, 2, 0.25);
    drawPagar({0, 1, 0}, {0, 0});
    drawNums({7, 12}, {0, 0, 0},  0.5, 2, 0.25);

    drawDiagonalTangga(mapCoordinate[4][4], mapCoordinate[1][1], warnaTangga);
    drawVerticalTangga(mapCoordinate[2][8], mapCoordinate[2][4], warnaTangga, 1.85, 0.65);
    drawHorizontalTangga(mapCoordinate[2][0], mapCoordinate[6][0], warnaTangga, 2, 0.75);

    Vector2D ular1[] = {mapCoordinate[1][11], mapCoordinate[3][9], mapCoordinate[2][8], mapCoordinate[3][7]};
    Vector2D ular2[] = {mapCoordinate[4][6], mapCoordinate[3][5], mapCoordinate[5][3], mapCoordinate[4][1]};
    Vector2D ular3[] = {mapCoordinate[0][7], mapCoordinate[2][5], mapCoordinate[1][4], mapCoordinate[1][2]};

    drawUlar(ular1, 4, warnaUlar);
    drawUlar(ular2, 4, warnaUlar);
    drawUlar(ular3, 4, warnaUlar);

    Vector2D player1Coor = {mapCoordinate[player1CoorX][player1CoorY].x, mapCoordinate[player1CoorX][player1CoorY].y + 0.5};
    Vector2D player2Coor = {mapCoordinate[player2CoorX][player2CoorY].x, mapCoordinate[player2CoorX][player2CoorY].y - 0.5};

    spawnPlayer(player1Coor, player2Coor, {0.0, 1.0, 1.0}, {0, 0, 0});

    glFlush();
}

void init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, SIZE_GRID.x * 2 + 1, 0, SIZE_GRID.y * 2 + 3.75);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(0,0,0,0);
	glColor3f(0.0,0.0,1.0);
}

// Bagian Menggambar atau Display atau View

void createRectangle(Vector2D position, float width, float height) {
    glBegin(GL_POLYGON);
        glVertex2d(position.x, position.y);
        glVertex2d(position.x, position.y - height);
        glVertex2d(position.x + width, position.y - height);
        glVertex2d(position.x + width, position.y);
    glEnd();
}

void printOne(Color color, Vector2D position) {
    glColor3f(color.r, color.g, color.b);
    createRectangle({position.x, position.y}, 0.1, 0.5);
}

void printSeven(Color color, Vector2D position) {
    glColor3f(color.r, color.g, color.b);
    createRectangle({position.x - 0.2, position.y}, 0.2, 0.13);
    createRectangle({position.x,  position.y}, 0.1, 0.5);
}

void printTwo(Color color, Vector2D position) {
    glColor3f(color.r, color.g, color.b);
    createRectangle({position.x - 0.2, position.y}, 0.2, 0.13);
    createRectangle({position.x,  position.y}, 0.1, 0.35);
    createRectangle({position.x - 0.2, position.y - 0.22}, 0.2, 0.13);
    createRectangle({position.x - 0.2,  position.y - 0.23}, 0.1, 0.25);
    createRectangle({position.x - 0.2, position.y - 0.4}, 0.3, 0.13);
}

void printFive(Color color, Vector2D position) {
    glColor3f(color.r, color.g, color.b);
    createRectangle({position.x - 0.2, position.y}, 0.3, 0.13);
    createRectangle({position.x - 0.2,  position.y}, 0.1, 0.25);
    createRectangle({position.x - 0.2, position.y - 0.20}, 0.2, 0.13);
    createRectangle({position.x,  position.y - 0.20}, 0.1, 0.30);
    createRectangle({position.x - 0.2, position.y - 0.4}, 0.3, 0.13);
}

void printSix(Color color, Vector2D position) {
    glColor3f(color.r, color.g, color.b);
    createRectangle({position.x - 0.2, position.y}, 0.3, 0.13);
    createRectangle({position.x - 0.2,  position.y}, 0.1, 0.25);
    createRectangle({position.x - 0.2, position.y - 0.20}, 0.2, 0.13);
    createRectangle({position.x,  position.y - 0.20}, 0.1, 0.30);
    createRectangle({position.x - 0.2, position.y - 0.4}, 0.3, 0.13);
    createRectangle({position.x - 0.2,  position.y - 0.20}, 0.1, 0.30);
}

void drawPagar(Color color, Vector2D position) {
    glColor3f(color.r, color.g, color.b);
    createRectangle({position.x + 0.25, position.y + (SIZE_GRID.y * 2 + 3.5)}, 0.25, SIZE_GRID.y * 2 + 3.25);
    createRectangle({position.x + 0.25, position.y + 0.5}, SIZE_GRID.x * 2 + 0.5, 0.25);
    createRectangle({position.x + SIZE_GRID.x * 2 + 0.5, position.y + (SIZE_GRID.y * 2 + 3.5)}, 0.25, SIZE_GRID.y * 2 + 3.25);
    createRectangle({position.x + 0.25, position.y + (SIZE_GRID.y * 2 + 3.5)}, SIZE_GRID.x * 2 + 0.5, 0.25);

    for (int i = 1; i < 13; i++)
    {
        if (i % 2 == 1)
        {
            createRectangle({position.x + 0.5, position.y + 0.5 + (2 * i) + (0.25 * i)}, SIZE_GRID.x * 2 - 2, 0.25 );
        } else {
            createRectangle({position.x + 0.5 + 2, position.y + 0.5 + (2 * i) + (0.25 * i)}, SIZE_GRID.x * 2 - 2, 0.25 );
        }
    }

}

void drawMap(Vector2D mapSize, Color firstColor, Color secondColor, float initPos, int sizeBlock, float gap) {
    int validNumber[] = {1, 2, 5, 6, 7};
    for (int i = 0; i < mapSize.y; i++)
    {
        for (int j = 0; j < mapSize.x; j++)
        {
            switch (j % 2 == i % 2) {
                case false:
                    glColor3f(firstColor.r, firstColor.g, firstColor.b);
                    break;
                case true:
                    glColor3f(secondColor.r, secondColor.g, secondColor.b);
                    break;
            }
            createRectangle({initPos + (j * sizeBlock), initPos + (sizeBlock * (i + 1)) + (gap * (i + 1))}, sizeBlock , sizeBlock + gap);
            Vector2D centerPos = {(initPos + (j * sizeBlock)) + 1, (initPos + (sizeBlock * (i + 1)) + (gap * i)) - 1};
            mapCoordinate[j][i] = centerPos;
        }
    }
}

void drawNums(Vector2D mapSize, Color numsColor ,float initPos, int sizeBlock, float gap) {

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
                    printOne({numsColor.r, numsColor.g, numsColor.b}, {initPos + ((j + 1) * sizeBlock)- 0.1 - 0.25, initPos + (sizeBlock * (i + 1)) + (gap * i) - 0.25});
                    numberGap = 0.2;
                    break;
                case 2:
                    printTwo({numsColor.r, numsColor.g, numsColor.b}, {initPos + ((j + 1) * sizeBlock)- 0.1 - 0.25, initPos + (sizeBlock * (i + 1)) + (gap * i) - 0.25});
                    break;
                case 5:
                    printFive({numsColor.r, numsColor.g, numsColor.b}, {initPos + ((j + 1) * sizeBlock)- 0.1 - 0.25, initPos + (sizeBlock * (i + 1)) + (gap * i) - 0.25});
                    break;
                case 6:
                    printSix({numsColor.r, numsColor.g, numsColor.b}, {initPos + ((j + 1) * sizeBlock)- 0.1 - 0.25, initPos + (sizeBlock * (i + 1)) + (gap * i) - 0.25});
                    break;
                case 7:
                    printSeven({numsColor.r, numsColor.g, numsColor.b}, {initPos + ((j + 1) * sizeBlock)- 0.1 - 0.25, initPos + (sizeBlock * (i + 1)) + (gap * i) - 0.25});
                    break;
                default:
                    numberGap = 0.0;
                    break;
            }


            if (first != 0) {
                switch (first) {
                    case 1:
                        printOne({numsColor.r, numsColor.g, numsColor.b}, {initPos + ((j + 1) * sizeBlock)- 0.1 - 0.25- numberGap, initPos + (sizeBlock * (i + 1)) + (gap * i) - 0.25});
                        break;
                    case 2:
                        printTwo({numsColor.r, numsColor.g, numsColor.b}, {initPos + ((j + 1) * sizeBlock)- 0.1 - 0.25 - numberGap, initPos + (sizeBlock * (i + 1)) + (gap * i) - 0.25});
                        break;
                    case 5:
                        printFive({numsColor.r, numsColor.g, numsColor.b}, {initPos + ((j + 1) * sizeBlock)- 0.1 - 0.25- numberGap, initPos + (sizeBlock * (i + 1)) + (gap * i) - 0.25});
                        break;
                    case 6:
                        printSix({numsColor.r, numsColor.g, numsColor.b}, {initPos + ((j + 1) * sizeBlock)- 0.1 - 0.25 - numberGap, initPos + (sizeBlock * (i + 1)) + (gap * i) - 0.25});
                        break;
                    case 7:
                        printSeven({numsColor.r, numsColor.g, numsColor.b}, {initPos + ((j + 1) * sizeBlock)- 0.1 - 0.25- numberGap, initPos + (sizeBlock * (i + 1)) + (gap * i) - 0.25});
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

void drawVerticalTangga(Vector2D start, Vector2D endPoint, Color color, float gap, float yMinus) {
    glColor3f(color.r, color.g, color.b);

    glBegin(GL_POLYGON);
        glVertex2d(start.x - 0.75, start.y);
        glVertex2d(endPoint.x - 0.75, endPoint.y);
        glVertex2d(endPoint.x - 0.5, endPoint.y);
        glVertex2d(start.x - 0.5, start.y);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2d(start.x + 0.5, start.y);
        glVertex2d(endPoint.x + 0.5, endPoint.y);
        glVertex2d(endPoint.x + 0.75, endPoint.y);
        glVertex2d(start.x + 0.75, start.y);
    glEnd();

    int heightLadder = std::floor(start.y - endPoint.y);
    int totalTangga = (heightLadder / 1);
    createRectangle({start.x - 0.5, start.y - yMinus}, 1, 0.25);

    while (gap < heightLadder)
    {
        createRectangle({start.x - 0.5, start.y - gap}, 1, 0.25);
        gap = gap + 1 + 0.25;
    }

    if (not(start.y - gap < endPoint.y + 0.5)) {
        createRectangle({endPoint.x - 0.5, start.y - gap}, 1, 0.25);
    }
}

void drawHorizontalTangga(Vector2D start, Vector2D endPoint, Color color, float gap, float xPlus) {
    glColor3f(color.r, color.g, color.b);

    glBegin(GL_POLYGON);
        glVertex2d(start.x, start.y + 0.75);
        glVertex2d(endPoint.x, endPoint.y + 0.75);
        glVertex2d(endPoint.x, endPoint.y + 0.5);
        glVertex2d(start.x, start.y + 0.5);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2d(start.x, start.y - 0.45);
        glVertex2d(endPoint.x, endPoint.y - 0.45);
        glVertex2d(endPoint.x, endPoint.y - 0.7);
        glVertex2d(start.x, start.y - 0.7);
    glEnd();

    int widthLadder = std::floor(endPoint.x - start.x);


    createRectangle({start.x + xPlus, start.y + 0.5}, 0.25, 1);

    while (gap < widthLadder)
    {
        createRectangle({start.x + gap, start.y + 0.5}, 0.25, 1);
        gap = gap + 1 + 0.25;
    }

    if (not(start.y - gap < endPoint.y + 0.5)) {
        createRectangle({endPoint.x + gap, start.y + 0.5}, 0.25, 1);
    }

}

void drawDiagonalTangga(Vector2D start, Vector2D endPoint, Color color) {
    glColor3f(color.r, color.g, color.b);

    glBegin(GL_POLYGON);
        glVertex2d(start.x - 0.5, start.y + 0.5);
        glVertex2d(endPoint.x - 0.5, endPoint.y + 0.5);
        glVertex2d(endPoint.x - 0.35, endPoint.y + 0.35);
        glVertex2d(start.x - 0.35, start.y + 0.35);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2d(start.x + 0.5, start.y - 0.5);
        glVertex2d(endPoint.x + 0.5, endPoint.y - 0.5);
        glVertex2d(endPoint.x + 0.35, endPoint.y - 0.35);
        glVertex2d(start.x + 0.35, start.y - 0.35);
    glEnd();


    float gap = 0.5;
    int loop = 0;
    float gap2 = 0;
    float panjangTangga = std::sqrt(pow(start.x - endPoint.x, 2) + pow(start.y - endPoint.y, 2));
    while (gap + 2 + (loop * 0.1) < panjangTangga) {
        glBegin(GL_POLYGON);
            glVertex2d((start.x - (0.4 - gap2)) - gap, (start.y + (0.4 - gap2)) - gap);
            glVertex2d((start.x - (0.4 - gap2)) - (gap + 0.15), (start.y + (0.4 - gap2)) - (gap + 0.15));
            glVertex2d(((start.x + (0.4 + gap2)) - (gap + 0.15)), ((start.y - (0.4 + gap2)) - (gap + 0.15)));
            glVertex2d((start.x + (0.4 + gap2)) - gap , ((start.y - (0.4 + gap2)) - gap));
        glEnd();
        gap = gap + 1;
        gap2 = gap2 + 0.07;
        loop = loop + 1;
    }

}

void drawUlar(Vector2D petak[], int length, Color color) {
    glColor3f(color.r, color.g, color.b);

    for (int i = 0; i < length - 1; i++)
    {
            glBegin(GL_POLYGON);
                glVertex2d(petak[i].x - 0.15, petak[i].y);
                glVertex2d(petak[i + 1].x - 0.15, petak[i + 1].y);
                glVertex2d(petak[i + 1].x + 0.15, petak[i + 1].y);
                glVertex2d(petak[i].x + 0.15, petak[i].y);
            glEnd();
    }
}

void spawnPlayer(Vector2D player1Coor, Vector2D player2Coor, Color pc1, Color pc2)
{
    glColor3f(pc1.r, pc1.g, pc1.b);
    createRectangle({player1Coor.x - 0.2, player1Coor.y + 0.2}, 0.4, 0.4);

    glColor3f(pc2.r, pc2.g, pc2.b);
    glBegin(GL_POLYGON);
        glVertex2d(player2Coor.x,  player2Coor.y + 0.2);
        glVertex2d(player2Coor.x - 0.2, player2Coor.y - 0.2);
        glVertex2d(player2Coor.x + 0.2, player2Coor.y - 0.2);
    glEnd();
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



