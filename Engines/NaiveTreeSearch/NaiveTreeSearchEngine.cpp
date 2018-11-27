//*****************************************************************************
//Includes
#include <chrono>
#include "NaiveTreeSearchEngine.h"

NaiveTreeSearchEngine::NaiveTreeSearchEngine(NaiveTreeSearchEngineSettings_t aSetting) {
	settings = aSetting;
}

int NaiveTreeSearchEngine::getMove(Game* game) {
	vector<int> v = game->getPossibleMoves();
	int weights[v.size()];
	for (uint i = 0; i < v.size(); i++) weights[i] = 0;
	auto start = chrono::steady_clock::now();
	while (chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - start).count() < settings.timePerMove_ms) {
		for (uint start = 0; start < v.size(); start++) {
			if (!isRunning()) return v.at(0);
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
