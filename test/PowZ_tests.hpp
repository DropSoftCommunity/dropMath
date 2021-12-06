#pragma once
inline
bool PowZ_tests(){
	using drop::math::powZ;
    auto t{ Timer("PowZ ultimative test") };

    for(int i{}; i<1000;++i)
	std::cout << powZ(i,5) << std::endl;



	return true;
}
