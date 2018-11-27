//*****************************************************************************
//Includes
#include "Connect4GameWindow.h"

Connect4GameWindow::Connect4GameWindow(Connect4Settings_t aSetting, Engine* engine1, Engine* engine2) : QWidget(0) {
	signalMapper = new QSignalMapper;
	game = new Connect4Game(aSetting);
	settings = aSetting;

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
	for (int y = 0; y < settings.height; y++) {
		for (int x = 0; x < settings.width; x++) {
			QPushButton* button = new QPushButton("", this);
			QPoint loc = QPoint((x+1)*settings.gapSize + x*settings.squareSize, (y+1)*settings.gapSize + y*settings.squareSize);
			button->setGeometry(QRect(loc, buttonSize));
			button->setAutoFillBackground(true);
			button->setFlat(true);
			button->setFocusPolicy(Qt::NoFocus);
			buttons.push_back(button);

			connect(button, SIGNAL (released()), signalMapper, SLOT(map()));
			signalMapper->setMapping(button, x + y*settings.width);
		}
	}
	connect(signalMapper, SIGNAL (mapped(int)), this, SLOT (boardButtonHandler(int)));
	connect(this, SIGNAL (sendMoveRequest()), this, SLOT (recieveMoveRequest()), Qt::QueuedConnection);

	messageBox = new QMessageBox;
	messageBox->setWindowTitle("Game Over");

	QSize windowSize = QSize((settings.width+1)*settings.gapSize + settings.width*settings.squareSize,
			(settings.height+1)*settings.gapSize + settings.height*settings.squareSize);
	this->setFixedSize(windowSize);
	this->setWindowTitle("Connect 4");

	p1Palette = buttons.at(0)->palette();
	p2Palette = buttons.at(0)->palette();
	backPalette = buttons.at(0)->palette();
	p1Palette.setColor(QPalette::Button, QColor(Qt::blue));
	p2Palette.setColor(QPalette::Button, QColor(Qt::red));
	backPalette.setColor(QPalette::Button, QColor(Qt::white));

	updateUI();
	emit sendMoveRequest();
}

Connect4GameWindow::~Connect4GameWindow() {
	cout << "deleting" << endl;;
}

void Connect4GameWindow::boardButtonHandler(int id) {
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

void Connect4GameWindow::checkForWinner() {
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

void Connect4GameWindow::recieveMoveRequest() {
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

void Connect4GameWindow::receiveP1EngineMove(int id) {
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

void Connect4GameWindow::receiveP2EngineMove(int id) {
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

void Connect4GameWindow::updateUI() {
	for (int y = 0; y < settings.height; y++) {
		for (int x = 0; x < settings.width; x++) {
			int p = game->getSquare(x, y);
			int i = x + y*settings.width;
			if (p == Game::player1) {
				buttons.at(i)->setPalette(p1Palette);
			} else if (p == Game::player2) {
				buttons.at(i)->setPalette(p2Palette);
			} else {
				buttons.at(i)->setPalette(backPalette);
			}
			buttons.at(i)->update();
		}
	}
}




