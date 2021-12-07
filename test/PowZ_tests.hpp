#pragma once

#include "../header/dropMath.hpp"
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
	std::cout << powZ(i,2) << std::endl;
	}


	return true;
}
