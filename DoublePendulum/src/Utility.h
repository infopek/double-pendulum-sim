#pragma once

#include "SFML/Graphics.hpp"

struct Polar
{
	float r;
	float phi;
};

class Utility
{
public:
	// Converts HSV to RGB color
	static sf::Color HSVtoRGB(float hue, float saturation, float value);

	// Converts rectangular coordinates to polar coordinates
	static Polar RectToPolar(float x, float y);
	
	// Converts radians to degrees
	static float RadToDeg(float rad);

	// Converts a position in a circle to its corresponding color in the color wheel
	static sf::Color XYtoRGB(const sf::Vector2f& pos, const sf::Vector2f& center, float radius);

public:
	static constexpr float PI = 3.14159f;
};

