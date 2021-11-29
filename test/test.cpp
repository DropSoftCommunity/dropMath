#include <iostream>
#include "../header/dropMath.hpp"

#include "Vector2_tests.hpp"


int main(){
	if(!Vector2_test()){
		std::cerr << "Vector2 tests failed!" << std::endl;
		return 1;
	}
}
