#include <iostream>
#include <fstream>

using namespace std;

int main(){
  ifstream infile;
  string name;
  float rad, a, tau, ecc, incl;
  char buf[1024];
  infile.open("solarData.txt");
  //read header lines
  infile.getline(buf,1024);
  cout << buf << endl; 
  infile.getline(buf,1024);
  cout << buf << endl;
  name = "";
  char end; 
  while(!infile.eof()){
    infile >> name >> rad >> a >> tau >> ecc >> incl;
    if(!infile.eof()){
      printf("%s %f %f %f %f %f\n", name.c_str(), rad, a, tau, ecc, incl);
    }
  }
  return 0;
}
