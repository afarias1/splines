#ifndef CS40_VECTOR3D_H
#define CS40_VECTOR3D_H

#include <ostream>

namespace cs40{

  class Vector3D{
    
    public:
      /* you can modify x,y,z directly */
      float x,y,z;  

      /* Construct vector (0,0,0) */
      Vector3D();

      /* Construct vector (xpos, ypos, zpos) */
      Vector3D(float xpos, float ypos, float zpos);

      /* Returns the length of the vector */
      float length() const;
  
      /* Return length of vector squared or v.dotProduct(v) */
      float lengthSquared() const;

      /* Modify the vector in place to have unit length
	 Will not normalize a null vector */
      void normalize();

      /* Return a new vector in the same direction as this vector, 
	 but with unit length */
      Vector3D normalized() const;

      /* Modify the vector to be scale*this */
      Vector3D& operator*=(float scale);

      /* Modify the vector to be this/scale */
      Vector3D& operator/=(float scale);
      
      /* Modify this vector by adding other */
      Vector3D& operator+=(const Vector3D& other);

      /* Modify this vector by subtracting other */
      Vector3D& operator-=(const Vector3D& other);

      /* Return dot product of this and other */
      float dotProduct(const Vector3D& other) const;

      /* Return cross product of this and other vector */
      Vector3D crossProduct(const Vector3D& other) const;
  };


}

/* these live outside the namespace */
cs40::Vector3D operator*(float scale, const cs40::Vector3D& vector);
cs40::Vector3D operator*(const cs40::Vector3D& vector, float scale);
cs40::Vector3D operator/(const cs40::Vector3D& vector, float scale);
cs40::Vector3D operator+(const cs40::Vector3D& v1, const cs40::Vector3D& v2);
cs40::Vector3D operator-(const cs40::Vector3D& v1, const cs40::Vector3D& v2);
cs40::Vector3D operator-(const cs40::Vector3D& vec);
std::ostream& operator<<(std::ostream& stream, const cs40::Vector3D& vector);

#endif
