//
// Created by mfbut on 3/10/2019.
//

#include "Board.h"

namespace BattleShip {
	Board::Board(int numRows, int numCols, char blankChar) :
		blankChar(blankChar){
		for (int i = 0; i < numRows; i++) {
			std::vector<Cell> vec;
			for (int j = 0; j < numCols; j++) {
				vec.push_back(Cell(blankChar));
			}
			boardState.push_back(vec);
		}
	}
	Board::Board(int numRows, int numCols) :
		blankChar('*'){
		for (int i = 0; i < numRows; i++) {
			std::vector<Cell> vec;
			for (int j = 0; j < numCols; j++) {
				vec.push_back(Cell(blankChar));
			}
			boardState.push_back(vec);
		}
	}
	bool Board::canPlaceShipAt(const ShipPlacement& shipPlacement) const {
		return spacesAreEmpty(shipPlacement);
	}

	int Board::getNumRows() const {
		return boardState.size();
	}
	int Board::getNumCols() const {
		return boardState[0].size();
	}

	std::vector<std::string> Board::getHiddenVersion() const {
		std::vector<std::string> vec;
		for (auto row : boardState) {
			std::string line = "";
			for (auto col : row) {
				line += col.getContentsIfHidden();
				line += " ";
			}
			vec.push_back(line);
		}
		return vec;
	}
	std::vector<std::string> Board::getVisibleVersion() const {
		std::vector<std::string> vec;
		for (auto row : boardState) {
			std::string line = "";
			for (auto col : row) {
				line += col.getContentsIfVisible();
				line += " ";
			}
			vec.push_back(line);
		}
		return vec;
	}

	void Board::AddShip(char shipChar, const ShipPlacement& shipPlacement) {
		if (spacesAreEmpty(shipPlacement)) {
			if (shipPlacement.rowStart == shipPlacement.rowEnd) {
				for (int i = shipPlacement.colStart; i <= shipPlacement.colEnd; i++) {
					boardState[shipPlacement.rowStart][i].setContents(shipChar);
				}
			}
			else {
				for (int i = shipPlacement.rowStart; i <= shipPlacement.rowEnd; i++) {
					boardState[i][shipPlacement.colStart].setContents(shipChar);
				}
			}
		}
	}
	bool Board::inBounds(int row, int col) const {
		if (col >= 0 && col < getNumCols() && row >= 0 && row < getNumRows()) {
			return true;
		}
		return false;
	}

	Cell& Board::at(int i, int j) {
		return boardState[i][j];
	}
	const Cell& Board::at(int i, int j) const {
		return boardState[i][j];
	}

	bool Board::inBounds(const ShipPlacement& shipPlacement) const {
		if (inBounds(shipPlacement.rowStart, shipPlacement.colStart) 
			&& inBounds(shipPlacement.rowEnd, shipPlacement.colEnd)) {
			return true;
		}
		return false;
	}

	bool Board::between(int value, int low, int high) const {
		if (value >= low && value <= high)
			return true;
		return false;
	}
	bool Board::spacesAreEmpty(const ShipPlacement& shipPlacement) const {
		if (!inBounds(shipPlacement))
			return false;
		if (shipPlacement.rowStart == shipPlacement.rowEnd) {
			for (int i = shipPlacement.colStart; i < shipPlacement.colEnd; i++) {
				if (boardState[shipPlacement.rowStart][i].containsShip())
					return false;
			}
			return true;
		}
		else {
			for (int i = shipPlacement.rowStart; i < shipPlacement.rowEnd; i++) {
				if (boardState[i][shipPlacement.colStart].containsShip())
					return false;
			}
			return true;
		}
	}

}