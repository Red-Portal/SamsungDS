#ifndef POINT_HPP
#define POINT_HPP

struct Point
{
	int x;
	int y;

	Point(int _x, int _y) : x(_x), y(_y) {}
	Point(Point const& other) : x(other.x), y(other.y) {}
	Point(Point&& other)
	{
		x = other.x;
		y = other.y;
		other.x = 0;
		other.y = 0;
	}

	bool operator==(Point const& other)
	{
		if(x == other.x && y == other.y)
			return true;
		else
			return false;
	}

	bool operator!=(Point const& other)
	{
		if(x == other.x && y == other.y)
			return false;
		else
			return true;
	}
};

#endif
