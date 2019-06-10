#pragma once
class IState
{
public:
	IState();
	~IState();

	virtual void Update(float p_delta) = 0;
	virtual void Draw() = 0;
	virtual void Enter() = 0;
	virtual void Exit() = 0;
};

