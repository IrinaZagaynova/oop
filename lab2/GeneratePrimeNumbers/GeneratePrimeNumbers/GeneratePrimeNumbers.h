#pragma once
#include <iostream>
#include <string>
#include <set>
#include <vector>

bool ParseArgs(int argc, char* argv[], int& upperBound);
std::set<int> GeneratePrimeNumbersSet(int upperBound);
bool IsItNumberWithinBoundsOfSet(const std::string& str, int& upperBound);
