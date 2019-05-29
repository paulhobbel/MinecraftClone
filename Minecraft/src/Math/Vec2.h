#pragma once

#include <functional>

class Vec2
{
public:
	union
	{
		struct
		{
			int x, y;
		};
		int v[2];
	};

	Vec2();
	Vec2(int x, int y);
	Vec2(const Vec2& other);

	bool operator == (const Vec2& other);
};

bool operator == (const Vec2& left, const Vec2& right) noexcept;

namespace std
{
	template<>
	struct hash<Vec2>
	{
		size_t operator()(const Vec2& v) const noexcept
		{
			std::hash<decltype(v.x)> hasher;

			auto hash1 = hasher(v.x);
			auto hash2 = hasher(v.y);

			return std::hash<decltype(v.x)>{}((hash1 ^ hash2) >> 2);
		}
	};
}