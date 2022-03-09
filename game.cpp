#include "game.h"
//Initialising functions
void game::initVariables(int board[9][9]) {
	this->window = NULL;
	for (int i = 0; i<9; i++){
		std::vector<int> myvector;
		for (int j = 0; j<9; j++){
			myvector.push_back(board[i][j]);
		}
		numbers.push_back(myvector);
	}
	for (int i = 0; i<9; i++) {
		std::vector<int> myvector;
		for (int j = 0; j<9; j++) {
			myvector.push_back(0);
		}
		firstChoice.push_back(myvector);
	}
	for (int i = 0; i<9; i++) {
		std::vector<sf::RectangleShape> myvector;
		for (int j = 0; j< 9; j++) {
			sf::RectangleShape pos;
			myvector.push_back(pos);
		}
		this->rectPos.push_back(myvector);
	}
	this->mouseHeld = false;
	this->keyHeld = false;
	this->wrongAnswers = 0;
}

void game::initWindow() {
	this->videoMode.height = 600;
	this->videoMode.width = 540;
	this->window = new sf::RenderWindow(videoMode, "Sudoku Solver", sf::Style::Titlebar | sf::Style::Close);
}


//Constructor and Destructor
game::game(int board[9][9]){
	initVariables(board);
	initWindow();
}

game::~game(){
	delete[] window;
}

const bool game::isRunning(){
	return this->window->isOpen();
}

//Update Mouse Position
void game::updateMousePosition() {
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	//This takes the mouse pos and safely transforms it from Vector2i to Vector2f
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

//Update and Render Individual
void game::updateFirstChoice() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (rectPos[i][j].getOutlineColor() == sf::Color::Red) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
					firstChoice[i][j] = 1;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
					firstChoice[i][j] = 2;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
					firstChoice[i][j] = 3;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
					firstChoice[i][j] = 4;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) {
					firstChoice[i][j] = 5;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)) {
					firstChoice[i][j] = 6;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7)) {
					firstChoice[i][j] = 7;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)) {
					firstChoice[i][j] = 8;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)) {
					firstChoice[i][j] = 9;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
					firstChoice[i][j] = 0;
				}
			}
		}
	}
}

void game::updateNumbers(int solvedBoard[9][9]) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (rectPos[i][j].getOutlineColor() == sf::Color::Red&&firstChoice[i][j]!=0) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)&&firstChoice[i][j] == solvedBoard[i][j]) {
					numbers[i][j] = firstChoice[i][j];
					firstChoice[i][j] = 0;
					rectPos[i][j].setOutlineColor(sf::Color::Green);
					rectPos[i][j].setOutlineThickness(1.f);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && firstChoice[i][j] != solvedBoard[i][j]) {
					if (keyHeld == false) {
						keyHeld = true;
						firstChoice[i][j] = 0;
						wrongAnswers++;
					}
				}
				else
					keyHeld = false;
			}
		}
	}
}

void game::colorPositions() {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (this->mouseHeld == false) {
			this->mouseHeld = true;
			for (int x = 0; x < 9; x++) {
				for (int y = 0; y < 9; y++) {
					rectPos[x][y].setOutlineColor(sf::Color::Black);
					rectPos[x][y].setOutlineThickness(1.f);
				}
			}
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					sf::RectangleShape pos = rectPos[i][j];
					if (pos.getGlobalBounds().contains(this->mousePosView)&&numbers[i][j]!=0) {
						rectPos[i][j].setOutlineColor(sf::Color::Green);
						rectPos[i][j].setOutlineThickness(2.f);
					}
					else if (pos.getGlobalBounds().contains(this->mousePosView) && numbers[i][j] == 0) {
						rectPos[i][j].setOutlineColor(sf::Color::Red);
						rectPos[i][j].setOutlineThickness(2.f);
					}
				}
			}
		
		}
	}
	else
		this->mouseHeld = false;
}

void game::initBoard() {
	float width = 0.f;
	float height = 0.f;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			rectPos[i][j].setPosition(sf::Vector2f(width, height));
			rectPos[i][j].setSize(sf::Vector2f(60.f, 60.f));
			rectPos[i][j].setFillColor(sf::Color::Transparent);
			rectPos[i][j].setOutlineColor(sf::Color::Black);
			rectPos[i][j].setOutlineThickness(1.f);
			width += 60.f;
		}
		height += 60.f;
		width = 0.f;
	}
}

void game::renderFirstChoice() {
	sf::Font font;
	if (!font.loadFromFile("OpenSans-Regular.ttf")) {
		std::cout << ("Could not load font!!");
	}
	float width = 5.f;
	float height = 0.f;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (this->firstChoice[i][j] == 0) {
				width += 60.f;
				continue;
			}
			std::ostringstream oss;
			oss << this->firstChoice[i][j];
			sf::Text text;
			text.setFont(font);
			text.setStyle(sf::Text::Bold);
			text.setString(oss.str());
			text.setFillColor(sf::Color (169, 169, 169));
			text.setScale(0.75f, 0.75f);
			text.setPosition(width, height);
			this->window->draw(text);
			width += 60.f;
		}
		height += 60.f;
		width = 5.f;
	}
}

void game::renderMistakes() {
	float width = 0.f;
	sf::Texture txt;
	if (!txt.loadFromFile("wrong.png"))
	{
		std::cout << "Error displaying images";
	}
	sf::Sprite sprt;
	int cpy;
	cpy = wrongAnswers;
	while (cpy != 0) {
		sf::Texture txt;
		if (!txt.loadFromFile("wrong.png"))
		{
			std::cout << "Error displaying images";
		}
		sf::Sprite sprt;
		sprt.setTexture(txt);
		sprt.scale(sf::Vector2f(0.05f, 0.05f));
		sprt.setPosition(sf::Vector2f(width, 550.f));
		width += 60.f;
		cpy--;
		this->window->draw(sprt);
	}
}

void game::renderBoard() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			this->window->draw(this->rectPos[i][j]);
		}
	}
}

void game::renderLines() {
	float width = 0.f;
	float height = 0.f;
	sf::RectangleShape pos;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			sf::RectangleShape pos;
			pos.setPosition(sf::Vector2f(width, height));
			pos.setSize(sf::Vector2f(180.f, 180.f));
			pos.setFillColor(sf::Color::Transparent);
			pos.setOutlineColor(sf::Color::Black);
			pos.setOutlineThickness(2.f);
			this->window->draw(pos);
			width += 180.f;
		}
		height += 180.f;
		width = 0.f;
	}
}
 
void game::renderNumbers() {
	sf::Font font;
	if (!font.loadFromFile("OpenSans-Regular.ttf")) {
		std::cout << ("Could not load font!!");
	}
	float width = 20.f;
	float height = 10.f;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (this->numbers[i][j] == 0) {
				width += 60.f;
				continue;
			}
			std::ostringstream oss;
			oss << this->numbers[i][j];
			sf::Text text;
			text.setFont(font);
			text.setStyle(sf::Text::Bold);
			text.setString(oss.str());
			text.setFillColor(sf::Color::Black);
			text.setPosition(width, height);
			this->window->draw(text);
			width += 60.f;
		}
		height += 60.f;
		width = 20.f;
	}

}

//Update and Render
void game::pollEvents() {
	while (this->window->pollEvent(this->ev)) {
		switch (this->ev.type) {
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}
void game::update(int solvedBoard[9][9]) {
	pollEvents();
	updateMousePosition();
	colorPositions();
	updateFirstChoice();
	updateNumbers(solvedBoard);
	updateSolution();
}

void game::render() {
	this->window->clear(sf::Color::White);
	//Draw game 
	renderFirstChoice();
	renderNumbers();
	renderBoard();
	renderLines();
	renderMistakes();
	this->window->display();
}
bool game::breaksSub(std::vector<std::vector<int>> board, int row, int col, int val) {
	int aux[3][3] = {
		{ 0, 1, 2 },
		{ 3, 4, 5 },
		{ 6, 7, 8 }
	};
	int subRow, subCol;
	for (int i = 0; i<3; i++) {
		for (int j = 0; j<3; j++) {
			if (aux[i][j] == row) {
				subRow = i;
			}
			if (aux[i][j] == col) {
				subCol = i;
			}
		}
	}
	for (int i = aux[subRow][0]; i <= aux[subRow][2]; i++) {
		for (int j = aux[subCol][0]; j <= aux[subCol][2]; j++) {
			if (val == board[i][j]) {
				return true;
			}
		}
	}
	return false;
}
bool game::breaksCol(std::vector<std::vector<int>> board, int col, int val) {
	for (int i = 0; i<9; i++) {
		if (val == board[i][col]) {
			return true;
		}
	}
	return false;
}
bool game::breaksRow(std::vector<std::vector<int>> board, int row, int val) {
	for (int i = 0; i<9; i++) {
		if (val == board[row][i]) {
			return true;
		}
	}
	return false;
}
void game::recursiveSolution(std::vector<std::vector<int>> board, int x, int y) {
	sf::Font font;
	if (!font.loadFromFile("OpenSans-Regular.ttf")) {
		std::cout << ("Could not load font!!");
	}
	float width = 20.f;
	float height = 10.f;
	if (x == 8 && y == 9) {
		return;
	}
	if (y == 9) {
		x++;
		y = 0;
	}
	if (board[x][y] == 0) {
		for (int i = 1; i <= 9; i++) {
			std::ostringstream oss;
				oss << i;
				sf::Text text;
				text.setFont(font);
				text.setStyle(sf::Text::Bold);
				text.setString(oss.str());
				text.setFillColor(sf::Color::Black);
				text.setPosition(width, height);
				this->window->draw(text);
				width += 60.f;
				std::cout << i;
				Sleep(1000);
			if (!breaksRow(board, x, i) && !breaksCol(board, y, i) && !breaksSub(board, x, y, i)) {
				board[x][y] = i;
				y++;
				if (y == 9) {
					height += 60.f;
					width = 20.f;
				}
				render();
				recursiveSolution(board, x, y);
				y--;
				board[x][y] = 0;
			}
		}
		if (board[x][y] == 0) {
			return;
		}
	}
	y++;
	recursiveSolution(board, x, y);
	y--;
}

void game::updateSolution() {
	keyHeld = false;
	int x = 0, y = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		if (keyHeld == false) {
			keyHeld = true;
			std::cout << "Merge";
			recursiveSolution(numbers, x, y);
		}
	}
	else
		keyHeld = false;
}
