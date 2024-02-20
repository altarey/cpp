#pragma once
#include <iostream>
#include <string>

using namespace std;

inline void log(const string& message) {
    cout << "[DBG] " << message << std::endl;
}
