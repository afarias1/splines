#include "mypanelopengl.h"
#include <cmath>
#include <iostream>

using std::cout;
using std::endl;
using cs40::Sphere;
using cs40::Square;

MyPanelOpenGL::MyPanelOpenGL(QWidget *parent) :
    QGLWidget(parent), m_angles(-65.,0.,0.) {

    m_shaderProgram=NULL;
    m_vertexShader=NULL;
    m_fragmentShader=NULL;

    m_sphere = NULL;
}

MyPanelOpenGL::~MyPanelOpenGL(){
    m_shaderProgram->release();
    destroyShaders();
}

void MyPanelOpenGL::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    createShaders();

    m_sphere = new Sphere(0.5,30,30);
    m_square = new Square(1.);
    m_textureID = bindTexture(QPixmap("earth.png"), GL_TEXTURE_2D);;
    glBindTexture(GL_TEXTURE_2D, m_textureID);

    m_shaderProgram->bind();


}

void MyPanelOpenGL::resizeGL(int w, int h)
{
    glViewport(0,0,w, h);
}

void MyPanelOpenGL::paintGL(){
    /* clear both color and depth buffer */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(!m_shaderProgram){return;}

    m_shaderProgram->setUniformValue("theta",m_angles);
    m_shaderProgram->setUniformValue("Tex0",0);

    //m_sphere->draw(m_shaderProgram);
    m_square->draw(m_shaderProgram);
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
        m_angles.setX(m_angles.x()+amt);
    }else if(idx == 1){
        m_angles.setY(m_angles.y()+amt);
    }else if(idx == 2){
        m_angles.setZ(m_angles.z()+amt);
    }
}


qreal MyPanelOpenGL::wrap(qreal amt){
    if (amt > 360.){ return amt - 360.; }
    else if (amt < 0.){ return amt + 360.; }
    return amt;
}

void MyPanelOpenGL::createShaders(){

    destroyShaders(); //get rid of any old shaders

    m_vertexShader = new QGLShader(QGLShader::Vertex);
    if (!m_vertexShader->compileSourceFile("vshader.glsl")){
        qWarning() << m_vertexShader->log();
    }

    m_fragmentShader = new QGLShader(QGLShader::Fragment);
    if(!m_fragmentShader->compileSourceFile("fshader.glsl")){
        qWarning() << m_fragmentShader->log();
    }

    m_shaderProgram = new QGLShaderProgram();
    m_shaderProgram->addShader(m_vertexShader);
    m_shaderProgram->addShader(m_fragmentShader);

    if(!m_shaderProgram->link()){
        qWarning() << m_shaderProgram->log() << endl;
    }
}

void MyPanelOpenGL::destroyShaders(){

    delete m_vertexShader; m_vertexShader=NULL;
    delete m_fragmentShader; m_fragmentShader=NULL;

    if(m_shaderProgram){
        m_shaderProgram->release();
        delete m_shaderProgram; m_shaderProgram=NULL;
    }
}

