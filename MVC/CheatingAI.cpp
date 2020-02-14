//
// Created by mfbut on 3/11/2019.
//
#include <stdexcept>
#include "CheatingAI.h"
#include "Attack.h"
namespace BattleShip {
	CheatingAI::CheatingAI(const GameAttributes& gameAttributes, View& view) :
		AiPlayer(gameAttributes, view){

	}
	std::unique_ptr<Move> CheatingAI::getMove() {
		int row, col;
		int i, j;
		Board board = getOpponent().getBoard();
		for (i = 0; i < board.getNumRows(); i++) {
			for (j = 0; j < board.getNumCols(); j++) {
				if (!board.at(i, j).HasBeenFiredAt() && board.at(i, j).containsShip()) {
					row = i;
					col = j;
					break;
				}
			}
			if (j < board.getNumCols())
				break;
		}
		AttackResult result = getOpponent().fireAt(row, col);
		view.showPlayersBoard(*this);
		view.showPlacementBoard(*this);
		view.showResultOfAttack(*this, result);
		return nullptr;
	}
}