#pragma once

#include <dropMath.hpp>
#include "Timer.hpp"

bool general_tests(){
	{
		using Vector3 = drop::math::Vector3;
		auto vectorAlgebra{ Timer("Vector Algebra Tests") };
		std::cout << "2[-2, 1, -2]+5[-1, 3, 0]-6[4, 1, 3]-[1, 1, 1]" 
		<< std::endl;

		auto result{ 
			2.f*Vector3(-2.f, 1.f, -2.f) 
		  + 5.f*Vector3(-1.f, 3.f, 0.f)
		  - 6.f*Vector3(4.f, 1.f, 3.f)
		  - Vector3(1.f, 1.f, 1.f)
		};
		
		std::cout <<"= " << result << std::endl;
		
	}
	{
		using Matrix = drop::math::Matrix_2x2;
		auto matrixAlgebra{ Timer("Matrix_2x2 Algebra Tests") };

		auto a{ Matrix(2.f, 4.f, -1.f, 3.f) };
		auto b{ Matrix(-5.f, -1.f, 2.f, 6.f) };
		auto c{ Matrix(3.f, 2.f, -1.f, 1.f) };

		std::cout << "Matrix A:\n"
		<< a 
		<< "\nMatrix B:\n"
		<< b
		<< "\nMatrix C:\n"
		<< c << std::endl;
		
		std::cout << "A Transposed:\n"
		<< a.transposed() << std::endl;

		std::cout << "A Transposed + 5B:\n"
		<< (a._transpose() + b*5.0f) << std::endl;
		
		std::cout << "A^T*B*C :\n"
		<< a.applyTo(b.applyTo(c)) << std::endl;
	}
	{
		using Matrix = drop::math::Matrix_3x3;
		using Vector = drop::math::Vector3;
		auto linearDependence{ Timer("Linear Dependence Test") };

		auto v1{ Vector(1.f, 1.f, 1.f) }; 
		auto v2{ Vector(3.f, 4.f, 5.f) }; 
		auto v3{ Vector(1.f, 2.f, 3.f) }; 
		
		auto m{ Matrix(v1, v2, v3) };

		std::cout 
		<< "Vector 1: " << v1
		<< "\nVector 2: " << v2
		<< "\nVector 3: " << v3
		<< "\nThe vectors are linear "
		<< (m.isIndependent()? "independent" : "dependent")
		<< std::endl;
		
	}
	{
		using Matrix = drop::math::Matrix_3x3;
		using Vector = drop::math::Vector3;
		auto linearDependence{ Timer("Linear Dependence Test 2") };

		auto v1{ Vector(-2.f, 3.f, 1.f) }; 
		auto v2{ Vector(4.f, 1.f, 0.f) }; 
		auto v3{ Vector(1.f, -1.f, 2.f) }; 
		
		auto m{ Matrix(v1, v2, v3) };

		std::cout << "Do these 3 Vectors form a basis of the R³?\n";
		std::cout 
		<< "Vector 1: " << v1
		<< "\nVector 2: " << v2
		<< "\nVector 3: " << v3
		<< "\nThe vectors "
		<< (m.isIndependent()? "form a basis" : "are not a basis")
		<< std::endl;
	}
	{
		using Matrix_2x2 = drop::math::Matrix_2x2;
		using Matrix_3x3 = drop::math::Matrix_3x3;
		using Matrix_4x4 = drop::math::Matrix_4x4;

		auto determinants{ Timer("Determinant Calculation Tests") };

		auto m1{ Matrix_2x2({1.f, 2.f}, {3.f, 4.f}) };
		auto m2{ Matrix_3x3({5.f, 7.f, 4.f}, {6.f, 1.f, 3.f}, {7.f, 2.f, 2.f}) };
		auto m3{ Matrix_4x4(
				{3.f, 9.f, 4.f, 4.f},
				{6.f, 2.f, 8.f, 2.f},
				{4.f, 6.f, 3.f, 1.f},
				{1.f, 9.f, 8.f, 0.f}) 
		};

		std::cout
		<< "Matrix M1:\n" << m1 << "\nhas a determinant of " << m1.determinant() << std::endl
		<< "Matrix M2:\n" << m2 << "\nhas a determinant of " << m2.determinant() << std::endl
		<< "Matrix M3:\n" << m3 << "\nhas a determinant of " << m3.determinant() << std::endl;
	}
	{
		using Matrix_2x2 = drop::math::Matrix_2x2;
		using Matrix_3x3 = drop::math::Matrix_3x3;
		using Matrix_4x4 = drop::math::Matrix_4x4;

		using Vector2 = drop::math::Vector2;
		using Vector3 = drop::math::Vector3;
		using Vector4 = drop::math::Vector4;

		auto linearEquationSystems{ Timer("Solving Linear Equation Systems") };

		auto lgs1{ Matrix_2x2({2.f, 3.f}, {1.f, 5.f}) };
		auto lgs2{ Matrix_3x3({5.f, 2.f, 8.f}, {1.f, 3.f, 4.f}, {2.f, 4.f, 7.f}) };
		auto lgs3{ 
			Matrix_4x4(
				{5.f, 2.f, 8.f, 4.f}, 
				{1.f, 3.f, 4.f, 6.f}, 
				{1.f, 3.f, 4.f, 7.f}, 
				{2.f, 4.f, 7.f, 6.f}
			) 
		};

		auto sol1{ Vector2(2.f, 3.f) };
		auto sol2{ Vector3(4.f, 5.f, 7.f) };
		auto sol3{ Vector4(1.f, 1.f, 2.f, 2.f) };
		
		auto res1{ lgs1.solveFor(sol1) };
		auto res2{ lgs2.solveFor(sol2) };
		auto res3{ lgs3.solveFor(sol3) };

		std::cout
		<< "Solving\n" << lgs1 << "\nfor " << sol1 
		<< "\nhas the solution: " << res1 << std::endl;
		std::cout
		<< "\nSolving\n" << lgs2 << "\nfor " << sol2 
		<< "\nhas the solution: " << res2 << std::endl;
		std::cout
		<< "\nSolving\n" << lgs3 << "\nfor " << sol3 
		<< "\nhas the solution: " << res3 << std::endl;
	}
	{
		using Matrix_2x2 = drop::math::Matrix_2x2;
		using Matrix_3x3 = drop::math::Matrix_3x3;
		using Matrix_4x4 = drop::math::Matrix_4x4;

		auto invertText{ Timer("Matrix Invertion test") };

		auto m1{ Matrix_2x2({1.f, 0.f}, {0.f, -1.f}) };
		auto m2{ Matrix_3x3({3.f, 0.f, 2.f}, {1.f, 0.f, 2.f}, {0.f, 1.f, 0.f}) };
		auto m3{ Matrix_4x4(
						{1.f, 0.f, 0.f, -1.f},
						{0.f, 2.f, -2.f, 0.f},
						{0.f, 0.f, 3.f, 0.f},
						{0.f, 0.f, 0.f, 4.f}
				)};
		
		std::cout <<"Matrix 1:\n"<<m1<<"\nMatrix 1 inverted:\n"<<m1.inverted()<<std::endl;
		std::cout <<"Matrix 2:\n"<<m2<<"\nMatrix 2 inverted:\n"<<m2.inverted()<<std::endl;
		std::cout <<"Matrix 3:\n"<<m3<<"\nMatrix 3 inverted:\n"<<m3.inverted()<<std::endl;

	}
	{
		using vec3 = drop::math::Vector3;
		
		auto angleTest{ Timer("Angle between 2 Vectors") };

		auto a{ vec3(1.f, 2.f, -2.f) };
		auto b{ vec3(-3.f, -3.f, 0.f) };
		std::cout << "a * b = " << a.dot_prod(b) << std::endl;
		std::cout << "Length of a is " << a.length() << std::endl;
		std::cout << "Length of b is " << b.length() << std::endl;

		std::cout << "Angle between Vector a : " << a
				  << " and Vector b : " << b
				  << "\nis " << a.angle_deg(b) << " degree."
				  << std::endl;
	}
	{
		using vec3 = drop::math::Vector3;
		
		auto grassman{ Timer("Grassman Identity") };

		auto c{ vec3(1.f, 3.f, 1.f) };
		auto b{ vec3(-2.f, 1.f, 1.f) };
		auto a{ vec3(2.f, 2.f, 3.f) };

		//c x (a x b)
		auto res = c.dot_prod(b)*a - c.dot_prod(a)*b; 

		std::cout << "Searched Vector is: " << res << std::endl;
	}
	return true;
}
