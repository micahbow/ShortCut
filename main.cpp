#include "mainwindow.h"

#include <QApplication>

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

void readData(std::string fileName, std::vector<cityNode*>& ourCityPointers);
void generateEdges(std::vector<cityNode*> cityPointas, std::vector<std::vector<std::pair<double, int>*>>& edges);
void readEdgeFile(std::string fileName, std::vector<std::vector<std::pair<double, int>*>>& edges);

int main(int argc, char *argv[])
{

    //TEST BLOCK START
    /*
    std::vector<cityNode*> deezNodes;
    std::vector<std::vector<std::pair<double,int>*>> deezEdges;

    cityNode* city1 = new cityNode("MIA",25.761681,-80.191788,0);
    deezNodes.push_back(city1);
    cityNode* city3 = new cityNode("ORL",28.538336,-81.379234,2);
    deezNodes.push_back(city3);
    cityNode* city4 = new cityNode("GNV",29.651634,-82.324829,3);
    deezNodes.push_back(city4);
    cityNode* city2 = new cityNode("TEST",85, -156.8050438189411,1);
    deezNodes.push_back(city2);
    cityNode* city7 = new cityNode("alabamaa",36.54063726808276, -95.77664281245616,7);
    deezNodes.push_back(city7);

    for(int i = 0; i < deezNodes.size(); i++)
    {
        deezEdges.push_back(std::vector<std::pair<double,int>*>());
        for (int j = 0; j < deezNodes.size(); j++)
        {
            if(i!=j)
            {
                double dist = cityNode::getDist(deezNodes[i],deezNodes[j],0);
                if(dist < 100)
                {
                    std::pair<double,int>* newEdge = new std::pair<double,int>(dist, j);
                    deezEdges[i].push_back(newEdge);
                }
            }

        }

    }

    */
    //TEST BLOCK END

    std::vector<cityNode*> nodes;
    readData("C:\\Users\\micah\\OneDrive\\Documents\\QTtest1\\worldcities.csv", nodes);

    std::vector<std::vector<std::pair<double, int>*>> edges;
    //generateEdges(nodes, edges); only a one-time use, an O(N^2) operation
    readEdgeFile("C:\\Users\\micah\\OneDrive\\Documents\\QTtest1\\CitiesEdgeList.txt",edges);


    QApplication a(argc, argv);
    MainWindow w(nodes,edges);
    //w.createGraph(nodes);
    w.show();

    return a.exec();
}

void readData(std::string fileName, std::vector<cityNode*>& ourCityPointers)
{
    std::ifstream inFile(fileName);

    if (inFile.is_open())
    {
        std::string lineFromFile;
        getline(inFile, lineFromFile);

        std::string cityName;
        std::string intData;
        int latitude;
        int longitude;
        int index = 0;

        while (getline(inFile, lineFromFile))
        {
            std::istringstream stream(lineFromFile);

            getline(stream, cityName, ',');
            getline(stream, intData, ',');
            latitude = stod(intData);
            getline(stream, intData, ',');
            longitude = stod(intData);

            cityNode* nodePointer = new cityNode(cityName, latitude, longitude, index);
            ourCityPointers.push_back(nodePointer);

            index++;
        }
    }
    else
    {
        throw std::invalid_argument("File not opened!");
    }
}

void generateEdges(std::vector<cityNode*> cityPointers, std::vector<std::vector<std::pair<double, int>*>>& edges)
{
    for (int i = 0; i < cityPointers.size(); i++)
    {
        edges.push_back(std::vector<std::pair<double, int>*>());
        for (int j = 0; j < cityPointers.size(); j++)
        {
            if (i != j)
            {
                double dist = cityNode::getDist(cityPointers.at(i), cityPointers.at(j), 0);
                if (dist < 100)
                {
                    std::pair<double, int>* newEdge = new std::pair<double, int>(dist, j);
                    edges.at(i).push_back(newEdge);
                }
            }

        }
    }
}

void readEdgeFile(std::string fileName, std::vector<std::vector<std::pair<double, int>*>>& edges)
{
    std::ifstream inFile(fileName);

    if (inFile.is_open())
    {
        std::string lineFromFile;

        std::string adjIndex;

        std::string adjDistance;

        std::string indexo;
        int theIndex = -1;

        while (getline(inFile, lineFromFile))
        {
            std::istringstream stream(lineFromFile);
            getline(stream, indexo, ',');
            theIndex = stoi(indexo);
            edges.push_back(std::vector<std::pair<double, int>*>());
            while (getline(stream, adjIndex, ','))
            {
                getline(stream, adjDistance, ',');
                std::pair<double, int>* newEdge = new std::pair<double, int>(stod(adjDistance), stoi(adjIndex));
                edges.at(theIndex).push_back(newEdge);
            }

        }
    }
    else
    {
        throw std::invalid_argument("File not opened!");
    }
}
