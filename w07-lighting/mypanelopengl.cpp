#include "mypanelopengl.h"
#include <cmath>
#include <iostream>

using std::cout;
using std::endl;
using cs40::Sphere;
using cs40::Square;

MyPanelOpenGL::MyPanelOpenGL(QWidget *parent) :
    QGLWidget(parent), m_angles(-125.,0.,0.) {

    m_shaderProgram=NULL;
    m_vertexShader=NULL;
    m_fragmentShader=NULL;

    m_sphere = NULL;
    m_square = NULL;
    m_drawSphere = true;
    m_polymode = 2;
}

MyPanelOpenGL::~MyPanelOpenGL(){
    m_shaderProgram->release();
    delete m_sphere; m_sphere=NULL;
    delete m_square; m_square=NULL;
    destroyShaders();
}

void MyPanelOpenGL::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    updatePolyMode(m_polymode);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    createShaders();

    m_sphere = new Sphere(0.5,30,30);
    m_square = new Square(1.);

    m_projection.perspective(40,1,1,8);
    m_camera.lookAt(vec3(0,0,3),vec3(0,0,0),vec3(0,1.,0.));
    m_model.setToIdentity();
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

    mat4 mview = m_camera*m_model;
    m_shaderProgram->setUniformValue("projection",m_projection);
    m_shaderProgram->setUniformValue("camera",m_camera);
    m_shaderProgram->setUniformValue("model", m_model);
    m_shaderProgram->setUniformValue("modelView",mview);
    m_shaderProgram->setUniformValue("normalMatrix",mview.normalMatrix());
    m_shaderProgram->setUniformValue("lightPos",vec4(0.8,0,2,1.)); //in world coordinates

    if(m_drawSphere){
      m_sphere->draw(m_shaderProgram);
      //m_square->draw(m_shaderProgram);
    }
    else{
      m_square->draw(m_shaderProgram);
    }
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
    case Qt::Key_C:
        if(glIsEnabled(GL_CULL_FACE)){glDisable(GL_CULL_FACE);}
        else{glEnable(GL_CULL_FACE);}
        break;
    case Qt::Key_P:
        m_polymode = (m_polymode+1)%3;
        updatePolyMode(m_polymode);
        break;
    case Qt::Key_S:
        m_drawSphere = !m_drawSphere;
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

void MyPanelOpenGL::updatePolyMode(int val){
    GLenum mode=GL_NONE;
    if(val==0){mode=GL_POINT;}
    else if(val==1){mode=GL_LINE;}
    else if(val==2){mode=GL_FILL;}

    if(mode != GL_NONE){
        glPolygonMode(GL_FRONT_AND_BACK, mode);
    }
    //glPolygonMode(GL_BACK,GL_POINT);
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

