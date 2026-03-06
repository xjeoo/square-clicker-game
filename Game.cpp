#include "Game.h"
#include <iostream>

Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initFonts();
	this->initText();
}

Game::~Game()
{
	delete this->window;
}

void Game::initVariables()
{
	this->gameOver = false;
	this->numberOfEnemies = 0;
	this->maxNumberOfEnemies = 10;
	this->maxEnemyTimer = 50.f;
	this->enemyTimer = this->maxEnemyTimer;
	this->points = 0;
	this->health = 100;
	this->enemies.clear();
	
}

void Game::initWindow()
{
	this->window = nullptr;
	this->window = new sf::RenderWindow(videomode, "Test", sf::Style::Titlebar | sf::Style::Close );
	this->window->setFramerateLimit(60);
}

void Game::initEnemy()
{
	//this->enemy.setSize(sf::Vector2f(50.f, 50.f));
	////this->enemy.setFillColor(sf::Color::Red);
	//this->enemy.setScale(sf::Vector2f(1.f, 1.f));
	int type = rand() % 4;
	switch (type)
	{
	case 0:
		this->enemy.setFillColor(sf::Color::Red);
		this->enemy.setSize(sf::Vector2f(20.f, 20.f));
		break;
	case 1:
		this->enemy.setFillColor(sf::Color(255, 125, 0, 255));
		this->enemy.setSize(sf::Vector2f(35.f, 35.f));
		break;
	case 2:
		this->enemy.setFillColor(sf::Color::Yellow);
		this->enemy.setSize(sf::Vector2f(50.f, 50.f));
		break;
	case 3:
		this->enemy.setFillColor(sf::Color::Green);
		this->enemy.setSize(sf::Vector2f(70.f, 70.f));
		break;

	default:
		break;
	}
	float randomX = static_cast<float>(rand() % (this->window->getSize().x - static_cast<int>(this->enemy.getSize().x)));
	this->enemy.setPosition(randomX, 0.f);
}

void Game::initFonts()
{
	this->font.loadFromFile("External/Fonts/Sixtyfour-Regular.ttf");
}

void Game::initText()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(24);
	this->uiText.setFillColor(sf::Color::Yellow);
	this->uiText.setString("None");

	this->deathText.setFont(this->font);
	this->deathText.setCharacterSize(24);
	this->deathText.setFillColor(sf::Color::Red);
	this->deathText.setPosition(sf::Vector2f((
		this->window->getSize().x / 2 - this->deathText.getLocalBounds().width)/2.f - this->deathText.getGlobalBounds().left
		, (this->window->getSize().y / 2 - this->deathText.getLocalBounds().height) / 2.f - this->deathText.getGlobalBounds().top));
	this->deathText.setString("You Died!\n Press R to play again.");

	
}
void Game::youDied()
{
	
	this->gameOver = true;
	this->enemies.clear();

	
}


void Game::spawnEnemy()
{
	
		this->initEnemy();
		this->enemies.push_back(this->enemy);
		this->numberOfEnemies += 1;
}

void Game::killEnemy()
{
	if (this->ev.type == sf::Event::MouseButtonPressed)
	{
		this->mouseHeld = false;
		this->mousePosWindow = sf::Mouse::getPosition(*this->window);
		this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
		if (!this->mouseHeld)
		{
			this->mouseHeld = true;
			for (int i = 0;i < this->enemies.size();i++)
			{
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
				{
					this->points += 1000* 1/this->enemies[i].getSize().x ;
					//std::cout << this->enemies[i].getSize().x<<" " << 1000 * 1 / this->enemies[i].getSize().x << "\n";
					this->enemies.erase(this->enemies.begin() + i);
					this->numberOfEnemies -= 1;
					
				}
			}
		}
	}
}

void Game::updateEnemy()
{
	while(this->numberOfEnemies < this->maxNumberOfEnemies)
	{
		if (this->enemyTimer < this->maxEnemyTimer)
		{
			this->enemyTimer += 1.5f;
			break;
		}
		else {
			this->spawnEnemy();
			this->enemyTimer = 0.f;
		}
		
	}

	for (int i = 0; i < this->enemies.size();i++)
	{
		this->enemies[i].move(sf::Vector2f(0.f, 4.f));
		if (this->enemies[i].getPosition().y > this->window->getSize().y )
		{
			this->health -= this->enemies[i].getSize().x - 10;
			this->enemies.erase(this->enemies.begin() + i);
			this->numberOfEnemies -= 1;
			
			
			if (this->health <= 0)
			{
				this->youDied();
			}

		}
	}
	
	
}

void Game::updateText()
{
	std::stringstream ss;
	
	if (this->health > 0)
	{
		ss << "Health: " << this->health << "\nPoints: " << this->points << '\n';
	}
	else
		ss << "Health: " << 0 << "\nPoints: " << this->points << '\n';
	this->uiText.setString(ss.str());
}	

void Game::drawEnemy(sf::RenderTarget& target)
{
	for (auto enm : this->enemies)
	{
		target.draw(enm);
	}
	
}

void Game::drawText(sf::RenderTarget& target)
{
	target.draw(this->uiText);
	if(this->health<=0)
		target.draw(this->deathText);

	
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
	
			if (this->ev.type == sf::Event::Closed)
			{
				this->window->close();
			}
			else if (this->ev.type == sf::Event::MouseButtonPressed)
				this->killEnemy();
			
			else if (this->ev.type == sf::Event::KeyPressed)
			{
				switch (this->ev.key.code)
				{
				case sf::Keyboard::Escape:
					this->window->close();
					break;
				case sf::Keyboard::R: 
					if (this->gameOver)
						this->initVariables();
					break;
				default:
					break;
				}
			}
			
	}
}

void Game::update()
{
	this->pollEvents();
	if (!this->gameOver)
	{
		this->updateEnemy();
		this->updateText();
	}
}

void Game::render()
{
	this->window->clear();
	this->drawEnemy(*this->window);
	this->drawText(*this->window);
	this->window->display();
}

const bool Game::running() const
{
	return this->window->isOpen();
}
