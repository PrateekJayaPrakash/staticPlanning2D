#include <iostream>
#include <vector>
#include <memory>
#include <nodes/node2d.h>
#include <fstream>
#include <random>
#include <queue>
#include <algorithm>

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
    void exportMap(const string& filename);
    void exportPath(const vector<shared_ptr<node2d>>& path, const string& filename);
    
    // Helpers
    int distToGoal(const node2d& start, const node2d& goal, const string method);
    
    // Solvers
    void djikstra(int x1, int y1, int x2, int y2);
    void aStar(int x1, int y1, int x2, int y2);
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

    //cout << "Edge added between {" << x1 << ", " << y1 
         //<< "} and {" << x2 << ", " << y2 << "} with weight " << weight << endl;
}

void NodeGraph::graphBuilder(){
    int width = 30;
    int height = 30;
    // Create horizontal lines
    for (int x : {0, 1, 2, 13, 14, 15, 16, 27, 28, 29}) {
        for (int y = 0; y < height-1; ++y) {
            addEdge(x, y, x, y+1, 5); // Add point at (x, y)
        }
    }

    // Create vertical line
    for (int y : {0, 1, 2, 13, 14, 15, 16, 27, 28, 29}) {
        for (int x = 0; x < width-1; ++x) {
            addEdge(x, y, x+1, y, 5); // Add point at (x, y)
        }
    }
    removeRandomPoints(0);
    exportMap("../output/map.csv");
}

// Method to export nodes' coordinates to a CSV file
void NodeGraph::exportMap(const string& filename) {
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

void NodeGraph::djikstra(int x1, int y1, int x2, int y2){
    // Assumption: start and goal exist in the map
    shared_ptr<node2d> startNode = findOrCreateNode(x1, y1);
    shared_ptr<node2d> goalNode = findOrCreateNode(x2, y2);
    bool goalFound = false;

    cout << "Start x:" << startNode->x <<" y:"<<startNode->y << " | Goal x:" << goalNode->x <<" y:"<<goalNode->y<< endl;

    // Priority queue to store nodes with their distances
    priority_queue<pair<int, shared_ptr<node2d>>, vector<pair<int, shared_ptr<node2d>>>, greater<pair<int, shared_ptr<node2d>>>> pq;
    
    // push the start node to the priority queue
    startNode->distance=0;
    pq.push({0, startNode});

    // Run till queue not empty
    while(!pq.empty()){
        auto current = pq.top().second;
        int current_dist = pq.top().first;
        pq.pop();

        // If goal found break
        if(current->x == x2 && current->y == y2){
            cout << "Goal found" << endl;
            goalFound = true;
            break;
        }

        // visit neighbors
        for(auto& n:current->edges){
            int newDist = current_dist + n.second;
            //cout << n.first->x << n.first->y <<n.first->distance << endl;
            if(newDist < n.first->distance){
                n.first->distance = newDist;
                n.first->parent = current;
                pq.push({newDist, n.first});
            }
        }
    }
    if(!goalFound){
        cout << "No path from start to goal. Search ended" << endl;
        return;
    }

    vector<shared_ptr<node2d>> path;
    auto current = goalNode;
    
    while(current){
        path.push_back(current);
        current = current -> parent;
    }
    std::reverse(path.begin(), path.end());
    exportPath(path, "../output/path.csv");
}

void NodeGraph::aStar(int x1, int y1, int x2, int y2){
    // O(V*E): Use only when edge weights are negative.
    // Assumption: start and goal exist in the map
    shared_ptr<node2d> startNode = findOrCreateNode(x1, y1);
    shared_ptr<node2d> goalNode = findOrCreateNode(x2, y2);
    bool goalFound = false;

    cout << "A* algo start x:" << startNode->x << " y:" 
            <<startNode->y << " | Goal x:" 
            << goalNode->x <<" y:"<<goalNode->y
            << endl;

    priority_queue<
        pair<int, shared_ptr<node2d>>,
        vector<pair<int, shared_ptr<node2d>>>,
        greater<pair<int, shared_ptr<node2d>>>
        > pq;
    
    // push the start node to the priority queue
    startNode->distance=0;
    int d2g = distToGoal(*startNode, *goalNode, "manhatten");
    pq.push({startNode->distance=0 + d2g, startNode});

    while(!pq.empty()){
        shared_ptr<node2d> current = pq.top().second;
        int currDist = pq.top().first;
        pq.pop();

        // If goal Node is the top of the priority queue then we stop
        if(current->x == x2 && current->y == y2){
            cout << "Goal found dist: " << current->distance << endl;
            goalFound = true;
            break;
        }

        // Cost to goal heurestic : Manhatten distance
        //d2g = distToGoal(*current, *goalNode, "manhatten");

        for(auto& n:current->edges){
            int newDist = current->distance + n.second;
            if(newDist < n.first->distance){
                n.first->distance = newDist;
                n.first->parent = current;
                pq.push({newDist+distToGoal(*n.first, *goalNode, "manhatten"), n.first});
            }
        }
    }
    if(!goalFound){
        cout << "No path from start to goal. Search ended" << endl;
        return;
    }

    vector<shared_ptr<node2d>> path;
    auto current = goalNode;
    
    while(current){
        path.push_back(current);
        current = current -> parent;
    }
    std::reverse(path.begin(), path.end());
    exportPath(path, "../output/path.csv");
}

int NodeGraph::distToGoal(const node2d& start, const node2d& goal, const string method){
    if(method == "manhatten"){
        return abs(start.x - goal.x) + abs(start.y - goal.y);
    }
    return -1;
}

void NodeGraph::exportPath(const vector<shared_ptr<node2d>>& path, const string& filename){
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file for writing." << endl;
        return;
    }

    // Write header
    file << "node_x,node_y" << endl;

    // Write coordinates
    for (const auto& node : path) {
        file << node->x << "," << node->y << endl;
    }

    file.close();
    cout << "Path Export successful." << endl;
}

int main()
{
    // Example usage
    NodeGraph graph(100);

    // Add edges
    graph.graphBuilder();
    //graph.djikstra(1,1,21,28);
    graph.aStar(1,1,21,28);
    return 0;
}