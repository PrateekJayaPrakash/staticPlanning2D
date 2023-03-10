#include <iostream>
#include <vector>
#include <memory>
#include <nodes/node2d.h>
#include <plot/pbPlots.hpp>
#include <plot/supportLib.hpp>
#include <queue>
#include <unordered_map>



using namespace std;


typedef pair<int, node2d*> nodeInfo; 

class Grid{
    public:
        int gridWidth, gridHeight;
        node2d* startNode;
        node2d* endNode;
        std::vector<vector<node2d*>> map;

        Grid(int, int);
        void updateObstacles();
        void setStartGoal(vector<int>, vector<int>);
        vector<node2d*> aStarPath();
        void printPath();
};

Grid::Grid(int gridWidth, int gridHeight){
    this->gridWidth = gridWidth;
    this->gridHeight = gridHeight;
    //this->map = vector<vector<node2d*>>(this->gridWidth, vector<node2d*>(this->gridHeight));

    this->map.resize(this->gridWidth, vector<node2d*>(this->gridHeight));
    
    /* Create nodes */
    for (int i = 0; i < this->gridWidth; i++){

        for(int j = 0; j < this->gridHeight; j++){

            this->map[j][i] = new node2d(i, j);
        }
    }

    /* Update neighbors */
    for(int i = 0; i < this->gridWidth; i++){

        for(int j = 0; j < this->gridHeight; j++){

            if (j < this -> gridHeight - 1) {
				this -> map[j][i]->neighbors.push_back(map[j + 1][i]);
			}
			if (i < this -> gridWidth - 1) {
				this -> map[j][i]->neighbors.push_back(map[j][i + 1]);
			}
			if (j > 0) {
				this -> map[j][i]->neighbors.push_back(map[j - 1][i]);
			}
			if (i > 0) {
				this -> map[j][i]->neighbors.push_back(map[j][i - 1]);
			}
        }
    }

    /* Update obstacles */
    this -> updateObstacles();   
}

void Grid::updateObstacles(){
    vector<int> obsX = {1, 2, 3, 4, 5, 5, 6, 7, 8};
    vector<int> obsY = {1, 2, 1, 1, 1, 4, 1, 1, 1};
    for(int i = 0; i < obsX.size(); i++){
        this -> map[obsY[i]][obsX[i]] -> obstacle = 1;
    }
}

void Grid::setStartGoal(vector<int> st, vector<int> gl){
    this->map[st[1]][st[0]] -> start = 1;
    this->map[gl[1]][gl[0]] -> goal = 1;    
}

void Grid::aStarPath(){
    
}

void Grid::printPath(){
    for (int i = this-> gridWidth - 1; i >=0; i--){
        for(int j = 0; j < this->gridHeight; j++){
            cout<< this->map[i][j]->obstacle << " ";
        }
        cout << endl;
    }
}

bool PlotPNG(vector<double> xs, vector<double> ys){
    bool success;
    StringReference *errorMessage = new StringReference();
	RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();

    RGBA *clr = CreateRGBAColor(1.0, 2.0, 1.0, 1.0);

	success = DrawScatterPlot(imageReference, 600, 400, &xs, &ys, errorMessage);
    //DrawPixel(imageReference, 10, 10, clr);

    //success = false;
    if(success){
        vector<double> *pngdata = ConvertToPNG(imageReference->image);
        WriteToFile(pngdata, "example1.png");
        DeleteImage(imageReference->image);
	}else{
	    cerr << "Error: ";
        for(wchar_t c : *errorMessage->string){
            wcerr << c;
        }
        cerr << endl;
    }
    return success;
}

int main()
{
    /* Initialize Variables */
    int width = 10;
    int height = 10;

    /* Create grid */
    Grid gd(width, height);
    gd.setStartGoal({0,0}, {6,6});
    gd.printPath();

    /* Plotting example */
    //vector<double> xs{-2, -1, 0, 1, 2};
	//vector<double> ys{2, -1, -2, -1, 2};
    //bool success = PlotPNG(xs, ys);   
    
    return 0;
}