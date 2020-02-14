//
// Created by mfbut on 3/11/2019.
//

#include <algorithm>
#include "HuntDestroyAI.h"
#include "Attack.h"
#include "Utility.h"
namespace BattleShip {
	HuntDestroyAI::HuntDestroyAI(const GameAttributes& gameAttributes, View& view) :
		RandomAI(gameAttributes, view)
	{
	}
	std::unique_ptr<Move> HuntDestroyAI::getMove() {

		int row, col;
		if (priorityFiringQueue.empty()) {
			auto it = chooseRandom(firingLocations, randomNumberGenerator);
			row = it->first;
			col = it->second;
			firingLocations.erase(it);
		}
		else {
			auto it = priorityFiringQueue.begin();
			row = it->first;
			col = it->second;
			priorityFiringQueue.erase(it);
		}
		AttackResult result = getOpponent().fireAt(row, col);
		
		if (result.hit) {
			auto vec = getSurroundingLocations(std::make_pair(row, col));
			for(auto v : vec){
				for (auto it = firingLocations.begin(); it != firingLocations.end(); it++) {
					if (it->first == v.first && it->second == v.second) {
						firingLocations.erase(it);
					}
				}
			}


			priorityFiringQueue.insert(priorityFiringQueue.end(), vec.begin(), vec.end());
		}
		
		view.showPlayersBoard(*this);
		view.showPlacementBoard(*this);
		view.showResultOfAttack(*this, result);
		return nullptr;
	}
	std::vector<std::pair<int, int>> HuntDestroyAI::getSurroundingLocations(const std::pair<int, int>& center) const {
		std::vector<std::pair<int, int>> vec;
		if (board.inBounds(center.first, center.second - 1) && !board.at(center.first, center.second).HasBeenFiredAt()) {
			vec.push_back(std::make_pair(center.first, center.second - 1));
			
		}
		if (board.inBounds(center.first-1, center.second) && !board.at(center.first, center.second).HasBeenFiredAt()) {
			vec.push_back(std::make_pair(center.first-1, center.second));
		}
		if (board.inBounds(center.first, center.second+1) && !board.at(center.first, center.second).HasBeenFiredAt()) {
			vec.push_back(std::make_pair(center.first, center.second+1));
		}
		if (board.inBounds(center.first-1, center.second) && !board.at(center.first, center.second).HasBeenFiredAt()) {
			vec.push_back(std::make_pair(center.first-1, center.second));
		}
		return std::vector<std::pair<int, int>>();
	}
}