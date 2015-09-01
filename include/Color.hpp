#ifndef __MODULE__COLOR_HPP__
#define __MODULE__COLOR_HPP__

#include <stdint.h>

namespace Module {

// A simple color class that holds 3 bytes (r, g and b)
class Color {
private:
	uint8_t red, green, blue;
public:
	Color(uint8_t r, uint8_t g, uint8_t b) : red(r), green(g), blue(b) {}
	uint8_t getRed() const;
	uint8_t getGreen() const;
	uint8_t getBlue() const;
};

inline uint8_t Color::getRed() const
{
	return red;
}

inline uint8_t Color::getGreen() const
{
	return green;
}

inline uint8_t Color::getBlue() const
{
	return blue;
}

}

#endif