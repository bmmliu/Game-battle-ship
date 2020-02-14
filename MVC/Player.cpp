//
// Created by mfbut on 3/9/2019.
//

#include "Player.h"

int BattleShip::Player::num_instances = 0;
namespace BattleShip {
	Player::Player(const GameAttributes& gameAttributes, View& view) 
	:	id(++ Player::num_instances),
		name(""),
		view(view),
		board(gameAttributes.getNumRows(), gameAttributes.getNumCols()),
		opponent(nullptr)
	{
		shipHealths = gameAttributes.getShipAttributes();
	}

	const std::string& Player::getName() const {
		return name;
	}
	void Player::setName(const std::string& name) {
		this->name = name;
	}
	const Board& Player::getBoard() const {
		return board;
	}
	Board& Player::getBoard() {
		return board;
	}
	const int Player::getId() const {
		return id;
	}

	//for hashing
	bool Player::operator==(const Player& rhs) const {
		if (rhs.name == name && rhs.id == id)
			return true;
		return false;
	}
	bool Player::operator!=(const Player& rhs) const {
		if (rhs.name != name || rhs.id != id)
			return true;
		return false;
	}

	bool Player::allShipsSunk() const {
		for (auto health : shipHealths) {
			if (health.second != 0)
				return false;
		}
		return true;
	}

	BattleShip::AttackResult Player::fireAt(int row, int col) {
		BattleShip::AttackResult result(false, false, board.at(row, col).getContents());
		board.at(row, col).setHasBeenFiredAt(true);
		for (auto it = shipHealths.begin(); it != shipHealths.end(); it++) {
			if (it->first == board.at(row, col).getContents()) {
				it->second = it->second > 0 ? it->second - 1 : 0;
				result.hit = true;
				if (it->second == 0)
					result.destroyed = true;
				break;
			}
		}
		return result;
	}

	Player& Player::getOpponent() {
		return *opponent;
	}
	const Player& Player::getOpponent() const {
		return *opponent;
	}
	void Player::setOpponent(Player& opponent) {
		if(nullptr == this->opponent)
			this->opponent = &opponent;
	}

	bool Player::hit(char shipChar) {
		return true;
	}
}