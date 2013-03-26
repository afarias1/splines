#ifndef CS40_NOISE_H
#define CS40_NOISE_H

#include <QVector3D>
#include <QVector2D>

typedef QVector3D vec3;
typedef QVector2D vec2;

class NoiseGenerator{
  private:
    int m_size;  //size of permutation vector

    float* g1;   //array of 1D noise vals
    vec2* g2;    //array of 2D noise gradients
    vec3* g3;    //array of 3D noise gradients
    int* perm;   //permutation array;

    /*Generate random float in range -1 to 1*/
    float randNoise();
    
    /*Generate random 2D Vector on unit circle*/
    vec2 randOnCircle();

    /*Generate random 3D Vector on unit sphere*/
    vec3 randOnSphere();

    /* compute s-curve value for t, assuming 
     * range of t = [0,1]. scurve(0) = 0, scurve(1) = 1*/
    inline float scurve(float t){
      return t*t*(3.0-2*t);
    }

    /* linearly interpolate f(t) in range t=[0,1], 
     * where f(0)=a and f(1)=b */
    inline float lerp(float a, float b, float t){
      return a+t*(b-a);
    }

    /* map 0..1 onto 0..size-1 (rounding down) */
    inline int index(float t){
			int val =  static_cast<int>(t*m_size);
      if (val==m_size){
				val--;
      }
      return val;
    }

    /* return fractional part of size*t-index(t) for
     * t in range 0..1 */
    inline float frac(float t){
      return m_size*t-index(t);
    }

    
    /* map t onto range [0,1) by wrapping */
    inline float wrap(float t){
      float val = t - static_cast<int>(t);
      if(val < 0) { val += 1; }
      return val;
    }
    
  public:
    NoiseGenerator(int size=256);
    ~NoiseGenerator();

    /* given t in range 0..1, return noise value in range
     * -1..1, wrap t to range 0..1 if needed */
    float noise1(float t, float freq=0.125);
   
    /* given s,t in range 0..1, return noise value
     * in range -1..1, wrapping s,t if needed */
    float noise2(float s, float t, float freq=0.125);

    /* given s,t,u in range 0..1, return noise value
     * in range -1..1, wrapping s,t,u if needed */
    float noise3(float s, float t, float u, float freq=0.125);
};


#endif

