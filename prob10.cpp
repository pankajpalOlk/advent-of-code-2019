//
//  main.cpp
//  advent
//
//  Created by pankaj pal on 03/12/19.
//  Copyright © 2019 pankaj pal. All rights reserved.
//

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <sstream>
#include <fstream>
#include <cmath>
using namespace std;

int modulomethod(int x, int n)
{
    return ((x % n) + n) % n;
}

double angle(int px, int py, int qx, int qy)
{
    return atan2(py-qy, px-qx);
}

double angleInDegree(int px, int py, int qx, int qy)
{
    double rad = atan2(py-qy, px-qx);
    double deg = (rad * 180)/3.141592653589793238463;

    deg += 90;
    if (deg < 0)
        deg += 360;

    return deg;
}

int distance(int px, int py, int qx, int qy)
{
    return ((px - qx)*(px-qx)) + ((py - qy)*(py-qy));
}

void problem2(const vector<pair<int, int>>& asteroids, int stationX, int stationY)
{
    cout << stationX << "," << stationY << endl;
    map<double, pair<int, int>> angles;

    for (auto const& asteroid : asteroids) {
        if (stationX == asteroid.first && stationY == asteroid.second) {
            continue;
        }

        double angleWithStation = angleInDegree(asteroid.first, asteroid.second, stationX, stationY);

        int dist = 0x0fffffff;
        if (angles.find(angleWithStation) != angles.end()) {
            if (distance(stationX, stationY, asteroid.first, asteroid.second) < dist) {
                angles[angleWithStation] = std::make_pair(asteroid.first, asteroid.second);
                dist = distance(stationX, stationY, asteroid.first, asteroid.second);
            }
        } else {
            angles[angleWithStation] = std::make_pair(asteroid.first, asteroid.second);
        }
    }

    int i = 1;
    for (auto const& keyVal : angles) {
        if (i == 200)
            cout << keyVal.second.first*100+keyVal.second.second << endl;

        i++;
    }

}

int problem1(const vector<pair<int, int>>& asteroids, int& stationX, int& stationY)
{
    int max = 0;
    int posx = 0, posy = 0;
    for (auto const& asteroid :  asteroids) {
        set<double> angles;
        for (auto const& other : asteroids) {
            if (other.first == asteroid.first && other.second == asteroid.second) {
                continue;
            }

            angles.insert(angle(asteroid.first, asteroid.second, other.first, other.second));
        }

        int count = (int)angles.size();
        if (count > max) {
           max = count;
           posx = asteroid.first;
           posy = asteroid.second;
        }
    }

    stationX = posx;
    stationY = posy;
    return max;
}

int main(int argc, const char * argv[]) {
    ifstream inputfile("prob10_input.txt");
    string line;
    int y = 0;
    vector<pair<int, int>> asteroids;

    while (getline(inputfile, line)) {
        for (int x = 0; x < line.length(); x++) {
            if (line[x] == '#') {
                asteroids.push_back(make_pair(x, y));
            }
        }
        y++;
    }

    int stationX = 0;
    int stationY = 0;
    cout << "Problem1:" << problem1(asteroids, stationX, stationY) << endl;

    cout << "Problem2:";
    problem2(asteroids, stationX, stationY);

    return 0;
}

