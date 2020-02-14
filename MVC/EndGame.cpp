//
// Created by mfbut on 3/10/2019.
//

#include "EndGame.h"
namespace BattleShip {
	EndGame::EndGame(Player& moveMaker) :
		Move(moveMaker)
	{
	}
	void EndGame::enact(Model& model, View& view) {

	}
	bool EndGame::isValid() const {
		return false;
	}
}