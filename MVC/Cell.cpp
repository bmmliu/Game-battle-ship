//
// Created by mfbut on 3/10/2019.
//

#include <stdexcept>
#include "Cell.h"
namespace BattleShip {
	Cell::Cell(char contents, const char hiddenMarker, const char hitMarker, const char missMarker) : 
		contents(contents),
		firedAt(false),
		hiddenMarker(hiddenMarker),
		hitMarker(hitMarker),
		missMarker(missMarker) 
	{
	}
	Cell::Cell(char contents) :
		Cell(contents, '*', 'X', 'O')
	{
	}
	char Cell::getContents() const {
		return contents;
	}
	void Cell::setContents(char contents) {
		this->contents = contents;
	}
	char Cell::getContentsIfHidden() const {
		if (HasBeenFiredAt()) {
			return containsShip() ? hitMarker : missMarker;
		}
		else {
			return hiddenMarker;
		}
	}
	char Cell::getContentsIfVisible() const {
		if (HasBeenFiredAt()) {
			return containsShip() ? hitMarker : missMarker;
		}
		else {
			return getContents();
		}
	}
	bool Cell::HasBeenFiredAt() const {
		return firedAt;
	}
	void Cell::setHasBeenFiredAt(bool hasBeenFiredAt) {
		firedAt = hasBeenFiredAt;
	}
	bool Cell::containsShip()const {
		if (getContents() == hiddenMarker)
			return false;
		return true;
	}
}
