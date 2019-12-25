//
//  main.cpp
//  advent
//
//  Created by pankaj pal on 25/12/19.
//  Copyright © 2019 pankaj pal. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <tuple>
#include <set>

struct Point {
    int x = 0, y = 0;
    int depth = 0;
    long long visitedMask = 0;

    Point() {}
    Point(int x, int y, int depth, long long mask) {
        this->x = x;
        this->y = y;
        this->depth = depth;
        this->visitedMask = mask;
    }
};

void ParseInput(std::fstream& in, std::vector<std::vector<char>>& grid, Point& startingPoint)
{
    std::string line;
    std::vector<char> vertices;

    while (std::getline(in, line)) {
        for (int i = 0; i < line.size(); i++) {
            if (line[i] == '@') {
                startingPoint.x = (int)grid.size();
                startingPoint.y = i;
                vertices[i] = '.';
            }
            vertices.push_back(line[i]);
        }

        grid.push_back(vertices);
        vertices.clear();
    }

    for (auto r : grid) {
        for (auto c : r) {
            std::cout << c;
        }
        std::cout << std::endl;
    }
}

bool isValid(int x, int y, int rows, int cols) {
    return x >= 0 && y >= 0 && x < rows && y < cols;
}

int BFS(const std::vector<std::vector<char>>& grid, const Point& startPoint)
{
    std::queue<Point> queue;
    Point curr;
    std::bitset<26> visited;
    std::vector<int> directionX {-1, 0, 0, 1};
    std::vector<int> directionY {0,  -1, 1, 0};
    std::set<std::tuple<int, int, long long>> keyCollected;

    queue.push(startPoint);

    while (!queue.empty()) {
        curr = queue.front();
        queue.pop();
        visited = curr.visitedMask;

        if (visited.all()) {
            // If all are visited
            return curr.depth;
        }

        // Try all directions
        for (int i = 0; i < 4; i++) {
            if (!isValid(curr.x, curr.y, (int)grid.size(), (int)grid[0].size())
                || (grid[curr.x+directionX[i]][curr.y+directionY[i]] == '#')
                || keyCollected.find(std::make_tuple(curr.x+directionX[i], curr.y+directionY[i], curr.visitedMask)) != keyCollected.end())
            {
                continue;
            }

            if (isupper(grid[curr.x+directionX[i]][curr.y+directionY[i]])
                && (!visited[grid[curr.x+directionX[i]][curr.y+directionY[i]] - 'A']))
            {
                continue;
            }

            if (islower(grid[curr.x+directionX[i]][curr.y+directionY[i]]))
            {
                visited[grid[curr.x+directionX[i]][curr.y+directionY[i]] - 'a'] = true;
            }

            queue.push(Point(curr.x+directionX[i], curr.y+directionY[i], curr.depth+1, visited.to_ullong()));
            keyCollected.insert(std::make_tuple(curr.x+directionX[i], curr.y+directionY[i], visited.to_ullong()));

            if (islower(grid[curr.x+directionX[i]][curr.y+directionY[i]]))
            {
                visited[grid[curr.x+directionX[i]][curr.y+directionY[i]] - 'a'] = false;
            }
        }
    }

    return 0;
}

// Found this awesome explanation on reddit: https://www.reddit.com/r/adventofcode/comments/ednz2o/2019_day_18_for_dummies/
//Basically it is the shortest path finding problem.
//
//You are moving from starting point to first key, then to another key, then next ... etc, until you collected them all. Each key need to pick up only one once. So: your path can be represented as collection of keys in the order in which they are need to be picked up.
//
//All other points of the maze are irreverent, they just a step on path to a key. Because of it is good to create a simpler map (graph if you prefer): for each key (and starting point) find the length of shortest paths (yes, only the number of steps on it, the path it self is irreverent) from it to all others keys.
//
//But we have also doors. So on our path from point x (which can be start position or a key location) to the key y you also need to remember all passed doors. And use them latter to limiting our possibilities in moving from some key.
//
//The maze guaranty that is the only one path (and the doors set) from point to point.
//
//So you will end up with a graph. In which all nodes will be keys (and starting position). Each node will connected to all other nodes. The vertex will be a the shortest joining path length and the set of doors on the path (a.k.a.: the keys require to follow that path).
//
//Let's say you will decide to use the Dijkstra algorithm for finding the quickest permutation of keys. The ending will picking up the last key. As neighbor nodes you will be check all not visited keys which you can reach (mean: you already picked up all keys need to open all doors on the way to it). Because we move from key to key it is not possible to omit the path where you pick up key along the way (the path like that will be spited, so don't worry about that).
//
//Real problem of this task is optimization: the simple searching will take too long (the example with 136 steps as result and task input is too complicated). But I suggest to leave this problem until you will have working code which can handle two given examples.
void Problem1(const std::vector<std::vector<char>>& grid, const Point& startPoint)
{
    std::cout << "Problem1: " << BFS(grid, startPoint) << std::endl;
}

void Problem2(std::vector<std::vector<char>>& grid, const Point& startPoint)
{
    /*
     Change

     ...
     .@.
     ...

     TO

     @#@
     ###
     @#@

    */

    grid[startPoint.x][startPoint.y] = '#';
    grid[startPoint.x-1][startPoint.y] = '#';
    grid[startPoint.x+1][startPoint.y] = '#';
    grid[startPoint.x][startPoint.y-1] = '#';
    grid[startPoint.x][startPoint.y+1] = '#';
    grid[startPoint.x-1][startPoint.y-1] = '@';
    grid[startPoint.x+1][startPoint.y+1] = '@';
    grid[startPoint.x-1][startPoint.y+1] = '@';
    grid[startPoint.x+1][startPoint.y-1] = '@';

    // Now there are multiple start points.
    std::vector<Point> startPoints;
    startPoints.push_back(Point(startPoint.x-1, startPoint.y-1, 0, 0));
    startPoints.push_back(Point(startPoint.x-1, startPoint.y+1, 0, 0));
    startPoints.push_back(Point(startPoint.x+1, startPoint.y-1, 0, 0));
    startPoints.push_back(Point(startPoint.x+1, startPoint.y+1, 0, 0));

    std::vector<std::bitset<26>> visited(4);

    // for each quadrant, Mark chars in visited as true as they will not be
    // accounting for the BFS traversal
    for (int r = 0; r < grid.size(); r++) {
        for (int c = 0; c < grid[0].size(); c++) {
            if (islower(grid[r][c])) {
                visited[0][grid[r][c]-'a'] = !((r <= startPoints[0].x) && (c <= startPoints[0].y) );
                visited[1][grid[r][c]-'a'] = !((r <= startPoints[1].x) && (c >= startPoints[1].y) );
                visited[2][grid[r][c]-'a'] = !((r >= startPoints[2].x) && (c <= startPoints[2].y) );
                visited[3][grid[r][c]-'a'] = !((r >= startPoints[3].x) && (c >= startPoints[3].y) );
            }
        }
    }

    int minSteps = 0;
    // Run for all 4 robots
    for (int i = 0; i < 4; i++)
    {
        startPoints[i].visitedMask = visited[i].to_ullong();
        minSteps += BFS(grid, startPoints[i]);
    }

    std::cout << "Problem2: " << minSteps << std::endl;
}

int main()
{
    std::fstream in("/Users/pankajpal/advent/input.txt", std::fstream::in);
    std::vector<std::vector<char>> grid;
    Point startPoint;

    ParseInput(in, grid, startPoint);

    Problem1(grid, startPoint);

    Problem2(grid, startPoint);

    in.close();
}
