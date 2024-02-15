#include <iostream>
#include <vector>
#include <memory>
#include <nodes/node2d.h>
#include <fstream>
#include <random>

using namespace std;

class NodeGraph{
private:
    // Number of nodes
    int N;
    // Start and end nodes
    shared_ptr<node2d> startNode;
    shared_ptr<node2d> goalNode;

public:
    //List of all nodes
    vector<shared_ptr<node2d>> nodeList;
    // Constructor
    NodeGraph(int N);
    // Method to find a node in a list
    shared_ptr<node2d> findNode(const node2d& node);
    shared_ptr<node2d> findOrCreateNode(int x, int y);
    // Method to add edge from one node to another
    void addEdge(int x1, int y1, int x2, int y2, int weight);
    // Types of graphs
    void graphBuilder();
    void removeRandomPoints(int N);
    void exportCSV(const string& filename);
    // Solvers
    void djikstra(node2d n1, node2d n2);
};

NodeGraph::NodeGraph(int N){
    this->N = N;
}

shared_ptr<node2d> NodeGraph::findNode(const node2d& node) {
    for (const auto& ptr : nodeList) {
        if (ptr && *(ptr.get()) == node) {
            return ptr;
        }
    }
    return nullptr; // Node not found
}

// Method to find or create a node for given coordinates
shared_ptr<node2d> NodeGraph::findOrCreateNode(int x, int y) {
    // Search for existing node
    for (const auto& ptr : nodeList) {
        if (ptr && ptr->x == x && ptr->y == y) {
            return ptr;
        }
    }

    // If node doesn't exist, create and add it to nodeList
    shared_ptr<node2d> newNode = make_shared<node2d>(x, y);
    nodeList.push_back(newNode);
    return newNode;
}

void NodeGraph::addEdge(int x1, int y1, int x2, int y2, int weight){
    // See if this point already exists in the map, else create it 
    shared_ptr<node2d> node1 = findOrCreateNode(x1, y1);
    shared_ptr<node2d> node2 = findOrCreateNode(x2, y2);

    node1->edges.push_back(make_pair(node2, weight));
    node2->edges.push_back(make_pair(node1, weight));

    cout << "Edge added between {" << x1 << ", " << y1 
         << "} and {" << x2 << ", " << y2 << "} with weight " << weight << endl;
}

void NodeGraph::graphBuilder(){
    int width = 30;
    int height = 30;
    // Create horizontal lines
    for (int x : {0, 1, 2, 13, 14, 15, 16, 27, 28, 29}) {
        for (int y = 0; y < height; ++y) {
            addEdge(x, y, x, y, 5); // Add point at (x, y)
        }
    }

    // Create vertical line
    for (int y : {0, 1, 2, 13, 14, 15, 16, 27, 28, 29}) {
        for (int x = 0; x < width; ++x) {
            addEdge(x, y, x, y, 5); // Add point at (x, y)
        }
    }
    removeRandomPoints(0);
    exportCSV("../output/map.csv");
}

// Method to export nodes' coordinates to a CSV file
void NodeGraph::exportCSV(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file for writing." << endl;
        return;
    }

    // Write header
    file << "node_x,node_y,obstacle" << endl;

    // Write coordinates
    for (const auto& node : nodeList) {
        file << node->x << "," << node->y << "," << 0 << endl;
    }

    file.close();
    cout << "Export successful." << endl;
}

// Method to remove N random points from the nodeList
void NodeGraph::removeRandomPoints(int N) {
    if (N >= nodeList.size()) {
        cout << "Cannot remove more points than available." << endl;
        return;
    }

    // Create a random number generator
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, nodeList.size() - 1);

    // Remove N random points
    for (int i = 0; i < N; ++i) {
        int index = dis(gen);
        nodeList.erase(nodeList.begin() + index);
    }

    cout << "Removed " << N << " random points." << endl;
}


int main()
{
    // Example usage
    NodeGraph graph(100);

    // Add edges
    graph.addEdge(0, 0, 1, 1, 10);
    graph.addEdge(0, 0, 2, 2, 5);
    graph.graphBuilder();

    cout << graph.nodeList.size();
    return 0;
}