#include "pch.h"
#include "SphereShape.h"

SphereShape::SphereShape(btScalar (radius))
{
	//m_radius = radius;
	m_shape = new btSphereShape(btScalar (radius)); //creates sphere shape based on the float provided
	


}