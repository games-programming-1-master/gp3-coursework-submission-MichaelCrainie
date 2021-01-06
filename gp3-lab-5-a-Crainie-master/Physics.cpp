#include "pch.h"
#include "Physics.h"
#include "RigidBody.h"

Physics* Physics::m_instance = nullptr;

Physics::Physics()
{
	Init();
}

void Physics::Init()
{
	m_world->setGravity(btVector3(0, -9.8, 0));
}

void Physics::AddRigidbody(RigidBody* r)
{
	m_rbodies.push_back(r);
	m_world->addRigidBody(r->Get());
}

void Physics::PreUpdate()
{
	for (auto r : m_rbodies)
	{
		r->UpdateRigidBody();
	}
}

void Physics::Update(float deltaTime)
{
	PreUpdate();
	m_world->stepSimulation(deltaTime, 2);
	for (auto r : m_rbodies)
	{
		r->UpdateParent();
	}
}

void Physics::Quit()
{
	delete m_world;
	delete m_solver;
	delete m_broadphase;
	delete m_dispatcher;
	delete m_collisionConfig;
}

bool Physics::Collision3D(btCollisionObject* object1, btCollisionObject* object2) //checks if two objects are colliding by checking if their x, y or z coordinates are overlapping
{
	if ((object1->getBroadphaseHandle()->m_aabbMax.x() < object2->getBroadphaseHandle()->m_aabbMin.x()) || (object1->getBroadphaseHandle()->m_aabbMin.x() > object2->getBroadphaseHandle()->m_aabbMax.x()))
	{
		return false;
	}

	if ((object1->getBroadphaseHandle()->m_aabbMax.y() < object2->getBroadphaseHandle()->m_aabbMin.y()) || (object1->getBroadphaseHandle()->m_aabbMin.y() > object2->getBroadphaseHandle()->m_aabbMax.y()))
	{
		return false;
	}

	if ((object1->getBroadphaseHandle()->m_aabbMax.z() < object2->getBroadphaseHandle()->m_aabbMin.z()) || (object1->getBroadphaseHandle()->m_aabbMin.z() > object2->getBroadphaseHandle()->m_aabbMax.z()))
	{
		return false;
	}

	return true;
}

btTransform Physics::ConvertTransformToBtTransform(Transform t)
{
	glm::quat rot = t.GetRotation();
	glm::vec3 pos = t.GetPosition();
	return btTransform(btQuaternion(rot.x, rot.y, rot.z, rot.w), btVector3(pos.x, pos.y, pos.z));
}

Physics* Physics::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new Physics();
	}
	return m_instance;
}
