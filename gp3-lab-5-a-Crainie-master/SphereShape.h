#pragma once
#include "pch.h"
#include "CollisionShape.h"

class SphereShape : public CollisionShape//created class that inherits from CollisionShape
{
private:
	double m_radius;
public:
	SphereShape(btScalar (radius)); 
};