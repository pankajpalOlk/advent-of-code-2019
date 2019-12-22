//
//  main.cpp
//  advent
//
//  Created by pankaj pal on 21/12/19.
//  Copyright © 2019 pankaj pal. All rights reserved.
//

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <array>

using namespace std;

vector<int> getPatternForIteration(int len, int repeatCount)
{
    array<int, 4> basePattern {0, 1, 0, -1};
    vector<int> result;

    int i = 0;
    while (i < len+1) {
        int baseIdx = (i/repeatCount)%4;
        for (int j = 0; j < repeatCount; j++) {
            result.push_back(basePattern[baseIdx]);
        }
        i += repeatCount;
    }

    result.erase(result.begin());

    return result;
}

int getPatternValueForIteration(int iteration, int index)
{
    array<int, 4> basePattern {0, 1, 0, -1};

    return basePattern[((index+1)/(iteration+1)) % 4];
}

void Problem1(const string& input)
{
    vector<int> vect;
    size_t inputLen = input.length();

    for (auto ch : input) {
        vect.push_back(ch - '0');
    }

    vector<int> result;
    result = vect;

    for (int i = 0; i < 100; i++) {
        auto tempInput = result;
        for (int k = 0; k < inputLen; k++) {
            int sum = 0;
            for(int j = 0; j < inputLen; j++) {
                sum += getPatternValueForIteration(k, j) * tempInput[j];
            }

            result[k] = abs(sum)%10;
        }
    }

    for (int i = 0; i < 8; i++) {
        cout << result[i];
    }

    cout << endl;

}


// Found on reddit:
// When running a 'phase':
// the second half of the output only depends on the second half of the input
// each digit i in the second half of the output is the sum of the digits of the input from i to the end of the input
// Calculating the sum from end also optimizes the running sum logic
void Problem2(const string& input)
{
    vector<int> vect;

    for (int i = 0; i < 10000; i++)
        for (auto ch : input) {
            vect.push_back(ch - '0');
        }

    vector<int> result(vect.begin()+5978199, vect.end());

    for (int i = 0; i < 100; i++) {
        int sum = 0;
        for (int j = (int)result.size()-1; j >= 0; j--) {
            sum = (sum + result[j])%10;
            result[j] = sum;
        }
    }

    for (int i = 0; i < 8; i++) {
        cout << result[i];
    }

    cout<<endl;
}

int main(int argc, const char * argv[]) {
    string input = "59781998462438675006185496762485925436970503472751174459080326994618036736403094024111488348676644802419244196591075975610084280308059415695059918368911890852851760032000543205724091764633390765212561307082338287866715489545069566330303873914343745198297391838950197434577938472242535458546669655890258618400619467693925185601880453581947475741536786956920286681271937042394272034410161080365044440682830248774547018223347551308590698989219880430394446893636437913072055636558787182933357009123440661477321673973877875974028654688639313502382365854245311641198762520478010015968789202270746880399268251176490599427469385384364675153461448007234636949";

    Problem1(input);
    Problem2(input);

    return 0;
}

