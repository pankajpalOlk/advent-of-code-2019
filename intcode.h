//
//  intcode.h
//  advent
//
//  Created by pankaj pal on 21/12/19.
//  Copyright © 2019 pankaj pal. All rights reserved.
//

#ifndef intcode_h
#define intcode_h

#include <vector>

using namespace std;

class Computer{
public:
    long result;
    long i = 0;
    bool done = false;
    vector<long> vect;
    long relativeAddress = 0;
    vector<long> input;

    void setInput(long input) {
        this->input.push_back(input);
    }

    long calculate()
    {
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
//                    if (input.empty()) {
//                        char str[256];
//                        cin.getline(str, 256);
//
//                        for(int i=0; str[i]; i++){
//                            input.push_back((long)str[i]);
//                        }
//                        input.push_back(10);
//                    }
                    vect[x] = input[0];
                    i += 2;
                    input.erase(input.begin());
                    break;
                case 4:
                    result = vect[x];
                    i += 2;
                    return result;
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
                    done = true;
                    return result;
            }
        }

        return result;
    }
};



#endif /* intcode_h */
