#pragma once
/*Written by Jerry jonsson for the Augustus engine.*/

#include <cassert>

template <typename T>
class ServiceLocator
{
public:
	static void SetService(T* p_service)
	{
		ms_service = p_service;
	};
	static T* GetService()
	{
		assert(ms_service != nullptr);
		return ms_service;
	}
private:
	static T* ms_service;
};

template <typename T>
T* ServiceLocator<T>::ms_service = nullptr;

