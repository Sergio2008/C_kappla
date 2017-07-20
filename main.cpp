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
#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

static int slices = 16;
static int stacks = 16;
static int compteur = 0;
static int kaplaAct = 0;
static int kaplaDer = 0;




typedef struct Kapla Kapla;
struct Kapla
{
    int x; // Abscisses
    int y; // Ordonnées
    int z; // Hauteur
    int t; // Taille
    float rotx;
    float roty;
    float rotz;

};


Kapla Liste[20];



/* GLUT callback Handlers */

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

static void display(void )
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    // const double a = t*90.0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,0,0);

    {
        for (compteur = 0 ; compteur < kaplaDer ; compteur++)
    {
        glPushMatrix();
        glTranslated(Liste[compteur].x,Liste[compteur].y,Liste[compteur].z);

        glRotatef(Liste[compteur].rotx,1,0,0);
        glRotatef(Liste[compteur].roty,0,1,0);
        glRotatef(Liste[compteur].rotz,0,0,1);
        glScalef(15,3,1);
        glutSolidCube(Liste[compteur].t);

        glPopMatrix();


    }

    }

    glutSwapBuffers();
}


static void initList( void )
{
    for (compteur = 0 ; compteur < 20 ; compteur++)
    {
    Liste[compteur].x = -1 ;
    Liste[compteur].y = 1  ;
    Liste[compteur].z = -4 ;
    Liste[compteur].t = 1  ;
    Liste[compteur].rotx = 1;
    Liste[compteur].roty = 1;
    Liste[compteur].rotz = 1;
    }
}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'd':
            Liste[kaplaAct-1].x ++ ;
            break;
        case 'q':
            Liste[kaplaAct-1].x -- ;
            break;
        case 'z':
            Liste[kaplaAct-1].y ++ ;
            break;
        case 's':
            Liste[kaplaAct-1].y -- ;
            break;
        case 'e':
            Liste[kaplaAct-1].z ++ ;
            break;
        case 'a':
            Liste[kaplaAct-1].z -- ;
            break;
        case '8':
            Liste[kaplaAct-1].rotx = Liste[kaplaAct-1].rotx + 0.5 ;
            break;
        case '2':
            Liste[kaplaAct-1].rotx = Liste[kaplaAct-1].rotx - 0.5 ;
            break;
        case '4':
            Liste[kaplaAct-1].roty = Liste[kaplaAct-1].roty + 0.5 ;
            break;
        case '6':
            Liste[kaplaAct-1].roty = Liste[kaplaAct-1].roty - 0.5 ;
            break;
        case '7':
            Liste[kaplaAct-1].rotz = Liste[kaplaAct-1].rotz + 0.5 ;
            break;
        case '9':
            Liste[kaplaAct-1].rotz = Liste[kaplaAct-1].rotz + 0.5 ;
            break;
        case '+':
            Liste[kaplaAct-1].t ++ ;
            break;
        case '-':
            Liste[kaplaAct-1].t -- ;
            break;
        case '*':
            slices++;
            stacks++;
            break;
         case '/':
            if (slices > 3 && stacks > 3)
            {
                slices--;
                stacks--;
            }
            break;
        case 'p':
            if (kaplaAct == kaplaDer)
            {
                 kaplaDer ++ ;
            }
             kaplaAct ++ ;
            break;

        case 'm':
            kaplaAct -- ;
            break;
    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}
/* Program entry point */

int main(int argc, char *argv[])
{
    initList();
    glutInit(&argc, argv);
    glutInitWindowSize(1024,800);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    kaplaAct = 1;
    kaplaDer = 1;

    glutMainLoop();

    return EXIT_SUCCESS;
}
