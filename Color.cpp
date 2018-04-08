#include "Color.h"
#include <assert.h>

/*
 * Set Color Black
 */
Color::Color()
{
    this->R = 0;
    this->G = 0;
    this->B = 0;
}

Color::Color( float r, float g, float b)
{
	this->R = r;
	this->G = g;
	this->B = b;
}

Color Color::operator*(const Color& c) const
{
	float new_r = this->R * c.R;
    float new_g = this->G * c.G;
    float new_b = this->B * c.B;
    return Color(new_r, new_g, new_b);
}

Color Color::operator*(const float Factor) const
{
    float new_r = this->R * Factor;
    float new_g = this->G * Factor;
    float new_b = this->B * Factor;
    return Color(new_r, new_g, new_b);
}

Color Color::operator+(const Color& c) const
{
    float new_r = this->R + c.R;
    float new_g = this->G + c.G;
    float new_b = this->B + c.B;
    return Color(new_r, new_g, new_b);
}

Color& Color::operator+=(const Color& c)
{
	this->R+= c.R;
    this->G+= c.G;
    this->B+= c.B;
	return *this; // dummy (remove)
}