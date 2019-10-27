#include <GL/glut.h>
#include <iostream>
#include <random>
#include <vector>
#include "time.h"
/*************************************************************************************/

// Funkcaja określająca, co ma być rysowane
// (zawsze wywoływana, gdy trzeba przerysować scenę)

int getRand(int a, int b)
{
    return a + rand() % (b - a);
}

// x, y to wspolrzedne lewego gornego wierzcholka
void drawSquare(float x ,float y, float size){
    glBegin(GL_POLYGON);

    glColor3f(getRand(0, 256) / 255.0f, getRand(0, 256) / 255.0f, getRand(0, 256) / 255.0f);
    glVertex2f(x, y);
    glVertex2f(x + size, y);
    glVertex2f(x + size, y - size);
    glVertex2f(x, y - size);
    glEnd();

    glFlush();
}

void drawBlankRect(float x, float y, float size){
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    drawSquare(x,y,size);
}

void renderScene(void)
{
    float initial_size = 100;
    int depth = 1;
    glClear(GL_COLOR_BUFFER_BIT);
    drawSquare(-initial_size/2.0f, initial_size/2.0f, initial_size);

    // drawSquare(-initial_size/2.0f, initial_size/2.0f, initial_size/3.0f);
    // drawSquare(-initial_size/2.0f + initial_size/3.0f, initial_size/2.0f, initial_size/3.0f);
    // drawSquare(-initial_size/2.0f + 2 * initial_size/3.0f, initial_size/2.0f, initial_size/3.0f);
    
    // drawSquare(-initial_size/2.0f, initial_size/2.0f - initial_size/3.0f, initial_size/3.0f);
    // drawSquare(-initial_size/2.0f + initial_size/3.0f, initial_size/2.0f  - initial_size/3.0f, initial_size/3.0f);
    // drawSquare(-initial_size/2.0f + 2 * initial_size/3.0f, initial_size/2.0f  - initial_size/3.0f, initial_size/3.0f);

    // drawSquare(-initial_size/2.0f, initial_size/2.0f - 2 * initial_size/3.0f, initial_size/3.0f);
    // drawSquare(-initial_size/2.0f + initial_size/3.0f, initial_size/2.0f  - 2 * initial_size/3.0f, initial_size/3.0f);
    // drawSquare(-initial_size/2.0f + 2 * initial_size/3.0f,initial_size/2.0f  -  2 * initial_size/3.0f, initial_size/3.0f);

    float x = -initial_size/2.0f;
    float y = initial_size/2.0f;
    for(int i = 0; i < 3; ++i){
        if(i != 0)
            y -= initial_size/3.0f;
        for(int j = 0; j < 3; ++j){
            drawSquare( x + j * (initial_size/3.0f), y, initial_size/3.0f);
        }
    }
    
}

/*************************************************************************************/

// Funkcja ustalająca stan renderowania

void myInit(void)

{

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    // Kolor okna wnętrza okna - ustawiono na szary
}

/*************************************************************************************/

// Parametry horizontal i vertical (szerokość i wysokość okna) są
// przekazywane do funkcji za każdym razem, gdy zmieni się rozmiar okna
void changeSize(GLsizei horizontal, GLsizei vertical)
{
    GLfloat aspectRatio;
    // Deklaracja zmiennej AspectRatio określającej proporcję wymiarów okna
    if (vertical == 0)
        // Zabezpieczenie pzred dzieleniem przez 0
        vertical = 1;

    glViewport(0, 0, horizontal, vertical);
    // Ustawienie wielkościokna okna urządzenia (Viewport)
    // W tym przypadku od (0,0) do (horizontal, vertical)

    glMatrixMode(GL_PROJECTION);
    // Określenie układu współrzędnych obserwatora

    glLoadIdentity();
    // Określenie przestrzeni ograniczającej

    aspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
    // Wyznaczenie współczynnika proporcji okna

    // Gdy okno na ekranie nie jest kwadratem wymagane jest
    // określenie okna obserwatora.
    // Pozwala to zachować właściwe proporcje rysowanego obiektu
    // Do określenia okna obserwatora służy funkcja glOrtho(...)

    if (horizontal <= vertical)
        glOrtho(-100.0, 100.0, -100.0 / aspectRatio, 100.0 / aspectRatio, 1.0, -1.0);
    else
        glOrtho(-100.0 * aspectRatio, 100.0 * aspectRatio, -100.0, 100.0, 1.0, -1.0);

    glMatrixMode(GL_MODELVIEW);
    // Określenie układu współrzędnych

    glLoadIdentity();
}

// Główny punkt wejścia programu. Program działa w trybie konsoli

int main(int argc, char *argv[])
{

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    // Ustawienie trybu wyświetlania
    // GLUT_SINGLE - pojedynczy bufor wyświetlania
    // GLUT_RGBA - model kolorów RGB

    glutInit(&argc, argv);

    glutCreateWindow("Pierwszy program w OpenGL");
    // Utworzenie okna i określenie treści napisu w nagłówku okna

    glutDisplayFunc(renderScene);
    // Określenie, że funkcja RenderScene będzie funkcją zwrotną (callback)
    // Biblioteka GLUT będzie wywoływała tą funkcję za każdym razem, gdy
    // trzeba będzie przerysować okno

    glutReshapeFunc(changeSize);
    // Dla aktualnego okna ustala funkcję zwrotną odpowiedzialną za
    // zmiany rozmiaru okna

    myInit();
    // Funkcja MyInit (zdefiniowana powyżej) wykonuje wszelkie
    // inicjalizacje konieczne przed przystąpieniem do renderowania

    glutMainLoop();
    // Funkcja uruchamia szkielet biblioteki GLUT
    return 0;
}