#pragma once
#include <string>
#include <iostream>

#define POLAROID_WIN32
#define POLAROID_DEBUG

#ifdef POLAROID_DEBUG
#define POLAROID_INFO(text) std::cout << text << "\n";
#endif