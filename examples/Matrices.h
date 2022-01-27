#include "common.hpp"

void matrices(){
	using mat = drop::math::Matrix_4x4;

	const mat A{
		{1.f, 3.f, 4.f, 5.f}, 
		{2.f, 4.f, 2.f, 6.f}, 
		{2.f, 4.f, 2.f, 6.f}, 
		{1.f, 2.f, 3.f, 7.f}
	};
	
	const mat B{
		{1.f, 3.f, 4.f, 5.f}, 
		{2.f, 4.f, 2.f, 6.f}, 
		{2.f, 4.f, 2.f, 6.f}, 
		{1.f, 2.f, 3.f, 7.f}
	};

	const mat C{
		{1.f, 3.f, 4.f, 5.f}, 
		{2.f, 4.f, 2.f, 6.f}, 
		{2.f, 4.f, 2.f, 6.f}, 
		{1.f, 2.f, 3.f, 7.f}
	};

	const mat sC	{ C.applyTo(C) }; 
	const mat tA	{ A.transposed() };
	const mat tCB	{ C.applyTo(B)._transpose() };

	const mat res	{ sC - tA*tCB };
	std::cout << "Result:\n" << res << std::endl;
}
