#include <vector3d.h>

using namespace cs40;

/* Construct vector (0,0,0) */
Vector3D::Vector3D(): x(0), y(0), z(0) {};

/* Construct vector (xpos, ypos, zpos) */
Vector3D::Vector3D(float xpos, float ypos, float zpos):
  x(xpos), y(ypos), z(zpos) {};

/* Returns the length of the vector */
//float length() const;

/* Return length of vector squared or v.dotProduct(v) */
//float lengthSquared() const;

/* Modify the vector in place to have unit length
   Will not normalize a null vector */
//void normalize();

/* Return a new vector in the same direction as this vector, 
   but with unit length */
//Vector3D::Vector3D normalized() const;

/* Modify the vector to be scale*this */
Vector3D& Vector3D::operator*=(float scale){
  x *= scale;
  y *= scale;
  z *= scale;
  return *this;
}

/* Modify the vector to be this/scale */
//Vector3D& operator/=(float scale);

/* Modify this vector by adding other */
//Vector3D& operator+=(const Vector3D& other);

/* Modify this vector by subtracting other */
//Vector3D& operator-=(const Vector3D& other);

/* Return dot product of this and other */
//float dotProduct(const Vector3D& other) const;

/* Return cross product of this and other vector */
//Vector3D crossProduct(const Vector3D& other) const;


Vector3D operator*(float scale, const Vector3D& vector){
  return Vector3D(vector.x*scale, vector.y*scale, vector.z*scale);
}

//Vector3D operator*(const Vector3D& vector, float scale);
//Vector3D operator/(const Vector3D& vector, float scale);
//Vector3D operator+(const Vector3D& v1, const Vector3D& v2);
//Vector3D operator-(const Vector3D& v1, const Vector3D& v2);
//Vector3D operator-(const Vector3D& vec);

std::ostream& operator<<(std::ostream& stream, const Vector3D& vector){
  stream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
  return stream;
}
