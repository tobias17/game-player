//*****************************************************************************
//Includes
#include "TicTacToeGameWindow.h"

TicTacToeGameWindow::TicTacToeGameWindow(TicTacToeSettings_t aSetting, Engine* engine1, Engine* engine2) : QWidget(0) {
	signalMapper = new QSignalMapper;
	game = new TicTacToeGame(aSetting);
	settings = aSetting;
	int size = settings.squareCount;

	engineHandlers[p1Engine] = new EngineHandler(engine1);
	connect(this, SIGNAL (sendP1EngineMove(Game*)), engineHandlers[p1Engine], SLOT (getMove(Game*)));
	connect(engineHandlers[p1Engine], SIGNAL (sendMove(int)), this, SLOT (receiveP1EngineMove(int)));
	engineHandlers[p1Engine]->moveToThread(&workerThread);

	engineHandlers[p2Engine] = new EngineHandler(engine2);
	connect(this, SIGNAL (sendP2EngineMove(Game*)), engineHandlers[p2Engine], SLOT (getMove(Game*)));
	connect(engineHandlers[p2Engine], SIGNAL (sendMove(int)), this, SLOT (receiveP2EngineMove(int)));
	engineHandlers[p2Engine]->moveToThread(&workerThread);

	workerThread.start();

	QSize buttonSize = QSize(settings.squareSize, settings.squareSize);
	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			QPushButton* button = new QPushButton("", this);
			QPoint loc = QPoint((x+1)*settings.gapSize + x*settings.squareSize, (y+1)*settings.gapSize + y*settings.squareSize);
			button->setGeometry(QRect(loc, buttonSize));
			buttons.push_back(button);

			connect(button, SIGNAL (released()), signalMapper, SLOT(map()));
			signalMapper->setMapping(button, x + y*size);
		}
	}
	connect(signalMapper, SIGNAL (mapped(int)), this, SLOT (boardButtonHandler(int)));
	connect(this, SIGNAL (sendMoveRequest()), this, SLOT (recieveMoveRequest()), Qt::QueuedConnection);

	messageBox = new QMessageBox;
	messageBox->setWindowTitle("Game Over");

	QSize windowSize = QSize((size+1)*settings.gapSize + size*settings.squareSize, (size+1)*settings.gapSize + size*settings.squareSize);
	this->setFixedSize(windowSize);
	this->setWindowTitle("Tic Tac Toe");

	emit sendMoveRequest();
}

TicTacToeGameWindow::~TicTacToeGameWindow() {
	cout << "deleting" << endl;;
}

void TicTacToeGameWindow::boardButtonHandler(int id) {
	int playerTurn = game->getPlayerTurn();
	if (playerTurn == Game::player1 && !engineHandlers[0]->getIsEngineHuman()) {
		return;
	} else if (playerTurn == Game::player2 && !engineHandlers[1]->getIsEngineHuman()) {
		return;
	}
	bool worked = game->makeMove(id, playerTurn);
	if (!worked) return;
	QPushButton* b = buttons.at(id);
	b->setText((playerTurn == Game::player1) ? PLAYER_1_CHAR : PLAYER_2_CHAR);

	checkForWinner();
	emit sendMoveRequest();
}

void TicTacToeGameWindow::checkForWinner() {
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

void TicTacToeGameWindow::recieveMoveRequest() {
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

void TicTacToeGameWindow::receiveP1EngineMove(int id) {
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

void TicTacToeGameWindow::receiveP2EngineMove(int id) {
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

void TicTacToeGameWindow::updateUI() {
	for (int y = 0; y < settings.squareCount; y++) {
		for (int x = 0; x < settings.squareCount; x++) {
			int p = game->getSquare(x, y);
			QString s = "";
			if (p == Game::player1) {
				s = PLAYER_1_CHAR;
			} else if (p == Game::player2) {
				s = PLAYER_2_CHAR;
			}
			buttons.at(x + y*settings.squareCount)->setText(s);
		}
	}
}




