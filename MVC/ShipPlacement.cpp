//
// Created by mfbut on 3/10/2019.
//

#include <algorithm>
#include "ShipPlacement.h"

ShipPlacement::ShipPlacement() :
	rowStart(-1),
	colStart(-1),
	rowEnd(-1),
	colEnd(-1)
{

}
ShipPlacement::ShipPlacement(int rowStart, int colStart, int rowEnd, int colEnd) :
	rowStart(rowStart),
	colStart(colStart),
	rowEnd(rowEnd),
	colEnd(colEnd)
{
}

void ShipPlacement::normalize() {

}
