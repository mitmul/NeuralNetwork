#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv.hpp>

#include "NeuralNetwork.h"

using namespace cv;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_horizontalSlider_InputLayerNumber_valueChanged(int value);
    void on_horizontalSlider_MiddleLayerNumber_valueChanged(int value);

    void on_horizontalSlider_OutputLayerNumber_valueChanged(int value);

    void on_pushButton_Calculate_clicked();

    void on_pushButton_Learn_clicked();

    void on_pushButton_LearnXOR_clicked();

    void on_pushButton_CalculateXOR_clicked();

private:
    Ui::MainWindow *ui;

    NeuralNetwork graph;
    int input_layer_num;
    int middle_layer_num;
    int output_layer_num;

    void createGraph();
    void drawGraph();
    void drawNode(Mat &image, Node node);
    void drawEdge(Mat &image, Edge edge, Node start, Node end);
};

#endif // MAINWINDOW_H
