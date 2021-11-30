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

			inline static auto down() -> Vector2{
				return Vector2(0.f, -1.f);
			}

			inline static auto left() -> Vector2{
				return Vector2(-1.f, 0.f);
			}

			inline static auto right() -> Vector2{
				return Vector2(1.f, 0.f);
			}

			inline static auto up() -> Vector2{
				return Vector2(0.f, 0.f);
			}
			
			inline
			Vector2(float x=0.f, float y=0.f): changed_length{true}, x{x}, y{y}{
			}

			inline
			Vector2(const Vector2& other): changed_length{true}, x{other.x}, y{other.y}{
			}

			/*
			Vector2(const Vector3& vec3): x{vec3.x}, y{vec3.y}{
			}
			*/

			inline auto getX() const -> float {
				return this->x;
			}
			
			inline auto getY() const -> float {
				return this->y;
			}

			inline auto setX(const float& new_x) -> Vector2& {
				this->changed_length = true;
				this->x = new_x;
				return *this;
			}

			inline auto setY(const float& new_y) -> Vector2& {
				this->changed_length = true;
				this->y = new_y;
				return *this;
			}

			inline auto set(const float& new_x, const float& new_y) -> Vector2& {
				this->changed_length = true;
				this->x = new_x;
				this->y = new_y;
				return *this;
			}

			inline auto set(const Vector2& other) -> Vector2& {
				if(this == &other) return *this;
				this->changed_length = true;
				this->x = other.getX();
				this->y = other.getY();
				return *this;
			}

			inline auto squared_length() const -> float {
				return x*x + y*y;
			}

			auto length() const -> float {
				static auto cache{ 0.f };;
				if(changed_length)
					cache = sqrtf(this->squared_length());
				this->changed_length = false;
				return cache;
			}

			inline auto to(const Vector2& other) const -> Vector2 {
				return Vector2(other.getX()-x, other.getY()-y);
			}

			inline auto dot_prod(const Vector2& other) const -> float {
				return this->x*other.getX() + this->y*other.getY();
			}

			inline auto infront_of(const Vector2& other, const Vector2& other_fwd)
			const -> float {
				auto vt { other.to(*this)._normalize() };
				auto vn { other_fwd.normalized() };
				return vn.dot_prod(vt);
			}

			inline auto behind_of(const Vector2& other, const Vector2& other_fwd)
			const -> float {
				return -1.f*infront_of(other, other_fwd);
			}

			inline auto move_towards(const Vector2& other, const float& amt)
			const -> Vector2{
				auto to{ this->to(other) };
				return (*this+to._scale(amt));
			}

			inline auto _move_towards(const Vector2& other, const float& amt)
			-> Vector2& {
				this->changed_length = true;
				return _add(to(other)._scale(amt));
			}

			inline auto normalized() const -> Vector2 {
				auto length{ this->length() };
				return Vector2(x/length, y/length);
			}

			inline auto _normalize() -> Vector2& {
				auto length { this->length() };
				this->x /= length;
				this->y /= length;
				this->changed_length = true;
				return *this;
			}

			inline auto scaled(const float& factor) const -> Vector2{
				return Vector2(x*factor, y*factor);
			}

			inline auto _scale(const float& factor) -> Vector2&{
				this->changed_length = true;
				this->x *= factor;
				this->y *= factor;
				return *this;
			}

			inline auto subtract(const Vector2& other) const -> Vector2 {
				return Vector2(x-other.getX(), y-other.getY());
			}
			
			inline auto _subtract(const Vector2& other) -> Vector2& {
				this->changed_length = true;
				this->x -= other.getX();
				this->y -= other.getY();
				return *this;
			}

			inline auto divide(const float& divisor) const -> Vector2 {
				//if(divisor == 0) return Vector2.infinity;
				return Vector2(x/divisor, y/divisor);
			}

			inline auto _divide(const float& divisor) -> Vector2& {
				this->changed_length = true;
				this->x /= divisor;
				this->y /= divisor;
				return *this;
			}

			inline auto add(const Vector2& other) const -> Vector2 {
				return Vector2(x+other.getX(), y+other.getY()); 
			}

			inline auto _add(const Vector2& other) -> Vector2& {
				this->changed_length = true;
				this->x += other.getX();
				this->y += other.getY();
				return *this;
			}

			inline auto operator*(const float& factor) const -> Vector2 {
				return this->scaled(factor);
			}

			inline auto operator/(const float& divisor) const -> Vector2 {
				return this->divide(divisor);
			}

			inline auto operator+(const Vector2& other) const -> Vector2 {
				return this->add(other);
			}

			inline auto operator-(const Vector2& other) const -> Vector2 {
				return this->subtract(other);
			}

			inline auto operator=(const Vector2& other) -> Vector2&{
				return this->set(other);
			}

			inline auto operator-=(const Vector2& other) -> Vector2&{
				return this->_subtract(other);
			}

			inline auto operator+=(const Vector2& other) -> Vector2&{
				return this->_add(other);
			}

			inline auto operator/=(const float& divisor) -> Vector2&{
				return this->_divide(divisor);
			}

			inline auto operator*=(const float& factor) -> Vector2&{
				return this->_scale(factor);
			}

			inline auto operator==(const Vector2& other) -> bool {
				return 
					fabs(x - other.getX()) < Vector2::tollerance
				 && fabs(y - other.getY()) < Vector2::tollerance;
			}

			inline auto operator!=(const Vector2& other) -> bool {
				return !(*this==other);
			}

			auto operator%=(const int& d) = delete;
			auto operator&=(const int& d) = delete;
			auto operator|=(const int& d) = delete;
			auto operator^=(const int& d) = delete;
			auto operator>>=(const int& d) = delete;
			auto operator<<=(const int& d) = delete;

			friend
			auto operator>>(std::istream &in, Vector2& vec)
			-> std::istream&;
    };

	inline auto operator*(float factor, const Vector2& vec) -> Vector2 {
		return vec.scaled(factor);
	}

	inline auto operator<<(std::ostream &out, const Vector2& vec) 
	-> std::ostream& {
       	out << "[X: " << vec.getX() << " Y: " << vec.getY() << " ]";
   		return out;
   	}
	
	inline auto operator>>(std::istream &in, Vector2& vec)
	-> std::istream& {
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

	inline auto lerp(const float& goal, const float& current, const float& step=0.1f)
	-> float {
		auto dif{ goal - current };
		[[likely]]
		if(dif > step)  return current+step;
		if(dif < -step) return current-step;
		return goal;
	}
}
}

