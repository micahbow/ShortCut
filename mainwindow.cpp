#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(std::vector<cityNode*> & cityNodes,std::vector<std::vector<std::pair<double,int>*>> edges, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    this->adjList = edges;
    this->cityVec = cityNodes;

    this->scale = 10;

    ui->input_list_start->clear();
    ui->input_list_end->clear();
    ui->input_list_start->setInsertPolicy(QComboBox::InsertAlphabetically);
    ui->input_list_end->setInsertPolicy(QComboBox::InsertAlphabetically);
    for (cityNode* C : this->cityVec)
    {
        std::string name = C->getName();
        ui->input_list_start->addItem(QString::fromStdString(name));
        ui->input_list_end->addItem(QString::fromStdString(name));
    }

    ui->input_units->addItem("Miles");
    ui->input_units->addItem("Kilometers");

    ui->input_method->addItem("Dijkstra's");
    ui->input_method->addItem("Depth-First");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_input_search_start_textChanged(const QString &arg1)
{
    ui->input_list_start->clear();
    ui->input_list_start->setInsertPolicy(QComboBox::InsertAlphabetically);
    QString key = ui->input_search_start->text();
    bool addAll = false;
    if (key == "") {addAll = true;}
    for (cityNode* C : this->cityVec)
    {
        std::string name = C->getName();
        if (addAll || name.rfind(key.toStdString()) == 0)
        {
            ui->input_list_start->addItem(QString::fromStdString(name));
        }
    }
}

void MainWindow::on_input_search_end_textChanged(const QString &arg1)
{
    ui->input_list_end->clear();
    ui->input_list_end->setInsertPolicy(QComboBox::InsertAlphabetically);
    QString key = ui->input_search_end->text();
    bool addAll = false;
    if (key == "") {addAll = true;}
    for (cityNode* C : this->cityVec)
    {
        std::string name = C->getName();
        if (addAll || name.rfind(key.toStdString()) == 0)
        {
            ui->input_list_end->addItem(QString::fromStdString(name));
        }

    }
}

std::string MainWindow::getSource()
{
    return ui->input_list_start->currentText().toStdString();
}

std::string MainWindow::getDest()
{
    return ui->input_list_end->currentText().toStdString();
}

int MainWindow::getUnits()
{
  return ui->input_units->currentIndex();
}

void MainWindow::displayDistance(double distance)
{
    ui->output_distance->display(distance);
    return;
}

void MainWindow::on_input_calculate_clicked()
{
    std::string source = this->getSource();
    std::string dest = this->getDest();

    if (source == "" || dest == "") {return;}

    cityNode* sourceCity = nullptr;
    cityNode* destCity = nullptr;
    for(int i = 0; i < this->cityVec.size(); i++)
    {
        if(this->cityVec.at(i)->getName() == source)
        {
            sourceCity = this->cityVec.at(i);

        }
        else if(this->cityVec.at(i)->getName() == dest)
        {
            destCity = this->cityVec.at(i);
        }
        if (sourceCity != nullptr && destCity != nullptr) { break;}
    }

    if (sourceCity == nullptr || destCity == nullptr)
    {
        return;
    }

    graph fullGraph(adjList);

    std::vector<cityNode*> finalPath;

    if(ui->input_method->currentText() == "Depth-First")
    {
        std::set<int> visited;
        std::vector<int> temp;
        std::vector<int> midPath;
        dfs(fullGraph,sourceCity->getIndex(),destCity->getIndex(),temp,visited,midPath);
        if(midPath.size() == 0) {throw std::invalid_argument("DFS BROKE");}
        for(int i = 0; i < midPath.size(); i++)
        {
            finalPath.push_back(cityVec.at(midPath.at(i)));
        }
    }
    else
    {

        if(savedPath.size() == 0 || sourceCity->getIndex()!=oldSource)
        {
            this->savedPath = dijkstra(fullGraph,sourceCity->getIndex());
            oldSource = sourceCity->getIndex();
        }

        std::vector<int> midPath = shortestPath(destCity->getIndex(),this->savedPath);

        for(int i = 0; i < midPath.size(); i++)
        {
            finalPath.push_back(cityVec.at(midPath.at(i)));
        }
    }
    this->createGraph(finalPath);

    this->readyState = true;
}


void MainWindow::createGraph(std::vector<cityNode*> toGraph)
{
    scene->clear();

    QImage map("C:\\Users\\micah\\OneDrive\\Documents\\QTtest1\\map.png");
    if (map.isNull()) { throw std::invalid_argument("image broke have a nice day");}

    //QImage zone = map.copy( xMinPixel-offset2, yMinPixel-offset2, width, height);
    //zone = zone.scaled(671,511);
    map = map.scaled(ui->graphicsView->width()*scale,ui->graphicsView->height()*scale);
    //zone.save("C:\\Users\\micah\\OneDrive\\Documents\\QTtest1\\cropped_image.png");
    //QGraphicsPixmapItem* background = new QGraphicsPixmapItem(QPixmap::fromImage(zone));
    QGraphicsPixmapItem* background = new QGraphicsPixmapItem(QPixmap::fromImage(map));
    scene->addItem(background);
    background->setPos(0,0);

    std::vector<double> xCoords,yCoords;

    for(cityNode* node : toGraph)
    {
        std::pair<double,double>* XY = node->getXY();
        xCoords.push_back(XY->first);
        yCoords.push_back(XY->second);
    }

    double p = 0.017453292519943295;
    /*
    QImage map("C:\\Users\\micah\\OneDrive\\Documents\\QTtest1\\map.png");
    if (map.isNull()) { throw std::invalid_argument("image broke have a nice day");}

    int imageXmax = map.width();
    int imageYmax = map.height();*/

    double leftAng = -180;
    double rightAng = 180;
    double topAng = 85;
    double botAng = -85;

    double mercXmin = leftAng * p;
    double mercXmax = rightAng * p;
    double mercYmin = log(tan(botAng*p) + (1.0/cos(botAng*p)));
    double mercYmax = log(tan(topAng*p) + (1.0/cos(topAng*p)));

    double xMax = mercXmax; //*max_element(xCoords.begin(),xCoords.end());
    double xMin = mercXmin;//*min_element(xCoords.begin(),xCoords.end());
    double yMax = mercYmax;//*max_element(yCoords.begin(),yCoords.end());
    double yMin = mercYmin;//*min_element(yCoords.begin(),yCoords.end());

    /*int xMaxPixel = (((xMax - mercXmin)/(mercXmax-mercXmin)) * (imageXmax));
    int xMinPixel = (((xMin - mercXmin)/(mercXmax-mercXmin)) * (imageXmax));
    int yMaxPixel = (((yMax) - mercYmin)/(mercYmax-mercYmin) * (imageYmax));
    int yMinPixel = (((yMin) - mercYmin)/(mercYmax-mercYmin) * (imageYmax));


    int width = ceil(abs(xMaxPixel-xMinPixel))+offset;
    int height = ceil(abs(yMaxPixel-yMinPixel))+offset;

    QImage zone = map.copy( xMinPixel-offset2, yMinPixel-offset2, width, height);
    zone = zone.scaled(671,511);
    zone.save("C:\\Users\\micah\\OneDrive\\Documents\\QTtest1\\cropped_image.png");
    QGraphicsPixmapItem* background = new QGraphicsPixmapItem(QPixmap::fromImage(zone));
    scene->addItem(background);
    background->setPos(0,0);*/

    QPen redpen(Qt::red);
    QPen blackpen(Qt::black);
    redpen.setWidth(10);
    blackpen.setWidth(2);



    double pathDist = 0;

    for (int i = 0; i < xCoords.size(); i++)
    {
        xCoords[i] = (((xCoords[i]-xMin)/(xMax-xMin))*(ui->graphicsView->width())*scale) - 20;
        yCoords[i] = (ui->graphicsView->height() - (((yCoords[i]-yMin)/(yMax-yMin))*(ui->graphicsView->height())))*scale +1120;

        if(i != 0)
        {
            double dist = cityNode::getDist(toGraph[i],toGraph[i-1],getUnits());
            pathDist += dist;
            scene->addLine(xCoords[i]+5,yCoords[i]+5,xCoords[i-1]+5,yCoords[i-1]+5,blackpen);
            nameText = scene->addText(QString::fromStdString(std::to_string(dist)));
            QString distTitle = "<div style='background-color:#00e0e0;'>  ";
            distTitle.append(QString::fromStdString(std::to_string(dist)));
            distTitle.append(QString::fromStdString("  </div>"));
            nameText->setHtml(distTitle);
            nameText->setPos((xCoords[i]+xCoords[i-1])/2,(yCoords[i]+yCoords[i-1])/2);
            nameText->setVisible(false);

        }

        scene->addEllipse(xCoords[i],yCoords[i],3,3,redpen);
        nameText = scene->addText(QString::fromStdString(toGraph.at(i)->getName()));
        QString cityTitle = "<div style='background-color:#00e0e0;'>  ";
        cityTitle.append(QString::fromStdString(toGraph.at(i)->getName()));
        cityTitle.append(QString::fromStdString("  </div>"));
        nameText->setPos(xCoords[i]-3,yCoords[i]-5);
        nameText->setHtml(cityTitle);


    }
    ui->output_distance->setSmallDecimalPoint(true);
    this->displayDistance(pathDist);
    this->readyState = false;
}

std::vector<int> MainWindow::dijkstra(const graph& ourgraph, int src) {
    std::priority_queue<std::pair<long long, int>, std::vector<std::pair<long long, int>>, std::greater<std::pair<long long, int>>> myPriorityQueue;  //make a min priority queue of pairs where the pairs hold distances and then vertices, this works because greater on pair compares the first integer which is our distance here so we have the minimum distances at the top
    std::vector<long long> distances; // create a vector of distances
    std::vector<int> thePreviousIndex;
    std::vector<int> directPath;
    for (int i = 0; i < ourgraph.numVertices; i++)
    {
        distances.push_back(LONG_MAX); //default all the values to being away by infinity in our distances vector
        thePreviousIndex.push_back(-1);
    }

    myPriorityQueue.push(std::make_pair(0, src)); // push the default distance 0 with source node 0 onto the min queue
    distances.at(src) = 0; // make the source node distance 0

    while (!myPriorityQueue.empty()) // while we have a min priority queue where all the edges havent been checked
    {
        std::pair<long long, int> currentNode = myPriorityQueue.top(); // grab top node
        myPriorityQueue.pop(); // pop that node
        int currentNodeLookingAt = currentNode.second; // find the vertice of the node we have

        for (auto iter = ourgraph.adjList.at(currentNodeLookingAt).begin(); iter != ourgraph.adjList.at(currentNodeLookingAt).end(); iter++) // now we apply edge relaxation to all the nodes we have near us
        {
            int nextNodeo = (*iter)->second; //this grabs a neighboring node
            long long nextNodeoWeight = (*iter)->first; //this grabs that neighboring node's weight
            if (distances.at(nextNodeo) > distances.at(currentNodeLookingAt) + nextNodeoWeight) // we check if the distance of that neighboring node is greater than the distance of the node we are originating at + the weight at this new node, if it is then we simply make it equal to that weight + the weight from before, so we have a smaller distance
            {
                distances.at(nextNodeo) = distances.at(currentNodeLookingAt) + nextNodeoWeight; // change the weight
                myPriorityQueue.push(std::make_pair(distances.at(nextNodeo), nextNodeo)); // add the next node to this min priority queue with it's updated/relaxed distance and with it's place
                thePreviousIndex.at(nextNodeo) = currentNodeLookingAt; // update previous node
            }
        }
    }
    return thePreviousIndex;
}

std::vector<int> MainWindow::shortestPath(int target, std::vector<int>& dijkPath) // this returns shortest path to a target AFTER initializing a dijkstra vector for a source node
{
    std::vector<int> thePath;
    int currentPlace = target;
    while (currentPlace != -1) // run until hitting source/just pushes the target itself if it's not reachable from the source
    {
        thePath.push_back(currentPlace);
        currentPlace = dijkPath.at(currentPlace);
    }
    return thePath;
}

void MainWindow::dfs(const graph& ourgraph, int src, int target, std::vector<int> thePath, std::set<int> & visited, std::vector<int> & finalResult) {

    if (visited.count(src) == 0)
    {
        visited.insert(src); // put initial node in both data types
        thePath.push_back(src);

        if (src == target)
        {
            finalResult = thePath;
            return;
        }

        int u = src;
        for (auto iter = ourgraph.adjList.at(u).begin(); iter != ourgraph.adjList.at(u).end(); iter++)
        {
            dfs(ourgraph, (*iter)->second, target, thePath, visited,finalResult);
        }
    }

}


void MainWindow::on_input_zoomIn_clicked()
{
    ui->graphicsView->scale(1.05,1.05);
}

void MainWindow::on_input_zoomOut_clicked()
{
    ui->graphicsView->scale(0.95,0.95);
}
