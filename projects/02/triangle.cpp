#include "triangle.h"

using namespace cs40;

Triangle::Triangle(const vec2& p1, const vec2& p2, const vec2& p3){
    pts[0] = p1;
    pts[1] = p2;
    pts[2] = p3;
    /* TODO: verify that points are in CCW order */
}

Triangle::Triangle(const Triangle *other){
  /* implement copy constructor */
}

void Triangle::move(float dx, float dy){
  /* implement this.
   * update pts
   * write updates to old QGLBuffer
   */
}

void Triangle::draw(QGLShaderProgram* prog){
    /* bind active vbo
     * set color uniform value in fragmen shader
     * enable attribute array for vPosition input in vertex shader
     * describe layout of VBO for attribute array
     * glDrawArrays
     * release vbo
     */
}

