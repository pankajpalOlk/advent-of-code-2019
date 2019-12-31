//
//  main.cpp
//  advent
//
//  Created by pankaj pal on 03/12/19.
//  Copyright © 2019 pankaj pal. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

static const int width = 25;
static const int height = 6;
void getImageMessage(const string& line)
{
    vector<int> colors;
    int layerSz = width*height;
    size_t len = line.length();

    int color = 2;

    for (int i = 0; i < layerSz; i++) {
        color = line[0] - '0';
        if (color != 2) {
            colors.push_back(color);
            continue;
        }

        for (int j = i; j < len; j += layerSz) {
            color = line[j] - '0';
            if (color != 2) {
                colors.push_back(color);
                break;
            }
        }
    }

    for (int i = 0; i < layerSz; i++)
    {
        if (i % width == 0) {
            cout << endl;
        }
        cout << ((colors[i] == 1) ? '1' : ' ');
    }
}

int least_count_zeros(const string& line)
{
    int layerSz = width*height;
    int countzero = 0;
    int mincount = 0xffffff;
    int start = 0;
    size_t len = line.length();

    for (int i = 0; i < len; i++) {
        if (i != 0 && i%layerSz == 0) {
            if (countzero < mincount) {
                mincount = countzero;
                start = i - layerSz;
            }

            countzero = 0;
        } else {
            if (line[i] == '0') {
                countzero++;
            }
        }
    }

    int countones = 0;
    int counttwos = 0;
    for (int i = start; i < start + layerSz; i++) {
        if (line[i] == '1') countones++;
        if (line[i] == '2') counttwos++;
    }

    return countones * counttwos;
}

int main(int argc, const char * argv[]) {
    ifstream inputfile("prob8_input.txt");
    string line;
    getline(inputfile, line);

    cout << "Problem1:" <<  least_count_zeros(line) << endl;

    getImageMessage(line);

    return 0;
}



