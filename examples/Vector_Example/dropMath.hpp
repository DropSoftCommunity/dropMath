#pragma once

#include <cmath>
#include <iostream>
#include <limits>

namespace drop{
namespace math{
	
	/**
	 *  Tolerance for floating point operations
	 */
	static constexpr
	auto floatTolerance{ 0.0001f };

	static constexpr
	auto PI{ 3.14159265f };

    class Vector2{
		mutable float length_cache;
		mutable bool changed_length;
        float x, y;
				
		public:
			static constexpr float tolerance{ floatTolerance };

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
			Vector2(float x=0.f, float y=0.f): length_cache{0.f}, 
				changed_length{true}, x{x}, y{y}{
			}

			inline constexpr
			Vector2(const Vector2& other): length_cache{0.f}, 
				changed_length{true}, x{other.x}, y{other.y}{
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
				if(changed_length)
					this->length_cache = sqrtf(this->squared_length());
				this->changed_length = false;
				return this->length_cache;
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
				return (180.f/PI)*acos(this->dot_prod(other));
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
					fabs(x - other.getX()) < Vector2::tolerance
				 && fabs(y - other.getY()) < Vector2::tolerance;
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
		mutable float length_cache;
		mutable bool changed_length;
        float x, y, z;
				
		public:
			static constexpr float tolerance{ floatTolerance };

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
			Vector3(float x=0.f, float y=0.f, float z=0.f): 
				length_cache{0.f}, changed_length{true}, x{x}, y{y}, z{z}{
			}

			inline constexpr
			Vector3(const Vector3& other): 
				length_cache{0.f}, changed_length{true}, x{other.x}, y{other.y}, z{other.z}{
			}

			inline constexpr
			Vector3(const Vector2& vec2): 
				length_cache{0.f}, changed_length{true}, x{vec2.getX()}, y{vec2.getY()}, z{0.f}{
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
				if(changed_length)
					this->length_cache = sqrtf(this->squared_length());
				this->changed_length = false;
				return this->length_cache;
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
				return x*other.x + y*other.y  + z*other.z;
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
				return (180.f/PI)*(acosf((x*other.x + y*other.y + z*other.z)
						/(this->length() * other.length())));
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
					fabs(x - other.getX()) < Vector3::tolerance
				 && fabs(y - other.getY()) < Vector3::tolerance
				 && fabs(z - other.getZ()) < Vector3::tolerance;
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
		mutable float length_cache;
		mutable bool changed_length;
        float x, y, z, w;
				
		public:
			static constexpr float tolerance{ floatTolerance };

			static constexpr auto infinity() -> Vector4 {
				const auto inf{ std::numeric_limits<float>::infinity()};
				return Vector4(inf, inf, inf, inf);
			}

			inline constexpr
			Vector4(float x=0.f, float y=0.f, float z=0.f, float w=0.f)
			:length_cache{0.f}, changed_length{true}, x{x}, y{y}, z{z}, w{w}{
			}

			inline constexpr
			Vector4(const Vector4& other)
			:length_cache{0.f}, changed_length{true}, x{other.x}, y{other.y}, z{other.z}, w{other.w}{
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
			auto set(const float& new_x, const float& new_y, 
					 const float& new_z, const float& new_w)
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
				if(changed_length)
					this->length_cache = sqrtf(this->squared_length());
				this->changed_length = false;
				return this->length_cache;
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
					fabs(x - other.getX()) < Vector4::tolerance
				 && fabs(y - other.getY()) < Vector4::tolerance
				 && fabs(z - other.getZ()) < Vector4::tolerance
				 && fabs(w - other.getW()) < Vector4::tolerance;
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

			auto operator%=	(const int& d) 	= delete;
			auto operator&=	(const int& d) 	= delete;
			auto operator|=	(const int& d) 	= delete;
			auto operator^=	(const int& d) 	= delete;
			auto operator>>=(const int& d) 	= delete;
			auto operator<<=(const int& d) 	= delete;

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

	class Matrix_2x2 {
		Vector2 i, j;
	public:
		inline static constexpr
		auto identity() -> Matrix_2x2 {
			return Matrix_2x2({1.f, 0.f}, {0.f, 1.f});
		}

		inline static constexpr
		auto rotation(float angle_deg=90.f) -> Matrix_2x2 {
			return Matrix_2x2(
				{cosf(angle_deg), sinf(angle_deg)},
				{-sinf(angle_deg), cosf(angle_deg)}
			);
		}
		
		inline constexpr
		Matrix_2x2(const Vector2& i, const Vector2& j)
		:i{i}, j{j}{}

		inline constexpr
		Matrix_2x2(Vector2&& i, Vector2&& j)
		:i{i}, j{j}{}

		inline constexpr
		Matrix_2x2(float x1, float x2, float x3, float x4):
		i(x1, x2), j(x3, x4){}

		inline constexpr
		auto isIndependent(float* opt_out_ratio=nullptr) const -> bool {
			auto tr1{ this->i.getX()/this->j.getX() };
			auto tr2{ this->i.getY()/this->j.getY() };

			if(fabs(tr1-tr2) < Vector2::tolerance){
				if(opt_out_ratio != nullptr) *opt_out_ratio = tr1;
				return true;
			}
			return false;
		}

		inline constexpr
		auto transposed() const -> Matrix_2x2 {
			return Matrix_2x2{
				{ this->i.getX(), this->j.getX() },
				{ this->i.getY(), this->j.getY() }
			};
		}

		inline constexpr
		auto _transpose() -> Matrix_2x2 {
			auto tmp{ this->i.getY() };
			this->i.setY(this->j.getX());
			this->j.setX(tmp);
			return *this;
		}

		inline constexpr
		auto adjugated() const -> Matrix_2x2 {
			return Matrix_2x2{
				{   this->j.getY(), -(this->i.getX()) },
				{ -(this->j.getX()),  this->i.getY()  }
			};
		}

		inline constexpr
		auto _adjugate() -> Matrix_2x2& {
			auto tmp{ this->i.getX() };
			this->i.setX(this->j.getY());
			this->i.setY(-this->i.getY());
			this->j.setX(tmp);
			this->j.setY(-this->j.getY());

			return *this;
		}

		inline constexpr
		auto determinant() const -> float {
			return (i.getX()*j.getY()) - (i.getY()*j.getX());
		}
		
		inline constexpr
		auto scaled(const float& scalar) const -> Matrix_2x2 {
			return Matrix_2x2 {
				this->i * scalar,
				this->j * scalar
			};
		}

		inline constexpr
		auto _scale(const float& scalar) -> Matrix_2x2& {
			this->i._scale(scalar);
			this->j._scale(scalar);

			return *this;
		}

		inline constexpr
		auto inverted() const -> Matrix_2x2 {
			return adjugated()._scale(1.f/determinant());
		}

		inline constexpr
		auto _invert() -> Matrix_2x2& {
			auto tmp{ determinant() };
			return _adjugate()._scale(1.f/tmp);
		}

		inline constexpr
		auto applyTo(const Vector2& v) const -> Vector2 {
			return Vector2(
				i.getX()*v.getX() + j.getX()*v.getY(),
				i.getY()*v.getX() + j.getY()*v.getY()
			);
		}

		inline constexpr
		auto applyTo(Vector2& v) const -> Vector2& {
			return v.set(
				i.getX()*v.getX() + j.getX()*v.getY(),
				i.getY()*v.getX() + j.getY()*v.getY()
			);
		}

		inline constexpr
		auto applyTo(const Matrix_2x2& m) const -> Matrix_2x2 {
			return Matrix_2x2(
				{ i.getX()*m.i.getX() + j.getX()*m.i.getY(),
				  i.getY()*m.i.getX() + j.getY()*m.i.getY() },
				{ i.getX()*m.j.getX() + j.getX()*m.j.getY(),
				  i.getY()*m.j.getX() + j.getY()*m.j.getY() }
			);
		}

		inline constexpr
		auto applyTo(Matrix_2x2& m) const -> Matrix_2x2& {
			m.i.set(
				i.getX()*m.i.getX() + j.getX()*m.i.getY(),
				i.getY()*m.i.getX() + j.getY()*m.i.getY() 
			);
			m.j.set(
				i.getX()*m.j.getX() + j.getX()*m.j.getY(),
				i.getY()*m.j.getX() + j.getY()*m.j.getY() 
			);
			return m;
		}

		inline constexpr
		auto _selfApply(Matrix_2x2& m) -> Matrix_2x2& {
			this->i.set(
				m.i.getX()*i.getX() + m.j.getX()*i.getY(),
				m.i.getY()*i.getX() + m.j.getY()*i.getY() 
			);
			this->j.set(
				m.i.getX()*j.getX() + m.j.getX()*j.getY(),
				m.i.getY()*j.getX() + m.j.getY()*j.getY() 
			);
			return *this;
		}

		inline constexpr
		auto solveFor(const Vector2& results) const -> Vector2 {
			auto det{ determinant() };
			
			auto m1{ Matrix_2x2(results, j) };
			auto m2{ Matrix_2x2(i, results) };

			auto d1{ m1.determinant() };
			auto d2{ m2.determinant() };

			return Vector2(d1/det, d2/det);
		}

		inline constexpr
		auto add(const Matrix_2x2& other) const -> Matrix_2x2 {
			return Matrix_2x2(
				i.add(other.i),
				j.add(other.j)
			);
		}

		inline constexpr
		auto operator+(const Matrix_2x2& other) const -> Matrix_2x2 {
			return add(other);	
		}

		inline constexpr
		auto operator*(const float& factor) const -> Matrix_2x2{
			return this->scaled(factor);
		}

		inline constexpr
		auto operator/(const float& divisor) const -> Matrix_2x2{
			return this->scaled(1.f/divisor);
		}

		inline constexpr
		auto operator=(const Matrix_2x2& other) -> Matrix_2x2&{
			this->i.set(other.i);
			this->j.set(other.j);
			
			return *this;
		}

		inline constexpr
		auto operator/=(const float& divisor) -> Matrix_2x2&{
			return this->_scale(1.f/divisor);
		}

		inline constexpr
		auto operator*=(const float& factor) -> Matrix_2x2&{
			return this->_scale(factor);
		}

		inline constexpr
		auto operator==(const Matrix_2x2& other) const -> bool {
			return 
			   fabs(i.getX() - other.i.getX()) < Vector2::tolerance
		 	&& fabs(i.getY() - other.i.getY()) < Vector2::tolerance
		 	&& fabs(j.getX() - other.j.getX()) < Vector2::tolerance
		 	&& fabs(j.getY() - other.j.getY()) < Vector2::tolerance;
		}

		inline constexpr
		auto operator!=(const Matrix_2x2& other) const -> bool {
			return !(*this==other);
		}

		friend inline
		auto operator<<(std::ostream &out, const Matrix_2x2& m)
		-> std::ostream&;
	};

	inline constexpr
	auto operator*(float scalar, const Matrix_2x2& m) -> Matrix_2x2 {
		return m.scaled(scalar);
	}

	inline 
	auto operator<<(std::ostream &out, const Matrix_2x2& m) 
	-> std::ostream& {
       	out << "[ " 	<< m.i.getX() 
			<< " | " 	<< m.j.getX() 
			<< " ]\n[ " << m.i.getY() 
			<< " | " 	<< m.j.getY() 
			<< " ]";
   		return out;
   	}

	class Matrix_3x3 {
		Vector3 i, j, k;
	public:
		inline static constexpr
		auto identity() -> Matrix_3x3 {
			return Matrix_3x3({1.f, 0.f, 0.f}, 
							  {0.f, 1.f, 0.f},
							  {0.f, 0.f, 1.f});
		}

		inline constexpr
		Matrix_3x3(const Vector3& i, const Vector3& j, const Vector3& k)
		:i{i}, j{j}, k{k}{}

		inline constexpr
		Matrix_3x3(Vector3&& i, Vector3&& j, Vector3&& k)
		:i{i}, j{j}, k{k}{}

		inline constexpr
		Matrix_3x3(float x1, float x2, float x3, 
				   float x4, float x5, float x6,
				   float x7, float x8, float x9):
		i(x1, x2, x3), j(x4, x5, x6), k{x7, x8, x9}{}

		inline constexpr
		auto isIndependent() const -> bool {
			return static_cast<bool>(determinant());
		}

		inline constexpr
		auto transposed() const -> Matrix_3x3 {
			return Matrix_3x3{
				{ i.getX(), j.getX(), k.getX() },
				{ i.getY(), j.getY(), k.getY() },
				{ i.getZ(), j.getZ(), k.getZ() }
			};
		}

		inline constexpr
		auto _transpose() -> Matrix_3x3 {
			const auto tmp_iy{ i.getY() };
			const auto tmp_iz{ i.getZ() };
			const auto tmp_jz{ j.getZ() };

			this->i.set(i.getX(), 	j.getX(), k.getX());
			this->j.set(tmp_iy, 	j.getY(), k.getY());
			this->k.set(tmp_iz, 	tmp_jz,	  k.getZ());

			return *this;
		}

		inline constexpr
		auto adjugated() const -> Matrix_3x3 {
			auto adj{ Matrix_3x3{
			{
				+Matrix_2x2({j.getY(), j.getZ()},{k.getY(), k.getZ()}).determinant(),
				-Matrix_2x2({j.getX(), j.getZ()},{k.getX(), k.getZ()}).determinant(),
				+Matrix_2x2({j.getX(), j.getY()},{k.getX(), k.getY()}).determinant()
			},
			{
				-Matrix_2x2({i.getY(), i.getZ()},{k.getY(), k.getZ()}).determinant(),
				+Matrix_2x2({i.getX(), i.getZ()},{k.getX(), k.getZ()}).determinant(),
				-Matrix_2x2({i.getX(), i.getY()},{k.getX(), k.getY()}).determinant()
			},
			{
				+Matrix_2x2({i.getY(), i.getZ()},{j.getY(), j.getZ()}).determinant(),
				-Matrix_2x2({i.getX(), i.getZ()},{j.getX(), j.getZ()}).determinant(),
				+Matrix_2x2({i.getX(), i.getY()},{j.getX(), j.getY()}).determinant()
			}
		 	}};
			return adj._transpose();
		}

		inline constexpr
		auto _adjugate() -> Matrix_3x3& {
			*this = adjugated();
			return *this;
		}

		inline constexpr
		auto determinant() const -> float {
			return
			 i.getX()*j.getY()*k.getZ()
			+j.getX()*k.getY()*i.getZ()
			+k.getX()*i.getY()*j.getZ()
			-i.getZ()*j.getY()*k.getX()
			-j.getZ()*k.getY()*i.getX()
			-k.getZ()*i.getY()*j.getX();
		}
		
		inline constexpr
		auto scaled(const float& scalar) const -> Matrix_3x3 {
			return Matrix_3x3 {
				this->i * scalar,
				this->j * scalar,
				this->k * scalar
			};
		}

		inline constexpr
		auto _scale(const float& scalar) -> Matrix_3x3& {
			this->i._scale(scalar);
			this->j._scale(scalar);
			this->k._scale(scalar);

			return *this;
		}

		inline constexpr
		auto inverted() const -> Matrix_3x3 {
			return adjugated()._scale(1.f/determinant());
		}

		inline constexpr
		auto _invert() -> Matrix_3x3& {
			auto tmp{ determinant() };
			return _adjugate()._scale(1.f/tmp);
		}

		inline constexpr
		auto applyTo(const Vector3& v) const -> Vector3 {
			return Vector3(
				i.getX()*v.getX()+j.getX()*v.getY()+k.getX()*v.getZ(),
				i.getY()*v.getX()+j.getY()*v.getY()+k.getY()*v.getZ(),
				i.getZ()*v.getX()+j.getZ()*v.getY()+k.getZ()*v.getZ()
			);
		}

		inline constexpr
		auto applyTo(Vector3& v) const -> Vector3& {
			return v.set(
				i.getX()*v.getX()+j.getX()*v.getY()+k.getX()*v.getZ(),
				i.getY()*v.getX()+j.getY()*v.getY()+k.getY()*v.getZ(),
				i.getZ()*v.getX()+j.getZ()*v.getY()+k.getZ()*v.getZ()
			);
		}

		inline constexpr
		auto applyTo(const Matrix_3x3& m) const -> Matrix_3x3 {
			return Matrix_3x3(
			{
				i.getX()*m.i.getX()+j.getX()*m.i.getY()+k.getX()*m.i.getZ(),
				i.getY()*m.i.getX()+j.getY()*m.i.getY()+k.getY()*m.i.getZ(),
				i.getZ()*m.i.getX()+j.getZ()*m.i.getY()+k.getZ()*m.i.getZ()
			},
			{
				i.getX()*m.j.getX()+j.getX()*m.j.getY()+k.getX()*m.j.getZ(),
				i.getY()*m.j.getX()+j.getY()*m.j.getY()+k.getY()*m.j.getZ(),
				i.getZ()*m.j.getX()+j.getZ()*m.j.getY()+k.getZ()*m.j.getZ()
			},
			{
				i.getX()*m.k.getX()+j.getX()*m.k.getY()+k.getX()*m.k.getZ(),
				i.getY()*m.k.getX()+j.getY()*m.k.getY()+k.getY()*m.k.getZ(),
				i.getZ()*m.k.getX()+j.getZ()*m.k.getY()+k.getZ()*m.k.getZ()
			}
			);
		}

		inline constexpr
		auto applyTo(Matrix_3x3& m) const -> Matrix_3x3& {
			m.i.set(
				i.getX()*m.i.getX()+j.getX()*m.i.getY()+k.getX()*m.i.getZ(),
				i.getY()*m.i.getX()+j.getY()*m.i.getY()+k.getY()*m.i.getZ(),
				i.getZ()*m.i.getX()+j.getZ()*m.i.getY()+k.getZ()*m.i.getZ()
			);
			m.j.set(
				i.getX()*m.j.getX()+j.getX()*m.j.getY()+k.getX()*m.j.getZ(),
				i.getY()*m.j.getX()+j.getY()*m.j.getY()+k.getY()*m.j.getZ(),
				i.getZ()*m.j.getX()+j.getZ()*m.j.getY()+k.getZ()*m.j.getZ()
			);
			m.k.set(
				i.getX()*m.k.getX()+j.getX()*m.k.getY()+k.getX()*m.k.getZ(),
				i.getY()*m.k.getX()+j.getY()*m.k.getY()+k.getY()*m.k.getZ(),
				i.getZ()*m.k.getX()+j.getZ()*m.k.getY()+k.getZ()*m.k.getZ()
		    );
			return m;
		}

		inline constexpr
		auto _selfApply(Matrix_3x3& m) -> Matrix_3x3& {
			this->i.set(
				i.getX()*m.i.getX()+j.getX()*m.i.getY()+k.getX()*m.i.getZ(),
				i.getY()*m.i.getX()+j.getY()*m.i.getY()+k.getY()*m.i.getZ(),
				i.getZ()*m.i.getX()+j.getZ()*m.i.getY()+k.getZ()*m.i.getZ()
			);
			this->j.set(
				i.getX()*m.j.getX()+j.getX()*m.j.getY()+k.getX()*m.j.getZ(),
				i.getY()*m.j.getX()+j.getY()*m.j.getY()+k.getY()*m.j.getZ(),
				i.getZ()*m.j.getX()+j.getZ()*m.j.getY()+k.getZ()*m.j.getZ()
			);
			this->k.set(
				i.getX()*m.k.getX()+j.getX()*m.k.getY()+k.getX()*m.k.getZ(),
				i.getY()*m.k.getX()+j.getY()*m.k.getY()+k.getY()*m.k.getZ(),
				i.getZ()*m.k.getX()+j.getZ()*m.k.getY()+k.getZ()*m.k.getZ()
		    );
			return *this;
		}

		inline constexpr
		auto solveFor(const Vector3& results) const -> Vector3 {
			auto det{ determinant() };
			
			auto m1{ Matrix_3x3(results, j, k) };
			auto m2{ Matrix_3x3(i, results, k) };
			auto m3{ Matrix_3x3(i, j, results) };

			auto d1{ m1.determinant() };
			auto d2{ m2.determinant() };
			auto d3{ m3.determinant() };

			return Vector3(d1/det, d2/det, d3/det);
		}

		inline constexpr
		auto operator*(const float& factor) const -> Matrix_3x3{
			return this->scaled(factor);
		}

		inline constexpr
		auto operator/(const float& divisor) const -> Matrix_3x3{
			return this->scaled(1.f/divisor);
		}

		inline constexpr
		auto operator=(const Matrix_3x3& other) -> Matrix_3x3&{
			this->i.set(other.i);
			this->j.set(other.j);
			this->k.set(other.k);
			
			return *this;
		}

		inline constexpr
		auto operator/=(const float& divisor) -> Matrix_3x3&{
			return this->_scale(1.f/divisor);
		}

		inline constexpr
		auto operator*=(const float& factor) -> Matrix_3x3&{
			return this->_scale(factor);
		}

		inline constexpr
		auto operator==(const Matrix_3x3& other) const -> bool {
			return (i == other.i)
				&& (j == other.j)
				&& (k == other.k);
		}

		inline constexpr
		auto operator!=(const Matrix_3x3& other) const -> bool {
			return !(*this==other);
		}

		friend inline
		auto operator<<(std::ostream &out, const Matrix_3x3& m)
		-> std::ostream&;
	};

	inline constexpr
	auto operator*(float scalar, const Matrix_3x3& m) -> Matrix_3x3 {
		return m.scaled(scalar);
	}

	inline 
	auto operator<<(std::ostream &out, const Matrix_3x3& m) 
	-> std::ostream& {
       	out << "[ " 	<< m.i.getX() 
			<< " | " 	<< m.j.getX() 
			<< " | " 	<< m.k.getX() 
			<< " ]\n[ " << m.i.getY() 
			<< " | " 	<< m.j.getY() 
			<< " | " 	<< m.k.getY() 
			<< " ]\n[ " << m.i.getZ() 
			<< " | " 	<< m.j.getZ() 
			<< " | " 	<< m.k.getZ() 
			<< " ]";
   		return out;
   	}

	class Matrix_4x4 {
		Vector4 i, j, k, l;
	public:
		inline static constexpr
		auto identity() -> Matrix_4x4 {
			return Matrix_4x4({1.f, 0.f, 0.f, 0.f}, 
							  {0.f, 1.f, 0.f, 0.f},
							  {0.f, 0.f, 1.f, 0.f},
							  {0.f, 0.f, 0.f, 1.f});
		}

		inline constexpr
		Matrix_4x4(const Vector4& i, const Vector4& j, 
				   const Vector4& k, const Vector4& l)
		:i{i}, j{j}, k{k}, l{l}{}

		inline constexpr
		Matrix_4x4(Vector4&& i, Vector4&& j, Vector4&& k, Vector4&& l)
		:i{i}, j{j}, k{k}, l{l}{}

		inline constexpr
		Matrix_4x4(float x1, float x2, float x3, float x4,
				   float x5, float x6, float x7, float x8,
				   float x9, float xa, float xb, float xc,
				   float xd, float xe, float xf, float xg):
		i(x1, x2, x3, x4), j(x5, x6, x7, x8),
		k{x9, xa, xb, xc}, l(xd, xe, xf, xg){}

		inline constexpr
		auto isIndependent() const -> bool {
			return static_cast<bool>(determinant());
		}

		inline constexpr
		auto transposed() const -> Matrix_4x4 {
			return Matrix_4x4{
				{ i.getX(), j.getX(), k.getX(), l.getX() },
				{ i.getY(), j.getY(), k.getY(), l.getY() },
				{ i.getZ(), j.getZ(), k.getZ(), l.getZ() },
				{ i.getW(), j.getW(), k.getW(), l.getW() }
			};
		}

		inline constexpr
		auto _transpose() -> Matrix_4x4 {
			*this = transposed();
			return *this;
		}

		inline constexpr
		auto adjugated() const -> Matrix_4x4 {
			auto adj{ Matrix_4x4{
			{
				+Matrix_3x3(
						{j.getY(), j.getZ(), j.getW()},
						{k.getY(), k.getZ(), k.getW()},
						{l.getY(), l.getZ(), l.getW()}
				 ).determinant(),
				-Matrix_3x3(
						{j.getX(), j.getZ(), j.getW()},
						{k.getX(), k.getZ(), k.getW()},
						{l.getX(), l.getZ(), l.getW()}
				 ).determinant(),
				+Matrix_3x3(
						{j.getX(), j.getY(), j.getW()},
						{k.getX(), k.getY(), k.getW()},
						{l.getX(), l.getY(), l.getW()}
				 ).determinant(),
				-Matrix_3x3(
						{j.getX(), j.getY(), j.getZ()},
						{k.getX(), k.getY(), k.getZ()},
						{l.getX(), l.getY(), l.getZ()}
				 ).determinant()
			},
			{
				-Matrix_3x3(
						{i.getY(), i.getZ(), i.getW()},
						{k.getY(), k.getZ(), k.getW()},
						{l.getY(), l.getZ(), l.getW()}
				 ).determinant(),
				+Matrix_3x3(
						{i.getX(), i.getZ(), i.getW()},
						{k.getX(), k.getZ(), k.getW()},
						{l.getX(), l.getZ(), l.getW()}
				 ).determinant(),
				-Matrix_3x3(
						{i.getX(), i.getY(), i.getW()},
						{k.getX(), k.getY(), k.getW()},
						{l.getX(), l.getY(), l.getW()}
				 ).determinant(),
				+Matrix_3x3(
						{i.getX(), i.getY(), i.getZ()},
						{k.getX(), k.getY(), k.getZ()},
						{l.getX(), l.getY(), l.getZ()}
				 ).determinant()
			},
			{
				+Matrix_3x3(
						{i.getY(), i.getZ(), i.getW()},
						{j.getY(), j.getZ(), j.getW()},
						{l.getY(), l.getZ(), l.getW()}
				 ).determinant(),
				-Matrix_3x3(
						{i.getX(), i.getZ(), i.getW()},
						{j.getX(), j.getZ(), j.getW()},
						{l.getX(), l.getZ(), l.getW()}
				 ).determinant(),
				+Matrix_3x3(
						{i.getX(), i.getY(), i.getW()},
						{j.getX(), j.getY(), j.getW()},
						{l.getX(), l.getY(), l.getW()}
				 ).determinant(),
				-Matrix_3x3(
						{i.getX(), i.getY(), i.getZ()},
						{j.getX(), j.getY(), j.getZ()},
						{l.getX(), l.getY(), l.getZ()}
				 ).determinant()
			},
			{
				+Matrix_3x3(
						{i.getY(), i.getZ(), i.getW()},
						{j.getY(), j.getZ(), j.getW()},
						{k.getY(), k.getZ(), k.getW()}
				 ).determinant(),
				-Matrix_3x3(
						{i.getX(), i.getZ(), i.getW()},
						{j.getX(), j.getZ(), j.getW()},
						{k.getX(), k.getZ(), k.getW()}
				 ).determinant(),
				+Matrix_3x3(
						{i.getX(), i.getY(), i.getW()},
						{j.getX(), j.getY(), j.getW()},
						{k.getX(), k.getY(), k.getW()}
				 ).determinant(),
				-Matrix_3x3(
						{i.getX(), i.getY(), i.getZ()},
						{j.getX(), j.getY(), j.getZ()},
						{k.getX(), k.getY(), k.getZ()}
				 ).determinant()
			}
		 	}};
			return adj._transpose();
		}

		inline constexpr
		auto _adjugate() -> Matrix_4x4& {
			*this = adjugated();
			return *this;
		}

		inline constexpr
		auto determinant() const -> float {
			return
			+i.getX()*Matrix_3x3(
					{j.getY(), j.getZ(), j.getW()},
					{k.getY(), k.getZ(), k.getW()},
					{l.getY(), l.getZ(), l.getW()}
			 ).determinant()
			-i.getY()*Matrix_3x3(
					{j.getX(), j.getZ(), j.getW()},
					{k.getX(), k.getZ(), k.getW()},
					{l.getX(), l.getZ(), l.getW()}
			 ).determinant()
			+i.getZ()*Matrix_3x3(
					{j.getX(), j.getY(), j.getW()},
					{k.getX(), k.getY(), k.getW()},
					{l.getX(), l.getY(), l.getW()}
			 ).determinant()
			-i.getW()*Matrix_3x3(
					{j.getX(), j.getY(), j.getZ()},
					{k.getX(), k.getY(), k.getZ()},
					{l.getX(), l.getY(), l.getZ()}
			 ).determinant();
		}
		
		inline constexpr
		auto scaled(const float& scalar) const -> Matrix_4x4 {
			return Matrix_4x4 {
				this->i * scalar,
				this->j * scalar,
				this->k * scalar,
				this->l * scalar
			};
		}

		inline constexpr
		auto _scale(const float& scalar) -> Matrix_4x4& {
			this->i._scale(scalar);
			this->j._scale(scalar);
			this->k._scale(scalar);
			this->l._scale(scalar);

			return *this;
		}

		inline constexpr
		auto inverted() const -> Matrix_4x4 {
			return adjugated()._scale(1.f/determinant());
		}

		inline constexpr
		auto _invert() -> Matrix_4x4& {
			auto tmp{ determinant() };
			return _adjugate()._scale(1.f/tmp);
		}

		inline constexpr
		auto applyTo(const Vector4& v) const -> Vector4 {
			return Vector4(
				i.getX()*v.getX()+j.getX()*v.getY()+k.getX()*v.getZ()+l.getX()*v.getW(),		
				i.getY()*v.getX()+j.getY()*v.getY()+k.getY()*v.getZ()+l.getY()*v.getW(),		
				i.getZ()*v.getX()+j.getZ()*v.getY()+k.getZ()*v.getZ()+l.getZ()*v.getW(),		
				i.getW()*v.getX()+j.getW()*v.getY()+k.getW()*v.getZ()+l.getW()*v.getW()		
			);
		}

		inline constexpr
		auto applyTo(Vector4& v) const -> Vector4& {
			return v.set(
				i.getX()*v.getX()+j.getX()*v.getY()+k.getX()*v.getZ()+l.getX()*v.getW(),		
				i.getY()*v.getX()+j.getY()*v.getY()+k.getY()*v.getZ()+l.getY()*v.getW(),		
				i.getZ()*v.getX()+j.getZ()*v.getY()+k.getZ()*v.getZ()+l.getZ()*v.getW(),		
				i.getW()*v.getX()+j.getW()*v.getY()+k.getW()*v.getZ()+l.getW()*v.getW()		
			);
		}

		inline constexpr
		auto applyTo(const Matrix_4x4& m) const -> Matrix_4x4 {
			return Matrix_4x4(
			{
				i.getX()*m.i.getX()+j.getX()*m.i.getY()+k.getX()*m.i.getZ()+l.getX()*m.i.getW(),		
				i.getY()*m.i.getX()+j.getY()*m.i.getY()+k.getY()*m.i.getZ()+l.getY()*m.i.getW(),		
				i.getZ()*m.i.getX()+j.getZ()*m.i.getY()+k.getZ()*m.i.getZ()+l.getZ()*m.i.getW(),		
				i.getW()*m.i.getX()+j.getW()*m.i.getY()+k.getW()*m.i.getZ()+l.getW()*m.i.getW()		
			},
			{
				i.getX()*m.j.getX()+j.getX()*m.j.getY()+k.getX()*m.j.getZ()+l.getX()*m.j.getW(),		
				i.getY()*m.j.getX()+j.getY()*m.j.getY()+k.getY()*m.j.getZ()+l.getY()*m.j.getW(),		
				i.getZ()*m.j.getX()+j.getZ()*m.j.getY()+k.getZ()*m.j.getZ()+l.getZ()*m.j.getW(),		
				i.getW()*m.j.getX()+j.getW()*m.j.getY()+k.getW()*m.j.getZ()+l.getW()*m.j.getW()		
			},
			{
				i.getX()*m.k.getX()+j.getX()*m.k.getY()+k.getX()*m.k.getZ()+l.getX()*m.k.getW(),		
				i.getY()*m.k.getX()+j.getY()*m.k.getY()+k.getY()*m.k.getZ()+l.getY()*m.k.getW(),		
				i.getZ()*m.k.getX()+j.getZ()*m.k.getY()+k.getZ()*m.k.getZ()+l.getZ()*m.k.getW(),		
				i.getW()*m.k.getX()+j.getW()*m.k.getY()+k.getW()*m.k.getZ()+l.getW()*m.k.getW()		
			},
			{
				i.getX()*m.l.getX()+j.getX()*m.l.getY()+k.getX()*m.l.getZ()+l.getX()*m.l.getW(),		
				i.getY()*m.l.getX()+j.getY()*m.l.getY()+k.getY()*m.l.getZ()+l.getY()*m.l.getW(),		
				i.getZ()*m.l.getX()+j.getZ()*m.l.getY()+k.getZ()*m.l.getZ()+l.getZ()*m.l.getW(),		
				i.getW()*m.l.getX()+j.getW()*m.l.getY()+k.getW()*m.l.getZ()+l.getW()*m.l.getW()		
			}
			);
		}

		inline constexpr
		auto applyTo(Matrix_4x4& m) const -> Matrix_4x4& {
			m.i.set(
				i.getX()*m.i.getX()+j.getX()*m.i.getY()+k.getX()*m.i.getZ()+l.getX()*m.i.getW(),		
				i.getY()*m.i.getX()+j.getY()*m.i.getY()+k.getY()*m.i.getZ()+l.getY()*m.i.getW(),		
				i.getZ()*m.i.getX()+j.getZ()*m.i.getY()+k.getZ()*m.i.getZ()+l.getZ()*m.i.getW(),		
				i.getW()*m.i.getX()+j.getW()*m.i.getY()+k.getW()*m.i.getZ()+l.getW()*m.i.getW()		
			);
			m.j.set(
				i.getX()*m.j.getX()+j.getX()*m.j.getY()+k.getX()*m.j.getZ()+l.getX()*m.j.getW(),		
				i.getY()*m.j.getX()+j.getY()*m.j.getY()+k.getY()*m.j.getZ()+l.getY()*m.j.getW(),		
				i.getZ()*m.j.getX()+j.getZ()*m.j.getY()+k.getZ()*m.j.getZ()+l.getZ()*m.j.getW(),		
				i.getW()*m.j.getX()+j.getW()*m.j.getY()+k.getW()*m.j.getZ()+l.getW()*m.j.getW()		
			);	
			m.k.set(	
				i.getX()*m.k.getX()+j.getX()*m.k.getY()+k.getX()*m.k.getZ()+l.getX()*m.k.getW(),		
				i.getY()*m.k.getX()+j.getY()*m.k.getY()+k.getY()*m.k.getZ()+l.getY()*m.k.getW(),		
				i.getZ()*m.k.getX()+j.getZ()*m.k.getY()+k.getZ()*m.k.getZ()+l.getZ()*m.k.getW(),		
				i.getW()*m.k.getX()+j.getW()*m.k.getY()+k.getW()*m.k.getZ()+l.getW()*m.k.getW()		
			);			
			m.l.set(
				i.getX()*m.l.getX()+j.getX()*m.l.getY()+k.getX()*m.l.getZ()+l.getX()*m.l.getW(),		
				i.getY()*m.l.getX()+j.getY()*m.l.getY()+k.getY()*m.l.getZ()+l.getY()*m.l.getW(),		
				i.getZ()*m.l.getX()+j.getZ()*m.l.getY()+k.getZ()*m.l.getZ()+l.getZ()*m.l.getW(),		
				i.getW()*m.l.getX()+j.getW()*m.l.getY()+k.getW()*m.l.getZ()+l.getW()*m.l.getW()		
			);
			return m;
		}

		inline constexpr
		auto _selfApply(Matrix_4x4& m) -> Matrix_4x4& {
			i.set(
				i.getX()*m.i.getX()+j.getX()*m.i.getY()+k.getX()*m.i.getZ()+l.getX()*m.i.getW(),		
				i.getY()*m.i.getX()+j.getY()*m.i.getY()+k.getY()*m.i.getZ()+l.getY()*m.i.getW(),		
				i.getZ()*m.i.getX()+j.getZ()*m.i.getY()+k.getZ()*m.i.getZ()+l.getZ()*m.i.getW(),		
				i.getW()*m.i.getX()+j.getW()*m.i.getY()+k.getW()*m.i.getZ()+l.getW()*m.i.getW()		
			);
			j.set(
				i.getX()*m.j.getX()+j.getX()*m.j.getY()+k.getX()*m.j.getZ()+l.getX()*m.j.getW(),		
				i.getY()*m.j.getX()+j.getY()*m.j.getY()+k.getY()*m.j.getZ()+l.getY()*m.j.getW(),		
				i.getZ()*m.j.getX()+j.getZ()*m.j.getY()+k.getZ()*m.j.getZ()+l.getZ()*m.j.getW(),		
				i.getW()*m.j.getX()+j.getW()*m.j.getY()+k.getW()*m.j.getZ()+l.getW()*m.j.getW()		
			);	
			k.set(	
				i.getX()*m.k.getX()+j.getX()*m.k.getY()+k.getX()*m.k.getZ()+l.getX()*m.k.getW(),		
				i.getY()*m.k.getX()+j.getY()*m.k.getY()+k.getY()*m.k.getZ()+l.getY()*m.k.getW(),		
				i.getZ()*m.k.getX()+j.getZ()*m.k.getY()+k.getZ()*m.k.getZ()+l.getZ()*m.k.getW(),		
				i.getW()*m.k.getX()+j.getW()*m.k.getY()+k.getW()*m.k.getZ()+l.getW()*m.k.getW()		
			);			
			l.set(
				i.getX()*m.l.getX()+j.getX()*m.l.getY()+k.getX()*m.l.getZ()+l.getX()*m.l.getW(),		
				i.getY()*m.l.getX()+j.getY()*m.l.getY()+k.getY()*m.l.getZ()+l.getY()*m.l.getW(),		
				i.getZ()*m.l.getX()+j.getZ()*m.l.getY()+k.getZ()*m.l.getZ()+l.getZ()*m.l.getW(),		
				i.getW()*m.l.getX()+j.getW()*m.l.getY()+k.getW()*m.l.getZ()+l.getW()*m.l.getW()		
			);
			return *this;
		}

		inline constexpr
		auto solveFor(const Vector4& results) const -> Vector4 {
			auto det{ determinant() };
			
			auto m1{ Matrix_4x4(results, j, k, l) };
			auto m2{ Matrix_4x4(i, results, k, l) };
			auto m3{ Matrix_4x4(i, j, results, l) };
			auto m4{ Matrix_4x4(i, j, k, results) };

			auto d1{ m1.determinant() };
			auto d2{ m2.determinant() };
			auto d3{ m3.determinant() };
			auto d4{ m4.determinant() };

			return Vector4(d1/det, d2/det, d3/det, d4/det);
		}

		inline constexpr
		auto operator*(const float& factor) const -> Matrix_4x4{
			return this->scaled(factor);
		}

		inline constexpr
		auto operator/(const float& divisor) const -> Matrix_4x4{
			return this->scaled(1.f/divisor);
		}

		inline constexpr
		auto operator=(const Matrix_4x4& other) -> Matrix_4x4&{
			this->i.set(other.i);
			this->j.set(other.j);
			this->k.set(other.k);
			this->l.set(other.l);
			
			return *this;
		}

		inline constexpr
		auto operator/=(const float& divisor) -> Matrix_4x4&{
			return this->_scale(1.f/divisor);
		}

		inline constexpr
		auto operator*=(const float& factor) -> Matrix_4x4&{
			return this->_scale(factor);
		}

		inline constexpr
		auto operator==(const Matrix_4x4& other) const -> bool {
			return (i == other.i)
				&& (j == other.j)
				&& (k == other.k)
				&& (l == other.l);
		}

		inline constexpr
		auto operator!=(const Matrix_4x4& other) const -> bool {
			return !(*this==other);
		}

		friend inline
		auto operator<<(std::ostream &out, const Matrix_4x4& m)
		-> std::ostream&;
	};

	inline constexpr
	auto operator*(float scalar, const Matrix_4x4& m) -> Matrix_4x4 {
		return m.scaled(scalar);
	}

	inline 
	auto operator<<(std::ostream &out, const Matrix_4x4& m) 
	-> std::ostream& {
       	out << "[ " 	<< m.i.getX() 
			<< " | " 	<< m.j.getX() 
			<< " | " 	<< m.k.getX() 
			<< " | " 	<< m.l.getX() 
			<< " ]\n[ " << m.i.getY() 
			<< " | " 	<< m.j.getY() 
			<< " | " 	<< m.k.getY() 
			<< " | " 	<< m.l.getY() 
			<< " ]\n[ " << m.i.getZ() 
			<< " | " 	<< m.j.getZ() 
			<< " | " 	<< m.k.getZ() 
			<< " | " 	<< m.l.getZ() 
			<< " ]\n[ " << m.i.getW() 
			<< " | " 	<< m.j.getW() 
			<< " | " 	<< m.k.getW() 
			<< " | " 	<< m.l.getW() 
			<< " ]";
   		return out;
   	}
	
	inline constexpr
	auto differentiate(const float& func) -> float {
		return 0;
	}

	inline constexpr
	auto integrate(const float& func) -> Vector2 {
		return Vector2(func, 0.f); 
	}

	inline constexpr 
	auto differentiate(const Vector2& func) -> float {
		return func.getX();
	}

	inline constexpr
	auto integrate(const Vector2& func) -> Vector3 {
		return Vector3(func.getX()/2, func.getY(), 0.f);	
	}

	inline constexpr
	auto differentiate(const Vector3& func) -> Vector2 {
		return Vector2(func.getX()*2, func.getY());
	}

	inline constexpr
	auto integrate(const Vector3& func) -> Vector4 {
		return Vector4(func.getX()/3, func.getY()/2, func.getZ());
	}

	inline constexpr
	auto differentiate(const Vector4& func) -> Vector3 {
		return Vector3(func.getX()*3, func.getY()*3, func.getZ());
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

	class Plane3 {
		Vector3 dir, r1, r2;

	public:
		inline constexpr
		Plane3(const Vector3& dir, const Vector3& span1, const Vector3& span2):
			dir{dir}, r1{span1}, r2{span2} {}

		inline constexpr
		auto getNormal() const -> const Vector3 {
			return r1.cross_prod(r2); 
		}

		inline constexpr
		auto isParallel(const Plane3& other) -> bool {
			return this->getNormal().cross_prod(other.getNormal()).equals( {0.f, 0.f, 0.f} );
		}

		inline
		auto distance(const Plane3& other) -> float {
			if(!isParallel(other)) return 0.f;
			return fabs(this->getNormal().dot_prod(r2-r1))
				 / this->getNormal().length();
		}
	};

	class Line2 {
		Vector2 a, b;
	public:
		inline constexpr
		Line2(const Vector2& from, const Vector2& to)
		:a{from}, b{to} {}

		inline constexpr
		Line2(Vector2&& from, Vector2&& to)
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

	class Line3 {
		Vector3 a, b;
	public:
		inline constexpr
		Line3(const Vector3& from, const Vector3& to)
		:a{from}, b{to} {}

		inline constexpr
		Line3(Vector3&& from, Vector3&& to)
		:a{from}, b{to} {}

		inline constexpr
		auto getFrom() const -> const Vector3& {
			return a;
		}

		inline constexpr
		auto getTo() const -> const Vector3 {
			return b;
		}

		inline constexpr
		auto getDir() const -> const Vector3 {
			return (b-a);
		}

		inline constexpr
		auto asVec3() const -> Vector3 {
			return this->getDir();
		}
	};

	inline 
	auto intersect_angle(const Line3& line, const Plane3& plane) -> float {
		return asinf(fabs(plane.getNormal().dot_prod(line.getDir()))
						/(plane.getNormal().length()*line.getDir().length())
				);
	}

	inline 
	auto intersect_angle(const Plane3& plane, const Line3& line) -> float {
		return intersect_angle(line, plane);
	}
	
	inline 
	auto intercet_angle(const Plane3& p1, const Plane3& p2) -> float {
		return acosf((p1.getNormal().dot_prod(p2.getNormal()))
					/(p1.getNormal().length()*p2.getNormal().length())
				);
	}

    inline 
	auto intersect_line(const Plane3& p1, const Plane3& p2) -> Line3 {
		auto pos{ p1.getNormal().cross_prod(p2.getNormal()) };
		auto dir{ Vector3(1.f, 1.f, 1.f) };
		//TODO: calculate dir

		return Line3(pos, (pos+dir));
	}

	inline constexpr
    auto lerp(const float& goal, const float& current, const float& step)-> float {
    	auto dif{ goal - current };
    	[[likely]]
    	if(dif > step)  return current+step;
    	if(dif < -step) return current-step;
    	[[unlikely]]
    	return goal;
    }

    inline
    auto lerp(const Vector2& goal, const Vector2& current, const float& step)-> Vector2 {
		auto fwd{ goal-current };
		fwd._normalize()._scale(step);
		return current.add(fwd);
    }

    inline 
    auto lerp(const Vector3& goal, const Vector3& current, const float& step)-> Vector3 {
		auto fwd{ goal-current };
		fwd._normalize()._scale(step);
		return current.add(fwd); 
    }

	inline constexpr
	auto quadratic_bezier(const float& p0, const float& p1, const float& p2, const float& progress) -> float {
		auto pr1{ fabs(p1-p0)*progress };	
		auto pr2{ fabs(p2-p1)*progress };

		auto l0{ lerp(p1, p0, pr1) };
		auto l1{ lerp(p2, p1, pr2) };

		auto pr3{ fabs(l1-l0)*progress };
		return lerp(l1, l0, pr3);
	}

	auto quadratic_bezier(const Vector2& p0, const Vector2& p1, const Vector2& p2, const float& progress) -> Vector2 {
		auto pr1{ (p1-p0).length()*progress };	
		auto pr2{ (p2-p1).length()*progress };

		auto l0{ lerp(p1, p0, pr1) };
		auto l1{ lerp(p2, p1, pr2) };

		auto pr3{ (l0-l1).length()*progress };
		return lerp(l1, l0, pr3);
	}

	auto quadratic_bezier(const Vector3& p0, const Vector3& p1, const Vector3& p2, const float& progress) -> Vector3 {
		auto pr1{ (p1-p0).length()*progress };	
		auto pr2{ (p2-p1).length()*progress };

		auto l0{ lerp(p1, p0, pr1) };
		auto l1{ lerp(p2, p1, pr2) };

		auto pr3{ (l0-l1).length()*progress };
		return lerp(l1, l0, pr3);
	}

	inline constexpr
	auto min(float& a, float& b) -> float& {
		return a<b?a:b;
	}

	inline constexpr
	auto max(float& a, float& b) -> float& {
		return a>b?a:b;
	}

    inline constexpr
    auto powZ(const float& b, const int& exp)-> float {
        [[unlikely]]
        if(b == 0){
            if(exp<0){
                return std::round_toward_infinity;
            }
            return 1;
        }
        if(exp == 0) return 0;

        auto base{b};
        [[likely]]
        for(int i{1}; i<exp; ++i){
            base *= b;
        }

        if(exp<0){
            return 1/b;
        }
        return base;
    }

	inline 
	auto pow(const float& b, const float& exp) -> float {
  		 return __builtin_powf(b, exp); 
	}
}
}
