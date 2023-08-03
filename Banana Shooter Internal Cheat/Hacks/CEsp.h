#include "Globals.h"

struct CEsp
{
	void RenderEsp();
	void DrawBox();
	void DrawTraceline();
	void DrawHealthbar(int health);			
	
	Vector3 wEntityHead = { 0.f, 0.f, 0.f }; 
	Vector3 wEntityFeet = { 0.f, 0.f, 0.f }; 

	Vector2 sEntityHead = { 0.f, 0.f }; 
	Vector2 sEntityFeet = { 0.f, 0.f }; 
			
};