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
#include <map>

using namespace std;

static int directionX[4] = {-1, 0, 0, 1};
static int directionY[4] = {0, -1, 1, 0};

struct Point {
    int x = 0, y = 0;
    int depth = 0;
    int level = 0;

    Point() {}

    Point(int x, int y, int depth) {
        this->x = x;
        this->y = y;
        this->depth = depth;
    }

    Point(int x, int y, int depth, int level) {
        this->x = x;
        this->y = y;
        this->depth = depth;
        this->level = level;
    }

    bool operator == (const Point& rhs) const
    {
        return ((this->x == rhs.x) && (this->y == rhs.y));
    }

    bool operator < (const Point& rhs) const
    {
        if (this->x == rhs.x)
            return this->y < rhs.y;

        return this->x < rhs.x;
    }
};

bool isValid(int x, int y, size_t rows, size_t cols) {
    return x >= 0 && y >= 0 && x < rows && y < cols;
}

bool isInner(int x, int y, size_t rows, size_t cols)
{
    return (x > 3 && y > 3 && x < rows-3 && y < cols-3);
}

void ParseInput(std::fstream& in, std::vector<std::vector<char>>& grid)
{
    std::string line;
    std::vector<char> vertices;

    while (std::getline(in, line)) {
        for (int i = 0; i < line.size(); i++) {
            vertices.push_back(line[i]);
        }

        grid.push_back(vertices);
        vertices.clear();
    }
}

void PopulatePortals(const std::vector<std::vector<char>>& grid, std::map<std::string, std::vector<Point>>& portals)
{
    std::string portalStr;
    Point portalPos;

    for (int r = 0; r < grid.size(); r++)
    {
        for (int c = 0; c < grid[0].size(); c++)
        {
            if (isupper(grid[r][c]))
            {
                if (isValid(r, c-1, grid.size(), grid[0].size())
                    && grid[r][c-1] == '.')
                {
                    char name[3] = {grid[r][c], grid[r][c+1], '\0'};
                    if (portals.find(name) != portals.end()) {
                        auto points = portals[name];
                        points.push_back(Point(r, c-1, 0));
                        portals[name] = points;
                    } else {
                        std::vector<Point> vec;
                        vec.push_back(Point(r, c-1, 0));
                        portals[name] = vec;
                    }
                }

                if (isValid(r, c+1, grid.size(), grid[0].size())
                    && grid[r][c+1] == '.')
                {
                    char name[3] = {grid[r][c-1], grid[r][c], '\0'};
                    if (portals.find(name) != portals.end()) {
                        auto points = portals[name];
                        points.push_back(Point(r, c+1, 0));
                        portals[name] = points;
                    } else {
                        std::vector<Point> vec;
                        vec.push_back(Point(r, c+1, 0));
                        portals[name] = vec;
                    }
                }

                if (isValid(r-1, c, grid.size(), grid[0].size())
                    && grid[r-1][c] == '.')
                {
                    char name[3] = {grid[r][c], grid[r+1][c], '\0'};
                    if (portals.find(name) != portals.end()) {
                        auto points = portals[name];
                        points.push_back(Point(r-1, c, 0));
                        portals[name] = points;
                    } else {
                        std::vector<Point> vec;
                        vec.push_back(Point(r-1, c, 0));
                        portals[name] = vec;
                    }
                }

                if (isValid(r+1, c, grid.size(), grid[0].size())
                    && grid[r+1][c] == '.')
                {
                    char name[3] = {grid[r-1][c], grid[r][c], '\0'};
                    if (portals.find(name) != portals.end()) {
                        auto points = portals[name];
                        points.push_back(Point(r+1, c, 0));
                        portals[name] = points;
                    } else {
                        std::vector<Point> vec;
                        vec.push_back(Point(r+1, c, 0));
                        portals[name] = vec;
                    }
                }
            }
        }
    }
}

int BFS(const std::vector<std::vector<char>>& grid, const map<Point, Point>& portalMap, const Point& start, const Point& finish)
{
    vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size()));
    queue<Point> queue;
    Point curr;

    queue.push(start);
    visited[start.x][start.y] = true;

    while (!queue.empty())
    {
        curr = queue.front();
        queue.pop();

        if (curr == finish)
        {
            return curr.depth;
        }

        for (int i = 0; i < 4; i++)
        {
            int x = curr.x + directionX[i];
            int y = curr.y + directionY[i];

            if (!isValid(x, y, grid.size(), grid[0].size()) || visited[x][y] || (grid[x][y] == '#'))
            {
                continue;
            }

            if (grid[x][y] == '.')
            {
                queue.push(Point(x, y, curr.depth+1));
                visited[x][y] = true;
            }
        }

        Point pointToSearch(curr.x, curr.y, 0);
        if (portalMap.find(pointToSearch) != portalMap.end())
        {
            Point _point = portalMap.at(pointToSearch);
            queue.push(Point(_point.x, _point.y, curr.depth+1));
            visited[_point.x][_point.y] = true;
        }
    }

    return 0;
}

void Problem1(const std::vector<std::vector<char>>& grid, std::map<std::string, std::vector<Point>>& portals)
{
    Point start = portals["AA"][0];
    Point finish = portals["ZZ"][0];

    map<Point, Point> portalMap;

    for (auto portal : portals)
    {
        if (portal.first == "AA" || portal.first == "ZZ")
            continue;

        Point p1 = portal.second[0];
        Point p2 = portal.second[1];

        portalMap[p1] = p2;
        portalMap[p2] = p1;
    }

    cout << "Problem1 : " << BFS(grid, portalMap, start, finish) << endl;
}

int BFS2(const std::vector<std::vector<char>>& grid, const map<Point, Point>& portalMap, const Point& start, const Point& finish)
{
    vector<vector<vector<bool>>> visited(500, vector<vector<bool>>(500, vector<bool>(500)));
    queue<Point> queue;
    Point curr;

    queue.push(start);
    visited[start.level][start.x][start.y] = true;

    while (!queue.empty())
    {
        curr = queue.front();
        queue.pop();

        if (curr == finish && curr.level == finish.level)
        {
            return curr.depth;
        }

        for (int i = 0; i < 4; i++)
        {
            int x = curr.x + directionX[i];
            int y = curr.y + directionY[i];

            if (!isValid(x, y, grid.size(), grid[0].size()) || visited[curr.level][x][y] || (grid[x][y] == '#'))
            {
                continue;
            }

            if (grid[x][y] == '.')
            {
                queue.push(Point(x, y, curr.depth+1, curr.level));
                visited[curr.level][x][y] = true;
            }
        }

        Point pointToSearch(curr.x, curr.y, 0);
        if (portalMap.find(pointToSearch) != portalMap.end())
        {
            Point _point = portalMap.at(pointToSearch);

            if (isInner(curr.x, curr.y, grid.size(), grid[0].size()))
            {
                queue.push(Point(_point.x, _point.y, curr.depth+1, curr.level+1));
                visited[curr.level+1][_point.x][_point.y] = true;
            }
            else
            {
                if (curr.level - 1 >= 0) {
                    queue.push(Point(_point.x, _point.y, curr.depth+1, curr.level-1));
                    visited[curr.level-1][_point.x][_point.y] = true;
                }
            }
        }
    }

    return 0;
}

void Problem2(const std::vector<std::vector<char>>& grid, std::map<std::string, std::vector<Point>>& portals)
{
    Point start = portals["AA"][0];
    Point finish = portals["ZZ"][0];

    map<Point, Point> portalMap;

    for (auto portal : portals)
    {
        if (portal.first == "AA" || portal.first == "ZZ")
            continue;

        Point p1 = portal.second[0];
        Point p2 = portal.second[1];

        portalMap[p1] = p2;
        portalMap[p2] = p1;
    }

    cout << "Problem2 : " << BFS2(grid, portalMap, start, finish) << endl;
}

int main()
{
    std::fstream in("prob20_input.txt", std::fstream::in);
    std::vector<std::vector<char>> grid;
    std::map<std::string, std::vector<Point>> portals;

    ParseInput(in, grid);
    PopulatePortals(grid, portals);

    Problem1(grid, portals);
    Problem2(grid, portals);

    in.close();
}
