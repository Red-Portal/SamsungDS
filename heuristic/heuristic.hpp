#ifndef HEURISTIC_HPP
#define HEURISTIC_HPP

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



namespace Heuristic
{


	namespace
	{

		// this enum might eventually make it out of
		// this namespace
		enum IDENTIFIER
		{
			EMPTY = 0,
			ME = 1,
			OPONNENT = 2,
			BLOCK = 3
		};	


		// this function is a generic row computation function
		template<typename _Op>
		int computeRow(Point const& start,
					   Point const& end,
					   _Op const& operation)
		{
			int previous = 0; //
			int score = 0; // total score of the row
			int value = 0; // value of the position on the board
			int count = 0;

			for(Point point(start); point != end; operation(point))
			{

				/* int value = showBoard(point.x, point.y);

				if(value == 0 && previous == 0) // traversing blank space
					continue;

				else
				{
					
				}

				*/
			}
			return score;
		}
	}

	int compute();
}


#endif
