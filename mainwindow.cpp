#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cityNode.h"
using namespace std;
MainWindow::MainWindow(vector<cityNode*> & cityNodes, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->cityVec = cityNodes;

    ui->input_list_start->clear();
    ui->input_list_end->clear();
    ui->input_list_start->setInsertPolicy(QComboBox::InsertAlphabetically);
    ui->input_list_end->setInsertPolicy(QComboBox::InsertAlphabetically);
    for (cityNode* C : this->cityVec)
    {
        string name = C->getName();
        ui->input_list_start->addItem(QString::fromStdString(name));
        ui->input_list_end->addItem(QString::fromStdString(name));
    }

    ui->output_progress->setValue(0);

    ui->input_units->addItem("Miles");
    ui->input_units->addItem("Kilometers");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_input_search_start_returnPressed()
{
    ui->input_list_start->clear();
    ui->input_list_start->setInsertPolicy(QComboBox::InsertAlphabetically);
    QString key = ui->input_search_start->text();
    bool addAll = false;
    if (key == "") {addAll = true;}
    for (cityNode* C : this->cityVec)
    {
        string name = C->getName();
        if (addAll || name.rfind(key.toStdString()) == 0)
        {
            ui->input_list_start->addItem(QString::fromStdString(name));
        }
    }
}

void MainWindow::on_input_search_end_returnPressed()
{
    ui->input_list_end->clear();
    ui->input_list_end->setInsertPolicy(QComboBox::InsertAlphabetically);
    QString key = ui->input_search_end->text();
    bool addAll = false;
    if (key == "") {addAll = true;}
    for (cityNode* C : this->cityVec)
    {
        string name = C->getName();
        if (addAll || name.rfind(key.toStdString()) == 0)
        {
            ui->input_list_end->addItem(QString::fromStdString(name));
        }

    }
}

void MainWindow::on_input_calculate_clicked()
{
    if (!(ui->output_progress->value() == 0 || ui->output_progress->value() == 100))
    {
        return;
    }
    ui->output_progress->setValue(0);
    this->readyState = true;
    for(int i = 0; i <= 1000000000; i++)
    {
        ui->output_progress->setValue(i/10000000 );
    }
}

bool MainWindow::getReadyState()
{
    return this->readyState;
}
string MainWindow::getSource()
{
    return ui->input_list_start->currentText().toStdString();
}
string MainWindow::getDest()
{
    return ui->input_list_end->currentText().toStdString();
}
int MainWindow::getUnits()
{
  return stoi(ui->input_units->currentText().toStdString());
}
void MainWindow::createGraph(vector<cityNode*> toGraph)
{


    this->readyState = false;
}
void MainWindow::displayDistance(double distance)
{
    ui->output_distance->display(distance);
    return;
}


