#include "mypanelopengl.h"
#include <cmath>

MyPanelOpenGL::MyPanelOpenGL(QWidget *parent) :
    QGLWidget(parent) {

    shaderProgram=NULL;
    vertexShader=NULL;
    fragmentShader=NULL;
    vboVertices = NULL;

    numVertices = 3;
    vertices = new QVector4D[3];
    vertices[0] = QVector4D(-1.0, -1.0, 0., 1.);
    vertices[1] = QVector4D(0.0, 1.0, 0., 1.);
    vertices[2] = QVector4D(1.0, -1.0, 0., 1.);


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


    glClear(GL_COLOR_BUFFER_BIT);

    if(!vboVertices){
        return;
    }

    shaderProgram->bind();
    vboVertices->bind();

    shaderProgram->enableAttributeArray("vPosition");
    shaderProgram->setAttributeBuffer("vPosition", GL_FLOAT, 0, 4, 0);

    glDrawArrays(GL_TRIANGLES, 0, numVertices);

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

    shaderProgram = new QGLShaderProgram();
    shaderProgram->addShader(vertexShader);
    shaderProgram->addShader(fragmentShader);

    if(!shaderProgram->link()){
        qWarning() << shaderProgram->log() << endl;
    }

    //QMessageBox::information((QWidget*)parent(), "debug", "iShade");

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
    vboVertices->allocate(vertices, numVertices*sizeof(QVector4D));

    delete [] vertices; vertices=NULL;
    //QMessageBox::information((QWidget*)parent(), "debug", "iVBO");
}

void MyPanelOpenGL::destroyVBOs(){
    if (vboVertices){
        vboVertices->release();
        delete vboVertices; vboVertices=NULL;
    }
}
