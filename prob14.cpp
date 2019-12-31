//
//  main.cpp
//  advent
//
//  Created by pankaj pal on 18/12/19.
//  Copyright © 2019 pankaj pal. All rights reserved.
//

#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include <cmath>
using namespace std;

struct Chemical
{
    int64_t value;
    string name;

    Chemical() {};

    Chemical(string invalue) {
        size_t splitter = invalue.find(" ");
        if (splitter != string::npos) {
            value = stoi(invalue.substr(0, splitter));
            name = invalue.substr(splitter+1);
        }
    }
};

struct Reaction
{
    vector<Chemical> inputs;
    Chemical output;

    Reaction() {};

    Reaction(vector<Chemical> _inputs, Chemical _output) {
        inputs =  _inputs;
        output = _output;
    }
};

map<string, Reaction> reactions;

vector<Chemical> ParseInputs(const string& in) {
    vector<string> vals;
    vector<Chemical> result;
    string inputval = in;

    while (inputval.size()) {
        size_t splitter = inputval.find(",");
        if (splitter != string::npos) {
            vals.push_back(inputval.substr(0, splitter));

            inputval = inputval.substr(splitter+2);
            if (inputval.size() == 0) {
                vals.push_back(inputval);
            }
        } else {
            vals.push_back(inputval);
            inputval = "";
        }
    }

    for (auto const& val : vals) {
        Chemical chemical = Chemical(val);

        result.push_back(chemical);
    }

    return result;
}

int64_t findSolution(string val, int64_t quantity)
{
    map<string, int64_t> have;
    have["FUEL"] = -quantity;

    vector<string> todo;
    todo.push_back("FUEL");

    while (!todo.empty()) {
        string ele = todo[todo.size()-1];
        todo.pop_back();

        double needed = -have[ele];
        Reaction reaction = reactions.at(ele);
        double outValue = reaction.output.value;
        double rem = needed/outValue;
        int64_t multiplier = ceil(rem);
        have[ele] += multiplier*reaction.output.value;

        for (const auto& input : reaction.inputs) {
            have[input.name] -= multiplier * input.value;
            if ((input.name != "ORE") && (have[input.name] < 0ll)) {
                todo.push_back(input.name);
            }
        }
    }

    return -have["ORE"];
}

int main(int argc, const char * argv[]) {
    ifstream inputfile("prob14_input.txt");
    string line;

    while (getline(inputfile, line)) {
        size_t splitter = line.find(" => ");
        if (splitter != string::npos) {
            vector<Chemical> _inputs = ParseInputs(line.substr(0, splitter));
            Chemical _output = Chemical(line.substr(splitter+4));

            reactions[_output.name] = Reaction(_inputs, _output);
        }
    }

    int64_t ores = findSolution("FUEL", 1);
    cout << "Problem1:" << ores << endl;

    int64_t max_ores = 1000000000000ll;

    int64_t min_fuel = (max_ores / ores);
    int64_t max_fuel = min_fuel * 2;

    while (min_fuel != max_fuel) {
        int64_t fuel = (min_fuel + max_fuel + 1) / 2;
        if (findSolution("FUEL", fuel) > max_ores) {
            max_fuel = fuel - 1;
        } else {
            min_fuel = fuel;
        }
    }

    cout << "Problem2:" << max_fuel << endl;

    return 0;
}

