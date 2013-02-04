#include "vector3d.h"
#include <iostream>

using namespace std;
using namespace cs40;

int main(){
  Vector3D v(1., 2., 3.);
  cout << v << endl;
  cout << 2*v << endl;
  v*=2; 
  cout << v << endl;
  return 0;
}
