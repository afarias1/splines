#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <cmath>
#include <cstdlib>

#include "common/rgbImage.h"
#include "noise.h"

using namespace std;
using namespace cs40;

NoiseGenerator ngen;

/* convert from -1-1 noise space to 0-255 greyscale */
RGBColor convertColor(float x){
  int r,g,b;
  x=0.5*(1+x); //map to 0..1
  r=(int)(255*x);
  g=(int)(255*x);
  b=(int)(255*x);
  return RGBColor(r,g,b);
}

float surf1(float x, float y){
   float freq=0.05;
   float amp = 0.5;
   float steps = 2;
   float val = 0;
   while(steps > 0){
     val += amp*ngen.noise2(x,y,freq);
     amp*=0.5;
     freq*=2;
     steps--;
   }
   return val;
}

float surf2(float x, float y){
   float freq=0.05;
   float amp = 0.5;
   float steps = 2;
   float val = 0;
   while(steps > 0){
     val += fabs(amp*ngen.noise2(x,y,freq));
     amp*=0.5;
     freq*=2;
     steps--;
   }
   return val;
}

float surf3(float x, float y){

   return sin(3*M_PI*(x+surf1(x,y)));
}

float surf4(float x, float y){
  float val = 5*ngen.noise2(x,y,0.01);
  return val-static_cast<int>(val);
}

float surf5(float x, float y, float z){
   float freq=0.05;
   float amp = 0.5;
   float steps = 2;
   float val = 0;
   while(steps > 0){
     val += fabs(amp*ngen.noise3(x,y,z,freq));
     amp*=0.5;
     freq*=2;
     steps--;
   }
   return sin(3*M_PI*(x+val));
}
int main(int argc, char* argv[]){
  srand(time(NULL));
  string fname = "test.png";
  int nrows=256, ncols=256;
  RGBImage img(nrows, ncols, RGBColor(255,255,255));

  float x,y,val;
  for(int j=0; j<nrows; j++){
    for(int i=0; i<ncols; i++){
      x = (i+0.5)/ncols-0.5;
      y = (j+0.5)/nrows-0.5;
      val = surf2(x,y);
      img(j,i) = convertColor(val);
    }
  }

  img.saveAs(fname, true);

  cout << "Saved result to " << fname << endl;
  return 0;
}

