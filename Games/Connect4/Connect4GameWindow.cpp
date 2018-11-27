//*****************************************************************************
//Includes
#include "Connect4GameWindow.h"

Connect4GameWindow::Connect4GameWindow(Connect4Settings aSetting, Engine* engine1, Engine* engine2)
		: GameWindow(new Connect4Game(aSetting), engine1, engine2) {
	// initialize the signal mapper and game
	signalMapper = new QSignalMapper;
	game = new Connect4Game(aSetting);
	// set the internal settings to those passed in
	settings = aSetting;

	// create a QSize for all of the buttons
	QSize buttonSize = QSize(settings.get(squareSize), settings.get(squareSize));
	// loop through all the buttons that have to be created
	for (int y = 0; y < settings.get(itemHeight); y++) {
		for (int x = 0; x < settings.get(itemWidth); x++) {
			// create a new button with no text
			QPushButton* button = new QPushButton("", this);
			// create a QPoint for the location of the button
			QPoint loc = QPoint((x+1)*settings.get(gapSize) + x*settings.get(squareSize),
					(y+1)*settings.get(gapSize) + y*settings.get(squareSize));
			// set the button location and size
			button->setGeometry(QRect(loc, buttonSize));
			// set auto fill and flat to make the color appear properly
			button->setAutoFillBackground(true);
			button->setFlat(true);
			// set focus policy to no focus so the last pressed button does not turn red
			button->setFocusPolicy(Qt::NoFocus);
			// add the button to the vector of buttons
			buttons.push_back(button);

			// connect the button to the signal mapper and bind it to its id
			connect(button, SIGNAL (released()), signalMapper, SLOT(map()));
			signalMapper->setMapping(button, x + y*settings.get(itemWidth));
		}
	}
	// connect the signal mapper to the button handler
	connect(signalMapper, SIGNAL (mapped(int)), this, SLOT (boardButtonHandler(int)));
	// connect the move request and set it to be queued
	connect(this, SIGNAL (sendMoveRequest()), this, SLOT (recieveMoveRequest()), Qt::QueuedConnection);

	// set the window size and title
	QSize windowSize = QSize((settings.get(itemWidth)+1)*settings.get(gapSize) +
			settings.get(itemWidth) * settings.get(squareSize),
			(settings.get(itemHeight)+1) * settings.get(gapSize) +
			settings.get(itemHeight) * settings.get(squareSize));
	this->setFixedSize(windowSize);
	this->setWindowTitle("Connect 4");

	// create the palates to set the buttons to the correct colors
	p1Palette = buttons.at(0)->palette();
	p2Palette = buttons.at(0)->palette();
	backPalette = buttons.at(0)->palette();
	p1Palette.setColor(QPalette::Button, QColor(Qt::blue));
	p2Palette.setColor(QPalette::Button, QColor(Qt::red));
	backPalette.setColor(QPalette::Button, QColor(Qt::white));

	// update the ui and send a move request
	updateUI();
	emit sendMoveRequest();
}

void Connect4GameWindow::updateUI() {
	// loop through all squares
	for (int y = 0; y < settings.get(itemHeight); y++) {
		for (int x = 0; x < settings.get(itemWidth); x++) {
			// get the single int id
			int id = x + y*settings.get(itemWidth);
			// get the square value
			int p = game->getSquare(id);
			// check to see what player has the square, then set the palate
			if (p == Game::player1) {
				buttons.at(id)->setPalette(p1Palette);
			} else if (p == Game::player2) {
				buttons.at(id)->setPalette(p2Palette);
			} else {
				buttons.at(id)->setPalette(backPalette);
			}
			// update the button
			buttons.at(id)->update();
		}
	}
}




