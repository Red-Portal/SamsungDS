#ifndef HEURISTIC_HPP
#define HEURISTIC_HPP

#include <vector>
#include <cmath>


#include "point.hpp"
#include "dummy.hpp"

namespace Heuristic
{
	namespace Constants
	{
		const int FLOOR = -10000;
		const int CEILING = 10000;
		const int enemyWeight = -2;
	}

	// this enum might eventually make it out of
	// this namespace
	enum IDENTIFIER
	{
		EMPTY = 0,
		ME = 1,
		OPONENT = 2,
		BLOCK = 3
	};	

	enum State
	{
		SEQUENCE,
		INITIAL
	};

	inline int bothOpen(int count)
	{
		return static_cast<int>(pow(2, count));
	}

	inline int oneOpen(int count)
	{
		return static_cast<int>(pow(2, count - 1));
	}

	// this function is where the real heuristic value is computed
	// and don't try to read this...
	inline int computeScore(int count,
							IDENTIFIER first,
							IDENTIFIER id,
							IDENTIFIER last)
	{
		if(id == EMPTY || id == BLOCK) //short circuit
			return 0;

		int extreme;
		int weight;
		IDENTIFIER other; // the opponent of 'the current id'

		if(id == ME)
		{
			other = OPONENT;
			weight = 1;
			extreme = Constants::CEILING;
		} // setting parameters

		else if(id == OPONENT)
		{
			other = ME;
			weight = Constants::enemyWeight;
			extreme = Constants::FLOOR;
		} // setting parameters

		if(count == 6) // extreme case (FLOOR or CEILING)
			return extreme;

		if(count > 6)
			return 0;

		if(first == last && first == (other || BLOCK))
			return 0;

		else if(first == last && first == EMPTY)
			return weight * bothOpen(count);
		else
		{
			if(first == EMPTY || last == EMPTY)
				return weight * oneOpen(count);

			return 0;
		}
		return 0;
	}

// this function is a generic row computation function
	template<typename _Op>
	int computeRow(Point const& start,
				   Point const& end,
				   _Op const& operation)
	{
		std::vector<IDENTIFIER> log;
		log.reserve(19);
		log.push_back(BLOCK);
		log.push_back(BLOCK);

		int score = 0; // total score of the row
		int current = 0; // value of the position on the board
		int count = 0;

		for(Point point(start); point != end; operation(point))
		{
			int current = showBoard(point.x, point.y);

			if(current == log.back())
				++count;

			else
			{
				auto currentID = static_cast<IDENTIFIER>(current);
				score += computeScore(count,
									  log.end()[-2],
									  log.back(),
									  currentID);
				log.push_back(currentID);
				count = 1;
			}
		}

		// last computation (against the wall)
		score += computeScore(count,
							  log.end()[-2],
							  log.back(),
							  BLOCK);
		return score;
	}

	int compute();
}




#endif
