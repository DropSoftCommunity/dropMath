#pragma once
#include "common.hpp"

void bezier(){
	namespace dm = drop::math;

	dm::Vector3 playerRotation(5.f, 1.f, 0.f);
	dm::Vector3 enemyRotation(241.f, 125.f, 0.f);
	dm::Vector3 midPoint{ (enemyRotation - playerRotation)/2 };
	midPoint.setX(midPoint.getX() + 10.f);
	midPoint.setY(midPoint.getY() + 300.f);

	dm::Vector3 newPos;
	float progress{ 0.f };
}
