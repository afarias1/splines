#include "mypanelopengl.h"
#include <cmath>
#include <GL/glu.h>

MyPanelOpenGL::MyPanelOpenGL(QWidget *parent) :
    QGLWidget(parent) {

    shaderProgram=NULL;
    vertexShader=NULL;
    fragmentShader=NULL;

    numVertices = 3;
    vertices = new QVector2D[3];
    vertices[0] = QVector2D(-1.0, -1.0);
    vertices[1] = QVector2D(0.0, 1.0);
    vertices[2] = QVector2D(1.0, -1.0);


}

MyPanelOpenGL::~MyPanelOpenGL(){
    destroyVBOs();
    destroyShaders();
}

void MyPanelOpenGL::initializeGL()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    createShaders();
    createVBOs();
}

void MyPanelOpenGL::resizeGL(int w, int h)
{
    glViewport(0,0,w, h);
}

void MyPanelOpenGL::paintGL(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(!vboVertices){
        return;
    }

    shaderProgram->bind();
    vboVertices->bind();

    shaderProgram->enableAttributeArray("vPosition");
    shaderProgram->setAttributeBuffer("vPosition", GL_FLOAT, 0, 2, 0);

    glDrawElements(GL_TRIANGLES, 1, GL_UNSIGNED_INT, 0);

    glFlush();

    vboVertices->release();
    shaderProgram->release();
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

    shaderProgram = new QGLShaderProgram;
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

void MyPanelOpenGL::createVBOs(){
    destroyVBOs(); //get rid of any old buffers

    vboVertices = new QGLBuffer(QGLBuffer::VertexBuffer);
    vboVertices->create();
    vboVertices->bind();
    vboVertices->setUsagePattern(QGLBuffer::StaticDraw);
    vboVertices->allocate(vertices, numVertices*sizeof(QVector2D));

    delete [] vertices; vertices=NULL;
}

void MyPanelOpenGL::destroyVBOs(){
    if (vboVertices){
        vboVertices->release();
        delete vboVertices; vboVertices=NULL;
    }
}
