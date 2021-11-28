#include "../header/dropMath.hpp"


int main(){
	using Vector2 = drop::math::Vector2;
	auto v1 = Vector2(1.f, 2.f);
	auto v2 = Vector2::up();

	auto len1 = v1.length();
	auto len2 = v2.length();

	auto v3 = v1 + v2;
}
