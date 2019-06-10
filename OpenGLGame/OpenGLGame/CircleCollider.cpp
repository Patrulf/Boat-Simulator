#include "CircleCollider.h"



CircleCollider::CircleCollider(float p_x, float p_z, float p_radius)
	: x(p_x),
	z(p_z),
	radius(p_radius)
{
}

CircleCollider::~CircleCollider()
{
}

float CircleCollider::GetX()
{
	return x;
}
float CircleCollider::GetZ()
{
	return z;
}

void CircleCollider::SetRadius(float p_value)
{
	radius = p_value;
}

float CircleCollider::GetRadius()
{
	return radius;
}

void CircleCollider::SetPosition(float p_x, float p_z)
{
	x = p_x;
	z = p_z;
}
