#pragma once
#include <string>
#include <iostream>

#define POLAROID_WIN32
#define POLAROID_DEBUG

#ifdef POLAROID_DEBUG
#define POLAROID_INFO(text) std::cout << "[INFO] " << text << "\n";
#define POLAROID_ERROR(text) std::cout << "[ERROR] " << text << "\n";
#define POLAROID_ASSERT(expression) if (!(##expression)) { POLAROID_ERROR(#expression) __debugbreak(); }
#endif