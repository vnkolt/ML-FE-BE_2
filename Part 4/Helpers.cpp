//
// Helpers.cpp
//
#include <random>
#include <cassert>
#include <fstream>
#include <string>
#include <chrono>

#include "Helpers.h"

// Integer square root (using binary search)
static unsigned int isqrt(unsigned int y) {
    unsigned int L = 0;
    unsigned int M;
    unsigned int R = y + 1;

    while (L != R - 1) {
        M = (L + R) / 2;

        if (M * M <= y)
            L = M;
        else
            R = M;
    }

    return L;
}

/*

 Function: randoms

 Description: generates a vector with random integer values from specified range

 Parameters:
      count - count of numbers to be generated (vector size)
      from - minimum of the range
      to - maximum of the range
 
 Returns: vector of integers with random numbers from a specified range

*/
std::vector<int> randoms(int count, int from, int to) {
    assert(count > 0 && (to - from) > count);
    std::vector<int> result(count, 0);
    std::vector<int> rinds;

    for (auto i = from; i <= to; ++i) {
        rinds.push_back(i);
    }

    auto now = std::chrono::high_resolution_clock::now();
    std::mt19937 rgen{std::random_device{}()};
    rgen.seed((unsigned int)now.time_since_epoch().count());

    for (auto i = 0; i < count; ++i) {
        std::uniform_int_distribution<int> distr(0, (int)(rinds.size() - 1));

        int idx = distr(rgen);
        result[i] = rinds[idx];
        rinds.erase(rinds.begin() + idx);
    }

    return result;
}

/*
   Function: black_holes_from_file

   Description: reads game conditions from the specified file and create a vector with indeces of black holes and sets board size

 Parameters:
      filename - file that contains game matrix like this

 0 1 0 1 0 0
 0 0 0 0 0 0
 0 1 1 0 0 0
 1 0 0 0 0 0
 0 1 0 0 1 0
 0 0 0 0 0 1

 where 1 means a black hole cell, 0 means a normal cell


      n - board size that corresponding to the input matrix

 Returns: vector of integers with indeces of black holes
          n - board size

*/
std::vector<int> black_holes_from_file(const char* filename, unsigned int& n) {
    std::ifstream ifs(filename);

    std::vector<int> v;
    std::string line;
    unsigned int index = 0;
    while (std::getline(ifs, line)) {
        for (char& c : line) {
            auto isdelim = [](char c) { return (' '==c || '\t'==c || ','==c || ';'==c || ':'==c || '-'==c); };
            auto ishole = [](char c) { return ('H' == c || 'h' == c || '1' == c); };
            if (ishole(c)) {
                v.push_back(index);
                index++;
            }
            else if (!isdelim(c)) {
                index++;
            }
        }
    }

    n = isqrt(index);

    return v;
}
