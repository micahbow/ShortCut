#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    //data parse




    QApplication a(argc, argv);
    vector<cityNode*> nodes;

    cityNode* city1 = new cityNode("alcantara",100,100,0);
    nodes.push_back(city1);
    cityNode* city2 = new cityNode("alcatraz",100,100,1);
    nodes.push_back(city2);
    cityNode* city3 = new cityNode("balcans",100,100,2);
    nodes.push_back(city3);
    cityNode* city4 = new cityNode("balcatraz",100,100,3);
    nodes.push_back(city4);
    cityNode* city5 = new cityNode("alabama",100,100,4);
    nodes.push_back(city5);


    MainWindow w(nodes);
    w.show();

    while(w.getReadyState() == false)
    {
        break;
    }

    string source = w.getSource();
    string dest = w.getDest();

    //find the source and dest cityNode*s

    //run djikstras

    //get the vector of path back

    //run w.createGraph(vector<cityNode*> toGraph);

    //also run displayDistance(double distance);

    //but first get the distance value in km or mi based on

    //w.getUnits(); 0 = miles, 1 = kilometers

    return a.exec();
}
