#pragma once

#include <dropMath.hpp>
#include "Timer.hpp"

inline 
auto line_box_test() -> bool {
	/* Find the point where line A_B hits a given rectangle
	 *
	 *            B
	 *           x
	 *      ____/_
	 *     |   /  | 
	 *     |__/___|
	 *       /\
	 *      /  hitPoint
	 *     x
	 *      A
	 */
	{
		using Line2d = drop::math::Line2;
		using Rect = drop::math::Rect;

		auto intersect_test{ Timer("Line-Box Intersect") };
		
		auto line{ Line2d({2.f, 1.f}, {5.f, 5.f}) };
		auto rect{ Rect(2.f, 3.f, 5.f, 2.f) };

		auto hitPoint{ line.intersect_point(rect) };

		std::cout << "Line intersects the rectange at:\n" << hitPoint
		<< std::endl;
	}

	return true;
}

