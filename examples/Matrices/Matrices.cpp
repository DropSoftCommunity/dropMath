#include "../common.hpp"

using mat2 = drop::math::Matrix_2x2;

auto isSymmetric(const mat2& m) -> bool {
	return m == m.transposed();
}

auto isAntiSymmetric(const mat2& m) -> bool {
	return m.transposed() == -1*m;
}

int main(){
	mat2 a {{0.f, 4.f}, {-4.f, 0.f}};
	mat2 b {{1.f, 2.f}, {2.f, 1.f}};

	std::cout << (isSymmetric(a)?"true":"false")  << std::endl;
	std::cout << (isSymmetric(b)?"true":"false") << std::endl;
	std::cout << (isAntiSymmetric(a)?"true":"false") << std::endl;
}
