#include<SFML/Graphics.hpp>
void window_open()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Window Opening", sf::Style::Titlebar | sf::Style::Close);
	sf::Event event;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (sf::Event::KeyPressed == sf::Keyboard::Escape)
					window.close();
			}
		}
	}
	window.clear(sf::Color::Red);
	window.display();
}