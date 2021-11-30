#pragma once

#include <cmath>
#include <iostream>

namespace drop{
namespace math{

    class Vector2{
		mutable bool changed_length;
        float x, y;
				
		public:
			static constexpr float tollerance{ 0.0001f };

			static auto down() -> Vector2{
				return Vector2(0.f, -1.f);
			}

			static auto left() -> Vector2{
				return Vector2(-1.f, 0.f);
			}

			static auto right() -> Vector2{
				return Vector2(1.f, 0.f);
			}

			static auto up() -> Vector2{
				return Vector2(0.f, 0.f);
			}

			Vector2(float x=0.f, float y=0.f): changed_length{true}, x{x}, y{y}{
			}

			Vector2(const Vector2& other): changed_length{true}, x{other.x}, y{other.y}{
			}

			/*
			Vector2(const Vector3& vec3): x{vec3.x}, y{vec3.y}{
			}
			*/

			auto getX() const -> float {
				return this->x;
			}
			
			auto getY() const -> float {
				return this->y;
			}

			auto setX(const float& new_x) -> Vector2& {
				this->changed_length = true;
				this->x = new_x;
				return *this;
			}

			auto setY(const float& new_y) -> Vector2& {
				this->changed_length = true;
				this->y = new_y;
				return *this;
			}

			auto set(const float& new_x, const float& new_y) -> Vector2& {
				this->changed_length = true;
				this->x = new_x;
				this->y = new_y;
				return *this;
			}

			auto set(const Vector2& other) -> Vector2& {
				if(this == &other) return *this;
				this->changed_length = true;
				this->x = other.getX();
				this->y = other.getY();
				return *this;
			}

			auto squared_length() const -> float {
				return x*x + y*y;
			}

			auto length() const -> float {
				static auto cache{ 0.f };;
				if(changed_length)
					cache = sqrtf(this->squared_length());
				this->changed_length = false;
				return cache;
			}

			auto to(const Vector2& other) const -> Vector2 {
				return Vector2(other.getX()-x, other.getY()-y);
			}

			auto moveTowards(const Vector2& other, const float& amt)
			const -> Vector2{
				auto to{ this->to(other) };
				return (*this+to._scale(amt));
			}

			auto _moveTowards(const Vector2& other, const float& amt)
			-> Vector2& {
				this->changed_length = true;
				return _add(to(other)._scale(amt));
			}

			auto normalized() const -> Vector2 {
				auto length{ this->length() };
				return Vector2(x/length, y/length);
			}

			auto _normalize() -> Vector2& {
				auto length { this->length() };
				this->x /= length;
				this->y /= length;
				this->changed_length = true;
				return *this;
			}

			auto scaled(const float& factor) const -> Vector2{
				return Vector2(x*factor, y*factor);
			}

			auto _scale(const float& factor) -> Vector2&{
				this->changed_length = true;
				this->x *= factor;
				this->y *= factor;
				return *this;
			}

			auto subtract(const Vector2& other) const -> Vector2 {
				return Vector2(x-other.getX(), y-other.getY());
			}
			
			auto _subtract(const Vector2& other) -> Vector2& {
				this->changed_length = true;
				this->x -= other.getX();
				this->y -= other.getY();
				return *this;
			}

			auto divide(const float& divisor) const -> Vector2 {
				//if(divisor == 0) return Vector2.infinity;
				return Vector2(x/divisor, y/divisor);
			}

			auto _divide(const float& divisor) -> Vector2& {
				this->changed_length = true;
				this->x /= divisor;
				this->y /= divisor;
				return *this;
			}

			auto add(const Vector2& other) const -> Vector2 {
				return Vector2(x+other.getX(), y+other.getY()); 
			}

			auto _add(const Vector2& other) -> Vector2& {
				this->changed_length = true;
				this->x += other.getX();
				this->y += other.getY();
				return *this;
			}

			auto operator*(const float& factor) const -> Vector2 {
				return this->scaled(factor);
			}

			auto operator/(const float& divisor) const -> Vector2 {
				return this->divide(divisor);
			}

			auto operator+(const Vector2& other) const -> Vector2 {
				return this->add(other);
			}

			auto operator-(const Vector2& other) const -> Vector2 {
				return this->subtract(other);
			}

			auto operator=(const Vector2& other) -> Vector2&{
				return this->set(other);
			}

			auto operator-=(const Vector2& other) -> Vector2&{
				return this->_subtract(other);
			}

			auto operator+=(const Vector2& other) -> Vector2&{
				return this->_add(other);
			}

			auto operator/=(const float& divisor) -> Vector2&{
				return this->_divide(divisor);
			}

			auto operator*=(const float& factor) -> Vector2&{
				return this->_scale(factor);
			}

			auto operator==(const Vector2& other) -> bool {
				return 
					fabs(x - other.getX()) < Vector2::tollerance
				 && fabs(y - other.getY()) < Vector2::tollerance;
			}

			auto operator!=(const Vector2& other) -> bool {
				return !(*this==other);
			}

			auto operator%=(const int& d) = delete;
			auto operator&=(const int& d) = delete;
			auto operator|=(const int& d) = delete;
			auto operator^=(const int& d) = delete;
			auto operator>>=(const int& d) = delete;
			auto operator<<=(const int& d) = delete;

			friend
			std::istream& operator>>( std::istream &in, Vector2& vec );
    };

	inline auto operator*(float factor, const Vector2& vec) -> Vector2 {
		return vec.scaled(factor);
	}

	inline std::ostream& operator<<( std::ostream &out, const Vector2& vec ) {
       	out << "[X: " << vec.getX() << " Y: " << vec.getY() << " ]";
   		return out;
   	}
	
	inline std::istream& operator>>( std::istream &in, Vector2& vec ) {
    	in >> vec.x >> vec.y;
    	return in;
	}

    class Vector3{
        float x, y, z;

    public:
        Vector3(float x=0, float y=0, float z=0): x{x}, y{y}, z{z}{
        }

        auto squared_length() -> float {
            return x*x + y*y + z*z;
        }

        auto length() -> float {
            return sqrt(this->squared_length());
        }
    };
}
}

