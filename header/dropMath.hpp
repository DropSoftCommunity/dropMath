#pragma once

#include <cmath>
#include <iostream>
#include <limits>

namespace drop{
namespace math{

    class Vector2{
		mutable bool changed_length;
        float x, y;
				
		public:
			static constexpr float tollerance{ 0.0001f };

			static constexpr auto infinity() -> Vector2 {
				const auto inf{ std::numeric_limits<float>::infinity()};
				return Vector2(inf, inf);
			}

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
			
			inline constexpr
			Vector2(float x=0.f, float y=0.f): changed_length{true}, x{x}, y{y}{
			}

			inline constexpr
			Vector2(const Vector2& other): changed_length{true}, x{other.x}, y{other.y}{
			}

			/*
			Vector2(const Vector3& vec3): x{vec3.x}, y{vec3.y}{
			}
			*/
			
			inline constexpr
			auto getX() const -> float {
				return this->x;
			}
					
			inline constexpr
			auto getY() const -> float {
				return this->y;
			}
			
			inline constexpr
			auto setX(const float& new_x) -> Vector2& {
				this->changed_length = true;
				this->x = new_x;
				return *this;
			}

			inline constexpr
			auto setY(const float& new_y) -> Vector2& {
				this->changed_length = true;
				this->y = new_y;
				return *this;
			}

			inline constexpr
			auto set(const float& new_x, const float& new_y) -> Vector2& {
				this->changed_length = true;
				this->x = new_x;
				this->y = new_y;
				return *this;
			}

			inline constexpr
			auto set(const Vector2& other) -> Vector2& {
				if(this == &other) return *this;
				this->changed_length = true;
				this->x = other.getX();
				this->y = other.getY();
				return *this;
			}

			inline constexpr 
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
			
			inline constexpr
			auto to(const Vector2& other) const -> Vector2 {
				return Vector2(other.getX()-x, other.getY()-y);
			}
			
			inline
			auto distance(const Vector2& to) const -> float {
				return this->to(to).length();
			}

			inline constexpr
			auto dot_prod(const Vector2& other) const -> float {
				return this->x*other.getX() + this->y*other.getY();
			}

			inline constexpr
			auto equals(const Vector2& other) const -> bool {
				return *this == other;
			}

			inline constexpr
			auto angle_deg(const Vector2& other) const -> float {
				[[unlikely]]
				if(this == &other) return 0.f;
				if(this->equals(other)) return 0.f;
				return acos(this->dot_prod(other));
			}

			inline
			auto infront_of(const Vector2& other, const Vector2& other_fwd)
			const -> float {
				auto vt { other.to(*this)._normalize() };
				auto vn { other_fwd.normalized() };
				return vn.dot_prod(vt);
			}

			inline 
			auto behind_of(const Vector2& other, const Vector2& other_fwd)
			const -> float {
				return -1.f*infront_of(other, other_fwd);
			}

			inline constexpr
			auto move_towards(const Vector2& other, const float& amt)
			const -> Vector2{
				auto to{ this->to(other) };
				return (*this+to._scale(amt));
			}

			inline constexpr
			auto _move_towards(const Vector2& other, const float& amt)
			-> Vector2& {
				this->changed_length = true;
				return _add(to(other)._scale(amt));
			}

			inline
			auto normalized() const -> Vector2 {
				auto length{ this->length() };
				return Vector2(x/length, y/length);
			}

			inline
			auto _normalize() -> Vector2& {
				auto length { this->length() };
				this->x /= length;
				this->y /= length;
				this->changed_length = true;
				return *this;
			}

			inline
			auto set_length(const float& n_length) -> Vector2 const {
				return this->normalized()._scale(n_length);
			}

			inline
			auto _set_length(const float& n_length) -> Vector2& {
				return this->_normalize()._scale(n_length);
			}

			inline constexpr
			auto scaled(const float& factor) const -> Vector2{
				return Vector2(x*factor, y*factor);
			}

			inline constexpr
			auto _scale(const float& factor) -> Vector2&{
				this->changed_length = true;
				this->x *= factor;
				this->y *= factor;
				return *this;
			}

			inline constexpr
			auto subtract(const Vector2& other) const -> Vector2 {
				return Vector2(x-other.getX(), y-other.getY());
			}
			
			inline constexpr
			auto _subtract(const Vector2& other) -> Vector2& {
				this->changed_length = true;
				this->x -= other.getX();
				this->y -= other.getY();
				return *this;
			}

			inline constexpr
			auto divide(const float& divisor) const -> Vector2 {
				if(divisor == 0) return Vector2::infinity();
				return Vector2(x/divisor, y/divisor);
			}

			inline constexpr
			auto _divide(const float& divisor) -> Vector2& {
				this->changed_length = true;
				this->x /= divisor;
				this->y /= divisor;
				return *this;
			}

			inline constexpr
			auto add(const Vector2& other) const -> Vector2 {
				return Vector2(x+other.getX(), y+other.getY()); 
			}

			inline constexpr
			auto _add(const Vector2& other) -> Vector2& {
				this->changed_length = true;
				this->x += other.getX();
				this->y += other.getY();
				return *this;
			}

			inline constexpr
			auto operator*(const float& factor) const -> Vector2 {
				return this->scaled(factor);
			}

			inline constexpr
			auto operator/(const float& divisor) const -> Vector2 {
				return this->divide(divisor);
			}

			inline constexpr
			auto operator+(const Vector2& other) const -> Vector2 {
				return this->add(other);
			}

			inline constexpr
			auto operator-(const Vector2& other) const -> Vector2 {
				return this->subtract(other);
			}

			inline constexpr
			auto operator=(const Vector2& other) -> Vector2&{
				return this->set(other);
			}

			inline constexpr
			auto operator-=(const Vector2& other) -> Vector2&{
				return this->_subtract(other);
			}

			inline constexpr
			auto operator+=(const Vector2& other) -> Vector2&{
				return this->_add(other);
			}

			inline constexpr
			auto operator/=(const float& divisor) -> Vector2&{
				return this->_divide(divisor);
			}

			inline constexpr
			auto operator*=(const float& factor) -> Vector2&{
				return this->_scale(factor);
			}

			inline constexpr
			auto operator==(const Vector2& other) const -> bool {
				return 
					fabs(x - other.getX()) < Vector2::tollerance
				 && fabs(y - other.getY()) < Vector2::tollerance;
			}

			inline constexpr
			auto operator!=(const Vector2& other) const -> bool {
				return !(*this==other);
			}

			inline constexpr
			auto operator[](const int& index) -> float& {
				return (!index ? this->x : this->y);
			}

			auto operator%=(const int& d) = delete;
			auto operator&=(const int& d) = delete;
			auto operator|=(const int& d) = delete;
			auto operator^=(const int& d) = delete;
			auto operator>>=(const int& d) = delete;
			auto operator<<=(const int& d) = delete;

			friend inline 
			auto operator>>(std::istream &in, Vector2& vec)
			-> std::istream&;
    };

	inline constexpr
	auto operator*(float factor, const Vector2& vec) -> Vector2 {
		return vec.scaled(factor);
	}

	inline 
	auto operator<<(std::ostream &out, const Vector2& vec) 
	-> std::ostream& {
       	out << "[X: " << vec.getX() << " Y: " << vec.getY() << " ]";
   		return out;
   	}
	
	inline 
	auto operator>>(std::istream &in, Vector2& vec)
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

	inline constexpr
	auto lerp(const float& goal, const float& current, const float& step)
	-> float {
		auto dif{ goal - current };
		[[likely]]
		if(dif > step)  return current+step;
		if(dif < -step) return current-step;
		[[unlikely]]
		return goal;
	}
}
}

