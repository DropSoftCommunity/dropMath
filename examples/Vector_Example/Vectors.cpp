#include "dropMath.hpp"
#include <iostream>

int main(){
	using vec2 = drop::math::Vector2;

	vec2 a{1.f, 2.f};
	vec2 b{2.f, 3.f};

	std::cout << (a+b) << std::endl;

}
