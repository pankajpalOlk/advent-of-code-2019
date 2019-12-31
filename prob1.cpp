#include <iostream>
#include <fstream>

using namespace std;


int fuel(int input)
{
    int sum = 0;

    do {
        input = input/3;
        if (input > 0) {
            input -= 2;
            if (input > 0) {
                sum += input;
            }
        }
    } while(input > 0);

    return sum;
}

// Run it using the following command: 
// g++ prob1.cpp
// cat prob1_input.txt | ./a.out
int main() {
    int value = 0;
    int sum = 0;

    while (cin>>value) {
        sum += fuel(value);
    }

    cout << sum;

    return 0;
}
