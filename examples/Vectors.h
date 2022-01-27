#include "common.hpp"

void vectors(){
	using vec3 = drop::math::Vector3;

	const vec3 v1{-2.f, 1.f, -2.f};
	const vec3 v2{-1.f, 3.f, 0.f};
	const vec3 v3{4.f, 1.f, 3.f};
	const vec3 v4{1.f, 1.f, 1.f};

	std::cout << "Problem:\n2*" << v1 <<" + 5*"<<v2 
			  << " - 6*" << v3 << " - " << v4;
	const vec3 res{2*v1+5*v2-6*v3-v4};
	std::cout << "\nResult: " << res << std::endl;
}
