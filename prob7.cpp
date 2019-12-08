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

class Amplifier {
public:
    bool done = false;
    int setting;
    vector<int> inputs = {};
    int value = 0;
    bool useSecondinput = false;
    int i = 0;

    int calculate(int input1, int input2)
    {
        if (done == true) {
            return value;
        }

        while(true) {
            int token = inputs[i];

            int opcode = token % 100;
            int x = 0, y = 0 ;
            if (opcode != 99) {
                x = (token/100) % 10 == 0 ? inputs[inputs[i+1]] : inputs[i+1];
                y = (token/1000) % 10 == 0 ? inputs[inputs[i+2]] :  inputs[i+2];
            }

            switch (opcode) {
                case 1:
                    inputs[inputs[i+3]] = x + y;
                    i += 4;
                    break;
                case 2:
                    inputs[inputs[i+3]] = x * y;
                    i += 4;
                    break;
                case 3:
                    inputs[inputs[i+1]] = useSecondinput ? input2 :  input1;
                    useSecondinput = true;
                    i += 2;
                    break;
                case 4:
                    value = x;
                    i += 2;
                    return value;
                case 5:
                    if (x != 0)
                        (i = y);
                    else
                        (i += 3);
                    break;
                case 6:
                    if (x == 0)
                        (i = y);
                    else
                            (i += 3);
                        break;
                case 7:
                    inputs[inputs[i+3]] = (x < y) ? 1 : 0;
                    i += 4;
                    break;
                case 8:
                    inputs[inputs[i+3]] = (x == y) ? 1 : 0;
                    i += 4;
                    break;
                case 99:
                    done = true;
                    return value;

                default:
                    return value;
            }
        }

        return 0;
    }

};


void getPremutations(string a, int l, int r, vector<string>& permutations)
{
    if (l == r) {
        permutations.push_back(a);
    } else {
        for (int i = l; i <= r; i++) {
            int temp;

            temp = a[l]; a[l] = a[i]; a[i] = temp;

            getPremutations(a, l+1, r, permutations);

            temp = a[l]; a[l] = a[i]; a[i] = temp;
        }
    }
}

int main(int argc, const char * argv[]) {
    string input = "3,8,1001,8,10,8,105,1,0,0,21,38,59,84,97,110,191,272,353,434,99999,3,9,1002,9,2,9,101,4,9,9,1002,9,2,9,4,9,99,3,9,102,5,9,9,1001,9,3,9,1002,9,5,9,101,5,9,9,4,9,99,3,9,102,5,9,9,101,5,9,9,1002,9,3,9,101,2,9,9,1002,9,4,9,4,9,99,3,9,101,3,9,9,1002,9,3,9,4,9,99,3,9,102,5,9,9,1001,9,3,9,4,9,99,3,9,101,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,101,2,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,101,2,9,9,4,9,3,9,1002,9,2,9,4,9,99,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,101,1,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,101,1,9,9,4,9,3,9,101,2,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,1001,9,1,9,4,9,3,9,1001,9,2,9,4,9,99,3,9,1001,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,2,9,4,9,3,9,1001,9,2,9,4,9,3,9,1001,9,1,9,4,9,3,9,1002,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,1002,9,2,9,4,9,99,3,9,101,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,102,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,101,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,102,2,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,99,3,9,1001,9,1,9,4,9,3,9,102,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,101,1,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,1,9,4,9,3,9,102,2,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,101,1,9,9,4,9,99";

    vector<int> vect;
    stringstream ss(input);

    for (int i; ss >> i;) {
        vect.push_back(i);
        if (ss.peek() == ',')
            ss.ignore();
    }

    vector<string> permutations;
    getPremutations("01234", 0, 4, permutations);

    int maxVal = -1;
    for(const auto& permutation: permutations) {
        int prevInput = 0;
        for (int i = 0; i < 5; i++) {
            Amplifier amplifier;
            amplifier.inputs = vect;
            amplifier.setting = permutation[i] - '0';

            prevInput = amplifier.calculate(amplifier.setting, prevInput);
        }
        maxVal = (maxVal < prevInput) ? prevInput : maxVal;
    }

    cout << "Problem1:" << maxVal << endl;

    vector<string> permutations2;
    getPremutations("56789", 0, 4, permutations2);


    maxVal = -1;
    for(const auto& permutation: permutations2) {
        int prevInput = 0;

        vector<Amplifier> amplifiers;
        for (int i = 0; i < 5; i++) {
            Amplifier amplifier;
            amplifier.inputs = vect;
            amplifier.setting = permutation[i] - '0';

            amplifiers.push_back(amplifier);
        }

        while (!amplifiers[4].done) {
            for (int i = 0; i < 5; i++) {
                prevInput = amplifiers[i].calculate(amplifiers[i].setting, prevInput);
            }
        }
        maxVal = (maxVal < prevInput) ? prevInput : maxVal;
    }

     cout << "Problem2:" << maxVal << endl;

    return 0;
}



