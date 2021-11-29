#include "../header/dropMath.hpp"
#include <cassert>
#include <iostream>
#include "Timer.hpp"

bool Vector2_test(){
	using Vector2 = drop::math::Vector2;

	/* Test 1)
	 * Example Problem:
	 * Given a paralelogram, show that the diagonals
	 * half each other.
	 *
	 *     A--------B
	 *    /        /
	 *   D--------C
	 */
	{
		auto t{ Timer("Pralelogram") };

		auto A{ Vector2(1.f, 1.f) };	
		auto B{ Vector2(5.f, 1.f) };	
		auto C{ Vector2(4.f, 0.f) };	
		auto D{ Vector2(0.f, 0.f) };	

		//diagonals:
		auto dia1{ D.to(B) };
		auto dia2{ A.to(C) };

		std::cout << "Diagonal 1:\t" << dia1 << std::endl;
		std::cout << "Diagonal 2:\t" << dia2 << std::endl;

		assert(D+dia1*0.5f == A+dia2*0.5f);
		if(D+0.5f*dia1 != A+0.5f*dia2) return false;
	}
	return true;
}
