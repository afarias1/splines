#include "rgbImage.h"
#include <stdexcept>
#include <iostream>

using namespace std;

int main(){
  RGBColor green(0,255,0);
  RGBColor clr;
  int r,c;
  clr=RGBColor(0,128,128);
  RGBImage img(512,512,green);
  img(10,10)=RGBColor(5,5,5);
  try{
    img(-1,700);
  }
  catch (range_error e){
    cout << "caught exception: " << e.what();
  }  
  
  string fname = "campus.png";
  cout << "Opening " << fname << endl;
  RGBImage img2(fname);
  cout << "Img2 (rows, cols)= " << img2.rows() << "  " << img2.cols() << endl;
  /*
  for(r=0; r<img2.rows(); r++){
    for(c=0; c<img2.cols(); c++){
      clr = img2(r,c);
      printf("%d %d %d %d %d\n", r, c, clr.r, clr.g, clr.b); 
    }
  }
  */

  string fname2="saved.png";
  cout << "Saving " << fname << " to " << fname2 << endl;
  if(!img2.saveAs(fname2, true)){
    cout << "Failed to save image" << endl;
  }

  return 0;
}
