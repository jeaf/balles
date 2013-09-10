#include "ckit.h"

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

array_obj a;

void gameloop_init()
{
    // Create the obj array that will contain all balls
    array_obj_ctor(&a);
    obj o;
    o.radius = 3.0;
    o.location[0] = 4.0;
    o.location[1] = 0.0;
    o.location[2] = 0.0;
    o.velocity[0] = 0.0;
    o.velocity[1] = 0.0;
    o.velocity[2] = 0.0;
    //*array_obj_pushback(&a) = o;
    o.radius = 1.0;
    o.location[0] = 0.0;
    o.location[1] = 6.0;
    o.location[2] = 0.0;
    o.velocity[0] = 0.0;
    o.velocity[1] = 0.0;
    o.velocity[2] = 0.5;
    *array_obj_pushback(&a) = o;

    // Init OpenGL stuff
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(110.0, 1.0, 0.5, 2000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void gameloop_update()
{
    for (int i = 0; i < a.size; ++i)
    {
        a.data[i].location[0] += 0.01 * a.data[i].velocity[0];
        a.data[i].location[1] += 0.01 * a.data[i].velocity[1];
        a.data[i].location[2] += 0.01 * a.data[i].velocity[2];
        a.data[i].velocity[1] += 0.01 * -9.8;

        if (a.data[i].location[1] < 0)
        {
            a.data[i].velocity[1] = -0.90 * a.data[i].velocity[1];
        }
    }
}

void gameloop_draw()
{
    //  Enable Z-buffer depth test
    glEnable(GL_DEPTH_TEST);

    glPushMatrix();

    // Rotate when user changes rotate_x and rotate_y
    //glRotatef(0.5, 1.0, 0.0, 0.0);
    //glRotatef(0.5, 0.0, 1.0, 0.0);
    //glTranslated(0.5, 0.0, 0.0);
    //gluLookAt(0.0, 0.0, 1.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);
    gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glClearColor( 0.3f, 0.3f, 0.3f, 0.0f );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glBegin(GL_POLYGON);
    //glColor3f(1.0, 0.0, 0.0);
    //glVertex3f(1.0, -0.5, 1.0);
    //glVertex3f(-1.0, -0.5, 1.0);
    //glVertex3f(-1.0, -0.5, -1.0);
    //glVertex3f(1.0, -0.5, -1.0);
    //glEnd();

    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(10.0, 0.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 10.0, 0.0);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 10.0);
    glEnd();

    for (int i = 0; i < a.size; ++i)
    {
        GLUquadric* quad = gluNewQuadric();
        gluQuadricDrawStyle(quad, GLU_FILL);
        gluQuadricNormals(quad, GLU_SMOOTH);
        gluQuadricOrientation(quad, GLU_OUTSIDE);
        gluQuadricTexture(quad, GL_TRUE);
        glPushMatrix();
        glTranslatef(a.data[i].location[0],
                     a.data[i].location[1],
                     a.data[i].location[2]);
        glColor3f(1.0, 0.4, 0.5);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        gluSphere(quad, a.data[i].radius, 25, 25);
        gluDeleteQuadric(quad);
        glPopMatrix();
    }

    glPopMatrix();

    glFlush();
}

