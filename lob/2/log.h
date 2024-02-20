#pragma once
#include <iostream>
#include <string>

using namespace std;

inline void log(const string& message) {
    cout << "[LOG] " << message << std::endl;
}
