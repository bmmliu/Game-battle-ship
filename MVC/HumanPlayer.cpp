//
// Created by mfbut on 3/9/2019.
//

#include <utility>
#include "HumanPlayer.h"
#include "ShipPlacement.h"
#include "Attack.h"
namespace BattleShip {
	HumanPlayer::HumanPlayer(const GameAttributes& gameAttributes, View& view)
		: Player(gameAttributes, view)
	{
	}
	std::unique_ptr<BattleShip::Move> HumanPlayer::getMove() {
		view.showPlayersBoard(*this);
		view.showPlacementBoard(*this);
		auto place = view.getFiringCoordinate(*this);
		AttackResult result = getOpponent().fireAt(place.first, place.second);
		view.showPlayersBoard(*this);
		view.showPlacementBoard(*this);
		view.showResultOfAttack(*this, result);
		return nullptr;
	}
	void HumanPlayer::placeShips() {
		for (auto attr : shipHealths) {
			ShipPlacement place = view.getShipPlacement(*this, attr.first, attr.second);
			while (!board.canPlaceShipAt(place)) {
				place = view.getShipPlacement(*this, attr.first, attr.second);
			}
			board.AddShip(attr.first, place);
			view.updateShipPlacementView(*this);
		}
	}
	void HumanPlayer::initializeName() {
		std::string playerName = view.getPlayerName(id);
		setName(playerName);
		view.updateShipPlacementView(*this);
	}
}

