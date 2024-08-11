#pragma once
#include <random>


namespace random
{
	int between(int from, int to) {
		return rand() % (to - from + 1) + from;
	}
}

