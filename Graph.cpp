#include "Graph.h"

NeuralNetwork::NeuralNetwork()
    : learn_coeff(2.4)
    , learn_iteration_limit(10000)
    , error_threshold(1E-4)
{
    srand((unsigned)time(NULL));
}

void NeuralNetwork::clearGraph()
{
    input_nodes.clear();
    middle_nodes.clear();
    output_nodes.clear();
    before_edges.clear();
    after_edges.clear();
}

void NeuralNetwork::clearInputNodes()
{
    input_nodes.clear();
}

void NeuralNetwork::clearMiddleNodes()
{
    middle_nodes.clear();
}

void NeuralNetwork::clearAnswerNodes()
{
    answers.clear();
}

void NeuralNetwork::addInputNode(double value, pair<double, double> position)
{
    int node_id = input_nodes.empty() ? 0 : input_nodes.size();
    Node new_node(node_id, value, position);
    input_nodes.push_back(new_node);
}

void NeuralNetwork::addMiddleNode(double value, pair<double, double> position)
{
    int node_id = middle_nodes.empty() ? 0 : middle_nodes.size();
    Node new_node(node_id, value, position);
    middle_nodes.push_back(new_node);
}

void NeuralNetwork::addOutputNode(double value, pair<double, double> position)
{
    int node_id = output_nodes.empty() ? 0 : output_nodes.size();
    Node new_node(node_id, value, position);
    output_nodes.push_back(new_node);
}

void NeuralNetwork::addAnswerNode(double value, pair<double, double> position)
{
    int node_id = answers.empty() ? 0 : answers.size();
    Node new_node(node_id, value, position);
    answers.push_back(new_node);
}

Node NeuralNetwork::getInputNode(int node_id)
{
    return input_nodes.at(node_id);
}

Node NeuralNetwork::getMiddleNode(int node_id)
{
    return middle_nodes.at(node_id);
}

Node NeuralNetwork::getOutputNode(int node_id)
{
    return output_nodes.at(node_id);
}

Node NeuralNetwork::getAnswerNode(int node_id)
{
    return answers.at(node_id);
}

vector<Edge> NeuralNetwork::getBeforeEdges(int middle_node_id)
{
    vector<Edge> edges;
    for(int i = 0; i < input_nodes.size(); ++i)
    {
        edges.push_back(before_edges.at(middle_nodes.size() * i + middle_node_id));
    }
    return edges;
}

vector<Edge> NeuralNetwork::getAfterEdges(int output_node_id)
{
    vector<Edge> edges;
    for(int i = 0; i < middle_nodes.size(); ++i)
    {
        edges.push_back(after_edges.at(output_nodes.size() * i + output_node_id));
    }
    return edges;
}

void NeuralNetwork::setLearnLimit(int limit)
{
    learn_iteration_limit = limit;
}

void NeuralNetwork::setLearnCoeff(double coeff)
{
    learn_coeff = coeff;
}

void NeuralNetwork::setLearnedError(double error)
{
    error_threshold = error;
}

void NeuralNetwork::setMiddleNode(int node_id, double value)
{
    middle_nodes.at(node_id).value = value;
}

void NeuralNetwork::setOutputNode(int node_id, double value)
{
    output_nodes.at(node_id).value = value;
}

void NeuralNetwork::setBeforeEdges()
{
    for(int i = 0; i < input_nodes.size(); ++i)
    {
        for(int m = 0; m < middle_nodes.size(); ++m)
        {
            Edge new_edge(pair<int, int>(i, m), rand() / (double)RAND_MAX * 2.0 - 1.0);
            before_edges.push_back(new_edge);
        }
    }
}

void NeuralNetwork::setBeforeEdge(Edge edge)
{
    before_edges.at(middle_nodes.size() * edge.node_id_pair.first + edge.node_id_pair.second) = edge;
}

void NeuralNetwork::setAfterEdges()
{
    for(int m = 0; m < middle_nodes.size(); ++m)
    {
        for(int o = 0; o < output_nodes.size(); ++o)
        {
            Edge new_edge(pair<int, int>(m, o), rand() / (double)RAND_MAX * 2.0 - 1.0);
            after_edges.push_back(new_edge);
        }
    }
}

void NeuralNetwork::setAfterEdge(Edge edge)
{
    after_edges.at(output_nodes.size() * edge.node_id_pair.first + edge.node_id_pair.second) = edge;
}

void NeuralNetwork::calculate()
{
    // 中間層の計算
    for(int m = 0; m < middle_nodes.size(); ++m)
    {
        Node middle = middle_nodes.at(m);
        middle.value = 0;

        vector<Edge> edges = getBeforeEdges(middle.id);
        for(int i = 0; i < input_nodes.size(); ++i)
        {
            Edge e = edges.at(i);
            middle.value += e.weight * input_nodes.at(i).value;
        }

        middle.value = sigmoid(middle.value);
        setMiddleNode(middle.id, middle.value);
    }

    // 出力層の計算
    for(int o = 0; o < output_nodes.size(); ++o)
    {
        Node output = output_nodes.at(o);
        output.value = 0;

        vector<Edge> edges = getAfterEdges(output.id);
        for(int m = 0; m < middle_nodes.size(); ++m)
        {
            Edge e = edges.at(m);
            output.value += e.weight * middle_nodes.at(m).value;
        }

        output.value = sigmoid(output.value);
        setOutputNode(output.id, output.value);
    }
}

void NeuralNetwork::backPropergation(int iterate_times)
{
    if(output_nodes.size() == answers.size())
    {
        int iterate_number = 0;
        while(1)
        {
            calculate();

            // 各出力ノードの誤差
            vector<double> delta;
            double total_error = 0.0;

            // 中間ー出力間の重み更新
            updateAfterEdges(delta, total_error);

            // 入力ー中間間の重み更新
            updateBeforeEdges(delta);

            total_error /= 2.0;

            // 終了条件
            if(iterate_times != 0 && iterate_number > iterate_times)
                break;
            else if(total_error < error_threshold || iterate_number > learn_iteration_limit)
                break;

            ++iterate_number;
        }
    }
}

void NeuralNetwork::updateAfterEdges(vector<double> &delta, double &total_error)
{
    // 各出力ノード
    for(int o = 0; o < output_nodes.size(); ++o)
    {
        // 誤差を計算
        Node output = getOutputNode(o);
        Node answer = getAnswerNode(o);
        double error = answer.value - output.value;
        total_error += error * error;

        // 微分値
        double deriv = output.value * (1.0 - output.value);

        // 誤差伝搬に使う
        delta.push_back(error * deriv);

        // 現在の出力ノードへ伸びてくるエッジ集合
        vector<Edge> edges = getAfterEdges(o);
        for(int i = 0; i < edges.size(); ++i)
        {
            Edge e = edges.at(i);           // あるエッジ
            Node m = getMiddleNode(i);      // 根元の中間ノード

            // 修正量の計算
            double update = learn_coeff * m.value * error * deriv;

            // 重みを修正して更新
            e.weight += update;
            setAfterEdge(e);
        }
    }
}

void NeuralNetwork::updateBeforeEdges(vector<double> &delta)
{
    // 各中間ノード
    for(int m = 0; m < middle_nodes.size(); ++m)
    {
        // 修正量を計算
        Node middle = getMiddleNode(m);
        double deriv = middle.value * (1.0 - middle.value);

        // 現在の中間ノードへ伝搬する誤差
        double error = 0.0;
        for(int o = 0; o < output_nodes.size(); ++o)
        {
            Edge after_edge = after_edges.at(output_nodes.size() * middle.id + o);
            error += after_edge.weight * delta.at(o);
        }

        // 現在の中間ノードへ伸びてくるエッジ集合
        vector<Edge> edges = getBeforeEdges(m);
        for(int i = 0; i < edges.size(); ++i)
        {
            Edge e = edges.at(i);               // あるエッジ
            Node input = getInputNode(i);       // 根元のノード

            // 修正量の計算
            double update = learn_coeff * input.value * error * deriv;

            // 重みを修正して更新
            e.weight += update;
            setBeforeEdge(e);
        }
    }
}

double NeuralNetwork::sigmoid(double x)
{
    return 1.0 / (1.0 + exp(-x));
}
