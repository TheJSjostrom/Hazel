#include "RandomNumber.h"

std::mt19937 Random::s_RandomEngine1;
std::uniform_int_distribution<std::mt19937::result_type> Random::s_Distribution1;
