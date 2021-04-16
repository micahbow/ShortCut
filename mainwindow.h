#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <vector>
#include <QMainWindow>
#include "cityNode.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(vector<cityNode*> & allNodes, QWidget *parent = nullptr);
    ~MainWindow();
    bool getReadyState();
    string getSource();
    string getDest();
    int getUnits();
    void createGraph(vector<cityNode*> toGraph);
    void displayDistance(double distance);

private slots:
    void on_input_search_start_returnPressed();

    void on_input_search_end_returnPressed();

    void on_input_calculate_clicked();

private:
    vector<cityNode*> cityVec;
    Ui::MainWindow *ui;
    bool readyState = false;
};
#endif // MAINWINDOW_H
