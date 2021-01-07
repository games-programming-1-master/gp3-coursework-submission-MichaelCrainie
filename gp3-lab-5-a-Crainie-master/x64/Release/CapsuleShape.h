#pragma once
#include "pch.h"
#include "CollisionShape.h"
class CapsuleShape : public CollisionShape
{
private:
	btScalar radius;
	btScalar height;
	btScalar zUP;
public:
	CapsuleShape(radius, height, zUP);
};
