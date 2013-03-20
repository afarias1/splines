#include "noise.h"
#include <cstdlib>
#include <iostream>

using namespace std;

NoiseGenerator::NoiseGenerator(int size){
  m_size = size;
  g1 = new float[m_size];
  g2 = new vec2[m_size];
  g3 = new vec3[m_size];
  perm = new int[m_size];

  int i;
  //generate some random noise, gradient vectors
  for(i=0; i<m_size; i++){
    perm[i]=i;
    g1[i]=randNoise();
    g2[i]=randOnCircle();
    g3[i]=randOnSphere();
  }

  //generate a random permutation
  int j, tmp;
  for(i=m_size; i>1; i--){
     j = rand()%i;
     //swap perm[i], perm[j];
     tmp = perm[i];
     perm[i] = perm[j];
     perm[j] = tmp;
  }
}

NoiseGenerator::~NoiseGenerator(){
  delete [] g1; g1 = NULL;
  delete [] g2; g2 = NULL;
  delete [] g3; g3 = NULL;
  delete [] perm; perm = NULL;
}

/*Generate random float in range -1 to 1*/
float NoiseGenerator::randNoise(){
   int digits = 10000;
   return (rand() % (2*digits)-digits*1.)/digits;
}

/*Generate random 2D Vector on unit circle*/
vec2 NoiseGenerator::randOnCircle(){
  vec2 v(randNoise(), randNoise());
  while(v.length() > 1){ //A little Monte Carlo
    v.setX(randNoise());
    v.setY(randNoise());
  }
  return v.normalized();
}

/*Generate random 3D Vector on unit sphere*/
vec3 NoiseGenerator::randOnSphere(){
  vec3 v(randNoise(), randNoise(), randNoise());
  while(v.lengthSquared() > 1){ //A little Monte Carlo
    v.setX(randNoise());
    v.setY(randNoise());
    v.setZ(randNoise());
  }
  return v.normalized();
}

/* given t in range 0..1, return noise value in range
 * -1..1 */
float NoiseGenerator::noise1(float t, float freq){
  t=wrap(t*freq);
  int pos0 = index(t);        //left index in perm array
  int pos1 = (pos0+1)%m_size; //right index in perm array
  float d0 = frac(t); //distance from pos0
  float a = d0*g1[perm[pos0]];  
  float b = (d0-1)*g1[perm[pos1]];
  return lerp(a, b, scurve(d0));
}  

/* given s,t in range 0..1, return noise value
 * in range -1..1 */
float NoiseGenerator::noise2(float s, float t, float freq){
  s=wrap(s*freq);
  int sp0 = index(s);
  int sp1 = (sp0+1)%m_size;
  float sd0 = frac(s);
  float sd1 = sd0-1;

  t=wrap(t*freq);
  int tp0 = index(t);
  int tp1 = (tp0+1)%m_size;
  float td0 = frac(t);
  float td1 = td0-1;

  //grab values at four corners;
  vec2 v00, v01, v10, v11;
  int si0, si1;
  si0=perm[sp0];
  si1=perm[sp1];

  v00=g2[perm[(si0+tp0)%m_size]];
  v01=g2[perm[(si0+tp1)%m_size]];
  v10=g2[perm[(si1+tp0)%m_size]];
  v11=g2[perm[(si1+tp1)%m_size]];

  float a,b,aa,bb, weight;
 
  weight = scurve(sd0);
  //interpolate across bottom
  aa=vec2::dotProduct(vec2(sd0,td0), v00);
  bb=vec2::dotProduct(vec2(sd1,td0), v10);
  a=lerp(aa,bb,weight);
  //interpolate across top
  aa=vec2::dotProduct(vec2(sd0,td1), v01);
  bb=vec2::dotProduct(vec2(sd1,td1), v11);
  b=lerp(aa,bb,weight);

  //interpolate top to bottom
  return lerp(a, b, scurve(td0));
}

/* given s,t,u in range 0..1, return noise value
 * in range -1..1 */
float NoiseGenerator::noise3(float s, float t, float u, float freq){
  s=wrap(s*freq);
  int sp0 = index(s);
  int sp1 = (sp0+1)%m_size;
  float sd0 = frac(s);
  float sd1 = sd0-1;

  t=wrap(t*freq);
  int tp0 = index(t);
  int tp1 = (tp0+1)%m_size;
  float td0 = frac(t);
  float td1 = td0-1;

  u=wrap(u*freq);
  int up0 = index(u);
  int up1 = (up0+1)%m_size;
  float ud0 = frac(u);
  float ud1 = ud0-1;

  //grab values at eight corners;
  vec3 v000, v010, v100, v110;
  vec3 v001, v011, v101, v111;

  int si0, si1, sti00, sti01, sti10, sti11;
  si0=perm[sp0];
  si1=perm[sp1];

  sti00 = perm[(si0+tp0)%m_size];
  sti01 = perm[(si0+tp1)%m_size];
  sti10 = perm[(si1+tp0)%m_size];
  sti11 = perm[(si1+tp1)%m_size];


  v000=g3[perm[(sti00+up0)%m_size]];
  v010=g3[perm[(sti01+up0)%m_size]];
  v100=g3[perm[(sti10+up0)%m_size]];
  v110=g3[perm[(sti11+up0)%m_size]];
  v001=g3[perm[(sti00+up1)%m_size]];
  v011=g3[perm[(sti01+up1)%m_size]];
  v101=g3[perm[(sti10+up1)%m_size]];
  v111=g3[perm[(sti11+up1)%m_size]];

  float front,back,a,b,aa,bb,sweight,tweight;
 
  sweight = scurve(sd0);
  tweight = scurve(td0);
  //interpolate across bottom back
  aa=vec3::dotProduct(vec3(sd0,td0,ud0), v000);
  bb=vec3::dotProduct(vec3(sd1,td0,ud0), v100);
  a=lerp(aa,bb,sweight);
  //interpolate across top back
  aa=vec3::dotProduct(vec3(sd0,td1,ud0), v010);
  bb=vec3::dotProduct(vec3(sd1,td1,ud0), v110);
  b=lerp(aa,bb,sweight);

  back = lerp(a,b,tweight);

  //interpolate across bottom front
  aa=vec3::dotProduct(vec3(sd0,td0,ud1), v001);
  bb=vec3::dotProduct(vec3(sd1,td0,ud1), v101);
  a=lerp(aa,bb,sweight);
  //interpolate across top front
  aa=vec3::dotProduct(vec3(sd0,td1,ud1), v011);
  bb=vec3::dotProduct(vec3(sd1,td1,ud1), v111);
  b=lerp(aa,bb,sweight);
  front = lerp(a,b,tweight);

  //interpolate back to front
  return lerp(back, front, scurve(ud0));
}
