#include "algos/grid_2d_solver.h"
#include <nodes/node2d.h>
#include <climits>
#include <iostream>
#include <memory>
#include <stack>
#include <algorithm>
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

vector<vector<int>> Grid2dSolver::iterativeDfs(
    node2d& startNode,
    node2d& goalNode
    )
{
    cout<<"Starting iterative DFS solve"<<endl;
    
    // If start is goal 
    if(startNode.goal == 1){
        return {{startNode.x, startNode.y}};
    }
    
    // Variable to store the path
    vector<vector<int>> path;
    
    // Stack for DFS
    std::stack<shared_ptr<node2d>> dfsStack;

    dfsStack.push(std::make_shared<node2d>(startNode));

    while(!dfsStack.empty())
    {
        std::shared_ptr<node2d> temp = dfsStack.top();
        dfsStack.pop();

        // check if goal is reached
        if(temp->x == goalNode.x && temp->y == goalNode.y){
            while(temp != nullptr)
            {
                path.push_back({temp->x, temp->y});
                temp = temp->parent;
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        // visit neighbors
        for(auto neighbor:temp->neighbors)
        {
            if(neighbor->visited == 0 && neighbor->obstacle != 1){
                neighbor->visited = 1;
                neighbor->parent = temp; // Set the parent node
                dfsStack.push(neighbor); // Push the neighbor onto the stack
            }
        }
    
    }
    
    return path;
}

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