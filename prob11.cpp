//
//  main.cpp
//  advent
//
//  Created by pankaj pal on 03/12/19.
//  Copyright © 2019 pankaj pal. All rights reserved.
//

#include <iostream>
#include <vector>
#include <map>
#include <sstream>
using namespace std;

class Computer{
public:
    long result;
    long i = 0;
    bool done = false;
    vector<long> vect;
    long relativeAddress = 0;
    vector<long> inputs;

    void setInput(long input) {
        inputs.push_back(input);
    }

    long calculate()
    {
        while(true) {
            long token = vect[i];

            long opcode = token % 100;

            long x = 0, y = 0, z = 0;
            if ((token/100) % 10 == 0) {
                x = vect[i+1];
            } else if ((token/100)%10 == 2) {
                x = vect[i+1] + relativeAddress;
            } else {
                x = i+1;
            }

            if ((token/1000) % 10 == 0) {
                y = vect[i+2];
            } else if ((token/1000)%10 == 2) {
                y = vect[i+2] + relativeAddress;
            } else {
                y = i+2;
            }

            if ((token/10000) % 10 == 0) {
                z = vect[i+3];
            } else if ((token/10000)%10 == 2) {
                z = vect[i+3] + relativeAddress;
            } else {
                z = i+3;
            }

            switch (opcode) {
                case 1:
                    vect[z] = vect[x] + vect[y];
                    i += 4;
                    break;
                case 2:
                    vect[z] = vect[x] * vect[y];
                    i += 4;
                    break;
                case 3:
                    vect[x] = inputs[0];
                    inputs.erase(inputs.begin());
                    i += 2;
                    break;
                case 4:
                    result = vect[x];
                    i += 2;
                    return result;
                case 5:
                    if (vect[x] != 0)
                        i = vect[y];
                    else
                        i += 3;
                    break;
                case 6:
                    if (vect[x] == 0)
                        i = vect[y];
                    else
                        i += 3;
                    break;
                case 7:
                    vect[z] = (vect[x] < vect[y]) ? 1 : 0;
                    i += 4;
                    break;
                case 8:
                    vect[z] = (vect[x] == vect[y]) ? 1 : 0;
                    i += 4;
                    break;
                case 9:
                    relativeAddress += vect[x];
                    i += 2;
                    break;
                case 99:
                    done = true;
                    return result;
            }
        }

        return result;
    }
};

class Robot{
public:
    Computer computer;
    int direction = 0; // 0 - UP, 1 - RIGHT, 2 - DWON, 3 - LEFT
    int x = 0;
    int y = 0;
    int startColor;
    map<pair<int,int>, long> grid;

    Robot(vector<long> inputs, int startColor) {
        vector<int> extravals(3000,0);
        inputs.insert(inputs.end(), extravals.begin(), extravals.end());
        computer.vect = inputs;
        grid[make_pair(0, 0)] = startColor;
        this->startColor = startColor;
    }

    void run()
    {
        while(!computer.done) {
            long color = 0;
            if (grid.find(make_pair(x, y)) != grid.end()) {
                color = grid.at(make_pair(x, y));
            }

            computer.setInput(color);
            grid[make_pair(x, y)] = computer.calculate();
            changeDirection(computer.calculate());
            changePosition();
        }
    }

    void paint()
    {
        int minx = 0x0fffff, miny = 0x0ffffff, maxx = 0xffffffff, maxy = 0xffffffff;

        for (const auto& indexes : grid) {
            minx = (indexes.first.first < minx) ? indexes.first.first : minx;
            miny = (indexes.first.second < miny) ? indexes.first.second : miny;
            maxx = (indexes.first.first > maxx) ? indexes.first.first : maxx;
            maxy = (indexes.first.second > maxy) ? indexes.first.second : maxy;
        }

        vector<string> result;
        for (long i = miny; i < maxy+1; i++) {
            string row;
            for (long j = minx; j < maxx+1; j++) {
                long color = (grid.find(make_pair(j, i)) != grid.end()) ? grid.at(make_pair(j, i)) : 0;
                row.append(color == 1 ? "#" : " ");
            }
            result.insert(result.begin(), row);
        }

        cout<< "Problem2:"<<endl;
        for (auto res : result) {
            cout << res << endl;
        }

    }

private:
    void changeDirection(long dir)
    {
        // Left
        if (dir == 0) {
            if (direction == 0) direction = 3;
            else direction = (direction - 1)%4;
        } else {
            direction = (direction + 1)%4;
        }
    }

    void changePosition()
    {
        if (direction == 0) {
            y += 1;
        } else if (direction == 1) {
            x += 1;
        } else if (direction == 2) {
            y -= 1;
        } else {
            x -= 1;
        }
    }

};

int main(int argc, const char * argv[]) {
    string input = "3,8,1005,8,310,1106,0,11,0,0,0,104,1,104,0,3,8,102,-1,8,10,1001,10,1,10,4,10,108,1,8,10,4,10,1002,8,1,28,1,105,11,10,3,8,102,-1,8,10,1001,10,1,10,4,10,1008,8,0,10,4,10,102,1,8,55,3,8,102,-1,8,10,1001,10,1,10,4,10,108,0,8,10,4,10,1001,8,0,76,3,8,1002,8,-1,10,101,1,10,10,4,10,108,0,8,10,4,10,102,1,8,98,1,1004,7,10,1006,0,60,3,8,102,-1,8,10,1001,10,1,10,4,10,108,0,8,10,4,10,1002,8,1,127,2,1102,4,10,1,1108,7,10,2,1102,4,10,2,101,18,10,3,8,1002,8,-1,10,1001,10,1,10,4,10,1008,8,0,10,4,10,102,1,8,166,1006,0,28,3,8,1002,8,-1,10,101,1,10,10,4,10,108,1,8,10,4,10,101,0,8,190,1006,0,91,1,1108,5,10,3,8,1002,8,-1,10,101,1,10,10,4,10,1008,8,1,10,4,10,1002,8,1,220,1,1009,14,10,2,1103,19,10,2,1102,9,10,2,1007,4,10,3,8,1002,8,-1,10,101,1,10,10,4,10,1008,8,1,10,4,10,101,0,8,258,2,3,0,10,1006,0,4,3,8,102,-1,8,10,1001,10,1,10,4,10,108,1,8,10,4,10,1001,8,0,286,1006,0,82,101,1,9,9,1007,9,1057,10,1005,10,15,99,109,632,104,0,104,1,21102,1,838479487636,1,21102,327,1,0,1106,0,431,21102,1,932813579156,1,21102,1,338,0,1106,0,431,3,10,104,0,104,1,3,10,104,0,104,0,3,10,104,0,104,1,3,10,104,0,104,1,3,10,104,0,104,0,3,10,104,0,104,1,21101,0,179318033447,1,21101,385,0,0,1105,1,431,21101,248037678275,0,1,21101,0,396,0,1105,1,431,3,10,104,0,104,0,3,10,104,0,104,0,21101,0,709496558348,1,21102,419,1,0,1105,1,431,21101,825544561408,0,1,21101,0,430,0,1106,0,431,99,109,2,22101,0,-1,1,21101,40,0,2,21102,462,1,3,21101,0,452,0,1106,0,495,109,-2,2105,1,0,0,1,0,0,1,109,2,3,10,204,-1,1001,457,458,473,4,0,1001,457,1,457,108,4,457,10,1006,10,489,1101,0,0,457,109,-2,2106,0,0,0,109,4,2101,0,-1,494,1207,-3,0,10,1006,10,512,21101,0,0,-3,22101,0,-3,1,22101,0,-2,2,21101,1,0,3,21102,531,1,0,1105,1,536,109,-4,2105,1,0,109,5,1207,-3,1,10,1006,10,559,2207,-4,-2,10,1006,10,559,22101,0,-4,-4,1106,0,627,21202,-4,1,1,21201,-3,-1,2,21202,-2,2,3,21102,578,1,0,1105,1,536,22101,0,1,-4,21101,1,0,-1,2207,-4,-2,10,1006,10,597,21102,0,1,-1,22202,-2,-1,-2,2107,0,-3,10,1006,10,619,21201,-1,0,1,21102,1,619,0,105,1,494,21202,-2,-1,-2,22201,-4,-2,-4,109,-5,2106,0,0";

    vector<long> vect;
    stringstream ss(input);

    for (long i; ss >> i;) {
        vect.push_back(i);
        if (ss.peek() == ',')
            ss.ignore();
    }

    Robot robot1(vect, 0);
    robot1.run();

    cout << "Problem1:" << robot1.grid.size() << endl;

    Robot robot2(vect, 1);
    robot2.run();
    robot2.paint();

    return 0;
}


