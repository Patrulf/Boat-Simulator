#include "StateMachine.h"
#include "IState.h"


StateMachine::StateMachine()
{
	currentState = nullptr;
}


StateMachine::~StateMachine()
{
	auto it = states.begin();
	while (it != states.end())
	{
		delete it->second;
		it->second = nullptr;
		it++;
	}
	currentState = nullptr;
	states.clear();

}

void StateMachine::Update(float p_delta)
{
	currentState->Update(p_delta);
}

void StateMachine::Draw()
{
	currentState->Draw();
}

void StateMachine::AddState(const std::string p_name, IState * p_state)
{
	auto it = states.find(p_name);
	if (it == states.end())
	{
		states.insert(std::pair<std::string, IState*>(p_name, p_state));
	}
}

void StateMachine::SetState(const std::string p_name)
{
	auto it = states.find(p_name);
	if (it != states.end())
	{
		if (it->second != currentState)
		{
			if (currentState != nullptr)
				currentState->Exit();
			currentState = it->second;
			currentState->Enter();
		}
	}
}


