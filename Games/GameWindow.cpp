//*****************************************************************************
//Includes
#include "GameWindow.h"

GameWindow::GameWindow(Game* aGame, Engine* engine1, Engine* engine2) : QWidget(0) {
	// set the internal game to the one passed in
	game = aGame;

	// create a new engine handler with the engine passed in
	engineHandlers[p1Engine] = new EngineHandler(engine1);
	// set up the signals and slots to communicate with the engine handler
	connect(this, SIGNAL (sendP1EngineMove(Game*)), engineHandlers[p1Engine], SLOT (getMove(Game*)));
	connect(engineHandlers[p1Engine], SIGNAL (sendMove(int)), this, SLOT (receiveP1EngineMove(int)));
	// send the engine handler to a separate thread
	engineHandlers[p1Engine]->moveToThread(&workerThread);

	// create a new engine handler with the engine passed in
	engineHandlers[p2Engine] = new EngineHandler(engine2);
	// set up the signals and slots to communicate with the engine handler
	connect(this, SIGNAL (sendP2EngineMove(Game*)), engineHandlers[p2Engine], SLOT (getMove(Game*)));
	connect(engineHandlers[p2Engine], SIGNAL (sendMove(int)), this, SLOT (receiveP2EngineMove(int)));
	// send the engine handler to a separate thread
	engineHandlers[p2Engine]->moveToThread(&workerThread);

	// start the worker thread
	workerThread.start();

	// create a new message box to be used when the game is over
	messageBox = new QMessageBox;
	messageBox->setWindowTitle("Game Over");

	// set the window attribute to Delete on Close to end the game when the window is closed
	this->setAttribute(Qt::WA_DeleteOnClose);
}

void GameWindow::boardButtonHandler(int id) {
	// get the player turn
	int playerTurn = game->getPlayerTurn();
	// check to see if the current player is human
	if (playerTurn == Game::player1 && !engineHandlers[0]->getIsEngineHuman()) {
		return;
	} else if (playerTurn == Game::player2 && !engineHandlers[1]->getIsEngineHuman()) {
		return;
	}
	// send a move request to the game
	bool worked = game->makeMove(id, playerTurn);
	// if the move failed, return
	if (!worked) return;

	// update the ui, check for winner, and send a new move request
	updateUI();
	checkForWinner();
	emit sendMoveRequest();
}

void GameWindow::recieveMoveRequest() {
	// grab the player turn
	int playerTurn = game->getPlayerTurn();
	// return if current player is human, otherwise send the appropriate engine a move request
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
	// grab the player turn
	int playerTurn = game->getPlayerTurn();
	// if the player turn is not player 1, return
	if (playerTurn != Game::player1) {
		cout << "returning" << endl;
		return;
	}

	// make the move
	bool worked = game->makeMove(id, playerTurn);
	// if the move failed, tell the user
	if (!worked) cout << "engine 1 move failed" << endl;

	// update the ui, check for winner, and send a new move request
	updateUI();
	checkForWinner();
	emit sendMoveRequest();
}

void GameWindow::receiveP2EngineMove(int id) {
	// grab the player turn
	int playerTurn = game->getPlayerTurn();
	// if the player turn is not player 2, return
	if (playerTurn != Game::player2) {
		cout << "returning" << endl;
		return;
	}

	// make the move
	bool worked = game->makeMove(id, playerTurn);
	// if the move failed, tell the user
	if (!worked) cout << "engine 1 move failed" << endl;

	// update the ui, check for winner, and send a new move request
	updateUI();
	checkForWinner();
	emit sendMoveRequest();
}

void GameWindow::checkForWinner() {
	// grab the winner from the game
	int winner = game->getWinner();
	// check to see if there is a winner
	if (winner != Game::none) {
		// if there is a winner tell the user who won
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
	// go through and kill all of the engines
	for (int i = p1Engine; i <= p2Engine; i++) engineHandlers[i]->killEngine();
	// tell the worker thread to quit and wait for it to finish
	workerThread.quit();
	workerThread.wait();
}
