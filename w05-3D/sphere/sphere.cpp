#include "sphere.h"
#include <iostream>

using namespace cs40;
using std::cout;
using std::endl;

Sphere::Sphere(float radius, int slices, int stacks):
    m_color(0,0,1,1), m_vbo(NULL), m_radius(radius),
    m_slices(slices), m_stacks(stacks)
{

    m_stripsize = (slices+1)*2;
    vec3* vertices = new vec3[m_stripsize*(m_stacks-2)+2*(slices+2)];
    double latstep = M_PI/m_stacks;
    double longstep = 2.*M_PI/m_slices;

    double lat0 = -M_PI/2.+latstep;
    double z0 = m_radius*sin(lat0);
    double zcos0 = m_radius*cos(lat0);
    double lng = -M_PI;
    double coslong = cos(lng);
    double sinlong = sin(lng);
    int idx = 0;

    /* mid lat strips */
    for(int i = 1; i < m_stacks-1; i++){

        double lat1 = lat0+latstep;
        double z1 = m_radius*sin(lat1);
        double zcos1 = m_radius*cos(lat1);

        //cout << 180*lat0/M_PI << " " << 180*lat1/M_PI << endl;
        lng = -M_PI;

        for(int j=0; j<=m_slices; j++){
            coslong = cos(lng);
            sinlong = sin(lng);
            vertices[idx++]=vec3(zcos1*coslong,zcos1*sinlong,z1);
            vertices[idx++]=vec3(zcos0*coslong,zcos0*sinlong,z0);
            lng+=longstep;
        }
        //swap lat1, z1, zcos1 up
        lat0 = lat1;
        z0 = z1;
        zcos0 = zcos1;
    }

    /* draw polar caps as fans */

    /* south pole */
    vertices[idx++]=vec3(0,0,-m_radius);
    cout << -m_radius << endl;
    lat0 = -M_PI/2+latstep;
    lng = M_PI;
    z0 = m_radius*sin(lat0);
    zcos0 = m_radius*cos(lat0);
    for(int i=0; i<=m_slices; i++){
        coslong = cos(lng);
        sinlong = sin(lng);
        vertices[idx++]=vec3(zcos0*coslong,zcos0*sinlong,z0);
        lng-=longstep;
    }

    /* north pole */
    vertices[idx++]=vec3(0,0,m_radius);
    lat0 = M_PI/2-latstep;
    lng = -M_PI;
    z0 = m_radius*sin(lat0);
    zcos0 = m_radius*cos(lat0);
    for(int i=0; i<=m_slices; i++){
        coslong = cos(lng);
        sinlong = sin(lng);
        vertices[idx++]=vec3(zcos0*coslong,zcos0*sinlong,z0);
        lng+=longstep;
    }

    if(initVBO()){
        int DataSize = m_stripsize*(m_stacks-2)*sizeof(vec3); /* all mid lat strips */
        DataSize += 2*(m_slices+2)*sizeof(vec3); /* two polar fans*/
        m_vbo->bind();
        m_vbo->allocate(DataSize);
        m_vbo->write(0,vertices,DataSize);
        m_vbo->release();
    }

    delete [] vertices; vertices=NULL;
}

bool Sphere::initVBO(){
    m_vbo = new QGLBuffer(QGLBuffer::VertexBuffer);
    bool ok = m_vbo->create();
    m_vbo->setUsagePattern(QGLBuffer::StaticDraw);
    return ok;
}

Sphere::~Sphere(){
    if(m_vbo){
        m_vbo->release();
        delete m_vbo; m_vbo=NULL;
    }
}

void Sphere::draw(QGLShaderProgram* prog){
    if(!prog){ return; }
    m_vbo->bind();
    prog->setUniformValue("vColor",m_color);
    prog->enableAttributeArray("vPosition");
    prog->setAttributeBuffer("vPosition",GL_FLOAT,0,3,0);
    for(int i=0; i<m_stacks-2; i++){
      glDrawArrays(GL_TRIANGLE_STRIP,i*m_stripsize, m_stripsize);
    }
    int offset = (m_stacks-2)*m_stripsize;
    int fansize = m_slices+2;
    glDrawArrays(GL_TRIANGLE_FAN, offset, fansize);
    glDrawArrays(GL_TRIANGLE_FAN, offset+fansize, fansize);
    m_vbo->release();
}
