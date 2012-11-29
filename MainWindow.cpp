#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    input_layer_num(5),
    middle_layer_num(6),
    output_layer_num(5)
{
    srand((unsigned)time(NULL));

    ui->setupUi(this);
    createGraph();
    drawGraph();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_horizontalSlider_InputLayerNumber_valueChanged(int value)
{
    input_layer_num = value;
    createGraph();
    drawGraph();
}

void MainWindow::on_horizontalSlider_MiddleLayerNumber_valueChanged(int value)
{
    middle_layer_num = value;
    createGraph();
    drawGraph();
}

void MainWindow::on_horizontalSlider_OutputLayerNumber_valueChanged(int value)
{
    output_layer_num = value;
    createGraph();
    drawGraph();
}

void MainWindow::on_pushButton_Calculate_clicked()
{
    graph.calculate();
    drawGraph();
}

void MainWindow::on_pushButton_Learn_clicked()
{
    // 正解
    graph.clearAnswerNodes();
    graph.addAnswerNode(1.0, pair<double, double>(0.0, 0.0));
    graph.addAnswerNode(0.0, pair<double, double>(0.0, 0.0));
    graph.addAnswerNode(0.2, pair<double, double>(0.0, 0.0));
    graph.addAnswerNode(0.5, pair<double, double>(0.0, 0.0));
    graph.addAnswerNode(1.0, pair<double, double>(0.0, 0.0));

    graph.backPropergation();
    drawGraph();
}

void MainWindow::on_pushButton_LearnXOR_clicked()
{
    // XORを学習
    input_layer_num = 3;
    middle_layer_num = 3;
    output_layer_num = 1;
    createGraph();
    drawGraph();

    for(int i = 0; i < 3000; ++i)
    {
        // 0,0 -> 0
        graph.clearInputNodes();
        graph.addInputNode(1.0, pair<double, double>(500 / 4, 1 * 500 / (input_layer_num + 1)));
        graph.addInputNode(0.0, pair<double, double>(500 / 4, 2 * 500 / (input_layer_num + 1)));
        graph.addInputNode(0.0, pair<double, double>(500 / 4, 3 * 500 / (input_layer_num + 1)));
        graph.clearAnswerNodes();
        graph.addAnswerNode(0.0, pair<double, double>(0.0, 0.0));
        graph.backPropergation(1);
        drawGraph();

        // 1,0 -> 1
        graph.clearInputNodes();
        graph.addInputNode(1.0, pair<double, double>(500 / 4, 1 * 500 / (input_layer_num + 1)));
        graph.addInputNode(1.0, pair<double, double>(500 / 4, 2 * 500 / (input_layer_num + 1)));
        graph.addInputNode(0.0, pair<double, double>(500 / 4, 3 * 500 / (input_layer_num + 1)));
        graph.clearAnswerNodes();
        graph.addAnswerNode(1.0, pair<double, double>(0.0, 0.0));
        graph.backPropergation(1);
        drawGraph();

        // 0,1 -> 1
        graph.clearInputNodes();
        graph.addInputNode(1.0, pair<double, double>(500 / 4, 1 * 500 / (input_layer_num + 1)));
        graph.addInputNode(0.0, pair<double, double>(500 / 4, 2 * 500 / (input_layer_num + 1)));
        graph.addInputNode(1.0, pair<double, double>(500 / 4, 3 * 500 / (input_layer_num + 1)));
        graph.clearAnswerNodes();
        graph.addAnswerNode(1.0, pair<double, double>(0.0, 0.0));
        graph.backPropergation(1);
        drawGraph();

        // 1,1 -> 0
        graph.clearInputNodes();
        graph.addInputNode(1.0, pair<double, double>(500 / 4, 1 * 500 / (input_layer_num + 1)));
        graph.addInputNode(1.0, pair<double, double>(500 / 4, 2 * 500 / (input_layer_num + 1)));
        graph.addInputNode(1.0, pair<double, double>(500 / 4, 3 * 500 / (input_layer_num + 1)));
        graph.clearAnswerNodes();
        graph.addAnswerNode(0.0, pair<double, double>(0.0, 0.0));
        graph.backPropergation(1);
        drawGraph();
    }

    // テスト
    graph.clearInputNodes();
    graph.addInputNode(1.0, pair<double, double>(500 / 4, 1 * 500 / (input_layer_num + 1)));
    graph.addInputNode(1.0, pair<double, double>(500 / 4, 2 * 500 / (input_layer_num + 1)));
    graph.addInputNode(1.0, pair<double, double>(500 / 4, 3 * 500 / (input_layer_num + 1)));
    graph.calculate();
    cout << "(1, 1)->" << graph.getOutputNode(0).value << endl;

    graph.clearInputNodes();
    graph.addInputNode(1.0, pair<double, double>(500 / 4, 1 * 500 / (input_layer_num + 1)));
    graph.addInputNode(1.0, pair<double, double>(500 / 4, 2 * 500 / (input_layer_num + 1)));
    graph.addInputNode(0.0, pair<double, double>(500 / 4, 3 * 500 / (input_layer_num + 1)));
    graph.calculate();
    cout << "(1, 0)->" << graph.getOutputNode(0).value << endl;

    graph.clearInputNodes();
    graph.addInputNode(1.0, pair<double, double>(500 / 4, 1 * 500 / (input_layer_num + 1)));
    graph.addInputNode(0.0, pair<double, double>(500 / 4, 2 * 500 / (input_layer_num + 1)));
    graph.addInputNode(1.0, pair<double, double>(500 / 4, 3 * 500 / (input_layer_num + 1)));
    graph.calculate();
    cout << "(0, 1)->" << graph.getOutputNode(0).value << endl;

    graph.clearInputNodes();
    graph.addInputNode(1.0, pair<double, double>(500 / 4, 1 * 500 / (input_layer_num + 1)));
    graph.addInputNode(0.0, pair<double, double>(500 / 4, 2 * 500 / (input_layer_num + 1)));
    graph.addInputNode(0.0, pair<double, double>(500 / 4, 3 * 500 / (input_layer_num + 1)));
    graph.calculate();
    cout << "(0, 0)->" << graph.getOutputNode(0).value << endl;
}

void MainWindow::on_pushButton_CalculateXOR_clicked()
{
    double input0 = this->ui->lineEdit_Input0->text().toDouble();
    double input1 = this->ui->lineEdit_Input1->text().toDouble();

    // 入力ノード
    graph.clearInputNodes();
    graph.addInputNode(1.0, pair<double, double>(500 / 4, 1 * 500 / (input_layer_num + 1)));
    graph.addInputNode(input0, pair<double, double>(500 / 4, 2 * 500 / (input_layer_num + 1)));
    graph.addInputNode(input1, pair<double, double>(500 / 4, 3 * 500 / (input_layer_num + 1)));
    graph.calculate();

    drawGraph();
}

void MainWindow::createGraph()
{
    graph.clearGraph();

    // ノード作成
    for(int i = 0; i < input_layer_num; ++i)
    {
        graph.addInputNode(rand() / (double)RAND_MAX, pair<double, double>(500 / 4, (i + 1) * 500 / (input_layer_num + 1)));
    }
    for(int i = 0; i < middle_layer_num; ++i)
    {
        graph.addMiddleNode(0.0, pair<double, double>(500 / 4 * 2, (i + 1) * 500 / (middle_layer_num + 1)));
    }
    for(int i = 0; i < output_layer_num; ++i)
    {
        graph.addOutputNode(0.0, pair<double, double>(500 / 4 * 3, (i + 1) * 500 / (output_layer_num + 1)));
    }

    // エッジ作成
    graph.setBeforeEdges();
    graph.setAfterEdges();
}

void MainWindow::drawGraph()
{
    Mat image(500, 500, CV_8UC3);
    image = Mat::zeros(image.size(), image.type());

    // エッジの描画
    for(int i = 0; i < middle_layer_num; ++i)
    {
        vector<Edge> edges = graph.getBeforeEdges(i);
        for(int j = 0; j < edges.size(); ++j)
        {
            Edge e = edges.at(j);
            Node start_node = graph.getInputNode(e.node_id_pair.first);
            Node end_node = graph.getMiddleNode(e.node_id_pair.second);
            drawEdge(image, e, start_node, end_node);
        }
    }
    for(int i = 0; i < output_layer_num; ++i)
    {
        vector<Edge> edges = graph.getAfterEdges(i);
        for(int j = 0; j < edges.size(); ++j)
        {
            Edge e = edges.at(j);
            Node start_node = graph.getMiddleNode(e.node_id_pair.first);
            Node end_node = graph.getOutputNode(e.node_id_pair.second);
            drawEdge(image, e, start_node, end_node);
        }
    }

    // ノードの描画
    for(int i = 0; i < input_layer_num; ++i)
    {
        drawNode(image, graph.getInputNode(i));
    }
    for(int i = 0; i < middle_layer_num; ++i)
    {
        drawNode(image, graph.getMiddleNode(i));
    }
    for(int i = 0; i < output_layer_num; ++i)
    {
        drawNode(image, graph.getOutputNode(i));
    }

    imshow("Graph", image);
}

void MainWindow::drawNode(Mat &image, Node node)
{
    if(node.value >= 0.0)
    {
        circle(image, Point(node.position.first, node.position.second), node.value * 30, Scalar(255, 255, 255), -1, CV_AA);
    }
    else
    {
        circle(image, Point(node.position.first, node.position.second), -node.value * 30, Scalar(255, 255, 255), -1, CV_AA);
        circle(image, Point(node.position.first, node.position.second), -node.value * 29, Scalar(0, 0, 0), -1, CV_AA);
    }

    stringstream ss;
    ss << node.value;
    putText(image, ss.str(), Point(node.position.first, node.position.second), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 3, CV_AA);
    putText(image, ss.str(), Point(node.position.first, node.position.second), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0), 1, CV_AA);
}

void MainWindow::drawEdge(Mat &image, Edge edge, Node start, Node end)
{
    Point start_point(start.position.first, start.position.second);
    Point end_point(end.position.first, end.position.second);

    line(image, start_point, end_point, Scalar(0, 0, 0), fabs(edge.weight) * 9 + 1, CV_AA);
    if(edge.weight >= 0.0)
    {
        line(image, start_point, end_point, Scalar(255, 200, 0), edge.weight * 9, CV_AA);
    }
    else
    {
        line(image, start_point, end_point, Scalar(0, 50, 255), -edge.weight * 9, CV_AA);
    }

    //cout << "weight:" << edge.weight << endl;
}



