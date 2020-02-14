//
// Created by mfbut on 3/9/2019.
//
#include <utility>
#include "Utility.h"
#include "GameAttributes.h"
namespace BattleShip {
	GameAttributes::GameAttributes() {
		numRows = 0;
		numCols = 0;
	}
	GameAttributes::GameAttributes(int numRows, int numCols) : numRows(numRows), numCols(numCols) {

	}
	GameAttributes::GameAttributes(std::istream& in) {
		int numShips = 0, shipSize = 0;
		char shipChar;
		BattleShip::verifiedRead(in, numRows);
		BattleShip::verifiedRead(in, numCols);
		BattleShip::verifiedRead(in, numShips);
		while (numShips--) {
			BattleShip::verifiedRead(in, shipChar);
			BattleShip::verifiedRead(in, shipSize);
			shipAttributes.insert(std::make_pair(shipChar, shipSize));
		}
	}

	int GameAttributes::getNumRows() const {
		return numRows;
	}
	void GameAttributes::setNumRows(int numRows) {
		this->numRows = numRows;
	}
	int GameAttributes::getNumCols() const {
		return numCols;
	}
	void GameAttributes::setNumCols(int numCols) {
		this->numCols = numCols;
	}

	int GameAttributes::getShipSize(const char ShipChar) const {
		for (auto ship : shipAttributes) {
			if (ship.first == ShipChar)
				return ship.second;
		}
		return 0;
	}
	const std::map<char, int>& GameAttributes::getShipAttributes() const {
		return shipAttributes;
	}
	std::istream& operator>>(std::istream& in, GameAttributes& gameAttributes) {
		int numShips = 0, shipSize = 0;
		char shipChar;
		BattleShip::verifiedRead(in, gameAttributes.numRows);
		BattleShip::verifiedRead(in, gameAttributes.numCols);
		BattleShip::verifiedRead(in, numShips);
		while (numShips--) {
			BattleShip::verifiedRead(in, shipChar);
			BattleShip::verifiedRead(in, shipSize);
			gameAttributes.shipAttributes.insert(std::make_pair(shipChar, shipSize));
		}
		return in;
	}

}