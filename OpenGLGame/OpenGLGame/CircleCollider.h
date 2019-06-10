#pragma once
class CircleCollider
{
public:
	CircleCollider(float p_x, float p_z, float p_radius);
	~CircleCollider();

	float GetX();
	float GetZ();
	float GetRadius();

	void SetPosition(float p_x, float p_z);
	void SetRadius(float p_value);
private:
	float x;
	float z;
	float radius;
};

