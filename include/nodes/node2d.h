#pragma once
#include <vector>
#include <memory>

using namespace std;

class node2d{
    public:
        int obstacle,start,goal;
        
        int x,y,cost, visited;

        vector<shared_ptr<node2d>> neighbors;
        shared_ptr<node2d> parent;
        node2d();
        node2d(int,int);

};

