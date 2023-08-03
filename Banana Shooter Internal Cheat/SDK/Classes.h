#pragma once
#include "CVectors.h"
#include "Offsets.h"

template <typename T, typename ...Arguments>
T CallMemberFunction(uintptr_t functionAddress, void* classInstance, Arguments...args)
{
	using pFunction = T(__thiscall*)(void*, decltype(args)...); 
	pFunction Function = reinterpret_cast<pFunction>(functionAddress); 
    return Function(classInstance, args...); 
}

#include <Windows.h>

struct Transform
{
	void LookAt(Vector3 WorldPosition, uintptr_t gameAssembly)
	{
		CallMemberFunction<void>(gameAssembly + Offsets::Transform::fnLookAt, this, WorldPosition); 
	}
	
	void Rotate(Vector3 angle, uintptr_t gameAssembly)
	{
		CallMemberFunction<void>(gameAssembly + 0x1CCD3F0, this, angle.x, angle.y, angle.z); 
	}

	Vector3 GetPosition(uintptr_t gameAssembly)
	{
		__try
		{
			return CallMemberFunction<Vector3>(gameAssembly + Offsets::Transform::fnGetPosition, this);
		}__except (EXCEPTION_EXECUTE_HANDLER)
		{
			return Vector3{ 0.f, 0.f, 0.f }; 
		}
	}
};

struct Camera
{
	Vector2 WorldToScreen(Vector3 WorldPosition, uintptr_t gameAssembly)
	{
		
		using pFnWorldToScreen = Vector3(__thiscall*)(void*, Vector3 WorldPosition); 
		pFnWorldToScreen fnWorldToScreen = reinterpret_cast<pFnWorldToScreen>(gameAssembly + Offsets::Camera::fnWorldToScreen); 
		Vector3 Result = fnWorldToScreen(this, WorldPosition); 

		if (Result.z < 0.f)
			return Vector2{ 0.f, 0.f}; 

		Vector2 ScreenPosition = { Result.x, 1080.f - Result.y }; 

		return ScreenPosition; 
	}
};

