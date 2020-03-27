
#include <GL/gl.h>
#include <GL/glut.h>
#include <cmath>
#include <iostream>

typedef float point3[3];
static GLfloat theta[] = {0.0, 0.0, 0.0}; // trzy kąty obrotu

static GLfloat r = 15; 

static GLfloat viewer[]= {0.0, 0.0, 3.0};
static GLfloat angle[]= {0.0, 1.0, 0.0};

int model = 3; //1- punkty, 2- siatka, 3 - wypełnione trójkąty


GLfloat light_position[] = {0, 0, 15.0, 1.0};
GLfloat light_position2[] = {0, 0, -15.0, 1.0};  

GLfloat light_ambient[] = {0.0, 0.1, 0.0, 1.0};
    // składowe intensywności świecenia źródła światła otoczenia
    // Ia = [Iar,Iag,Iab]

    GLfloat light_diffuse[] = {0.0, 0.6, 0.0, 1.0};       
    // składowe intensywności świecenia źródła światła powodującego
    // odbicie dyfuzyjne Id = [Idr,Idg,Idb]

    GLfloat light_specular[]= {0.0, 0.9, 0.0, 1.0};
    // składowe intensywności świecenia źródła światła powodującego
    // odbicie kierunkowe Is = [Isr,Isg,Isb]



struct Point{
	float x;
	float y;
	float z;
};

int getRand(int a, int b){
	return a + rand()%(b-a);
}

// Funkcja rysująca osie układu współrzędnych
void Axes(void)
{

point3  x_min = {-5.0, 0.0, 0.0};
point3  x_max = { 5.0, 0.0, 0.0};
// początek i koniec obrazu osi x

point3  y_min = {0.0, -5.0, 0.0};
point3  y_max = {0.0,  5.0, 0.0};
// początek i koniec obrazu osi y

point3  z_min = {0.0, 0.0, -5.0};
point3  z_max = {0.0, 0.0,  5.0};
//  początek i koniec obrazu osi y
glColor3f(1.0f, 0.0f, 0.0f);  // kolor rysowania osi - czerwony
glBegin(GL_LINES); // rysowanie osi x
glVertex3fv(x_min);
glVertex3fv(x_max);
glEnd();

glColor3f(0.0f, 1.0f, 0.0f);  // kolor rysowania - zielony
glBegin(GL_LINES);  // rysowanie osi y

glVertex3fv(y_min);
glVertex3fv(y_max);                           
glEnd();

glColor3f(0.0f, 0.0f, 1.0f);  // kolor rysowania - niebieski
glBegin(GL_LINES); // rysowanie osi z

glVertex3fv(z_min);
glVertex3fv(z_max);
glEnd();

}

float fx(float u, float v){

	return (float)(-90*u*u*u*u*u + 225*u*u*u*u - 270*u*u*u + 180*u*u -45*u)*cos(M_PI*v);
}

float fy(float u, float v){
	return (float)(160*u*u*u*u - 320*u*u*u + 160*u*u - 5);
}

float fz(float u, float v){
	return (float)(-90*u*u*u*u*u + 225*u*u*u*u - 270*u*u*u + 180*u*u - 45*u)*sin(M_PI*v);
}

void Egg(int n){
	Point** table = new Point*[n];
	for(int i = 0; i < n; ++i)
    		table[i] = new Point[n];	
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			float x = fx( (float)i/(n-1), (float)j/(n-1) );
			float y = fy( (float)i/(n-1), (float)j/(n-1) );	
			float z = fz( (float)i/(n-1), (float)j/(n-1) );
			table[i][j].x = x;
			table[i][j].y = y;
			table[i][j].z = z;
		}
	}
if(model == 1){
	
	glBegin(GL_POINTS);
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			glVertex3f( table[i][j].x, table[i][j].y, table[i][j].z );
		}
	}
	glEnd();
}
else if(model == 2){
	glBegin(GL_LINES);
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n-1; ++j){
			glVertex3f(table[i][j].x, table[i][j].y, table[i][j].z);
			glVertex3f(table[i][j+1].x, table[i][j+1].y, table[i][j+1].z);
		}
	}
	glEnd();

	glBegin(GL_LINES);
	for(int i = 0; i < n-1; ++i){
		for(int j = 0; j < n; ++j){
			glVertex3f(table[i][j].x, table[i][j].y, table[i][j].z);
			glVertex3f(table[i+1][j].x, table[i+1][j].y, table[i+1][j].z);
		}
	}
	glEnd();

	glBegin(GL_LINES);
	for(int i = 0; i < n-1; ++i){
		for(int j = 0; j < n-1; ++j){
			glVertex3f(table[i][j].x, table[i][j].y, table[i][j].z);
			glVertex3f(table[i+1][j+1].x, table[i+1][j+1].y, table[i+1][j+1].z);
		}
	}
	glEnd();
}

else if(model == 3){

	glBegin(GL_TRIANGLES);
	for(int i = 0; i < n-1; ++i){
		for(int j = 0; j < n-1; ++j){
			glColor3ub( (i + j)%256 , (i * j)%256, (i + j)%256 );
			glVertex3f(table[i][j].x, table[i][j].y, table[i][j].z);

			glColor3ub( (i + j)%256 , (i * j)%256, (i + j)%256 );
			glVertex3f(table[i][j+1].x, table[i][j+1].y, table[i][j+1].z);
			
			glColor3ub( (i + j)%256 , (i * j)%256, (i + j)%256 );
			glVertex3f(table[i+1][j+1].x, table[i+1][j+1].y, table[i+1][j+1].z);
		}
	}
	glEnd();

	glBegin(GL_TRIANGLES);
	for(int i = 0; i < n-1; ++i){
		for(int j = 0; j < n-1; ++j){
			
			

			//glColor3ub( (i + j)%256 , (i + j)%256, (i + j)%256 );
			glColor3ub( (i + j)%256 , (i * j)%256, (i + j)%256 );
			glVertex3f(table[i+1][j].x, table[i+1][j].y, table[i+1][j].z);

			//glColor3ub( (i + j)%256, (i + j)%256, (i + j)%256 );
			glColor3ub( 200, 200, 50); 
			glVertex3f(table[i][j].x, table[i][j].y, table[i][j].z);

			//glColor3ub( (i + j)%256 , (i + j)%256, (i + j)%256 );
			glColor3ub( 200, 200, 50); 
			glVertex3f(table[i+1][j+1].x, table[i+1][j+1].y, table[i+1][j+1].z);
		}
	}
	glEnd();
}
return;
}

void RenderScene()
{

 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// Czyszczenie okna aktualnym kolorem czyszczącym

glLoadIdentity();
// Czyszczenie macierzy bieżącej
gluLookAt(viewer[0],viewer[1],viewer[2], 0.0, 0.0, 0.0, angle[0], angle[1], angle[2]);

Axes();
// Narysowanie osi przy pomocy funkcji zdefiniowanej wyżej

glColor3ub( 200, 200, 50); // Ustawienie koloru rysowania na biały

int n = 30;
glRotated(30.0, 1.0, 1.0, 1.0 );  // Obrót


glRotatef(theta[0], 1.0, 0.0, 0.0);

glRotatef(theta[1], 0.0, 1.0, 0.0);

glRotatef(theta[2], 0.0, 0.0, 1.0);
Egg(n); // Narysowanie jajka
//glutSolidTeapot(3.0);
glFlush();
// Przekazanie poleceń rysujących do wykonania
 

glutSwapBuffers();

 }

// Funkcja ustalająca stan renderowania

 

void MyInit(void)
{

glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
// Kolor czyszcący (wypełnienia okna) ustawiono na czarny







/*************************************************************************************/

//  Definicja materiału z jakiego zrobiony jest czajnik
//  i definicja źródła światła

/*************************************************************************************/


/*************************************************************************************/ 
// Definicja materiału z jakiego zrobiony jest czajnik

    GLfloat mat_ambient[]  = {1.0, 1.0, 1.0, 1.0};       
    // współczynniki ka =[kar,kag,kab] dla światła otoczenia

    GLfloat mat_diffuse[]  = {1.0, 1.0, 1.0, 1.0};
    // współczynniki kd =[kdr,kdg,kdb] światła rozproszonego

    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    // współczynniki ks =[ksr,ksg,ksb] dla światła odbitego               
   
    GLfloat mat_shininess  = {20.0};
    // współczynnik n opisujący połysk powierzchni


/*************************************************************************************/
// Definicja pierwszego źródła światła


    

    GLfloat light_ambient[] = {0.0, 0.1, 0.0, 1.0};
    // składowe intensywności świecenia źródła światła otoczenia
    // Ia = [Iar,Iag,Iab]

    GLfloat light_diffuse[] = {0.0, 0.6, 0.0, 1.0};       
    // składowe intensywności świecenia źródła światła powodującego
    // odbicie dyfuzyjne Id = [Idr,Idg,Idb]

    GLfloat light_specular[]= {0.0, 0.9, 0.0, 1.0};
    // składowe intensywności świecenia źródła światła powodującego
    // odbicie kierunkowe Is = [Isr,Isg,Isb]

    GLfloat att_constant  = {1.0};
    // składowa stała ds dla modelu zmian oświetlenia w funkcji
    // odległości od źródła

    GLfloat att_linear    = {0.05};
    // składowa liniowa dl dla modelu zmian oświetlenia w funkcji
    // odległości od źródła

    GLfloat att_quadratic  = {0.001};
    // składowa kwadratowa dq dla modelu zmian oświetlenia w funkcji
    // odległości od źródła

/*************************************************************************************/                                      
// Ustawienie parametrów materiału i źródła światła

/*************************************************************************************/
// Ustawienie patrametrów materiału


    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);


/*************************************************************************************/
// Ustawienie parametrów pierwszego źródła

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, att_constant);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, att_linear);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, att_quadratic);



// Definicja drugiego źródła światła
    // położenie źródła

    GLfloat light_ambient2[] = {0.1, 0.0, 0.0, 1.0};
    // składowe intensywności świecenia źródła światła otoczenia
    // Ia = [Iar,Iag,Iab]

    GLfloat light_diffuse2[] = {0.6, 0.0, 0.0, 1.0};       
    // składowe intensywności świecenia źródła światła powodującego
    // odbicie dyfuzyjne Id = [Idr,Idg,Idb]

    GLfloat light_specular2[]= {0.9, 0.0, 0.0, 1.0};
    // składowe intensywności świecenia źródła światła powodującego
    // odbicie kierunkowe Is = [Isr,Isg,Isb]

    GLfloat att_constant2  = {1.0};
    // składowa stała ds dla modelu zmian oświetlenia w funkcji
    // odległości od źródła

    GLfloat att_linear2    = {0.05};
    // składowa liniowa dl dla modelu zmian oświetlenia w funkcji
    // odległości od źródła

    GLfloat att_quadratic2  = {0.001};
    // składowa kwadratowa dq dla modelu zmian oświetlenia w funkcji
    // odległości od źródła

/*************************************************************************************/                                      
// Ustawienie parametrów materiału i drugiego źródła światła

glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient2);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse2);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular2);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position2);

    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, att_constant2);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, att_linear2);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, att_quadratic2);

/*************************************************************************************/
// Ustawienie patrametrów materiału


    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);







/*************************************************************************************/
// Ustawienie opcji systemu oświetlania sceny

    glShadeModel(GL_SMOOTH); // właczenie łagodnego cieniowania
    glEnable(GL_LIGHTING);   // właczenie systemu oświetlenia sceny
    glEnable(GL_LIGHT0);     // włączenie źródła o numerze 0
    glEnable(GL_LIGHT1);     // włączenie źródła o numerze 1

    glEnable(GL_DEPTH_TEST); // włączenie mechanizmu z-bufora

/*************************************************************************************/

}

// Funkcja ma za zadanie utrzymanie stałych proporcji rysowanych
// w przypadku zmiany rozmiarów okna.
// Parametry vertical i horizontal (wysokość i szerokość okna) są
// przekazywane do funkcji za każdym razem gdy zmieni się rozmiar okna.

 

void ChangeSize(GLsizei horizontal, GLsizei vertical )
{

GLfloat AspectRatio;
// Deklaracja zmiennej AspectRatio  określającej proporcję
// wymiarów okna 
if(vertical == 0)  // Zabezpieczenie przed dzieleniem przez 0
vertical = 1;  
glViewport(0, 0, horizontal, vertical);
// Ustawienie wielkościokna okna widoku (viewport)
// W tym przypadku od (0,0) do (horizontal, vertical)  
glMatrixMode(GL_PROJECTION);
// Przełączenie macierzy bieżącej na macierz projekcji 
glLoadIdentity();
// Czyszcznie macierzy bieżącej            
AspectRatio = (GLfloat)horizontal/(GLfloat)vertical;
// Wyznaczenie współczynnika  proporcji okna
// Gdy okno nie jest kwadratem wymagane jest określenie tak zwanej
// przestrzeni ograniczającej pozwalającej zachować właściwe
// proporcje rysowanego obiektu.
// Do okreslenia przestrzeni ograniczjącej służy funkcja
// glOrtho(...)            
if(horizontal <= vertical)

glOrtho(-7.5,7.5,-7.5/AspectRatio,7.5/AspectRatio,10.0, -10.0); 
else

glOrtho(-7.5*AspectRatio,7.5*AspectRatio,-7.5,7.5,10.0,-10.0);                     
glMatrixMode(GL_MODELVIEW);
// Przełączenie macierzy bieżącej na macierz widoku modelu                                   

glLoadIdentity();
// Czyszcenie macierzy bieżącej
}

void keys(unsigned char key, int x, int y)
{

    if(key == '1') {
        viewer[0] = 1; viewer[1] = 7; viewer[2] = 3;
        angle[0] = 0; angle[1] = 1.0; angle[2] = 0;
    }
    if(key == '2'){
        viewer[0] = 1; viewer[1] = -7; viewer[2] = -3;
        angle[0] = 0; angle[1] = 1.0; angle[2] = 0;
    }
    if(key == '3'){
        viewer[0] = 1; viewer[1] = 4; viewer[2] = -3;
        angle[0] = 0; angle[1] = 1.0; angle[2] = 0;
    }
    if(key == '0') {
        viewer[0] = 0; viewer[1] = 1; viewer[2] = 3;
        angle[0] = 0; angle[1] = 1.0; angle[2] = 0;
    }

    if(key == '4') light_ambient[1] += 0.05;
    if(key == '5') light_diffuse[1] += 0.05;
    if(key == '6') light_ambient[1] += 0.1;
    if(key == '7') light_ambient[1] -= 0.05;
    if(key == '8') light_diffuse[1] -= 0.05;
    if(key == '9') light_ambient[1] -= 0.1;
    if(key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9'){
        glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    }


    

    if(key == 'w') light_position[0] += 1.0;
    if(key == 's') light_position[0] -= 1.0;
    if(key == 'w' || key == 's') glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    if(key == 'd') light_position2[0] += 1.0;   
    if(key == 'a') light_position2[0] -= 1.0;
    if(key == 'a' || key == 'd') glLightfv(GL_LIGHT1, GL_POSITION, light_position2);

    RenderScene(); // przerysowanie obrazu sceny
}

void spinEgg()
{
    theta[0] -= 0.5;
    if( theta[0] > 360.0 ) theta[0] -= 360.0;

    theta[1] -= 0.5;
    if( theta[1] > 360.0 ) theta[1] -= 360.0;

    theta[2] -= 0.5;
    if( theta[2] > 360.0 ) theta[2] -= 360.0;

    glutPostRedisplay(); //odświeżenie zawartości aktualnego okna
}

// Główny punkt wejścia programu. Program działa w trybie konsoli
int main(int argc, char *argv[])
{          
srand (time(NULL));
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB |GLUT_DEPTH);

glutInitWindowSize(300, 300);

glutInit(&argc, argv);

glutCreateWindow("Jajko w 3D");
         
//glutIdleFunc(spinEgg); //kręcenie jajkiem

glutDisplayFunc(RenderScene);
// Określenie, że funkcja RenderScene będzie funkcją zwrotną
// (callback function).  Bedzie ona wywoływana za każdym razem
// gdy zajdzie potrzba przeryswania okna 
glutReshapeFunc(ChangeSize);
// Dla aktualnego okna ustala funkcję zwrotną odpowiedzialną
// zazmiany rozmiaru okna      
MyInit();
// Funkcja MyInit() (zdefiniowana powyżej) wykonuje wszelkie
// inicjalizacje konieczne  przed przystąpieniem do renderowania
glEnable(GL_DEPTH_TEST);
// Włączenie mechanizmu usuwania powierzchni niewidocznych
glutKeyboardFunc(keys);
glutMainLoop();
// Funkcja uruchamia szkielet biblioteki GLUT
return 0;
}