#pragma once

#include "dropMath.hpp"
#include "Timer.hpp"

inline
bool PowZ_tests(){
	/*
	 * PowZ performance test
	 */
	{
	using drop::math::powZ;
    auto t{ Timer("PowZ ultimative test") };

    for(int i{0}; i<10000;++i)
		powZ(rand() % 10001,rand() % 50);
	}


	return true;
}
