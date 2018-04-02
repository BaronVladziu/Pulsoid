#pragma once
#include "header.h"
#include "Effects.h"
#include "Map.h"

void restart(Effects & effects, Map & map)
{
	effects.restart();
	map.restart();
}