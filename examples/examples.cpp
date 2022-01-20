#include "../header/dropMath.hpp"
#include <raylib.h>

int main(){
	InitWindow(800, 450, "Dropsoft - dropMath Examples");

	while(!WindowShouldClose()){
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("This will be used for example visualizations", 190, 200, 20, LIGHTGRAY);
		EndDrawing();
	}
	CloseWindow();
	return 0;
}

