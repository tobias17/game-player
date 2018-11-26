//*****************************************************************************
//Includes
#include <chrono>
#include "NaiveTreeSearchEngine.h"

NaiveTreeSearchEngine::NaiveTreeSearchEngine(NaiveTreeSearchEngineSettings_t aSetting) {
	settings = aSetting;
}

int NaiveTreeSearchEngine::getMove(Game* game) {
	Game* newGame2 = game->copy();
	cout << "Player turn: " << newGame2->getPlayerTurn() << endl;;
	vector<int> v = game->getPossibleMoves();
	cout << v.size() << endl;
	int weights[v.size()];
	for (uint i = 0; i < v.size(); i++) weights[i] = 0;
	for (uint start = 0; start < v.size(); start++) {
		cout << v.at(start) << endl;
		for (uint c = 0; c < 1000; c++) {
			Game* newGame = game->copy();
			newGame->makeMove(v.at(start), newGame->getPlayerTurn());
			while (newGame->getWinner() == Game::none) {
				vector<int> newMoves = newGame->getPossibleMoves();
				newGame->makeMove(newMoves.at(rand() % newMoves.size()), newGame->getPlayerTurn());
			}
			if (newGame->getWinner() == game->getPlayerTurn()) {
				weights[start]++;
			} else if (newGame->getWinner() == Game::otherPlayer(game->getPlayerTurn())) {
				weights[start]--;
			}
		}
	}
	for (uint i = 0; i < v.size(); i++) cout << v.at(i) << ": " << weights[i] << endl;
	int best = weights[0];
	int bestMove = v.at(0);
	for (uint i = 1; i < v.size(); i++) {
		if (weights[i] > best) {
			best = weights[i];
			bestMove = v.at(i);
		}
	}
	return bestMove;
}
