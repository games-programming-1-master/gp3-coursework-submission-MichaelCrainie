#pragma once
#include "pch.h"
#include "CollisionShape.h"

class SphereShape : public CollisionShape
{
private:
	double m_radius;
public:
	SphereShape(btScalar (radius));
};