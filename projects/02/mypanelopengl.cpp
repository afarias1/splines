#include "mypanelopengl.h"
#include "triangle.h"
#include <cmath>
#include <iostream>

using namespace std;
using cs40::Drawable;
using cs40::Triangle;

typedef QVector2D vec2;
typedef QVector3D vec3;

MyPanelOpenGL::MyPanelOpenGL(QWidget *parent) :
    QGLWidget(parent){

    shaderProgram=NULL;
    vertexShader=NULL;
    fragmentShader=NULL;
    tri = NULL;

    vboVertices = NULL;

    numVertices = 3;
    vertices = new QVector2D[3];
    vertices[0] = QVector2D(-1.0, -1.0);
    vertices[1] = QVector2D(0.0, 1.0);
    vertices[2] = QVector2D(1.0, -1.0);
}

/* handy helper for debugging using cout and QVector2D 
 * allows
 *   cout << myvec;
 * for QVector2D myvec object.
 */
ostream& operator<<(ostream& str, const QVector2D& vec){
    str << (float) vec.x() << ", " << (float) vec.y();
    return str;
}

MyPanelOpenGL::~MyPanelOpenGL(){
    destroyShaders();
    destroyVBOs();
    delete tri;
}

void MyPanelOpenGL::initializeGL()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    createShaders();
    createVBOs();
    shaderProgram->bind();

    tri = new Triangle(vec2(-1.,-1.), vec2(0,1.), vec2(1,-1.));
    tri->setColor(vec3(1.,0,0));
}

void MyPanelOpenGL::resizeGL(int w, int h)
{
    glViewport(0,0,w, h);
}

void MyPanelOpenGL::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if(!vboVertices || !shaderProgram){
        return;
    }

    vboVertices->bind();
    shaderProgram->setUniformValue("color", QVector4D(1.,0,0.,1.));
    shaderProgram->enableAttributeArray("vPosition");
    shaderProgram->setAttributeBuffer("vPosition", GL_FLOAT, 0, 2, 0);

    glDrawArrays(GL_TRIANGLES, 0, numVertices);

    glFlush();

    vboVertices->release();
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

void MyPanelOpenGL::createVBOs(){
    destroyVBOs(); //get rid of any old buffers

    vboVertices = new QGLBuffer(QGLBuffer::VertexBuffer);
    vboVertices->create();
    vboVertices->bind();
    vboVertices->setUsagePattern(QGLBuffer::StaticDraw);
    vboVertices->allocate(vertices, numVertices*sizeof(QVector4D));

    delete [] vertices; vertices=NULL;
}

void MyPanelOpenGL::destroyVBOs(){
    if (vboVertices){
        vboVertices->release();
        delete vboVertices; vboVertices=NULL;
    }
}
