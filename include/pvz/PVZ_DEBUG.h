#pragma once
#include <iostream>

#ifdef ENABLE_DEBUG
#define DEBUG std::cout
#else
class NullBuffer : public std::streambuf {
public:
    int overflow(int c) override { return c; }
};

static NullBuffer null_buf;
static std::ostream null_out(&null_buf);

#define DEBUG null_out
#endif

