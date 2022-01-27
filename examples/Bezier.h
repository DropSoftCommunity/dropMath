#pragma once
#include "common.hpp"

void bezier(){
	namespace dm = drop::math;
	SetTargetFPS(30);

	//Quadratic Bezier example

	InitWindow(800, 600, "Dropsoft - dropMath Examples");

	dm::Vector3 playerRotation(5.f, 1.f, 0.f);
	dm::Vector3 enemyRotation(241.f, 125.f, 0.f);
	dm::Vector3 midPoint{ (enemyRotation - playerRotation)/2 };
	midPoint.setX(midPoint.getX() + 10.f);
	midPoint.setY(midPoint.getY() + 300.f);

	dm::Vector3 newPos;
	float progress{ 0.f };
	while(!WindowShouldClose()){
		BeginDrawing();
		DrawCircle(playerRotation.getX(), playerRotation.getY(), 3.f, RED);
		DrawCircle(enemyRotation.getX(), enemyRotation.getY(), 3.f, RED);
		DrawCircle(midPoint.getX(), midPoint.getY(), 3.f, YELLOW);
		DrawLineBezierQuad(
				{ playerRotation.getX(), playerRotation.getY() }, 
				{ enemyRotation.getX(), enemyRotation.getY() }, 
				{ midPoint.getX(), midPoint.getY() }, 1.f, GREEN
			);

		//calculate the new position every frame:

		progress += GetFrameTime()*0.1f;
		newPos = dm::quadratic_bezier(playerRotation, midPoint, enemyRotation, progress);
		DrawCircle(newPos.getX(), newPos.getY(), 3.f, GREEN);

		if(progress > 1.f){
			progress = 0.1f;
		}

		ClearBackground(RAYWHITE);
		DrawText("dropMath - Bezier Example", 10, 20, 20, LIGHTGRAY);
		
	


		EndDrawing();
	}
	CloseWindow();
}
