#include "Vec2.h"

Vec2::Vec2() : x(0), y(0)
{
}

Vec2::Vec2(int x, int y) : x(x), y(y)
{
}

Vec2::Vec2(const Vec2& other) : x(other.x), y(other.y)
{
}

bool Vec2::operator==(const Vec2& other)
{
	return x == other.x && y == other.y;
}

bool operator==(const Vec2& left, const Vec2& right) noexcept
{
	return  (left.x == right.x) &&
		(left.y == right.y);
}

