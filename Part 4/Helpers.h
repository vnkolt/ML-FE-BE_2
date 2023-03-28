#ifndef Helpers_h
#define Helpers_h

#include <vector>

std::vector<int> randoms(int count, int from, int to);
std::vector<int> black_holes_from_file(const char* filename, unsigned int& n);

#endif // Helpers_h
