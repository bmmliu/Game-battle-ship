//
// Created by mfbut on 3/9/2019.
//

#include <fstream>
#include <algorithm>
#include "Model.h"
namespace BattleShip {
	Model::Model() {
		forcedGameOver = false;
		playerTurn = 0;
	}
	Player& Model::getAttackingPlayer() {
		return *(players[playerTurn]);
	}
	const Player& Model::getAttackingPlayer() const {
		return *(players[playerTurn]);
	}

	Player& Model::getDefendingPlayer() {
		return playerTurn == 0 ? *(players[1]) : *(players[0]);
	}
	const Player& Model::getDefendingPlayer() const {
		return playerTurn == 0 ? *(players[1]) : *(players[0]);
	}

	bool Model::isGameOver() const {
		if (forcedGameOver)
			return true;
		if (players[0]->allShipsSunk() || players[1]->allShipsSunk())
			return true;
		return false;
	}
	void Model::changeTurn() {
		playerTurn = playerTurn == 0 ? 1 : 0;
	}
	void Model::loadGameConfigurationFromFile(const std::string& gameConfigurationFile) {
		std::ifstream in;
		in.open(gameConfigurationFile);
		gameAttributes = GameAttributes(in);
	}

	void Model::endGame() {
		forcedGameOver = true;
	}
	std::unique_ptr<Move> Model::getNextMove() {
		return players[playerTurn]->getMove();
	}

	Player& Model::getWinner() {
		if (players[0]->allShipsSunk())
			return *players[1];
		else
			return *players[0];
	}

	void Model::SetOpponents() {
		players[0]->setOpponent(*players[1]);
		players[1]->setOpponent(*players[0]);
	}
}