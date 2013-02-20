#include "mypanelopengl.h"
#include <cmath>
#include <iostream>

using std::cout;
using std::endl;
using cs40::Sphere;

MyPanelOpenGL::MyPanelOpenGL(QWidget *parent) :
    QGLWidget(parent), angles(0.,0.,0.) {

    shaderProgram=NULL;
    vertexShader=NULL;
    fragmentShader=NULL;

    m_sphere = NULL;
}

MyPanelOpenGL::~MyPanelOpenGL(){
    shaderProgram->release();
    destroyShaders();
}

void MyPanelOpenGL::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    createShaders();

    m_sphere = new Sphere(0.5,30,30);

    shaderProgram->bind();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void MyPanelOpenGL::resizeGL(int w, int h)
{
    glViewport(0,0,w, h);
}

void MyPanelOpenGL::paintGL(){
    /* clear both color and depth buffer */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(!shaderProgram){return;}

    shaderProgram->setUniformValue("theta",angles);

    m_sphere->draw(shaderProgram);

    glFlush();

    //swapBuffers(); /* not need in QT see QGLWidget::setAutoBufferSwap */
}


void MyPanelOpenGL::keyPressEvent(QKeyEvent *event)
{
    qreal step=1;
    /*Enable strong Focus on GL Widget to process key events*/
    switch(event->key()){
    case Qt::Key_X:
        if (event->text()=="x"){updateAngles(0,step);}
        else{updateAngles(0,-step);}
        break;
    case Qt::Key_Y:
        if (event->text()=="y"){ updateAngles(1,step);}
        else{ updateAngles(1,-step);}
        break;
    case Qt::Key_Z:
        if (event->text()=="z"){updateAngles(2,step);}
        else{updateAngles(2,-step);}
        break;
    default:
        QWidget::keyPressEvent(event); /* pass to base class */
    }
    updateGL();
}

void MyPanelOpenGL::updateAngles(int idx, qreal amt){
    if(idx == 0){
        angles.setX(angles.x()+amt);
    }else if(idx == 1){
        angles.setY(angles.y()+amt);
    }else if(idx == 2){
        angles.setZ(angles.z()+amt);
    }
}


qreal MyPanelOpenGL::wrap(qreal amt){
    if (amt > 360.){ return amt - 360.; }
    else if (amt < 0.){ return amt + 360.; }
    return amt;
}

void MyPanelOpenGL::createShaders(){

    destroyShaders(); //get rid of any old shaders

    vertexShader = new QGLShader(QGLShader::Vertex);
    if (!vertexShader->compileSourceFile("vshader.glsl")){
        qWarning() << vertexShader->log();
    }

    fragmentShader = new QGLShader(QGLShader::Fragment);
    if(!fragmentShader->compileSourceFile("fshader.glsl")){
        qWarning() << fragmentShader->log();
    }

    shaderProgram = new QGLShaderProgram();
    shaderProgram->addShader(vertexShader);
    shaderProgram->addShader(fragmentShader);

    if(!shaderProgram->link()){
        qWarning() << shaderProgram->log() << endl;
    }
}

void MyPanelOpenGL::destroyShaders(){

    delete vertexShader; vertexShader=NULL;
    delete fragmentShader; fragmentShader=NULL;

    if(shaderProgram){
        shaderProgram->release();
        delete shaderProgram; shaderProgram=NULL;
    }
}

