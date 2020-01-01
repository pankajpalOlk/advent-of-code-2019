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

class Computer{
public:
    long i = 0;
    bool done = false;
    vector<long> vect;
    long relativeAddress = 0;
    vector<long> input;
    vector<long> result;
    bool isIdle = false;

    void setInput(long input) {
        this->input.push_back(input);
    }

    bool fIsIdle() {
        return isIdle;
    }

    void calculate()
    {
        result.clear();
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
                    if (input.empty())
                    {
                        vect[x] = -1;
                        isIdle = true;
                        i += 2;
                        return;
                    }

                    isIdle = false;
                    vect[x] = input[0];
                    input.erase(input.begin());

                    i += 2;
                    break;
                case 4:
                    result.push_back(vect[x]);
                    i += 2;

                    if (result.size() == 3) {
                        return;
                    }

                    break;
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
                    isIdle = true;
                    done = true;
                    return;
            }
        }
    }
};

void Problem1(const vector<long>& vect)
{
    vector<Computer> computers;
    for (int i = 0; i < 50; i++)
    {
        Computer computer;
        computer.vect = vect;
        computer.setInput(i);

        computers.push_back(computer);
    }

    while (true) {
        for (auto& comp : computers)
        {
            comp.calculate();

            auto output = comp.result;
            if (output.size() == 0)
                continue;

            if (output[0] == 255)
            {
                cout << "Problem1: " << output[2] << endl;
                return;
            }

            for (int i = 0; i < output.size(); i += 3)
            {
                computers[output[i]].setInput(output[i+1]);
                computers[output[i]].setInput(output[i+2]);
            }
        }
    }
}

void Problem2(const vector<long>& vect)
{
    set<long> history;

    long nat_inp1 = 0, nat_inp2 = 0;

    vector<Computer> computers;
    for (int i = 0; i < 50; i++)
    {
        Computer computer;
        computer.vect = vect;
        computer.setInput(i);

        computers.push_back(computer);
    }

    while (true) {
        for (auto& comp : computers)
        {
            comp.calculate();

            auto output = comp.result;
            if (output.size() == 0)
                continue;

            if (output[0] == 255)
            {
                nat_inp1 = output[1];
                nat_inp2 = output[2];
                continue;
            }

            for (int i = 0; i < output.size(); i += 3)
            {
                computers[output[i]].setInput(output[i+1]);
                computers[output[i]].setInput(output[i+2]);
            }
        }

        bool fAllIdle = true;
        for (auto comp : computers)
        {
            if (!comp.isIdle)
                fAllIdle = false;
        }

        if (fAllIdle)
        {
            if (nat_inp2 == 0)
                continue;

            computers[0].setInput(nat_inp1);
            computers[0].setInput(nat_inp2);

            if (history.find(nat_inp2) != history.end()) {
                cout << "Problem2: " << nat_inp2 << endl;
                return;
            }

            history.insert(nat_inp2);
        }
    }
}

int main()
{
    vector<long> vect;
    fstream in("prob23_input.txt");

    long number = 0;
    char ignore;
    while (in >> number)
    {
        vect.push_back(number);

        // ignore ,
        in >> ignore;
    }

    for (int i = 0; i < 2000; i++)
    {
        vect.push_back(0);
    }

    Problem1(vect);
    Problem2(vect);

    return 0;
}
