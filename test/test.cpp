#include <iostream>
#include "../header/dropMath.hpp"

#include "Vector2_tests.hpp"
#include "Vector3_tests.hpp"
#include "line_box_tests.hpp"
#include "PowZ_tests.hpp"

int main(){
	if(!Vector2_test()){
		std::cerr << "Vector2 tests failed!" << std::endl;
		return 1;
	}

	if(!Vector3_test()){
		std::cerr << "Vector3 tests failed!" << std::endl;
	}

	if(!line_box_test()){
		std::cerr << "Line-Box tests failed!" << std::endl;
	}

	if(!PowZ_tests()){
	    std::cerr <<"PowZ tests failed failed!" << std::endl;
	}

}
