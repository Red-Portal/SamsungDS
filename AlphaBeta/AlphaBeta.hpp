#ifndef ALPHA_BETA_HPP
#define ALPHA_BETA_HPP

#include <utility>
#include <mutex>
#include <future>
#include <memory>

#include "Point.hpp"

namespace AlphaBeta
{
	enum IDENTIFIER {NOTHING = 0, ME = 1, OPONENT = 2, BLOCK = 3};

	namespace Constants
	{
		const int CEILING = 10000;
		const int FLOOR = -10000;
		const int DEPTH = 5;
	}

	/* namespace LookupTable	
	{
		namespace
		{
			std::mutex mtx;
			int table;
		}
		bool isNext();
		Point getBest();
		Point getWorst();
		void revert();
		}; */

	class LookupTable
	{
		static std::unique_ptr<LookupTable> instance;
		std::mutex mtx;
	public:
		static LookupTable& getInstance();
	};

	struct Table
	{
		std::array<IDENTIFIER, 19 * 19> table;
		int movable;

		Table() = default;
		Table(bool);
		Table(Table const&);
		Table(Table&&);

		inline IDENTIFIER& getPos(int x, int y)
		{
			return table[x*19 + y];
		}
	};

	int alphaBeta(Table& table,
				  int depth,
				  int alpha,
				  int beta,
				  IDENTIFIER current);


	std::tuple<Point, Point, int> startAlphaBeta(Table table,
												 int start,
												 int end);
	inline Point decode(int idx)
	{
		return Point(idx / 19, idx % 19);
	}

	std::pair<Point, Point> threadHandler();
}

#endif
