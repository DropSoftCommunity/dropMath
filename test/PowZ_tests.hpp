#pragma once
inline
bool PowZ_tests(){
	using drop::math::powZ;
    auto t{ Timer("PowZ ultimative test") };

    for(int i{}; i<10000;++i)
	std::cout << powZ(rand() % 101-1,rand() % 101-1) << std::endl;



	return true;
}
