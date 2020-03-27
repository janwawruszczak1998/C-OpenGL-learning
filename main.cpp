#include <GL/glut.h>
#include <iostream>
#include <random>
#include <vector>
#include "time.h"

int getRand(int a, int b)
{
    return a + rand() % (b - a);
}

// x, y to wspolrzedne lewego gornego wierzcholka
void drawSquare(float x, float y, float size)
{
    glBegin(GL_TRIANGLES);

    	glColor3ub(getRand(150, 255), getRand(150, 255), getRand(0, 10));
    	glVertex2f(x, y);
	glColor3ub(getRand(150, 255), getRand(150, 255), getRand(0, 10));
    	glVertex2f(x + size, y);
	glColor3ub(getRand(150, 255), getRand(150, 255), getRand(0, 10));	
    	glVertex2f(x + size, y - size);

    glEnd();

    glBegin(GL_TRIANGLES);

    glColor3ub(getRand(150, 255), getRand(150, 255), getRand(0, 10));
    glVertex2f(x + size, y - size);
    glColor3ub(getRand(150, 255), getRand(150, 255), getRand(0, 10));
    glVertex2f(x, y - size);
    glColor3ub(getRand(150, 255), getRand(150, 255), getRand(0, 10));
    glVertex2f(x, y);

    glEnd();
}

void drawBlankSquare(float x, float y, float size)
{
    glBegin(GL_TRIANGLES);
    glColor3f(0.5f, 0.5f, 0.5f);

    glVertex2f(x, y);
    glVertex2f(x + size, y);
    glVertex2f(x + size, y - size);

    glEnd();

    glBegin(GL_TRIANGLES);

    glVertex2f(x + size, y - size);
    glVertex2f(x, y - size);
    glVertex2f(x, y);

    glEnd();
}

void drawCarpet(float x, float y, float size, int depth)
{
    if (depth == 0)
    {
	drawSquare(x, y, size / 3.0f + getRand(-5, 5));	
        return;
    }
    for (int i = 0; i < 3; ++i)
    {
        if (i != 0)
            y -= size / 3.0f;
        for (int j = 0; j < 3; ++j)
        {
            if (i == 1 && j == 1)
                drawBlankSquare(x + j * (size / 3.0f), y, size / 3.0f + getRand(-5, 5));
            else
            {
                drawCarpet(x + j * (size / 3.0f), y, size / 3.0f, depth - 1);
            }
        }
    }
}

void renderScene(void)
{
    float initial_size = 100;
    int depth = 7;
    glClear(GL_COLOR_BUFFER_BIT);
    drawCarpet(-50, 50, initial_size, depth);
    glFlush();
}

void myInit(void)
{
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
}

void changeSize(GLsizei horizontal, GLsizei vertical)
{
    GLfloat aspectRatio;
    if (vertical == 0)
        vertical = 1;

    glViewport(0, 0, horizontal, vertical);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    aspectRatio = (GLfloat)horizontal / (GLfloat)vertical;

    if (horizontal <= vertical)
        glOrtho(-100.0, 100.0, -100.0 / aspectRatio, 100.0 / aspectRatio, 1.0, -1.0);
    else
        glOrtho(-100.0 * aspectRatio, 100.0 * aspectRatio, -100.0, 100.0, 1.0, -1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char *argv[])
{

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

    glutInit(&argc, argv);
    glutCreateWindow("Pierwszy program w OpenGL");

    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    myInit();
    glutMainLoop();
    return 0;
}
