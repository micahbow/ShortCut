#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>
#include <queue>
#include <QMainWindow>
#include "cityNode.h"
#include "graph.h"

#include <QtGui>
#include <QtCore>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(std::vector<cityNode*> & allNodes, std::vector<std::vector<std::pair<double,int>*>> edges, QWidget *parent = nullptr);
    ~MainWindow();
    std::string getSource();
    std::string getDest();
    int getUnits();
    void createGraph(std::vector<cityNode*> toGraph);
    void displayDistance(double distance);
    std::vector<int> shortestPath(int target, std::vector<int>& dijkPath);
    std::vector<int> dijkstra(const graph& ourgraph, int src);

private slots:

    void on_input_calculate_clicked();

    void on_input_search_start_textChanged(const QString &arg1);

    void on_input_search_end_textChanged(const QString &arg1);

    void on_input_zoomIn_clicked();

    void on_input_zoomOut_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsEllipseItem *ellipse;
    QGraphicsLineItem *edge;
    QGraphicsTextItem * nameText;

    std::vector<std::vector<std::pair<double,int>*>> adjList;
    std::vector<cityNode*> cityVec;
    bool readyState = false;
    int scale;
    std::vector<int> savedPath;
    int oldSource = -1;
};
#endif // MAINWINDOW_H
