#ifndef CITYNODE_H
#define CITYNODE_H
#include <string>
using namespace std;
//STANDARD CITYNODE CLASS TO BE USED ACROSS ALL CODE
class cityNode {
      double lat, lon;
      int index;
      string cityName;
      //maybe add int population and other fields provided by data if planning to use
  public:
      cityNode(string name, double lat, double lon,int ind) { this->cityName = name; this->lat = lat; this->lon = lon; index = ind;}
      int getLat() { return lat;}
      int getLong() { return lon;}
      string getName() { return cityName;}
};
#endif // CITYNODE_H
