#include "Utility.h"

sf::Color Utility::HSVtoRGB(float hue, float saturation, float value)
{
	float chroma = value * saturation;
	float hPrime = hue / 60.0f;
	float x = chroma * (1.0f - fabs(fmodf(hPrime, 2) - 1));

	float r = 0.0f;
	float g = 0.0f;
	float b = 0.0f;

	float c = chroma;
	switch (static_cast<int>(hPrime))
	{
	case 0: r = c; g = x;        break;
	case 1: r = x; g = c;        break;
	case 2:        g = c; b = x; break;
	case 3:        g = x; b = c; break;
	case 4: r = x;        b = c; break;
	case 5: r = c;        b = x; break;
	}

	float m = value - chroma;
	r += m;
	g += m;
	b += m;

	sf::Color color;
	color.r = static_cast<sf::Uint8>(std::round(r * 255));
	color.g = static_cast<sf::Uint8>(std::round(g * 255));
	color.b = static_cast<sf::Uint8>(std::round(b * 255));

	return color;
}

Polar Utility::RectToPolar(float x, float y)
{
	float r = sqrtf(x * x + y * y);
	float phi = atan2f(y, x);
	return Polar(r, phi);
}

float Utility::RadToDeg(float rad)
{
	return ((rad + PI) / (2.0f * PI)) * 360.0f;
}

sf::Color Utility::XYtoRGB(const sf::Vector2f& pos, const sf::Vector2f& center, float radius)
{
	auto [r, phi] = RectToPolar(pos.x, pos.y);
	float deg = RadToDeg(phi);

	float hue = deg;
	float saturation = r / radius;
	float value = 1.0f;

	sf::Color rgb = HSVtoRGB(hue, saturation, value);
	return rgb;
}