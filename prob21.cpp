//
//  main.cpp
//  advent
//
//  Created by pankaj pal on 29/12/19.
//  Copyright © 2019 pankaj pal. All rights reserved.
//

#include "intcode.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <set>
#include <sstream>

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

void Problem1(const vector<long>& vect)
{
    /*
     # J = (!A | !B | !C) & D
     #   = !(A & B & C) & D

     OR A J    # J = A
     AND B J   # J = A & B
     AND C J   # J = A & B & C
     NOT J J   # J = !(A & B & C)
     AND D J   # J = !(A & B & C) & D
     */

    string inputString = "OR A J\nAND B J\nAND C J\nNOT J J\nAND D J\nWALK\n";
    Computer computer;
    computer.vect = vect;
    computer.setInputArray(GetComputerInputs(inputString));

    cout << "Problem1: ";
    while (!computer.done)
    {
        long output = computer.calculate();
        if (output > 255)
            cout << computer.calculate();
    }

    cout << endl;
}

void Problem2(const vector<long>& vect)
{
    /*
     * ((!A | !B | !C) & D) & (H | E)
     * (!A | !B | !C) & D & (H | E)
     */
    string inputString = "OR A J\nAND B J\nAND C J\nNOT J J\nAND D J\nOR H T\nOR E T\nAND T J\nRUN\n";
    Computer computer;
    computer.vect = vect;
    computer.setInputArray(GetComputerInputs(inputString));

    cout << "Problem2: ";

//    while (!computer.done)
//    {
//        // Print out the trace that fails with input string from Problem1.
//        cout << (char)computer.calculate();
//    }

    while (!computer.done)
    {
        long output = computer.calculate();
        if (output > 255)
            cout << computer.calculate();
    }

    cout << endl;
}

int main()
{
    vector<long> vect;
    fstream in("prob21_input.txt");

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
