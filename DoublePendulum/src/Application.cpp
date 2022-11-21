#include <iostream>
#include <algorithm>

#include <forward_list>

#include <SFML/graphics.hpp>

#include "Utility.h"

// Constants
constexpr int WIDTH = 1600;
constexpr int HEIGHT = 1080;

// Initial conditions
float l1 = 500;
float l2 = 520;
float m1 = 40.3f;
float m2 = 41.0f;
float theta1 = Utility::PI / 2.0f;
float theta2 = 2.14f;
float g = 1.2f;
float damp = 0.9998f;

// Angular velocity (rad/s)
float omega1 = 0.0f;
float omega2 = 0.0f;

// Angular acceleration (rad/s^2)
float alpha1 = 0.0f;
float alpha2 = 0.0f;

// Trace
constexpr int TRACE_SIZE = 6000;
std::pair<float, float> trace[TRACE_SIZE];
int trIdx = 0;

// Colors
sf::Color gray(45, 45, 45);
sf::Color white(225, 225, 225);

// Draw routines
void DrawPendulum(sf::RenderWindow& window, bool pause)
{
	// Calculate current position of pendulums based on angles and string lengths
	float x1 = l1 * sinf(theta1);
	float y1 = l1 * cosf(theta1);
	float x2 = x1 + l2 * sinf(theta2);
	float y2 = y1 + l2 * cosf(theta2);

	// Line positions that connect the circles
	sf::Vertex line1[2] =
	{
		sf::Vertex(sf::Vector2f(0.0f, 0.0f), white),
		sf::Vertex(sf::Vector2f(x1, y1), white)
	};
	sf::Vertex line2[2] =
	{
		sf::Vertex(sf::Vector2f(x1, y1), white),
		sf::Vertex(sf::Vector2f(x2, y2), white)
	};

	// Circles
	sf::CircleShape c1(m1);
	c1.setFillColor(white);
	c1.setOrigin(sf::Vector2f(m1, m1));
	c1.setPosition(x1, y1);

	sf::CircleShape c2(m2);
	c2.setFillColor(white);
	c2.setOrigin(sf::Vector2f(m2, m2));
	c2.setPosition(x2, y2);

	// Draw calls
	window.draw(line1, 2, sf::LineStrip);
	window.draw(line2, 2, sf::LineStrip);
	window.draw(c1);
	window.draw(c2);

	if (!pause)
	{
		// Update trace
		trace[trIdx] = std::make_pair(x2, y2);
		trIdx = (trIdx + 1) % TRACE_SIZE;

		// Update angular positions, velocities and accelerations
		float numer1 = -g * (2.0f * m1 + m2) * sinf(theta1)
			- m2 * g * sinf(theta1 - 2.0f * theta2)
			- 2.0f * sinf(theta1 - theta2)
			* m2 * (omega2 * omega2 * l2
				+ omega1 * omega1 * l1 * cosf(theta1 - theta2));
		float denom1 = l1 * (2.0f * m1 + m2 - m2 * cosf(2.0f * (theta1 - theta2)));
		float numer2 = 2.0f * sinf(theta1 - theta2)
			* (omega1 * omega1 * l1 * (m1 + m2)
				+ g * (m1 + m2) * cosf(theta1)
				+ omega2 * omega2 * l2 * m2 * cosf(theta1 - theta2));
		float denom2 = l2 * (2.0f * m1 + m2 - m2 * cosf(2.0f * (theta1 - theta2)));

		alpha1 = numer1 / denom1;
		alpha2 = numer2 / denom2;

		omega1 += alpha1;
		omega2 += alpha2;

		theta1 += omega1;
		theta2 += omega2;

		// Dampening
		omega1 *= damp;
		omega2 *= damp;
	}
}

void DrawTrace(sf::RenderWindow& window)
{
	sf::Vertex triangles[TRACE_SIZE][3];
	int i = 0;
	for (const auto& point : trace)
	{
		float x = point.first;
		float y = point.second;
		sf::Color color = Utility::XYtoRGB(sf::Vector2f(x, y), sf::Vector2f(0.0f, 0.0f), l1 + l2 + m1);

		triangles[i][0] = sf::Vertex(sf::Vector2f(x, y + 6.0f), color);
		triangles[i][1] = sf::Vertex(sf::Vector2f(x - 6.0f, y), color);
		triangles[i][2] = sf::Vertex(sf::Vector2f(x + 6.0f, y), color);

		i++;
	}

	for (int i = 0; i < TRACE_SIZE; i++)
	{
		window.draw(triangles[i], 3, sf::Triangles);
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Double Pendulum Simulation");

	// View
	sf::View view(sf::FloatRect(0.0f, 0.0f, WIDTH, HEIGHT));
	view.move(sf::Vector2f(-WIDTH / 2.0f, -HEIGHT / 4.0f));
	view.zoom(2.0f);
	window.setView(view);

	// Simulation loop
	window.setFramerateLimit(100);
	bool pause = true;
	while (window.isOpen())
	{
		// Handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// On close
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			// On pause & resume
			if (event.type == sf::Event::KeyPressed)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					pause = !pause;
				}
			}

			// Move masses
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					// Drag
				}
			}
			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					// Drop
				}
			}
		}

		// Draw calls
		window.clear(gray);

		DrawTrace(window);
		DrawPendulum(window, pause);

		window.display();
	}
}