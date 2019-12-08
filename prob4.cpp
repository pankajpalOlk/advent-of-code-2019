//
//  main.cpp
//  advent
//
//  Created by pankaj pal on 03/12/19.
//  Copyright © 2019 pankaj pal. All rights reserved.
//

#include <iostream>
#include <vector>
#include <sstream>
#include <set>
#include <map>
using namespace std;



int main(int argc, const char * argv[]) {
    int input1 = 152085;
    int input2 = 670283;

    int problem1 = 0;
    int problem2 = 0;
    for (int i = input1; i < input2; i++) {
        int num = i;
        int prev = 10;
        int equal1 = 0;
        bool valid1 = true;
        bool valid2 = false;
        bool valid3 = false;
        while (num > 0) {
            int digit = num % 10;
            num /= 10;
            if (digit > prev) {
                valid1 = false;
                break;
            }

            if (digit == prev) {
                equal1++;
                valid2 |= (equal1 == 1);
            } else {
                valid3 |= (equal1 == 1);
                equal1 = 0;
            }

            prev = digit;
        }

        if (valid1 && valid2) {
            problem1++;
        }

        if (valid1 && (valid3 || equal1 == 1)) {
            problem2++;
        }
    }

    cout << problem1 << endl;
    cout << problem2 << endl;

    return 0;
}



