//*****************************************************************************
//Includes
#include "GameWindow.h"

GameWindow::GameWindow(Game* aGame, Engine* engine1, Engine* engine2) : QWidget(0) {
	game = aGame;

	engineHandlers[p1Engine] = new EngineHandler(engine1);
	connect(this, SIGNAL (sendP1EngineMove(Game*)), engineHandlers[p1Engine], SLOT (getMove(Game*)));
	connect(engineHandlers[p1Engine], SIGNAL (sendMove(int)), this, SLOT (receiveP1EngineMove(int)));
	engineHandlers[p1Engine]->moveToThread(&workerThread);

	engineHandlers[p2Engine] = new EngineHandler(engine2);
	connect(this, SIGNAL (sendP2EngineMove(Game*)), engineHandlers[p2Engine], SLOT (getMove(Game*)));
	connect(engineHandlers[p2Engine], SIGNAL (sendMove(int)), this, SLOT (receiveP2EngineMove(int)));
	engineHandlers[p2Engine]->moveToThread(&workerThread);

	workerThread.start();

	messageBox = new QMessageBox;
	messageBox->setWindowTitle("Game Over");

	this->setAttribute(Qt::WA_DeleteOnClose);
}

void GameWindow::boardButtonHandler(int id) {
	int playerTurn = game->getPlayerTurn();
	if (playerTurn == Game::player1 && !engineHandlers[0]->getIsEngineHuman()) {
		return;
	} else if (playerTurn == Game::player2 && !engineHandlers[1]->getIsEngineHuman()) {
		return;
	}
	bool worked = game->makeMove(id, playerTurn);
	if (!worked) return;

	updateUI();
	checkForWinner();
	emit sendMoveRequest();
}

void GameWindow::recieveMoveRequest() {
	int playerTurn = game->getPlayerTurn();
	if (playerTurn == Game::player1) {
		if (engineHandlers[p1Engine]->getIsEngineHuman()) {
			return;
		} else {
			emit sendP1EngineMove(game);
		}
	} else if (playerTurn == Game::player2) {
		if (engineHandlers[p2Engine]->getIsEngineHuman()) {
			return;
		} else {
			emit sendP2EngineMove(game);
		}
	} else {
		return;
	}
}

void GameWindow::receiveP1EngineMove(int id) {
	int playerTurn = game->getPlayerTurn();
	if (playerTurn != Game::player1) {
		cout << "returning" << endl;
		return;
	}

	game->makeMove(id, playerTurn);
	updateUI();
	checkForWinner();
	emit sendMoveRequest();
}

void GameWindow::receiveP2EngineMove(int id) {
	int playerTurn = game->getPlayerTurn();
	if (playerTurn != Game::player2) {
		cout << "returning" << endl;
		return;
	}

	game->makeMove(id, playerTurn);
	updateUI();
	checkForWinner();
	emit sendMoveRequest();
}

void GameWindow::checkForWinner() {
	int winner = game->getWinner();
	if (winner != Game::none) {
		if (winner == Game::player1) {
			messageBox->setText("Player 1 has won the game!");
		} else if (winner == Game::player2) {
			messageBox->setText("Player 2 has won the game!");
		} else {
			messageBox->setText("The game has ended in a tie.");
		}
		messageBox->exec();
	}
}

void GameWindow::closeEvent(QCloseEvent *bar) {
	for (int i = p1Engine; i <= p2Engine; i++) engineHandlers[i]->killEngine();
	workerThread.quit();
	workerThread.wait();
}
