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
#include "intcode.h"

using namespace std;

std::vector<long> GetComputerInputs(const string& inputString)
{
    vector<long> returnVal;

    for (auto c : inputString)
    {
        returnVal.push_back((long)c);
    }

    return returnVal;
}

// Played game manually by adding minor chage to intCode - it will prompt for
// user input when input queue is empty.
// Figured out that Molten Lava, Infinite loop, Giant EM, Escape Pod and Photons shoulnt be taken
// That left me with 8 options:
// Sand, Hat, Prime number, mug, weather machine, astronaut ice cream, mutext, boulder
void Problem1(const vector<long>& vect)
{
    Computer computer;
    computer.vect = vect;

    string inputStr = "east\n";
    inputStr += "east\n";
    inputStr += "north\n";
    inputStr += "east\n";
    inputStr += "east\n";
    inputStr += "take astronaut ice cream\n";
    inputStr += "west\n";
    inputStr += "west\n";
    inputStr += "south\n";
    inputStr += "west\n";
    inputStr += "west\n";
    inputStr += "north\n";
    inputStr += "west\n";
    inputStr += "take sand\n";
    inputStr += "east\n";
    inputStr += "south\n";
    inputStr += "south\n";
    inputStr += "south\n";
    inputStr += "take mutex\n";
    inputStr += "south\n";
    inputStr += "take boulder\n";
    inputStr += "east\n";
    inputStr += "south\n";
    inputStr += "east\n";

    computer.setInputArray(GetComputerInputs(inputStr));

    while (!computer.done)
    {
        cout << (char)computer.calculate();
    }

    cout << endl;
}

void Problem1_AutoSolve(const vector<long>& vect)
{
    // First take every valid item to the penultimate node
    // and then try all the combinations

    vector<string> validItems{"astronaut ice cream", "prime number", "weather machine", "mug", "festive hat", "sand", "mutex", "boulder"};

    Computer computer;
    computer.vect = vect;

    string inputStr = "east\n";
    inputStr += "east\n";
    inputStr += "north\n";
    inputStr += "east\n";
    inputStr += "east\n";
    inputStr += "take astronaut ice cream\n";
    inputStr += "west\n";
    inputStr += "west\n";
    inputStr += "south\n";
    inputStr += "west\n";
    inputStr += "north\n";
    inputStr += "take weather machine\n";
    inputStr += "north\n";
    inputStr += "take mug\n";
    inputStr += "south\n";
    inputStr += "south\n";
    inputStr += "west\n";
    inputStr += "north\n";
    inputStr += "take festive hat\n";
    inputStr += "east\n";
    inputStr += "take prime number\n";
    inputStr += "west\n";
    inputStr += "west\n";
    inputStr += "take sand\n";
    inputStr += "east\n";
    inputStr += "south\n";
    inputStr += "south\n";
    inputStr += "south\n";
    inputStr += "take mutex\n";
    inputStr += "south\n";
    inputStr += "take boulder\n";
    inputStr += "east\n";
    inputStr += "south\n";

    for (auto s : validItems)
    {
        inputStr += "drop " + s + "\n";
    }

    for (int i = 0; i < 256; i++)
    {
        set<string> set;
        for (int j = 0; j < 8; j++) {
            if (((i >> j) & 1) == 1)
            {
                set.insert(validItems[j]);
            }
        }

        for (auto s : set)
        {
            inputStr += "take " + s + "\n";
        }

        inputStr += "east\n";

        for (auto s : set)
        {
            inputStr += "drop " + s + "\n";
        }
    }

    computer.setInputArray(GetComputerInputs(inputStr));

    while (!computer.done)
    {
        cout << (char)computer.calculate();
    }

    cout << endl;
}

int main()
{
    vector<long> vect;
    fstream in("prob25_input.txt");

    long number = 0;
    char ignore;
    while (in >> number)
    {
        vect.push_back(number);

        // ignore ,
        in >> ignore;
    }

    for (int i = 0; i < 4000; i++)
    {
        vect.push_back(0);
    }

    Problem1(vect);

    Problem1_AutoSolve(vect);

    return 0;
}
