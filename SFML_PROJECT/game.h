#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include<vector>
#include<ctime>
#include<sstream>



class Game
{
private:
	
		sf::RenderWindow* window;
		sf::VideoMode videomode;
		sf::Event ev;

		sf::Vector2i mouseposWIndow;
		sf::Vector2f mousePosView;
		sf::Font font;
		sf::Text uitext;

		float enemySpawnTimer;
		float enemySpawnTimerMax;
		int points;
		int maxEnemies;
		bool mouseheld;
		int health;
		bool endgame;

		std::vector<sf::RectangleShape>enemies;
		sf::RectangleShape enemy;

		
		void initvariable();
		void initwindow();
		void initFonts();
		void initenemies();
		void initText();
	
public:
	
		Game();
		virtual ~Game();

		const bool running() const;
        
		void spawnEnemy();

		void pollEvents();
		void updateMousePositions();
		void updateEnemies();
		void updateText();
		void update();

		void renderText(sf::RenderTarget& target);
		void renderEnemies(sf::RenderTarget& target);
		void render();
		 
};

