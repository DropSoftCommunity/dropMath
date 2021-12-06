#pragma once
inline
bool PowZ_tests(){
	using drop::math::powZ;
    auto t{ Timer("PowZ ultimative test") };


	std::cout << powZ(2,3) << std::endl;



	return true;
}
