#include "pch.h"
#include "CapsuleShape.h"

CapsuleShape::CapsuleShape(radius, height, zUP)
{
	
	m_shape = new btCapsuleShape(radius, height, zUP)
	//m_type = CShapeType::BOX;
}