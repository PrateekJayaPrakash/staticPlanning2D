#include<vector>
#include <nodes/node2d.h>
#include <memory>

using namespace std;

class Grid2dSolver{
    private:
        int obstacle,start,goal;
        int x,y,cost;
        void recursiveDFS(
            node2d& startNode,
            const node2d& endNode,
            vector<vector<int>>& path
        );

    public:        
        int solve();
        Grid2dSolver(){}

        //vector<int> astarSolve(
         //   vector<vector<node2d*>> searchMap,
          //  std::shared_ptr<node2d> startNode,
        // std::shared_ptr<node2d> endNode);

        vector<vector<int>> DfsSolve(
            node2d& startNode,
            node2d& endNode);
        
        vector<vector<int>> iterativeDfs(
            node2d& startNode,
            node2d& endNode);
        
        vector<vector<int>> iterativeBfs(
            node2d& startNode,
            node2d& endNode);
};