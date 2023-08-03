#pragma once
#include "CGui.h"

struct CMenu : CGui
{
	void BeginRender();
	void RenderMenu(); 
	void EndRender(); 
};
