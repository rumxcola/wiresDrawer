#include "randomizer.h"

std::default_random_engine Randomizer::rndGen__;
std::uniform_int_distribution<uint8_t> Randomizer::range__(0,255);
