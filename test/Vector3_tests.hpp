#pragma once

#include "Timer.hpp"
#include "../header/dropMath.hpp"
#include <cassert>
inline
auto Vector3_test() -> bool {
	/*	Movement in 3D-Space
	 *
	 *	^
	 *	|
	 *	|     ^
	 *	|    /  ^ ^
	 *	|   /   |/
	 *	|  /    x-->
	 *	| /
	 *	|/
	 *	 ---------------->
	 */
	{
		using Vector3 = drop::math::Vector3;
		auto move_test{ Timer("3D-Movement Test") };

		auto position{ Vector3(3.f, 0.f, 4.f) };
		auto up{ Vector3::up() };
		auto look_direction{ Vector3::forward() };

		auto left{ look_direction.cross_prod(up)._normalize() };

		std::cout << "Our start position: " << position;

		position += 2*look_direction + 3*left;
		std::cout << "\nAfter taking 2 steps forward and 3 steps to the right:"
		<< position << std::endl;
		assert(position == Vector3(0.f, 0.f, 6.f));
	}
	return true;
}
