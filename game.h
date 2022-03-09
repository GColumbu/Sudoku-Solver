#pragma once
#include <windows.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
class game{
private:
	int wrongAnswers;
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;
	std::vector<std::vector<int>> numbers;
	std::vector<std::vector<int>> firstChoice;
	std::vector<std::vector<sf::RectangleShape>> rectPos;
	//Mouse position
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	bool mouseHeld;
	bool keyHeld;
	//Initialising functions
	void initVariables(int[9][9]);
	void initWindow();
public:
	//Constructor and Destructor
	game(int[9][9]);
	~game();
	void initBoard();
	const bool isRunning();
	//Update Mouse Position
	void updateMousePosition();
	//Update and Render Individual
	void updateFirstChoice();
	void updateNumbers(int[9][9]);
	void colorPositions();
	void renderMistakes();
	void renderFirstChoice();
	void renderBoard();
	void renderLines();
	void renderNumbers();
	void solution();
	//Update and Render
	void pollEvents();
	void update(int[9][9]);
	void render();
	// Solution Frame to frame animation
	bool breaksRow(std::vector<std::vector<int>>, int, int);
	bool breaksCol(std::vector<std::vector<int>>, int, int);
	bool breaksSub(std::vector<std::vector<int>>, int, int, int);
	void recursiveSolution(std::vector<std::vector<int>>, int, int);
	void updateSolution();
};

