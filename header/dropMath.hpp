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
				return Vector2(0.f, 1.f);
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

			inline constexpr
			auto rotated(const float& angle_deg) const -> Vector2 {
				return Vector2(
						x*cos(angle_deg) - y*sin(angle_deg),
						x*sin(angle_deg) + y*cos(angle_deg)
				);
			}

			inline constexpr
			auto _rotate(const float& angle_deg) -> Vector2& {
				return this->set(
						x*cos(angle_deg) - y*sin(angle_deg),
						x*sin(angle_deg) + y*cos(angle_deg)
				);
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

			inline constexpr
			auto project(const Vector2& other) const -> Vector2 {
				return (this->dot_prod(other)/other.dot_prod(other));
			}

			inline constexpr
			auto _project(const Vector2& other) -> Vector2& {
				return this->set(project(other));
			}

			inline
			auto set_length(const float& n_length) -> Vector2 {
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
		mutable bool changed_length;
        float x, y, z;
				
		public:
			static constexpr float tollerance{ 0.0001f };

			static constexpr auto infinity() -> Vector3 {
				const auto inf{ std::numeric_limits<float>::infinity()};
				return Vector3(inf, inf, inf);
			}

			inline static auto down() -> Vector3{
				return Vector3(0.f, -1.f, 0.f);
			}

			inline static auto left() -> Vector3{
				return Vector3(-1.f, 0.f, 0.f);
			}

			inline static auto right() -> Vector3{
				return Vector3(1.f, 0.f, 0.f);
			}

			inline static auto up() -> Vector3{
				return Vector3(0.f, 1.f, 0.f);
			}
			
			inline static auto forward() -> Vector3{
				return Vector3(0.f, 0.f, 1.f);
			}

			inline static auto backward() -> Vector3{
				return Vector3(0.f, 0.f, -1.f);
			}

			inline constexpr
			Vector3(float x=0.f, float y=0.f, float z=0.f): changed_length{true}, x{x}, y{y}, z{z}{
			}

			inline constexpr
			Vector3(const Vector3& other): changed_length{true}, x{other.x}, y{other.y}, z{other.z}{
			}

			inline constexpr
			Vector3(const Vector2& vec2): changed_length{true}, x{vec2.getX()}, y{vec2.getY()}, z{0.f}{
			}
			
			inline constexpr
			auto getX() const -> float {
				return this->x;
			}
					
			inline constexpr
			auto getY() const -> float {
				return this->y;
			}

			inline constexpr
			auto getZ() const -> float {
				return this->z;
			}
			
			inline constexpr
			auto setX(const float& new_x) -> Vector3& {
				this->changed_length = true;
				this->x = new_x;
				return *this;
			}

			inline constexpr
			auto setY(const float& new_y) -> Vector3& {
				this->changed_length = true;
				this->y = new_y;
				return *this;
			}

			inline constexpr
			auto setZ(const float& new_z) -> Vector3& {
				this->changed_length = true;
				this->z = new_z;
				return *this;
			}

			inline constexpr
			auto set(const float& new_x, const float& new_y, const float& new_z) -> Vector3& {
				this->changed_length = true;
				this->x = new_x;
				this->y = new_y;
				this->z = new_z;
				return *this;
			}

			inline constexpr
			auto set(const Vector3& other) -> Vector3& {
				if(this == &other) return *this;
				this->changed_length = true;
				this->x = other.getX();
				this->y = other.getY();
				this->z = other.getZ();
				return *this;
			}

			inline constexpr 
			auto squared_length() const -> float {
				return x*x + y*y + z*z;
			}
			
			auto length() const -> float {
				static auto cache{ 0.f };
				if(changed_length)
					cache = sqrtf(this->squared_length());
				this->changed_length = false;
				return cache;
			}
			
			inline constexpr
			auto to(const Vector3& other) const -> Vector3 {
				return Vector3(other.getX()-x, other.getY()-y, other.getZ()-z);
			}
			
			inline
			auto distance(const Vector3& to) const -> float {
				return this->to(to).length();
			}

			inline 
			auto dot_prod(const Vector3& other) const -> float {
				return Vector3(x*other.x, y*other.y, z*other.z).length()
					   *cos(this->angle_deg(other));
			}

			inline constexpr
			auto cross_prod(const Vector3& other) const -> Vector3 {
				return Vector3(y*other.z - z*other.y,
							   z*other.x - x*other.z,
							   x*other.y - y*other.x);
			}

			inline constexpr
			auto equals(const Vector3& other) const -> bool {
				return *this == other;
			}

			inline 
			auto angle_deg(const Vector3& other) const -> float {
				return acos((x*other.x+y*other.y+z*other.z)
						/(this->length() * other.length()));
			}

			inline
			auto infront_of(const Vector3& other, const Vector3& other_fwd)
			const -> float {
				auto vt { other.to(*this)._normalize() };
				auto vn { other_fwd.normalized() };
				return vn.dot_prod(vt);
			}

			inline 
			auto behind_of(const Vector3& other, const Vector3& other_fwd)
			const -> float {
				return -1.f*infront_of(other, other_fwd);
			}

			inline constexpr
			auto move_towards(const Vector3& other, const float& amt)
			const -> Vector3{
				auto to{ this->to(other) };
				return (*this+to._scale(amt));
			}

			inline constexpr
			auto _move_towards(const Vector3& other, const float& amt)
			-> Vector3& {
				this->changed_length = true;
				return _add(to(other)._scale(amt));
			}

			inline
			auto normalized() const -> Vector3 {
				auto length{ this->length() };
				return Vector3(x/length, y/length, z/length);
			}

			inline
			auto _normalize() -> Vector3& {
				auto length { this->length() };
				this->x /= length;
				this->y /= length;
				this->z /= length;
				this->changed_length = true;
				return *this;
			}

			inline
			auto set_length(const float& n_length) -> Vector3 const {
				return this->normalized()._scale(n_length);
			}

			inline
			auto _set_length(const float& n_length) -> Vector3& {
				return this->_normalize()._scale(n_length);
			}

			inline constexpr
			auto scaled(const float& factor) const -> Vector3{
				return Vector3(x*factor, y*factor, z*factor);
			}

			inline constexpr
			auto _scale(const float& factor) -> Vector3&{
				this->changed_length = true;
				this->x *= factor;
				this->y *= factor;
				this->z *= factor;
				return *this;
			}

			inline constexpr
			auto subtract(const Vector3& other) const -> Vector3 {
				return Vector3(x-other.getX(), y-other.getY(), z-other.getZ());
			}
			
			inline constexpr
			auto _subtract(const Vector3& other) -> Vector3& {
				this->changed_length = true;
				this->x -= other.getX();
				this->y -= other.getY();
				this->z -= other.getZ();
				return *this;
			}

			inline constexpr
			auto divide(const float& divisor) const -> Vector3 {
				if(divisor == 0) return Vector2::infinity();
				return Vector3(x/divisor, y/divisor, z/divisor);
			}

			inline constexpr
			auto _divide(const float& divisor) -> Vector3& {
				this->changed_length = true;
				this->x /= divisor;
				this->y /= divisor;
				this->z /= divisor;
				return *this;
			}

			inline constexpr
			auto add(const Vector3& other) const -> Vector3 {
				return Vector3(x+other.getX(), y+other.getY(), z+other.getZ()); 
			}

			inline constexpr
			auto _add(const Vector3& other) -> Vector3& {
				this->changed_length = true;
				this->x += other.getX();
				this->y += other.getY();
				this->z += other.getZ();
				return *this;
			}

			inline constexpr
			auto operator*(const float& factor) const -> Vector3 {
				return this->scaled(factor);
			}

			inline constexpr
			auto operator/(const float& divisor) const -> Vector3 {
				return this->divide(divisor);
			}

			inline constexpr
			auto operator+(const Vector3& other) const -> Vector3 {
				return this->add(other);
			}

			inline constexpr
			auto operator-(const Vector3& other) const -> Vector3 {
				return this->subtract(other);
			}

			inline constexpr
			auto operator=(const Vector3& other) -> Vector3&{
				return this->set(other);
			}

			inline constexpr
			auto operator-=(const Vector3& other) -> Vector3&{
				return this->_subtract(other);
			}

			inline constexpr
			auto operator+=(const Vector3& other) -> Vector3&{
				return this->_add(other);
			}

			inline constexpr
			auto operator/=(const float& divisor) -> Vector3&{
				return this->_divide(divisor);
			}

			inline constexpr
			auto operator*=(const float& factor) -> Vector3&{
				return this->_scale(factor);
			}

			inline constexpr
			auto operator==(const Vector3& other) const -> bool {
				return 
					fabs(x - other.getX()) < Vector3::tollerance
				 && fabs(y - other.getY()) < Vector3::tollerance
				 && fabs(z - other.getZ()) < Vector3::tollerance;
			}

			inline constexpr
			auto operator!=(const Vector3& other) const -> bool {
				return !(*this==other);
			}

			inline constexpr
			auto operator[](const int& index) -> float& {
				switch(index){
					case 0:  return this->x;
					case 1:  return this->y;
					default: return this->z;
				}
			}

			auto operator%=(const int& d) = delete;
			auto operator&=(const int& d) = delete;
			auto operator|=(const int& d) = delete;
			auto operator^=(const int& d) = delete;
			auto operator>>=(const int& d) = delete;
			auto operator<<=(const int& d) = delete;

			friend inline 
			auto operator>>(std::istream &in, Vector3& vec)
			-> std::istream&;
    };

	inline constexpr
	auto operator*(float factor, const Vector3& vec) -> Vector3 {
		return vec.scaled(factor);
	}

	inline 
	auto operator<<(std::ostream &out, const Vector3& vec) 
	-> std::ostream& {
       	out << "[X: " << vec.getX() 
			<< " Y: " << vec.getY() 
			<< " Z: " << vec.getZ() << " ]";
   		return out;
   	}
	
	inline 
	auto operator>>(std::istream &in, Vector3& vec)
	-> std::istream& {
    	in >> vec.x >> vec.y >> vec.z;
    	return in;
	}

    class Vector4{
		mutable bool changed_length;
        float x, y, z, w;
				
		public:
			static constexpr float tollerance{ 0.0001f };

			static constexpr auto infinity() -> Vector4 {
				const auto inf{ std::numeric_limits<float>::infinity()};
				return Vector4(inf, inf, inf, inf);
			}

			inline constexpr
			Vector4(float x=0.f, float y=0.f, float z=0.f, float w=0.f)
			:changed_length{true}, x{x}, y{y}, z{z}, w{w}{
			}

			inline constexpr
			Vector4(const Vector4& other)
			:changed_length{true}, x{other.x}, y{other.y}, z{other.z}, w{other.w}{
			}

			inline constexpr
			auto getX() const -> float {
				return this->x;
			}
					
			inline constexpr
			auto getY() const -> float {
				return this->y;
			}

			inline constexpr
			auto getZ() const -> float {
				return this->z;
			}
			
			inline constexpr
			auto getW() const -> float {
				return this->w;
			}

			inline constexpr
			auto setX(const float& new_x) -> Vector4& {
				this->changed_length = true;
				this->x = new_x;
				return *this;
			}

			inline constexpr
			auto setY(const float& new_y) -> Vector4& {
				this->changed_length = true;
				this->y = new_y;
				return *this;
			}

			inline constexpr
			auto setZ(const float& new_z) -> Vector4& {
				this->changed_length = true;
				this->z = new_z;
				return *this;
			}

			inline constexpr
			auto setW(const float& new_w) -> Vector4& {
				this->changed_length = true;
				this->w = new_w;
				return *this;
			}

			inline constexpr
			auto set(const float& new_x, const float& new_y, const float& new_z, const float& new_w)
			-> Vector4& {
				this->changed_length = true;
				this->x = new_x;
				this->y = new_y;
				this->z = new_z;
				this->w = new_w;
				return *this;
			}

			inline constexpr
			auto set(const Vector4& other) -> Vector4& {
				if(this == &other) return *this;
				this->changed_length = true;
				this->x = other.getX();
				this->y = other.getY();
				this->z = other.getZ();
				this->z = other.getW();
				return *this;
			}

			inline constexpr 
			auto squared_length() const -> float {
				return x*x + y*y + z*z + w*w;
			}
			
			auto length() const -> float {
				static auto cache{ 0.f };
				if(changed_length)
					cache = sqrtf(this->squared_length());
				this->changed_length = false;
				return cache;
			}
			
			inline constexpr
			auto to(const Vector4& other) const -> Vector4 {
				return Vector4(other.getX()-x, other.getY()-y,
							   other.getZ()-z, other.getW()-w);
			}
			
			inline
			auto distance(const Vector4& to) const -> float {
				return this->to(to).length();
			}

			inline constexpr
			auto equals(const Vector4& other) const -> bool {
				return *this == other;
			}

			inline constexpr
			auto move_towards(const Vector4& other, const float& amt)
			const -> Vector4{
				auto to{ this->to(other) };
				return (*this+to._scale(amt));
			}

			inline constexpr
			auto _move_towards(const Vector4& other, const float& amt)
			-> Vector4& {
				this->changed_length = true;
				return _add(to(other)._scale(amt));
			}

			inline
			auto normalized() const -> Vector4 {
				auto length{ this->length() };
				return Vector4(x/length, y/length, z/length, w/length);
			}

			inline
			auto _normalize() -> Vector4& {
				auto length { this->length() };
				this->x /= length;
				this->y /= length;
				this->z /= length;
				this->w /= length;
				this->changed_length = true;
				return *this;
			}

			inline
			auto set_length(const float& n_length) -> Vector4 const {
				return this->normalized()._scale(n_length);
			}

			inline
			auto _set_length(const float& n_length) -> Vector4& {
				return this->_normalize()._scale(n_length);
			}

			inline constexpr
			auto scaled(const float& factor) const -> Vector4{
				return Vector4(x*factor, y*factor, z*factor, w*factor);
			}

			inline constexpr
			auto _scale(const float& factor) -> Vector4&{
				this->changed_length = true;
				this->x *= factor;
				this->y *= factor;
				this->z *= factor;
				this->w *= factor;
				return *this;
			}

			inline constexpr
			auto subtract(const Vector4& other) const -> Vector4 {
				return Vector4(x-other.getX(), y-other.getY(),
							   z-other.getZ(), w-other.getW());
			}
			
			inline constexpr
			auto _subtract(const Vector4& other) -> Vector4& {
				this->changed_length = true;
				this->x -= other.getX();
				this->y -= other.getY();
				this->z -= other.getZ();
				this->w -= other.getW();
				return *this;
			}

			inline constexpr
			auto divide(const float& divisor) const -> Vector4 {
				if(divisor == 0) return Vector4::infinity();
				return Vector4(x/divisor, y/divisor, z/divisor, w/divisor);
			}

			inline constexpr
			auto _divide(const float& divisor) -> Vector4& {
				this->changed_length = true;
				this->x /= divisor;
				this->y /= divisor;
				this->z /= divisor;
				this->w /= divisor;
				return *this;
			}

			inline constexpr
			auto add(const Vector4& other) const -> Vector4 {
				return Vector4(x+other.getX(), y+other.getY(),
							   z+other.getZ(), w+other.getW()); 
			}

			inline constexpr
			auto _add(const Vector4& other) -> Vector4& {
				this->changed_length = true;
				this->x += other.getX();
				this->y += other.getY();
				this->z += other.getZ();
				this->w += other.getW();
				return *this;
			}

			inline constexpr
			auto operator*(const float& factor) const -> Vector4 {
				return this->scaled(factor);
			}

			inline constexpr
			auto operator/(const float& divisor) const -> Vector4 {
				return this->divide(divisor);
			}

			inline constexpr
			auto operator+(const Vector4& other) const -> Vector4 {
				return this->add(other);
			}

			inline constexpr
			auto operator-(const Vector4& other) const -> Vector4 {
				return this->subtract(other);
			}

			inline constexpr
			auto operator=(const Vector4& other) -> Vector4&{
				return this->set(other);
			}

			inline constexpr
			auto operator-=(const Vector4& other) -> Vector4&{
				return this->_subtract(other);
			}

			inline constexpr
			auto operator+=(const Vector4& other) -> Vector4&{
				return this->_add(other);
			}

			inline constexpr
			auto operator/=(const float& divisor) -> Vector4&{
				return this->_divide(divisor);
			}

			inline constexpr
			auto operator*=(const float& factor) -> Vector4&{
				return this->_scale(factor);
			}

			inline constexpr
			auto operator==(const Vector4& other) const -> bool {
				return 
					fabs(x - other.getX()) < Vector4::tollerance
				 && fabs(y - other.getY()) < Vector4::tollerance
				 && fabs(z - other.getZ()) < Vector4::tollerance
				 && fabs(w - other.getW()) < Vector4::tollerance;
			}

			inline constexpr
			auto operator!=(const Vector4& other) const -> bool {
				return !(*this==other);
			}

			inline constexpr
			auto operator[](const int& index) -> float& {
				switch(index){
					case 0:  return this->x;
					case 1:  return this->y;
					case 2:	 return this->w;
					default: return this->z;
				}
			}

			auto operator%=(const int& d) = delete;
			auto operator&=(const int& d) = delete;
			auto operator|=(const int& d) = delete;
			auto operator^=(const int& d) = delete;
			auto operator>>=(const int& d) = delete;
			auto operator<<=(const int& d) = delete;

			friend inline 
			auto operator>>(std::istream &in, Vector4& vec)
			-> std::istream&;
    };

	inline constexpr
	auto operator*(float factor, const Vector4& vec) -> Vector4 {
		return vec.scaled(factor);
	}

	inline 
	auto operator<<(std::ostream &out, const Vector4& vec) 
	-> std::ostream& {
       	out << "[X: " << vec.getX() 
			<< " Y: " << vec.getY() 
			<< " Z: " << vec.getZ() 
			<< " W: " << vec.getW() << " ]";
   		return out;
   	}
	
	inline 
	auto operator>>(std::istream &in, Vector4& vec)
	-> std::istream& {
    	in >> vec.x >> vec.y >> vec.z >> vec.w;
    	return in;
	}

	class Rect {
		float x, y;
		float width, height;
		
	public:
		inline constexpr
		Rect(float x, float y, float width, float height)
		:x{x}, y{y}, width{width}, height{height}{}

		inline constexpr
		auto getXMin() const -> float {
			[[likely]]
			if(width > 0) return x;
			return x+width;
		}

		inline constexpr
		auto getXMax() const -> float {
			[[likely]]
			if(width > 0) return x+width;
			return x;
		}

		inline constexpr
		auto getYMax() const -> float {
			[[likely]]
			if(height > 0) return y+height;
			return y;
		}

		inline constexpr
		auto getYMin() const -> float {
			[[likely]]
			if(height > 0) return y;
			return y+height;
		}
	};

	class Line2d {
		Vector2 a, b;
	public:
		inline constexpr
		Line2d(const Vector2& from, const Vector2& to)
		:a{from}, b{to} {}

		inline constexpr
		Line2d(Vector2&& from, Vector2&& to)
		:a{from}, b{to} {}

		inline constexpr
		auto getFrom() const -> const Vector2& {
			return a;
		}

		inline constexpr
		auto getTo() const -> const Vector2 {
			return b;
		}

		inline constexpr
		auto intersect_fraction(const Rect& rectangle) const -> float {
			auto fract{ Vector2(
				((rectangle.getYMin() - a.getY())/(b.getY() - a.getY())),
				((rectangle.getXMin() - a.getX())/(b.getX() - a.getX()))
			)};
			
			return fract.getX() > fract.getY() ? fract.getX() : fract.getY();
		}

		inline constexpr
		auto asVec2() const -> Vector2 {
			return (b-a);
		}

		inline constexpr
		auto intersect_point(const Rect& rectangle) const -> Vector2 {
			return a+intersect_fraction(rectangle)*asVec2();
		}
		
		inline
		auto disctance_to(const Vector2& point) const -> float {
			return point.subtract(a.add(a.to(point).project(asVec2()))).length();	
		}
	};

    inline constexpr
    auto lerp(const float& goal, const float& current, const float& step)-> float {
    auto dif{ goal - current };
    [[likely]]
    if(dif > step)  return current+step;
    if(dif < -step) return current-step;
    [[unlikely]]
    return goal;
    }

    inline constexpr
    auto powZ(const float& base, const int& exp)-> float {
        if(base == 0 || exp == 0){
            return 1;
        }else{
            for(int i{1}; i<exp; ++i){
                base *= base;
            }
            if(exp<0){
                base = 1/base;
            }
        }
        return base;
    }
}
}

