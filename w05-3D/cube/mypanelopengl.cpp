#include "mypanelopengl.h"
#include <cmath>
#include <iostream>

using std::cout;
using std::endl;

MyPanelOpenGL::MyPanelOpenGL(QWidget *parent) :
    QGLWidget(parent), angles(0.,0.,0.) {

    shaderProgram=NULL;
    vertexShader=NULL;
    fragmentShader=NULL;
    vboData = NULL;

    numVertices = 36; //(6 faces)(2 triangles/face)(3 vertices/triangle)
    points = new point4[numVertices];
    colors = new color4[numVertices];

    vertices = new point4[8];
    vertex_colors = new color4[8];
}

MyPanelOpenGL::~MyPanelOpenGL(){
    vboData->release();
    shaderProgram->release();
    destroyVBO();
    destroyShaders();
}

void MyPanelOpenGL::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    makeCube();
    createShaders();
    createVBO();

    shaderProgram->bind();
    vboData->bind();

    shaderProgram->enableAttributeArray("vPosition");
    shaderProgram->setAttributeBuffer("vPosition", GL_FLOAT, 0, 4, 0);

    shaderProgram->enableAttributeArray("vColor");
    shaderProgram->setAttributeBuffer("vColor", GL_FLOAT, numVertices*sizeof(point4),4,0);

    glEnable(GL_DEPTH_TEST);
}

void MyPanelOpenGL::resizeGL(int w, int h)
{
    glViewport(0,0,w, h);
}

void MyPanelOpenGL::paintGL(){
    /* clear both color and depth buffer */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    if(!vboData){
        return;
    }

    shaderProgram->setUniformValue("theta", angles);
    glDrawArrays(GL_TRIANGLES, 0, numVertices);

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

void MyPanelOpenGL::makeCube(){

    /* setup 8 corners of cube */
    vertices[0] = point4( -0.5, -0.5,  0.5, 1.0 );
    vertices[1] = point4( -0.5,  0.5,  0.5, 1.0 );
    vertices[2] = point4(  0.5,  0.5,  0.5, 1.0 );
    vertices[3] = point4(  0.5, -0.5,  0.5, 1.0 );
    vertices[4] = point4( -0.5, -0.5, -0.5, 1.0 );
    vertices[5] = point4( -0.5,  0.5, -0.5, 1.0 );
    vertices[6] = point4(  0.5,  0.5, -0.5, 1.0 );
    vertices[7] = point4(  0.5, -0.5, -0.5, 1.0 );

    /* assign one color to each corner */
    vertex_colors[0] = color4( 0.0, 0.0, 0.0, 1.0 );  // black
    vertex_colors[1] = color4( 1.0, 0.0, 0.0, 1.0 );  // red
    vertex_colors[2] = color4( 1.0, 1.0, 0.0, 1.0 );  // yellow
    vertex_colors[3] = color4( 0.0, 1.0, 0.0, 1.0 );  // green
    vertex_colors[4] = color4( 0.0, 0.0, 1.0, 1.0 );  // blue
    vertex_colors[5] = color4( 1.0, 0.0, 1.0, 1.0 );  // magenta
    vertex_colors[6] = color4( 1.0, 1.0, 1.0, 1.0 );  // white
    vertex_colors[7] = color4( 0.0, 1.0, 1.0, 1.0 );  // cyan

    /* construct faces of cube */
    quad( 1, 0, 3, 2 );
    quad( 2, 3, 7, 6 );
    quad( 3, 0, 4, 7 );
    quad( 6, 5, 1, 2 );
    quad( 4, 5, 6, 7 );
    quad( 5, 4, 0, 1 );

    delete [] vertices; vertices=NULL;
    delete [] vertex_colors; vertex_colors=NULL;
}

void MyPanelOpenGL::quad(int a, int b, int c, int d){
    /* static variable initialized once. same var (though different value)
     * used on all function calls. a 'mini global' variable */
    static int Index = 0;

    /* first triangle */
    colors[Index] = vertex_colors[a]; points[Index] = vertices[a]; Index++;
    colors[Index] = vertex_colors[b]; points[Index] = vertices[b]; Index++;
    colors[Index] = vertex_colors[c]; points[Index] = vertices[c]; Index++;
    /* second triangle */
    colors[Index] = vertex_colors[a]; points[Index] = vertices[a]; Index++;
    colors[Index] = vertex_colors[c]; points[Index] = vertices[c]; Index++;
    colors[Index] = vertex_colors[d]; points[Index] = vertices[d]; Index++;
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
    if (amt > 360.){
        return amt - 360.;
    }
    if (amt < 0.){
        return amt + 360.;
    }
    return amt;
}



void MyPanelOpenGL::createVBO(){
    destroyVBO(); //get rid of any old buffers

    vboData = new QGLBuffer(QGLBuffer::VertexBuffer);
    vboData->create();
    vboData->bind();
    vboData->setUsagePattern(QGLBuffer::StaticDraw);

    vboData->allocate(numVertices*(sizeof(point4)+sizeof(color4)));
    vboData->write(0,points,numVertices*sizeof(point4));
    vboData->write(numVertices*sizeof(point4),colors,numVertices*sizeof(color4));

    delete [] points; points=NULL;
    delete [] colors; colors=NULL;
}

void MyPanelOpenGL::destroyVBO(){
    if (vboData){
        vboData->release();
        delete vboData; vboData=NULL;
    }
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

