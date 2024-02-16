#pragma once
#include <vector>
#include <memory>

using namespace std;

class node2d{
    public:
        int obstacle,start,goal;
        int x,y,cost, visited, distance;
        vector<pair<shared_ptr<node2d>, int>> edges;
        vector<shared_ptr<node2d>> neighbors;
        shared_ptr<node2d> parent;
        node2d();
        node2d(int,int);
        // Overload the equality operator to compare nodes
        bool operator==(const node2d& other) const {
            return (x == other.x && y == other.y);
        }
};

