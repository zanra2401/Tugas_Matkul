#include <windows.h>
#include <GL/glut.h>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <iostream>

using namespace std;

const int COLS = 17;
const int ROWS = 5;
const int TOTAL_CELLS = COLS * ROWS;

float cellWidth = 2.0f / COLS;
float cellHeight = 2.0f / ROWS;

int rows[ROWS][COLS] = {
    {0,  0,  1, 2,  0,  0, 5,  0,  0, 8,  0,  8, 81, 82, 8,  8,  85},
    {52, 5, 5, 55, 5, 5, 58, 5, 0, 1, 2, 0, 0, 5, 0, 0, 8},
    {5,  0,  0, 8,  0,  0, 1,  2,  0,  0, 5,  0, 0,  8,  0, 5, 51},
    {18, 1, 2, 21, 22, 2, 2, 25, 2, 2, 28, 2, 0, 1, 2, 0, 0},
    {1,  2,  0,  0,  5,  0,  0,  8,  0, 1, 11, 12,  1, 1, 15,  1, 1}
};

void drawText(float x, float y, const std::string& text) {
    glRasterPos2f(x, y);
    for (size_t i = 0; i < text.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
    }
}

void drawNumbers() {
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            int number = rows[row][col];
            if (number == 0) continue;

            int realCol = (row % 2 == 0) ? col : (COLS - 1 - col);
            float x = -1.0f + (realCol * cellWidth) + (cellWidth * 0.55f);
            float y = -1.0f + ((ROWS - 1 - row) * cellHeight) + (cellHeight * 0.5f);

            std::stringstream ss;
            ss << number;

            glColor3f(0.0f, 0.4f, 0.0f);
            drawText(x, y, ss.str());
            drawText(x + 0.003f, y + 0.003f, ss.str());
        }
    }
}

void getCoordinates(int num, float& x, float& y) {
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            if (rows[row][col] == num) {
                int realCol = (row % 2 == 0) ? col : (COLS - 1 - col);
                x = -1.0f + (realCol * cellWidth) + (cellWidth / 2);
                y = -1.0f + ((ROWS - 1 - row) * cellHeight) + (cellHeight / 2);
                return;
            }
        }
    }
}

void drawBoard() {
    int count = TOTAL_CELLS;
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            int realCol = (row % 2 == 0) ? col : (COLS - 1 - col);
            float x = realCol * cellWidth - 1.0f;
            float y = row * cellHeight - 1.0f;

            if (count % 2 == 0) glColor3f(1.0f, 1.0f, 0.9f);
            else glColor3f(0.0f, 0.0f, 0.5f);

            glBegin(GL_POLYGON);
            glVertex2f(x, y);
            glVertex2f(x + cellWidth, y);
            glVertex2f(x + cellWidth, y + cellHeight);
            glVertex2f(x, y + cellHeight);
            glEnd();

            bool isTransitionCell = (row % 2 == 0 && realCol == COLS - 1) || (row % 2 == 1 && realCol == 0);
            if (!isTransitionCell) {
                glColor3f(0.0f, 0.4f, 0.0f);
                glBegin(GL_POLYGON);
                glVertex2f(x, y + cellHeight);
                glVertex2f(x + cellWidth, y + cellHeight);
                glVertex2f(x + cellWidth, y + cellHeight - 0.02f); // ketebalan dinaikkan
                glVertex2f(x, y + cellHeight - 0.02f);
                glEnd();
            }
            count--;
        }
    }

    float outerThickness = 0.005f;
    float innerThickness = 0.007f;
    float thickerInner = innerThickness + 0.03f;

    // Border hijau
    glColor3f(0.0f, 0.4f, 0.0f); // Hijau

    // Bawah
    glBegin(GL_POLYGON);
    glVertex2f(-1.0f + outerThickness, -1.0f + outerThickness);
    glVertex2f(1.0f - outerThickness, -1.0f + outerThickness);
    glVertex2f(1.0f - outerThickness, -1.0f + outerThickness + thickerInner);
    glVertex2f(-1.0f + outerThickness, -1.0f + outerThickness + thickerInner);
    glEnd();

    // Kanan
    glBegin(GL_POLYGON);
    glVertex2f(1.0f - outerThickness - innerThickness, -1.0f + outerThickness);
    glVertex2f(1.0f - outerThickness, -1.0f + outerThickness);
    glVertex2f(1.0f - outerThickness, 1.0f - outerThickness);
    glVertex2f(1.0f - outerThickness - innerThickness, 1.0f - outerThickness);
    glEnd();

    // Atas

    glBegin(GL_POLYGON);
    glVertex2f(-1.0f + outerThickness, 1.0f - outerThickness - thickerInner);
    glVertex2f(1.0f - outerThickness, 1.0f - outerThickness - thickerInner);
    glVertex2f(1.0f - outerThickness, 1.0f - outerThickness);
    glVertex2f(-1.0f + outerThickness, 1.0f - outerThickness);
    glEnd();


    // Kiri
    glBegin(GL_POLYGON);
    glVertex2f(-1.0f + outerThickness, -1.0f + outerThickness);
    glVertex2f(-1.0f + outerThickness + innerThickness, -1.0f + outerThickness);
    glVertex2f(-1.0f + outerThickness + innerThickness, 1.0f - outerThickness);
    glVertex2f(-1.0f + outerThickness, 1.0f - outerThickness);
    glEnd();

    // border hitam
    glColor3f(0.0f, 0.0f, 0.0f); // Hitam

    // Bawah
    glBegin(GL_POLYGON);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f + outerThickness + 0.02);
    glVertex2f(-1.0f, -1.0f + outerThickness + 0.02);
    glEnd();

    // Kanan
    glBegin(GL_POLYGON);
    glVertex2f(1.0f - outerThickness, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(1.0f - outerThickness, 1.0f);
    glEnd();

    // Atas
    glBegin(GL_POLYGON);
    glVertex2f(-1.0f, 1.0f - outerThickness - 0.02);
    glVertex2f(1.0f, 1.0f - outerThickness - 0.02);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    glEnd();

    // Kiri
    glBegin(GL_POLYGON);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(-1.0f + outerThickness, -1.0f);
    glVertex2f(-1.0f + outerThickness, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    glEnd();

}


void drawSnakes() {
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.1, -0.5);
    glVertex2f(0.12, -0.5);
    glVertex2f(0.25, -0.01);
    glVertex2f(0.27, -0.01);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(0.25, -0.01);
    glVertex2f(0.27, -0.01);
    glVertex2f(0.35, -0.5);
    glVertex2f(0.37, -0.5);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(0.35, -0.5);
    glVertex2f(0.37, -0.5);
    glVertex2f(0.45, -0.80);
    glVertex2f(0.43, -0.80);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0.8, 0.35);
    glVertex2f(0.82, 0.35);
    glVertex2f(0.95, -0.1);
    glVertex2f(0.97, -0.1);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0.95, -0.1);
    glVertex2f(0.97, -0.1);
    glVertex2f(0.82, -0.5);
    glVertex2f(0.84, -0.5);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0.82, -0.5);
    glVertex2f(0.84, -0.5);
    glVertex2f(0.93, -0.8);
    glVertex2f(0.95, -0.8);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-0.7, 0.75);
    glVertex2f(-0.72, 0.75);
    glVertex2f(-0.59, 0.4);
    glVertex2f(-0.61, 0.4);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-0.59, 0.4);
    glVertex2f(-0.61, 0.4);
    glVertex2f(-0.59, 0.0);
    glVertex2f(-0.61, 0.0);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-0.59, 0.0);
    glVertex2f(-0.61, 0.0);
    glVertex2f(-0.7, -0.45);
    glVertex2f(-0.72, -0.45);
    glEnd();
}

void drawStairs() {
    glLineWidth(3.0f);
    glColor3f(0.294f, 0.325f, 0.125f);

    // tangga pertama
    glBegin(GL_POLYGON);
    glVertex2f(-0.08f, -0.8f); // kiri atas
    glVertex2f(-0.08f, 0.5f);  // kanan atas
    glVertex2f(-0.087f, 0.5f);  // kanan bawah
    glVertex2f(-0.087f, -0.8f); // kiri bawah
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-0.14f, -0.8f); // kiri atas
    glVertex2f(-0.14f, 0.5f);   // kanan atas
    glVertex2f(-0.147f, 0.5f); // kanan bawah
    glVertex2f(-0.147f, -0.8f); // kiri bawah
    glEnd();


    float y = -0.8f;
    for (int i = 0; i < 8; i++) {
         float yTop = y + 0.12f;
         float ybottom = y + 0.1f;
        glBegin(GL_POLYGON);
        glVertex2f(-0.14f, ybottom);  // kiri bawah
        glVertex2f(-0.08f, ybottom);  // kanan bawah
        glVertex2f(-0.08f, yTop);   // kanan atas
        glVertex2f(-0.14f, yTop);   // kiri atas
        glEnd();
        y += 0.15f;  // ge
    }

    // tangga kedua
    glBegin(GL_POLYGON);
    glVertex2f(-0.95f, -0.1f);   // kiri atas
    glVertex2f(-0.6f, -0.1f);    // kanan atas
    glVertex2f(-0.6f, -0.12f);   // kanan bawah
    glVertex2f(-0.95f, -0.12f);  // kiri bawah
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-0.95f, 0.07f); // kiri atas
    glVertex2f(-0.6f, 0.07f);  // kanan atas
    glVertex2f(-0.6f, 0.09f); // kanan bawah
    glVertex2f(-0.95f, 0.09f); // kiri bawah

    glEnd();

    float x1 = -0.9f;
    for (int i = 0; i < 6; i++) {
        float cx = 0.009;
        float width = 0.009f;
        float height = 0.17f;
        float y_top = 0.07f;
        float y_bottom = y_top - height;

        glBegin(GL_POLYGON);
        glVertex2f(x1, y_top);
        glVertex2f(x1 + width, y_top);
        glVertex2f(x1 + width, y_bottom);
        glVertex2f(x1, y_bottom);
        glEnd();
        x1 += 0.05f;

    }

    // tangga ketiga

    glBegin(GL_POLYGON);
    glVertex2f(0.31f, 0.72f);
    glVertex2f(0.32f, 0.73f);
    glVertex2f(0.71f, -0.49f);
    glVertex2f(0.7f, -0.5f);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0.37f, 0.85f);
    glVertex2f(0.39f, 0.83f);
    glVertex2f(0.77f, -0.38f);
    glVertex2f(0.76f, -0.4f);
    glEnd();

    float x1_start = 0.7f, y1_start = -0.5f;
    float x1_end = 0.31f, y1_end = 0.75f;
    float x2_start = 0.76f, y2_start = -0.4f;
    float x2_end = 0.37f, y2_end = 0.85f;

    for (int i = 1; i < 7; i++) {
        float t = (float)i / 7;
        float x_kiri = x1_start + (x1_end - x1_start) * t;
        float y_kiri = y1_start + (y1_end - y1_start) * t;
        float x_kanan = x2_start + (x2_end - x2_start) * t;
        float y_kanan = y2_start + (y2_end - y2_start) * t;

        glBegin(GL_POLYGON);
        glVertex2f(x_kiri, y_kiri);
        glVertex2f(x_kanan, y_kanan);
        glVertex2f(x_kanan + 0.01, y_kanan - 0.02);
        glVertex2f(x_kiri + 0.008, y_kiri - 0.02);
        glEnd();
    }
}

void drawPlayers(float player1X, float player1Y, float player2X, float player2Y) {
    // player 1
    glColor3f(255.0f, 255.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(player1X - 0.03f, player1Y - 0.03f);
    glVertex2f(player1X + 0.03f, player1Y - 0.03f);
    glVertex2f(player1X + 0.03f, player1Y + 0.03f);
    glVertex2f(player1X - 0.03f, player1Y + 0.03f);
    glEnd();

    // player 2
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(player2X - 0.03f, player2Y - 0.03f);
    glVertex2f(player2X + 0.03f, player2Y - 0.03f);
    glVertex2f(player2X, player2Y + 0.03f);
    glEnd();
}

bool turn_player1 = true;
int posisiPlayer1 = 1;
int posisiPlayer2 = 1;
bool gameOver = false;


void input(unsigned char roll, int x, int y) {
    if (roll == ' ' && !gameOver) {
        int dadu = rand() % 6 + 1;

        if (turn_player1) {
            posisiPlayer1 += dadu;
            if (posisiPlayer1 == 8){
                posisiPlayer1 = 61;
            }
            else if (posisiPlayer1 == 25){
                posisiPlayer1 = 13;
            }
            else if (posisiPlayer1 == 35){
                posisiPlayer1 = 38;
            }
            else if (posisiPlayer1 == 20){
                posisiPlayer1 = 80;
            }
            else if (posisiPlayer1 == 53){
                posisiPlayer1 = 17;
            }
            else if (posisiPlayer1 == 71){
                posisiPlayer1 = 32;
            }
            else if (posisiPlayer1 >= 85) {
                posisiPlayer1 = 85;
                gameOver = true;
                cout << "Player 1 menang!" << endl;
            }
            if (!gameOver){
                cout << "Angka dadu player 1: " << dadu << ", posisi player di kotak " << posisiPlayer1 <<endl;
            }

        } else {
            posisiPlayer2 += dadu;
            if (posisiPlayer2 == 8){
                posisiPlayer2 = 61;
            }
            else if (posisiPlayer2 == 25){
                posisiPlayer2 = 13;
            }
            else if (posisiPlayer2 == 35){
                posisiPlayer2 = 38;
            }
            else if (posisiPlayer2 == 20){
                posisiPlayer2 = 80;
            }
            else if (posisiPlayer2 == 53){
                posisiPlayer2 = 17;
            }
            else if (posisiPlayer2 == 71){
                posisiPlayer2 = 32;
            }
            else if (posisiPlayer2 >= 85) {
                posisiPlayer2 = 85;
                gameOver = true;
                cout << "Player 2 menang!" << endl;
            }
            if (!gameOver){
                cout << "Angka dadu player 2: " << dadu << ", posisi player di kotak " << posisiPlayer2 <<endl;
            }

        }

        turn_player1 = !turn_player1;
        glutPostRedisplay();
    }

}
void getPlayerCoordinates(int posisi, float& x, float& y) {
    int kolom = (posisi - 1) % 17;
    int baris = (posisi - 1) / 17;

    // Set arah horizontal
    if (baris % 2 == 1) {
        kolom = 16 - kolom;
    }

    x = -0.93f + kolom * (2.0f / 17.0f);
    y = -0.8f + baris * (2.0f / 5.0f);

}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawBoard();
    drawNumbers();
    drawStairs();
    drawSnakes();

    float player1X = -0.93f, player1Y = -0.8f;
    float player2X = -0.93f, player2Y = -0.8f;
    getPlayerCoordinates(posisiPlayer1, player1X, player1Y);
    getPlayerCoordinates(posisiPlayer2, player2X, player2Y);
    drawPlayers(player1X, player1Y, player2X, player2Y);

    if (gameOver) {
        if (turn_player1) {
            glColor3f(0.0f, 0.0f, 1.0f); // Player 2 menang → biru
        } else {
            glColor3f(1.0f, 1.0f, 0.0f); // Player 1 menang → kuning
        }

        string winner = turn_player1 ? "Player 2 menang!" : "Player 1 menang!";
        drawText(-0.2f, 0.0f, winner);
    }

    glutSwapBuffers();
}


void myInit() {
    glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000, 350);
    glutCreateWindow("Ular Tangga 17x5");
    myInit();
    srand(time(0));
    glutKeyboardFunc(input);
    cout << "press space to play the game..." << endl;
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
