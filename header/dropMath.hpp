#pragma once

#include <math.h>

namespace dropMath{
    class Vector2{
        float x, y;
				
		public:
			Vector2(float x=0, float y=0): x{x}, y{y}{
			}

			auto squared_length() -> float {
				return x*x + y*y;
			}

			auto length() -> float {
				return sqrt(this->squared_length());
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

