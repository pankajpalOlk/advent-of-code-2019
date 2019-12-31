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

int countDepth(const string& node, const map<string, string>& tree, const string& root)
{
    if (node == root) {
        return 0;
    }

    return 1 + countDepth(tree.at(node), tree, root);
}

int getAllOrbits(const map<string, string>& tree)
{
    int count = 0;

    for (auto const& node : tree) {
        count += countDepth(node.first, tree, "COM");
    }

    return count;
}

vector<string> getPathToRoot(string child, const map<string, string>& tree)
{
    vector<string> path;

    while (child != "COM") {
        child = tree.at(child);
        path.push_back(child);
    }

    return path;
}

string getCommonParent(string c1, string c2, const map<string, string>& tree)
{
    vector<string> c1_path = getPathToRoot(c1, tree);
    vector<string> c2_path = getPathToRoot(c2, tree);

    for (auto const& val1 : c1_path) {
        for (auto const& val2 : c2_path) {
            if (val1 == val2) {
                return val1;
            }
        }
    }

    return {};
}

int getTransferLength(const map<string, string>& tree)
{
    string commonParent = getCommonParent("YOU", "SAN", tree);

    return countDepth(tree.at("YOU"), tree, commonParent) + countDepth(tree.at("SAN"), tree, commonParent);
}


int main(int argc, const char * argv[]) {
    ifstream inputfile("prob6_input.txt");
    string line;
    map<string, string> tree;

    if (!inputfile.is_open()) {
        cout << "error opening file " <<endl;
    }
    system("pwd");
    while(getline(inputfile, line)) {
        size_t pos = line.find(")");
        string parent = line.substr(0, pos);
        string child = line.substr(pos+1);

        tree[child] = parent;
    }

    cout << getAllOrbits(tree) << endl;

    cout << getTransferLength(tree) << endl;

    return 0;
}



