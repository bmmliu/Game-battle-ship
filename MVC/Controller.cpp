//
// Created by mfbut on 3/9/2019.
//

#include <stdexcept>
#include <vector>
#include <sstream>
#include "PlayerConfiguration.h"
#include "Controller.h"
#include "HumanPlayer.h"
#include "AiPlayer.h"
#include "StandardView.h"
#include "CheatingAI.h"
#include "RandomAI.h"
#include "HuntDestroyAI.h"
namespace BattleShip {
	Controller::Controller() {
		hasBeenSetUp = false;
		model = Model();
		view = std::make_unique<StandardView>();
	}
	void Controller::setupGame(const std::string& GameConfigurationFile, int seed) {
		if (hasBeenSetUp == false) {
			hasBeenSetUp = true;
			model.loadGameConfigurationFromFile(GameConfigurationFile);
			AiPlayer::seed_random_number_generator(seed);
		}
	}
	void Controller::setupGame(const std::string& GameConfigurationFile) {
		if (hasBeenSetUp == false) {
			hasBeenSetUp = true;
			model.loadGameConfigurationFromFile(GameConfigurationFile);
			AiPlayer::seed_random_number_generator(0);
		}
	}
	void Controller::setupGame() {
		hasBeenSetUp = true;
	}
	void Controller::playGame() {
		PlayerConfiguration cfg = view->getPlayerConfiguration();
		int numHumanPlayers = cfg.numHumanPlayers;
		int numAiPlayers = cfg.numAiPlayers;
		while (numHumanPlayers--) {
			model.addPlayer<HumanPlayer>(*view);
		}
		while (numAiPlayers--) {
			switch (view->getAiChoice()) {
			case 1: model.addPlayer<CheatingAI>(*view); break;
			case 2: model.addPlayer<RandomAI>(*view); break;
			case 3: model.addPlayer<HuntDestroyAI>(*view); break;
			}
		}
		model.SetOpponents();

		while (true) {
			model.getNextMove();
			if (model.isGameOver()) {
				view->showWinner(model.getWinner());
				break;
			}
			model.changeTurn();
		}
	}
}