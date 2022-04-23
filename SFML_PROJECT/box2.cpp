#include "game.h"

int main(void)
{
	srand(time(0));
	Game game;
	while (game.running()) 
	{

		//sf::RenderWindow window (sf::VideoMode(800, 600), "My Game");
		//update
		game.update();

		//render
		game.render();
		//window.clear();
		

	}
	
}