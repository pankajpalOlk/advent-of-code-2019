//
//  main.cpp
//  advent
//
//  Created by pankaj pal on 29/12/19.
//  Copyright © 2019 pankaj pal. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <set>
#include <sstream>

typedef __int128_t bigint;

using namespace std;

constexpr int64_t numOfCards = 10007;
constexpr int64_t cardOfInterest = 2019;

enum MoveTpe
{
    DEAL_NEW, DEAL_INC, DEAL_CUT
};

struct Move
{
    MoveTpe type;
    int64_t amount;

    Move();
    Move(enum MoveTpe type, int64_t amount)
    {
        this->type = type;
        this->amount = amount;
    }
};


void Problem1(const vector<Move>& moves)
{
    int64_t position = cardOfInterest;

    for (auto curr : moves)
    {
        if (curr.type == DEAL_NEW)
        {
            position = numOfCards - position - 1;
        }
        else if (curr.type == DEAL_INC)
        {
            position = (position*curr.amount) % numOfCards;
        }
        else
        {
            // DEAL_CUT
            int64_t amount = curr.amount;
            if (curr.amount < 0)
            {
                amount += numOfCards;
            }

            if (position < amount)
            {
                position = numOfCards + position - amount;
            }
            else
            {
                position = position - amount;
            }
        }
    }

    cout << "Problem1: " << position << endl;
}


bigint mod(bigint x, bigint m)
{
    return (x % m + m) % m;
}

bigint modular_power(bigint base, bigint exponent, bigint n)
{
  assert(exponent >= 0);
  if (exponent == 0) {
    return (base == 0) ? 0 : 1;
  }

  bigint bit = 1;
  bigint power = mod(base, n);
  bigint out = 1;
  while (bit <= exponent) {
    if (exponent & bit) {
      out = mod(out * power, n);
    }
    power = mod(power * power, n);
    bit <<= 1;
  }

  return out;
}


// Impossible for me to solve this.
// Followed this - https://github.com/mebeim/aoc/blob/master/2019/README.md#day-22---slam-shuffle
void Problem2(const vector<Move>& moves)
{
    bigint start = 0;
    bigint step = 1;
    bigint size = 119315717514047;
    bigint reps = 101741582076661;

    for (auto curr : moves)
    {
        if (curr.type == DEAL_NEW)
        {
            start = mod((start - step), size);
            step = mod(-step, size);
        }
        else if (curr.type == DEAL_INC)
        {
            step = mod((step * modular_power(curr.amount, size - 2, size)), size);
        }
        else
        {
            if (curr.amount < 0)
                curr.amount += size;

                start = mod((start + step * curr.amount), size);
        }
    }

    bigint finalStep = modular_power(step, reps, size);
    bigint temp = (1 - finalStep) * modular_power(1-step, size-2, size);
    bigint finalStart = mod(start, size) * mod(temp, size);

    bigint result = mod((finalStart + finalStep * 2020), size);

    cout << "Problem2: "<< (int64_t)result << endl;
}

int main()
{
    string line;
    vector<Move> moves;
    fstream in("/Users/pankajpal/advent/prob22_input.txt");

    while (getline(in, line))
    {
        int64_t inputValue;

        if (sscanf(line.c_str(), "cut %lld", &inputValue) == 1)
        {
            moves.push_back(Move(DEAL_CUT, inputValue));
        }
        else if (sscanf(line.c_str(), "deal with increment %lld", &inputValue) == 1)
        {
            moves.push_back(Move(DEAL_INC, inputValue));
        }
        else
        {
            // deal new card
            moves.push_back(Move(DEAL_NEW, 0));
        }
    }

    Problem1(moves);
    Problem2(moves);

    in.close();
    return 0;
}
