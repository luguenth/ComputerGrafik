#include "vector.h"
#include <assert.h>
#include <math.h>

Vector::Vector( float x, float y, float z)
{
	this->X = x;
    this->Y = y;
    this->Z = z;
}

Vector::Vector()
{

}

float Vector::dot(const Vector& v) const
{
	float  dot = this->Z * v.Z + this->Y * v.Y + this->X * v.X;
	return dot;
}

Vector Vector::cross(const Vector& v) const
{
    float new_x = this->Y * v.Z - this->Z * v.Y;
    float new_y = this->Z * v.X - this->X * v.Z;
    float new_z = this->X * v.Y - this->Y * v.X;
	return Vector(new_x, new_y, new_z); // dummy (remove)
}



Vector Vector::operator+(const Vector& v) const
{
	float new_x = this->X + v.X;
    float new_y = this->Y + v.Y;
    float new_z = this->Z + v.Z;
	return Vector(new_x, new_y, new_z);
}

Vector Vector::operator-(const Vector& v) const
{
    float new_x = this->X - v.X;
    float new_y = this->Y - v.Y;
    float new_z = this->Z - v.Z;
    return Vector(new_x, new_y, new_z);
}

Vector Vector::operator*(float c) const
{
    float new_x = this->X * c;
    float new_y = this->Y * c;
    float new_z = this->Z * c;
    return Vector(new_x, new_y, new_z);
}


Vector Vector::operator-() const
{
	return *this*-1; // dummy (remove)
}

Vector& Vector::operator+=(const Vector& v)
{
	this->X += v.X;
    this->Y += v.Y;
    this->Z += v.Z;
	return *this;
}



Vector& Vector::normalize()
{
    float l = length();
	this->X = this->X / l;
    this->Y = this->Y / l;
    this->Z = this->Z / l;
	return *this;
}


/*
 * Uses lengthSquared and not otherwise because the length of a vector is the square root of it.
 */
float Vector::length() const
{
    return sqrt(this->lengthSquared());
}

float Vector::lengthSquared() const
{
	return (this->X * this->X + this->Y * this->Y + this->Z * this->Z);
}

/*
 *  x' = x - n * D * 2
 *
 *  x   => Vector to reflect
 *  x'  => reflected Vector
 *  n   => normal Vector to reflect at
 *  d   => x.dot(n)/n.length
 */
Vector Vector::reflection( const Vector& normal) const
{
	return *this - ((normal * (this->dot(normal)/normal.length())) * 2);
}


/*
 * triangle         = a<->b<->c
 * direction_vec    = d
 * location_of_coll = s
 */
bool Vector::triangleIntersection( const Vector& d, const Vector& a, const Vector& b, const Vector& c, float& s) const
{

    Vector av = b - a;
    Vector bv = c - b;

    if(av.cross(bv).dot(d))
    {
        Vector g = (*this)+(d*s);

    }
    else
    {
        return false;
    }
}

