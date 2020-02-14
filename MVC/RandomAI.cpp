//
// Created by mfbut on 3/11/2019.
//

#include "RandomAI.h"
#include "Attack.h"
#include "Utility.h"
namespace BattleShip {
	RandomAI::RandomAI(const GameAttributes& gameAttributes, View& view) :
		AiPlayer(gameAttributes, view)
	{
		for (int i = 0; i < board.getNumRows(); i++) {
			for (int j = 0; j < board.getNumCols(); j++) {
				firingLocations.push_back(std::make_pair(i, j));
			}
		}
	}
	std::unique_ptr<Move> RandomAI::getMove() {
		auto it = chooseRandom(firingLocations, randomNumberGenerator);
		AttackResult result = getOpponent().fireAt(it->first, it->second);
		firingLocations.erase(it);
		view.showPlayersBoard(*this);
		view.showPlacementBoard(*this);
		view.showResultOfAttack(*this, result);
		return nullptr;
	}
}