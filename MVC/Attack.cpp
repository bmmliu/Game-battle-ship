//
// Created by mfbut on 3/10/2019.
//

#include "Attack.h"
namespace BattleShip {
	Attack::Attack(BattleShip::Player& attacker, int row, int col) :
		Move(attacker), row(row), col(col)
	{
	}
	void Attack::enact(Model& model, View& view) {

	}
	bool Attack::isValid() const {
		return true;
	}
	const int Attack::getRow() const {
		return row;
	}
	const int Attack::getCol() const {
		return col;
	}
}

