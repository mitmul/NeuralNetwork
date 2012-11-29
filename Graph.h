#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class Node
{
public:
    Node(int node_id, double node_value, pair<double, double> node_position)
        : id(node_id)
        , value(node_value)
        , position(node_position)
    {}

    int id;
    double value;
    pair<double, double> position;
};

class Edge
{
public:
    Edge(pair<int, int> node_id_pair, double edge_weight)
        : node_id_pair(node_id_pair)
        , weight(edge_weight)
    {}

    pair<int, int> node_id_pair;
    double weight;
};

class NeuralNetwork
{
public:
    NeuralNetwork();

    void clearGraph();
    void clearInputNodes();
    void clearMiddleNodes();
    void clearAnswerNodes();

    void addInputNode(double value, pair<double, double> position);
    void addMiddleNode(double value, pair<double, double> position);
    void addOutputNode(double value, pair<double, double> position);
    void addAnswerNode(double value, pair<double, double> position);

    Node getInputNode(int node_id);
    Node getMiddleNode(int node_id);
    Node getOutputNode(int node_id);
    Node getAnswerNode(int node_id);
    vector<Edge> getBeforeEdges(int middle_node_id);
    vector<Edge> getAfterEdges(int output_node_id);

    void setLearnLimit(int limit);
    void setLearnCoeff(double coeff);
    void setLearnedError(double error);
    void setMiddleNode(int node_id, double value);
    void setOutputNode(int node_id, double value);
    void setBeforeEdges();
    void setBeforeEdge(Edge edge);
    void setAfterEdges();
    void setAfterEdge(Edge edge);

    void calculate();
    void backPropergation(int iterate_times = 0);
    void updateAfterEdges(vector<double> &delta, double &total_error);
    void updateBeforeEdges(vector<double> &delta);

private:
    vector<Node> input_nodes;
    vector<Node> middle_nodes;
    vector<Node> output_nodes;
    vector<Edge> before_edges;
    vector<Edge> after_edges;
    vector<Node> answers;
    double learn_coeff;
    double error_threshold;
    int learn_iteration_limit;

    double sigmoid(double x);
};

#endif // GRAPH_H
