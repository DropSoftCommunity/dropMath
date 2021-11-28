#pragma once

#include <math.h>

namespace drop{
namespace math{

    class Vector2{
        float x, y;
				
		public:
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

			Vector2(float x=0.f, float y=0.f): x{x}, y{y}{
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
				this->x = new_x;
				return *this;
			}

			auto setY(const float& new_y) -> Vector2& {
				this->y = new_y;
				return *this;
			}

			auto set(const float& new_x, const float& new_y) -> Vector2& {
				this->x = new_x;
				this->y = new_y;
				return *this;
			}

			auto set(const Vector2& other) -> Vector2& {
				this->x = other.getX();
				this->y = other.getY();
				return *this;
			}

			auto squared_length() const -> float {
				return x*x + y*y;
			}

			auto length() const -> float {
				return sqrt(this->squared_length());
			}

			auto normalized() const -> Vector2 {
				auto length{ this->length() };
				return Vector2(x/length, y/length);
			}

			auto normalize() -> Vector2& {
				auto length { this->length() };
				this->x /= length;
				this->y /= length;
				return *this;
			}

			auto scaled(const float& factor) const -> Vector2{
				return Vector2(x*factor, y*factor);
			}

			auto scale(const float& factor) -> Vector2&{
				this->x *= factor;
				this->y *= factor;
				return *this;
			}

			auto substract(const Vector2& other) const -> Vector2 {
				return Vector2(x-other.getX(), y-other.getY());
			}
			
			auto _substract(const Vector2& other) -> Vector2& {
				this->x -= other.getX();
				this->y -= other.getY();
				return *this;
			}

			auto divide(const float& divisor) const -> Vector2 {
				//if(divisor == 0) return Vector2.infinity;
				return Vector2(x/divisor, y/divisor);
			}

			auto _divide(const float& divisor) -> Vector2& {
				this->x /= divisor;
				this->y /= divisor;
				return *this;
			}

			auto add(const Vector2& other) const -> Vector2 {
				return Vector2(x+other.getX(), y+other.getY()); 
			}

			auto _add(const Vector2& other) -> Vector2& {
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
				return this->substract(other);
			}
    };
	
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

