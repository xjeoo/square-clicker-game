#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <vector>
#include <cstdlib>
#include <sstream>

class Game
{
private:
	// Private Variables
	sf::VideoMode videomode = sf::VideoMode(800, 600);
	sf::RenderWindow* window;
	sf::Event ev;

	//Mouse Position
	bool mouseHeld;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Resources
	sf::Font font;


	//Text

	sf::Text uiText;
	sf::Text deathText;

	//Game Logic
	std::vector <sf::RectangleShape> enemies;
	sf::RectangleShape enemy;
	int numberOfEnemies;
	int maxNumberOfEnemies;
	float enemyTimer;
	float maxEnemyTimer;
	int points;
	int health;
	bool gameOver;


	void initVariables();
	void initWindow();
	void initEnemy();
	void initFonts();
	void initText();
	void youDied();

public:

	Game();
	~Game();

	//Public Functions


	
	void spawnEnemy();
	void killEnemy();
	void updateEnemy();
	void updateText();
	void drawEnemy(sf::RenderTarget& target);
	void drawText(sf::RenderTarget& target);
	void pollEvents();
	void update();
	void render();

	//Accessors
	const bool running()const;

};

