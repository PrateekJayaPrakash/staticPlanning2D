#include "nodes/node2d.h"
#include<climits>
#define INF INT_MAX

node2d::node2d(){
    this->obstacle=0;
    this->visited=0;
    this->start=0;
    this->goal=0;
    this->parent=nullptr;
    this->cost=INF;
}

node2d::node2d(int x, int y){
    this->x=x;
    this->visited=0;
    this->y=y;
    this->obstacle=0;
    this->start=0;
    this->goal=0;
    this->parent=nullptr;
    this->cost=INF;
}