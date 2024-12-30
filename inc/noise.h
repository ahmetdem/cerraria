#pragma once

#include <stdint.h>

void init_noise(uint32_t seed);
float get_noise(float x);
float get_normalized_noise(float x);
