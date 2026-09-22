#include <bits/stdc++.h> 

using namespace std;

const int NO_VALUE = -1; 
const char WALL = '1';
const char LEFT = 'l'; 
const char RIGHT = 'r';
const char DOWN = 'd';
const char UP = 'u'; 

struct Point {
    Point(){
        row = NO_VALUE; 
        col = NO_VALUE;
    }
    Point(int _row, int _col){
        row = _row; 
        col = _col; 
    }
    bool operator==(const Point& other) const {
        return row == other.row && col == other.col;
    }
    bool is_valid(int n, int m){
        return 0 <= row && row < n && 0 <= col && col < m; 
    }
    int row, col; 
};

void find_minimum_path(int n, int m, vector <string> &grid, Point currentPoint, Point &endPoint, vector <char> &currentPath, vector <char> &minimumPath, vector <vector<bool>> &visit){
    if (currentPoint == endPoint){
        if (minimumPath.empty() || minimumPath.size() > currentPath.size()){
            minimumPath = currentPath; 
        }
        return; 
    }
    int deltaRow[4] = {1, -1, 0, 0};
    int deltaCol[4] = {0, 0, 1, -1};
    char direction[4] = {DOWN, UP, RIGHT, LEFT};
    for (int i = 0; i < 4; i++){
        Point adjacentPoint(currentPoint.row + deltaRow[i], currentPoint.col + deltaCol[i]); 
        if (adjacentPoint.is_valid(n, m) && !visit[adjacentPoint.row][adjacentPoint.col] && grid[adjacentPoint.row][adjacentPoint.col] != WALL){
            currentPath.push_back(direction[i]);
            visit[adjacentPoint.row][adjacentPoint.col] = true; 
            find_minimum_path(n, m, grid, adjacentPoint, endPoint, currentPath, minimumPath, visit);
            currentPath.pop_back();
            visit[adjacentPoint.row][adjacentPoint.col] = false; 
        }
    }
}

int main() {
    int n, m; 
    cin >> n >> m; 
    vector <string> grid(n, string("")); 
    vector <vector<bool>> visit(n, vector<bool>(m, false));
    vector <char> currentPath, minimumPath; 
    for (int i = 0; i < n; i++){
        cin >> grid[i];
    }
    Point startPoint, endPoint, currentPoint;
    for (int row = 0; row < n; row++){
        for (int col = 0; col < m; col++){
            if (grid[row][col] == 'S')
                startPoint = Point(row, col);
            if (grid[row][col] == 'M')
                endPoint = Point(row, col);
        }
    }
    find_minimum_path(n, m, grid, startPoint, endPoint, currentPath, minimumPath, visit); 

    for (auto direction : minimumPath){
        cout << direction; 
    }

    if (minimumPath.empty())
    {
        std::cout << "NO_PATH" << std::endl;
    }
    
    return 0;
}
