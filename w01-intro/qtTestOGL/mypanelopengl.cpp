#include "mypanelopengl.h"
#include <cmath>
#include <GL/glu.h>

MyPanelOpenGL::MyPanelOpenGL(QWidget *parent) :
    QGLWidget(parent), sides(3), radius(1.0)
{
}

void MyPanelOpenGL::initializeGL()
{

    glShadeModel(GL_SMOOTH);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void MyPanelOpenGL::resizeGL(int w, int h)
{
    double xMin = 0, xMax=10, yMin = 0, yMax = 10;
    glViewport(0,0,(GLint)w, (GLint)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1,1,-1,1);
    if (w > h){
        h = h?h:1;
        double newWidth = (xMax-xMin)*w/h;
        double diffWidth = newWidth - (xMax-xMin);
        xMin = 0 + diffWidth/2.0;
        xMax = 10 + diffWidth/2.0;
    } else{
        w = w?w:1;
        double newHeight = (yMax-yMin)*w/h;
        double diffHeight = newHeight- (yMax-yMin);
        yMin = 0 + diffHeight/2.0;
        yMax = 10 + diffHeight/2.0;
    }
    gluOrtho2D(xMin, xMax, yMin, yMax);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

void MyPanelOpenGL::paintGL(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslated(5.f, 5.f, 0.0);
    glLineWidth(1);
    glColor3f(0,0.7f,0.7f);
    glBegin(GL_POLYGON);
    for(int i = 0; i<sides; i++){
        glVertex2f(radius*cos(i*2*M_PI/sides), radius*sin(i*2*M_PI/sides));
    }
    glEnd();
}

void MyPanelOpenGL::changeSides(int s){ sides = s; updateGL();}

void MyPanelOpenGL::changeRadius(double r){ radius = r; updateGL();}

