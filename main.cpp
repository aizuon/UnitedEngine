#include <SFML/Graphics.hpp>

#include "united_solver.h"
#include "DisplayManager.h"
#include <sstream>
#include "props.h"
#include <stdlib.h>
#include "utils.hpp"
#include "segment.hpp"

#include <iostream>

int main()
{
	const uint32_t win_width = 1600;
	const uint32_t win_height = 900;
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;

	sf::RenderWindow window(sf::VideoMode(win_width, win_height), "UE2", sf::Style::Default, settings);
	window.setVerticalSyncEnabled(true);
	//window.setFramerateLimit(60);

	float body_radius = 2;
	up::Vec2 world_dimension(2000.0f, 500.0f);
	up::UnitedSolver solver(world_dimension, body_radius, { 0.0f, 900.0f });

	DisplayManager displayManager(&window, &solver);
	displayManager.setZoom(1);

	sf::Font font;
	font.loadFromFile("font.ttf");

	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::White);

	up::BodyPtr b1 = solver.addBody(50, 50);
	up::BodyPtr b2 = solver.addBody(100, 50);
	up::BodyPtr b3 = solver.addBody(100, 100);
	up::BodyPtr b4 = solver.addBody(50, 100);

	std::vector<up::SolidSegment> segments;

	segments.emplace_back(b1, b2);
	segments.emplace_back(b3, b2);
	segments.emplace_back(b3, b4);
	segments.emplace_back(b1, b4);
	segments.emplace_back(b3, b1);
	segments.emplace_back(b4, b1);

	solver.addConstraint(b1, b2);
	solver.addConstraint(b2, b3);
	solver.addConstraint(b3, b4);
	solver.addConstraint(b4, b1);
	solver.addConstraint(b3, b1);
	solver.addConstraint(b4, b2);

	while (window.isOpen())
	{
		displayManager.processEvents();

		solver.update(0.016f);

		window.clear(sf::Color::White);
		displayManager.draw(false);
		window.display();
	}

	return 0;
}