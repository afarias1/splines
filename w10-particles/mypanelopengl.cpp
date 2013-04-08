#include "mypanelopengl.h"
#include "common/matrixstack.h"
#include <cmath>
#include <iostream>

using std::cout;
using std::endl;
using cs40::Sphere;
using cs40::MatrixStack;

MyPanelOpenGL::MyPanelOpenGL(QWidget *parent) :
    QGLWidget(parent), m_angles(0,0.,0.) {

    for(int i=0; i<CS40_NUM_PROGS; i++){
        m_shaderPrograms[i]=NULL;
        m_vertexShaders[i]=NULL;
        m_fragmentShaders[i]=NULL;
    }

    m_sphere = NULL;
    m_polyMode = 0;
    m_curr_prog = 0;
    m_nparticles = 100;
    m_fountain = NULL;
    m_timer = NULL;
    m_time = 0;
    srand(time(NULL));
}

MyPanelOpenGL::~MyPanelOpenGL(){
    m_shaderPrograms[m_curr_prog]->release();
    delete m_sphere; m_sphere=NULL;
    delete m_timer; m_timer=NULL;
    if(m_fountain){
        m_fountain->release();
        delete m_fountain; m_fountain=NULL;
    }
    for(int i=0; i<CS40_NUM_PROGS; i++){
        destroyShaders(i);
    }
}

void MyPanelOpenGL::initializeGL()
{
    glewInit(); //manually do this now that we aren't using QtOpenGL
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    updatePolyMode(m_polyMode);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    createShaders(0, "vshader.glsl", "fshader.glsl");

    m_sphere = new Sphere(0.5,30,30);

    m_shaderPrograms[m_curr_prog]->bind();

    m_projection.perspective(40,1,1,8);
    m_camera.lookAt(vec3(0,0,3),vec3(0,0,0),vec3(0,1.,0.));
    updateModel();

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(step()));
    m_timer->start(10);
}

void MyPanelOpenGL::step(){
    m_time += 0.005;
    updateAngles(0,0.5);
    updateGL();
}

void MyPanelOpenGL::resizeGL(int w, int h)
{
    glViewport(0,0,w, h);
}



void MyPanelOpenGL::paintGL(){
    /* clear both color and depth buffer */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPointSize(5);

    if(!m_shaderPrograms[m_curr_prog]){return;}
    m_shaderPrograms[m_curr_prog]->bind();
    mat4 mview = m_camera*m_model;
    m_shaderPrograms[m_curr_prog]->setUniformValue("projection",m_projection);
    m_shaderPrograms[m_curr_prog]->setUniformValue("camera",m_camera);
    m_shaderPrograms[m_curr_prog]->setUniformValue("model", m_model);
    m_shaderPrograms[m_curr_prog]->setUniformValue("modelView",mview);
    m_shaderPrograms[m_curr_prog]->setUniformValue("normalMatrix",mview.normalMatrix());
    m_shaderPrograms[m_curr_prog]->setUniformValue("lightPos",vec4(1.5,0,2,1.)); //in world coordinates

    m_sphere->draw(m_shaderPrograms[m_curr_prog]);

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
        m_polyMode = (m_polyMode+1)%3;
        updatePolyMode(m_polyMode);
        break;
    case Qt::Key_V:
        m_curr_prog = (m_curr_prog+1)%CS40_NUM_PROGS;
        break;

    default:
        QWidget::keyPressEvent(event); /* pass to base class */
    }
    updateGL();
}

float MyPanelOpenGL::randFloat(){
   static int digits = 10000;
   return (rand() % digits)/(1.*digits);
}

void MyPanelOpenGL::makeFountain(){
    //Chapter 9 OpenGL 4.0 GLSL cookbook
    m_fountain = new QGLBuffer(QGLBuffer::VertexBuffer);
    bool ok = m_fountain->create();
    if(!ok){
        cout << "Unable to create VBO" << endl;
    }
    m_fountain->setUsagePattern(QGLBuffer::DynamicDraw);

    vec3 v(0,0,0);
    float velocity, theta, phi;
    float *data = new float[m_nparticles*3]; //Initial velocities of particles
    for (int i=0; i<m_nparticles; i++){
        theta = randFloat()*M_PI/6;
        phi = randFloat()*2*M_PI;
        v.setX(sin(theta)*cos(phi));
        v.setY(cos(theta));
        v.setZ(sin(theta)*sin(phi));
        velocity = 1.25 + 0.25*randFloat();
        v *= velocity;
        data[3*i] = v.x();
        data[3*i+1] = v.y();
        data[3*i+2] = v.z();
    }

    float *times = new float[m_nparticles]; //Initial start time of particles
    float time_now = 0, time_step=0.00075;
    for (int i=0; i<m_nparticles; i++){
        times[i] = time_now;
        time_now += time_step;
    }

    m_fountain->bind();
    m_fountain->allocate(m_nparticles*(sizeof(vec3)+sizeof(float)));
    m_fountain->write(0,data,m_nparticles*sizeof(vec3));
    m_fountain->write(m_nparticles*sizeof(vec3),times,m_nparticles*sizeof(float));
    m_fountain->release();
}

void MyPanelOpenGL::drawFountain(){
    m_fountain->bind();
    m_shaderPrograms[m_curr_prog]->setUniformValue("vColor",vec3(0.8,0.8,1.));
    m_shaderPrograms[m_curr_prog]->setUniformValue("vSColor",vec3(1.,1.,1.));
    m_shaderPrograms[m_curr_prog]->enableAttributeArray("vPosition");
    m_shaderPrograms[m_curr_prog]->setAttributeBuffer("vPosition",GL_FLOAT,0,3,0);
    glDrawArrays(GL_POINTS, 0, m_nparticles);
    m_fountain->release();
}

void MyPanelOpenGL::updateAngles(int idx, qreal amt){
    if(idx == 0){
        m_angles.setX(wrap(m_angles.x()+amt));
    }else if(idx == 1){
        m_angles.setY(wrap(m_angles.y()+amt));
    }else if(idx == 2){
        m_angles.setZ(wrap(m_angles.z()+amt));
    }
    updateModel();
}

void MyPanelOpenGL::updateModel(){
    m_model.setToIdentity();
    m_model.rotate(m_angles.z(), vec3(0,0,1.));
    m_model.rotate(m_angles.y(), vec3(0,1,0.));
    m_model.rotate(m_angles.x(), vec3(1,0,0.));
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

void MyPanelOpenGL::createShaders(int i, QString vertName, QString fragName){

    cout << "building shader " << i << endl;
    destroyShaders(i); //get rid of any old shaders
    m_vertexShaders[i] = new QGLShader(QGLShader::Vertex);
    if (!m_vertexShaders[i]->compileSourceFile(vertName)){
        qWarning() << m_vertexShaders[i]->log();
    }

    m_fragmentShaders[i] = new QGLShader(QGLShader::Fragment);
    if(!m_fragmentShaders[i]->compileSourceFile(fragName)){
        qWarning() << m_fragmentShaders[i]->log();
    }

    m_shaderPrograms[i] = new QGLShaderProgram();
    m_shaderPrograms[i]->addShader(m_vertexShaders[i]);
    m_shaderPrograms[i]->addShader(m_fragmentShaders[i]);

    if(!m_shaderPrograms[i]->link()){
        qWarning() << m_shaderPrograms[i]->log() << endl;
    }
}

void MyPanelOpenGL::destroyShaders(int i){
    delete m_vertexShaders[i]; m_vertexShaders[i]=NULL;
    delete m_fragmentShaders[i]; m_fragmentShaders[i]=NULL;

    if(m_shaderPrograms[i]){
        m_shaderPrograms[i]->release();
        delete m_shaderPrograms[i]; m_shaderPrograms[i]=NULL;
    }
}