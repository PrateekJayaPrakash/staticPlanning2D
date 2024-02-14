#include "algos/grid_2d_solver.h"
#include <nodes/node2d.h>
#include <climits>
#include <iostream>
#include <memory>
#include <stack>
#define INF INT_MAX


int Grid2dSolver::solve()
{
    return 10;
}

// vector<vector<int>> Grid2dSolver::astarSolve(
//     vector<vector<node2d*>> searchMap,
//     node2d* startNode,
//     node2d* goalNode
//     )
// {
//     // If start is goal, 
//     if(startNode->goal == 1){
//         return {{startNode->x, startNode->y}};
//     }

     
// }

vector<vector<int>> Grid2dSolver::DfsSolve(
    node2d& startNode,
    node2d& goalNode
    )
{
    cout<<"--"<<endl;
    // If start is goal, 
    if(startNode.goal == 1){
        return {{startNode.x, startNode.y}};
    }
    
    // Variable to store the path
    vector<vector<int>> path;
    
    Grid2dSolver::recursiveDFS(startNode, goalNode, path);
    return path;
}

void Grid2dSolver::recursiveDFS(
    node2d& currentNode,
    const node2d& goalNode,
    vector<vector<int>>& path)
{
    // base case
    if (currentNode.visited == 1 || currentNode.obstacle==1) {
        return;
    }
    
    // mark current node as visited
    currentNode.visited = 1;
    //std::cout << currentNode.x << " " << currentNode.y << std::endl;

    path.push_back({currentNode.x, currentNode.y});

    if (currentNode.x == goalNode.x && currentNode.y == goalNode.y) {
        std::cout << "found" << std::endl;
        std::cout << currentNode.x << " " << currentNode.y << std::endl;
        return;  // Terminate function after goal is found
    }

    for (auto& next : currentNode.neighbors) {
        if (next->visited == 0) {
            Grid2dSolver::recursiveDFS(*next, goalNode, path);
            if (path.back()[0] == goalNode.x && path.back()[1] == goalNode.y) {
                return;
            }
        }
    }

    path.pop_back();
}