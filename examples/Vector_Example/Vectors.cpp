#include "../common.hpp"

using v2 = drop::math::Vector2;

int main(){
	const int width{ 500 };
	const int height{ 500 };

	InitWindow(width, height, "Vector Window");
	SetTargetFPS(30);

	const v2 a{1.f, 1.f};
	const v2 b{3.f, 1.f};
	const v2 c{2.f, 3.f};
	const v2 d{4.f, 3.f};

	const auto d1{ b-c };
	const auto d2{ d-a };

	const auto mid{ a.add((d2.scaled(0.5f))) };

	const auto same{ c+(d1.scaled(0.5f)) == a+(d2.scaled(0.5f)) };
	std::cout << (same?"They half each other" : "Theory was wrong!") << std::endl;

	while(!WindowShouldClose()){
		ClearBackground(BLACK);
		BeginDrawing();
		DrawLine(a.getX()*100, height-a.getY()*100, 0, 500, BLUE);
		DrawLine(b.getX()*100, height-b.getY()*100, 0, 500, BLUE);
		DrawLine(c.getX()*100, height-c.getY()*100, 0, 500, BLUE);
		DrawLine(d.getX()*100, height-d.getY()*100, 0, 500, BLUE);

		DrawLine(a.getX()*100, height-a.getY()*100, b.getX()*100, height-b.getY()*100, VIOLET);
		DrawLine(b.getX()*100, height-b.getY()*100, d.getX()*100, height-d.getY()*100, VIOLET);
		DrawLine(a.getX()*100, height-a.getY()*100, c.getX()*100, height-c.getY()*100, VIOLET);
		DrawLine(c.getX()*100, height-c.getY()*100, d.getX()*100, height-d.getY()*100, VIOLET);

		DrawLine(c.getX()*100, height-c.getY()*100, b.getX()*100, height-b.getY()*100, YELLOW);
		DrawLine(a.getX()*100, height-a.getY()*100, d.getX()*100, height-d.getY()*100, YELLOW);

		DrawLine(mid.getX()*100, height-mid.getY()*100, 0, 500, RED);

		EndDrawing();
	}
}
