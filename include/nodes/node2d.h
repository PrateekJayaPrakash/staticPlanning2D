#include<vector>

using namespace std;

class node2d{
    public:
        int obstacle,start,goal;
        
        int x,y,cost;

        vector<node2d*> neighbors;
        node2d* parent;
        node2d();
        node2d(int,int);

};

