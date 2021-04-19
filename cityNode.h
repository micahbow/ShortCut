#ifndef CITYNODE_H
#define CITYNODE_H
#include <string>
#include <cmath>
//STANDARD CITYNODE CLASS TO BE USED ACROSS ALL CODE
class cityNode {
      double lat, lon;
      int index;
      std::string cityName;
      //maybe add int population and other fields provided by data if planning to use
  public:
      cityNode(std::string name, double lat, double lon,int ind) { this->cityName = name; this->lat = lat; this->lon = lon; index = ind;}
      int getLat() { return lat;}
      int getLong() { return lon;}
      int getIndex() { return index;}
      std::string getName() { return cityName;}

      static double getDist(cityNode* city1, cityNode* city2, int units) {
        double lat1 = city1->lat;
        double lon1 = city1->lon;
        double lat2 = city2->lat;
        double lon2 = city2->lon;
        double r = (units == 0)?3963.19059:6378.137; //0 = miles, 1 = kilometers
        double p = 0.017453292519943295;  //pi factor/180 for degrees
        double a = 0.5 - cos((lat2-lat1)*p)/2 + cos(lat1*p)*cos(lat2*p) * (1-cos((lon2-lon1)*p)) / 2;
        return 2 * r * asin(sqrt(a));
      }

      std::pair<double,double>* getXY() {
        double p = 0.017453292519943295;  //pi factor/180 for degrees
        double lonRad = this->lon * p;
        double latRad = this->lat * p;
        double Ycoord = log(tan(latRad) + (1.0/cos(latRad)));
        double Xcoord = lonRad;
        return new std::pair<double,double>(Xcoord,Ycoord);
      }
};
#endif // CITYNODE_H
