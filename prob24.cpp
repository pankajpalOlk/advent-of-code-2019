//
//  main.cpp
//  advent
//
//  Created by pankaj pal on 1/1/20.
//  Copyright © 2019 pankaj pal. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <set>
#include <sstream>

using namespace std;

static int numRows = 5;
static int numCols = 5;

static vector<int> directionX{-1, 0 ,0, 1};
static vector<int> directionY{0, -1, 1, 0};

bool isValid(int x, int y) {
    return x >= 0 && y >= 0 && x < numRows && y < numCols;
}

class Grid {
public:

    Grid() {}

    Grid(int val)
    {
        this->_value = val;
    }

    void Set(int row, int col, char val)
    {
        if (isValid(row, col))
        {
            if (val == '#')
                _value |= (1u << (row*numCols + col));
            else
                _value &= ~(1u << (row*numCols + col));
        }
    }

    bool Get(int row, int col) const
    {
        if (isValid(row, col)) {
            return (_value & (1u << (row*numCols + col))) != 0;
        }

        return false;
    }

    void SimultateOneTimeTick(const Grid& from)
    {
        for (int r = 0; r < numRows; r++)
        {
            for (int c = 0; c < numCols; c++)
            {
                bool isBug = from.Get(r, c);
                int numAdjacentBugs = 0;

                // Try all 4 neighbours
                numAdjacentBugs += from.Get(r-1, c) ? 1 : 0;
                numAdjacentBugs += from.Get(r+1, c) ? 1 : 0;
                numAdjacentBugs += from.Get(r, c-1) ? 1 : 0;
                numAdjacentBugs += from.Get(r, c+1) ? 1 : 0;

                if (isBug && numAdjacentBugs != 1)
                {
                    Set(r, c, '.');
                }

                if (!isBug && (numAdjacentBugs ==1 || numAdjacentBugs == 2))
                {
                    Set(r, c, '#');
                }
            }
        }
    }

    uint32_t GetValue()
    {
        return _value;
    }

private:
    uint32_t _value = 0;
};

void Problem1(Grid& grid)
{
    set<uint32_t> visited;

    while (true)
    {
        if (visited.find(grid.GetValue()) != visited.end())
        {
            break;
        }

        Grid temp = grid;
        visited.insert(temp.GetValue());
        grid.SimultateOneTimeTick(temp);
    }

    cout << "Problem1: " << grid.GetValue() << endl;
}

void Problem2(Grid& grid)
{
    int minutes = 200;
    vector<Grid> levels;

    Grid levelGrid(0);

    for (int i = 0; i <= minutes; i++)
    {
        levels.push_back(levelGrid);
    }
    levels.push_back(grid);
    for (int i = 0; i <= minutes; i++)
    {
        levels.push_back(levelGrid);
    }

    int lowLevel = minutes, highLevel = minutes + 2;
    Grid currGrid;
    vector<Grid> currLevels (levels);

    for (int i = 1; i <= minutes; i++)
    {
        for (int lvl = lowLevel; lvl <= highLevel; lvl++)
        {
            currGrid = levels[lvl];

            for (int r = 0; r < numRows; r++)
            {
                for (int c = 0; c < numCols; c++)
                {
                    if (r == 2 && c == 2)
                        continue;

                    bool isBug = levels[lvl].Get(r, c);
                    int numAdjacentBugs = 0;

                    // Try all neighbours
                    for (int d = 0; d < 4; d++)
                    {
                        if (isValid(r + directionX[d], c + directionY[d]))
                        {
                            if ((r + directionX[d] == 2) && (c + directionY[d] == 2))
                            {
                                if (d == 0)
                                {
                                    // count bugs from upper sub matrix
                                    for (int s = 0; s < 5; s++)
                                    {
                                        numAdjacentBugs += levels[lvl+1].Get(4, s) ? 1 : 0;
                                    }
                                }

                                if (d == 1)
                                {
                                    // count bugs from left sub matrix
                                    for (int s = 0; s < 5; s++)
                                    {
                                        numAdjacentBugs += levels[lvl+1].Get(s, 4) ? 1 : 0;
                                    }
                                }

                                if (d == 2)
                                {
                                    // count bugs from lower sub matrix
                                    for (int s = 0; s < 5; s++)
                                    {
                                        numAdjacentBugs += levels[lvl+1].Get(s, 0) ? 1 : 0;
                                    }
                                }

                                if (d == 3)
                                {
                                    // count bugs from right sub matrix
                                    for (int s = 0; s < 5; s++)
                                    {
                                        numAdjacentBugs += levels[lvl+1].Get(0, s) ? 1 : 0;
                                    }
                                }
                            }
                            else
                            {
                                numAdjacentBugs += levels[lvl].Get(r+directionX[d], c+directionY[d]) ? 1 : 0;
                            }
                        }
                        else
                        {
                            // Check from the super matrix
                            if (levels[lvl-1].Get(2+directionX[d], 2+directionY[d]))
                            {
                                numAdjacentBugs++;
                            }
                        }
                    }


                    if (isBug && numAdjacentBugs != 1)
                    {
                        currGrid.Set(r, c, '.');
                    }

                    if (!isBug && (numAdjacentBugs ==1 || numAdjacentBugs == 2))
                    {
                        currGrid.Set(r, c, '#');
                    }
                }
            }

            currLevels[lvl] = currGrid;
        }

        lowLevel--;
        highLevel++;
        levels = currLevels;
    }

    uint32_t bugs = 0;
    for (auto l : levels)
    {
        bugs += __builtin_popcount(l.GetValue());
    }

    cout << "Problem2: " << bugs << endl;
}

int main()
{
    fstream in("prob24_input.txt");
    string line;

    int row = 0;
    Grid grid1;
    Grid grid2;
    while (getline(in, line))
    {
        for (int col = 0; col < numCols; col++)
        {
            grid1.Set(row, col, line[col]);

            if (col == 2 && row == 2)
            {
                grid2.Set(row, col, '?');
            }
            else
            {
                grid2.Set(row, col, line[col]);
            }

        }
        row++;
    }

    Problem1(grid1);
    Problem2(grid2);

    return 0;
}
