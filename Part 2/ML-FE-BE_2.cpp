#include <random>
#include <cassert>
#include <vector>
#include <chrono>
#include <iostream>

#include "GameData.h"

std::vector<int> randoms(int count, int from, int to) {
    assert(count > 0 && (to - from) > count);
    std::vector<int> result(count, 0);
    std::vector<int> rinds;

    for (auto i = from; i <= to; ++i) {
        rinds.push_back(i);
    }

    auto now = std::chrono::high_resolution_clock::now();
    std::mt19937 rgen{std::random_device{}()};
    rgen.seed(now.time_since_epoch().count());

    for (auto i = 0; i < count; ++i) {
        std::uniform_int_distribution<int> distr(0, (int)(rinds.size() - 1));

        int idx = distr(rgen);
        result[i] = rinds[idx];
        rinds.erase(rinds.begin() + idx);
    }

    return result;
}


int main() {
    const int N = 8;  // board size
    const int K = 10; // number of black holes
    GameBoard board(N);

    std::cout << "Game board " << N << "x" << N << ", " << K << " black holes" << ":\n";

/* Part 2:
   Populate your data structure with K black holes placed in random locations. Note that should
   place exactly K black holes and their location should be random with a uniform distribution.
*/

    std::vector<int> black_holes = randoms(K, 0, N*N-1);
    board.set_black_holes(black_holes);

    // Display this game board
    for( auto r = 0u; r < N; r++ ) {
      for( auto c = 0u; c < N; c++ ) {
        char ch = (board.is_black_hole_cell(r,c) ? 'H' : '0'+board.black_holes_nearby(r,c));
        std::cout << ch << " ";
      }
      std::cout << std::endl;
    }

    return 0;
}