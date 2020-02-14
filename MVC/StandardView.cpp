//
// Created by mfbut on 3/9/2019.
//

#include <algorithm>
#include <vector>
#include <cctype>
#include "StandardView.h"
#include "Utility.h"
#include <string>
namespace BattleShip {
	StandardView::StandardView():in(std::cin), out(std::cout) {}

	StandardView::StandardView(std::istream& in, std::ostream& out):in(in), out(out) {}

	PlayerConfiguration StandardView::StandardView::getPlayerConfiguration() {
		int choose = -1;
		while (choose < 1 || choose > 3) {
			out << "What type of game do you want to play?" << std::endl
				<< "1. Human vs Human" << std::endl
				<< "2. Human vs AI" << std::endl
				<< "3. AI vs AI" << std::endl
				<< "Your choice: ";
			BattleShip::verifiedRead(in, choose);
		}
		
		switch (choose) {
		case 1: return PlayerConfiguration(2, 0);
		case 2: return PlayerConfiguration(1, 1);
		case 3: return PlayerConfiguration(0, 2);
		default: return PlayerConfiguration(1, 1);
		}
	}
	std::string StandardView::getPlayerName(int i) {
		std::string playerName;
		out << "Player " << i << " please enter your name: ";
		BattleShip::verifiedRead(in, playerName);
		return playerName;
	}
	ShipPlacement StandardView::getShipPlacement(const Player& player, char shipChar, int shipLen) {
		char choose = 0;
		while (choose != 'h' && choose != 'v') {
			out << player.getName() << ", do you want to place " <<
				shipChar << " horizontally or vertically?" << std::endl <<
				"Enter h for horizontal or v for vertical" << std::endl <<
				"Your choice: ";
			verifiedRead(in, choose);
		}

		out << player.getName() << ", enter the row and column you want to place " <<
			shipChar << ", which is " << shipLen <<
			" long, at with a space in between row and col: ";
		int row, col;
		verifiedRead(in, row);
		verifiedRead(in, col);
		if (choose == 'v') {
			return ShipPlacement(row, col, row + shipLen, col);
		}
		else {
			return ShipPlacement(row, col, row, col + shipLen);
		}
	}
	void StandardView::updateShipPlacementView(const Player& player) {
		out << player.getName() << "'s Board" << std::endl;
		out << "  ";
		for (int j = 0; j < player.getBoard().getNumCols(); j++) {
			out << j << " ";
		}
		out << std::endl;

		std::vector<std::string> vec = player.getBoard().getVisibleVersion();
		for (unsigned int i = 0; i < vec.size(); i++) {
			out << i << " " << vec[i] << std::endl;
		}
		out << std::endl;
	}
	std::pair<int, int> StandardView::getFiringCoordinate(const BattleShip::Player& attacker) {
		out << attacker.getName() << ", where would you like to fire?" << std::endl
			<< "Enter your attack coordinate in the form row col: ";
		int row, col;
		verifiedRead(in, row);
		verifiedRead(in, col);
		return std::make_pair(row, col);
	}
	void StandardView::showWinner(const Player& winner) {
		out << winner.getName() << " won the game!" << std::endl;
	}
	void StandardView::showResultOfAttack(const BattleShip::Player& attacker,
		const BattleShip::AttackResult& attackResult) {
		if (attackResult.hit == false) {
			out << "Missed." << std::endl;
		}
		if (attackResult.hit)
			out << attacker.getName() << " hit " << attacker.getOpponent().getName()
			<< "'s " << attackResult.shipChar << "!" << std::endl;
		if (attackResult.destroyed)
			out << attacker.getName() << " destroyed " << attacker.getOpponent().getName()
			<< "'s " << attackResult.shipChar << "!" << std::endl;
		out << std::endl;
	}

	void StandardView::showPlayersBoard(const Player& player) {
		out << player.getName() << "'s Firing Board" << std::endl;
		printBoardAsObscured(player.getOpponent().getBoard());
		out << std::endl << std::endl;
	}
	void StandardView::showPlacementBoard(const Player& player) {
		out << player.getName() << "'s Placement Board" << std::endl;
		printBoardAsVisible(player.getBoard());
	}

	void StandardView::printBoard(const std::vector<std::string>& board) {


	}
	void StandardView::printBoardAsVisible(const Board& board) {
		out << "  ";
		for (int j = 0; j < board.getNumCols(); j++) {
			out << j << " ";
		}
		out << std::endl;

		std::vector<std::string> vec = board.getVisibleVersion();
		for (unsigned int i = 0; i < vec.size(); i++) {
			out << i << " " << vec[i] << std::endl;
		}
	}
	void StandardView::printBoardAsObscured(const Board& board) {
		out << "  ";
		for (int j = 0; j < board.getNumCols(); j++) {
			out << j << " ";
		}
		out << std::endl;

		std::vector<std::string> vec = board.getHiddenVersion();
		for (unsigned int i = 0; i < vec.size(); i++) {
			out << i << " " << vec[i] << std::endl;
		}
	}

	int StandardView::getAiChoice() {
		int choose = -1;
		while (choose < 1 || choose > 3) {
			out << "What AI do you want?" << std::endl
				<< "1. Cheating AI" << std::endl
				<< "2. Random AI" << std::endl
				<< "3. Hunt Destroy AI" << std::endl
				<< "Your choice: ";
			BattleShip::verifiedRead(in, choose);
		}
		return choose;
	}


	void StandardView::clearInput() {

	}
}

