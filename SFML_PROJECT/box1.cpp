#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include"game.h"


using namespace std;
using namespace sf;

void Game:: initvariable()
{
	this->window = nullptr;

	enemySpawnTimerMax=5.f;
    points=0;
    maxEnemies=5;
	enemySpawnTimer = enemySpawnTimerMax;
	mouseheld = false;
	health = 10; 
	endgame = false;


}


void Game:: initwindow()
{
this->videomode.height = 800;
this->videomode.width = 600;
this->window = new sf::RenderWindow(this->videomode, "Game 1", sf::Style::Close | sf::Style::Titlebar);

this->window->setFramerateLimit(50);
}



void Game::initenemies()
{
	this->enemy.setPosition(10, 10);
	this->enemy.setScale(.5f, .5f);
	
	//	this->enemy.setOutlineColor(sf::Color::Green);
	//	this->enemy.setOutlineThickness(1.0f);



}

void Game::initFonts()
{
	font.loadFromFile("Fonts/font.ttf");
}

Game::Game()
{
	initvariable();
	initwindow();
	initFonts();
	initText();
	initenemies();

}

Game::~Game()
{
	delete this->window;
}

void Game::initText()
{
	uitext.setFont(font);
	uitext.setCharacterSize(50);
	uitext.setFillColor(sf::Color::Blue);
	uitext.setString("NONE");
}  
 

const bool Game::running() const
{
	return this->window->isOpen();

}

void Game::spawnEnemy()
{
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(window->getSize().x - enemy.getSize().x)),
		0.f
		//static_cast<float>(rand() % static_cast<int>(window->getSize().y - enemy.getSize().y))

	);

	int type = rand() % 5;
	if (type == 0)
	{
		this->enemy.setSize(sf::Vector2f(50.f, 50.f));
		this->enemy.setFillColor(sf::Color::Cyan);
	}
	else if (type == 1)
	{
		this->enemy.setSize(sf::Vector2f(200.f,200.f));
		this->enemy.setFillColor(sf::Color::Magenta);
	}
	else if (type == 2)
	{
		this->enemy.setSize(sf::Vector2f(100.f, 100.f));
		this->enemy.setFillColor(sf::Color::Green);
	}
	else if (type == 3)
	{
		this->enemy.setSize(sf::Vector2f(40.f, 40.f));
		this->enemy.setFillColor(sf::Color::White);
	}
	else if (type == 4)
	{
		this->enemy.setSize(sf::Vector2f(60.f, 60.f));
		this->enemy.setFillColor(sf::Color::Blue);
	}
	enemies.push_back(enemy);
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		if (ev.type == sf::Event::Closed)
		{
			this->window->close();
		}
		else if (ev.type == sf::Event::KeyPressed)
		{
			if (ev.key.code == sf::Keyboard::Escape)
			{
				this->window->close();
			}
		}

	}
}

void Game::updateMousePositions()
{
	mouseposWIndow = sf::Mouse::getPosition(*this->window);
	mousePosView = window->mapPixelToCoords(this->mouseposWIndow);
}

void Game::updateEnemies()
{
	if (enemies.size() < maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			spawnEnemy();
			enemySpawnTimer = 0.f;
		}
		else
		{
			enemySpawnTimer += 1.f;
		}
	}
	for (int i = 0; i < enemies.size(); i++)
	{
		bool deleted = false;
		enemies[i].move(0.f, 5.f);
		if (enemies[i].getPosition().y > window->getSize().y)
		{
		    enemies.erase(enemies.begin() + i);
			health--;
			cout << "Health: " << health << endl;
			if (health <= 0)
			{
				endgame = true;
				window->close();
			}
        }
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (mouseheld == false)
		{
			mouseheld = true;
			bool deleted = false;
			for (int i = 0; i < enemies.size(); i++)
			{
				if (this->enemies[i].getGlobalBounds().contains(mousePosView))
				{
					deleted = true;
					if (enemies[i].getFillColor() == Color::White)
					{
						points += 20;
					}
					else if (enemies[i].getFillColor() == Color::Magenta)
					{
						points += 1;
					}
					else if (enemies[i].getFillColor() == Color::Green)
					{
						points += 5;
					}
					else if (enemies[i].getFillColor() == Color::Cyan)
					{
						points += 15;
					}
					else
					{
						points += 10;
					}
					enemies.erase(enemies.begin() + i);
					
					cout << "Points: " << points << endl;
					break;
				}
			}
		}

	}
	else
	{
		mouseheld = false;
	}
}

void Game::updateText()
{
	std::stringstream ss;
	ss << "Points: " << points<<endl<<"Health: "<<health;
	this->uitext.setString(ss.str());
	ss << "Points: " << points << endl << "Health: " << health;

}

void Game::renderText(sf::RenderTarget& target)
{
	target.draw(this->uitext);
}


void Game::renderEnemies(sf::RenderTarget& target)
{

///	printf("FFF\n");
	for (auto& e : enemies)
	{
		
		target.draw(e);
	}
}

void Game::update()
{
	this->pollEvents();

	if (!endgame)
	{
		updateMousePositions();
		updateText();
		updateEnemies();
	}
	
	//update mouse position
	//relative to the screen
	//cout << "Mouse Pos: " << sf::Mouse::getPosition(*window).x << " " << sf::Mouse::getPosition(*window).y<<endl;

} 


void Game::render()
{
	this->window->clear();
	
	renderEnemies(*window);
//	printf("AAA\n");

	renderText(*window);

	this->window->display();

}  
