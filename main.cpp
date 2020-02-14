#include "Controller.h"

#include <iostream>
#include <vector>
#include <algorithm>

using Controller = BattleShip::Controller;
int main(int argc, char** argv) {
	Controller *ctrl = new Controller();
	if (argc < 2) {
		std::cout << "Error: Command Line invalid!" << std::endl;
		return -1;
	}
	else if (argc == 2) {
		ctrl->setupGame(argv[1]);
	}
	else {
		ctrl->setupGame(argv[1], atoi(argv[2]));
	}
	ctrl->playGame();

	delete ctrl;
	return 0;
}
