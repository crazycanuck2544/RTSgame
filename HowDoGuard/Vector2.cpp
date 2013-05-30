#include "Vector2.h"

Vector2 Vector2::ZERO          = Vector2(0);
Vector2 Vector2::ONE          = Vector2(1);
Vector2 Vector2::NEGATIVE_ONE = Vector2(-1);

Vector2::Vector2( void )
{
}

Vector2::Vector2( float x, float y )
{
    X = x;
    Y = y;
}

Vector2::Vector2( float both )
{
    X = both;
    Y = both;
}

Vector2::~Vector2( void )
{
}

std::string Vector2::toString( void ) const
{
    stringstream ss;
    ss << "Vector2 [X: " << X << ", Y: " << Y << "]";
    return ss.str();
}

const Vector2 Vector2::operator+( const Vector2 &rhs ) const
{
    Vector2 result = *this;
    result += rhs;
    return result;
}

const Vector2 Vector2::operator-( const Vector2 &rhs ) const
{
    Vector2 result = *this;
    result -= rhs;
    return result;
}

const Vector2 Vector2::operator*( float value ) const
{
    Vector2 result = *this;
    result *= value;
    return result;
}

const Vector2 Vector2::operator/( float value ) const
{
    Vector2 result = *this;
    result /= value;
    return result;
}

Vector2 & Vector2::operator+=( const Vector2 &rhs )
{
    X += rhs.X;
    Y += rhs.Y;
    return *this;
}

Vector2 & Vector2::operator-=( const Vector2 &rhs )
{
    X -= rhs.X;
    Y -= rhs.Y;
    return *this;
}

Vector2 & Vector2::operator*=( float value )
{
    X *= value;
    Y *= value;
    return *this;
}

Vector2 & Vector2::operator/=( float value )
{
    X /= value;
    Y /= value;
    return *this;
}

Vector2 & Vector2::operator=( const Vector2 &rhs )
{
    if (rhs == *this)
        return *this;

    X = rhs.X;
    Y = rhs.Y;
    return *this;
}

bool Vector2::operator==( const Vector2 &rhs ) const
{
    return (X == rhs.X && Y == rhs.Y);
}

bool Vector2::operator!=( const Vector2 &rhs ) const
{
    return !(*this == rhs);
}

float Vector2::distanceTo( Vector2 other )
{
    float dx = other.X - X,
          dy = other.Y - Y;

    return sqrt(dx * dx + dy * dy);
}

float Vector2::directionToDeg( Vector2 other )
{
    return toDeg(directionToRad(other));
}

float Vector2::directionToRad( Vector2 other )
{
    float dx = other.X - X,
          dy = other.Y - Y;

    return atan2(dy, dx);
}
