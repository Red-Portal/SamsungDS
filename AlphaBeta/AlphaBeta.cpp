#include <algorithm>
#include <vector>
#include <tuple>

#include "AlphaBeta.hpp"
#include "Point.hpp"

AlphaBeta::Table::Table(bool flag)
{
	int current;
	
	for(int i = 0; i < 19; ++i)
	{
		for(int j = 0; j < 19; ++j)
		{
			current = showBoard(i, j);

			if(current == 0)
				++movable;

			getPos(i, j) = static_cast<IDENTIFIER>(current);
		}
	}
}

AlphaBeta::Table::Table(Table const& other)
{
	table = other.table;
}

AlphaBeta::Table::Table(Table&& other)
{
	table = std::move(other.table);
}

std::pair<Point, Point> AlphaBeta::threadHandler()
{
	auto table = Table(true);

	if(table.movable < 7)
	{
		auto result = startAlphaBeta(table, 0, 19*19);
		return std::pair<Point, Point>(std::get<0>(result),
									   std::get<1>(result));
	}

	std::vector<std::future<std::tuple<Point, Point, int>>> results;

	results.push_back(std::async(startAlphaBeta, table, 0, 19));
	results.push_back(std::async(startAlphaBeta, table, 0, 19));
	results.push_back(std::async(startAlphaBeta, table, 0, 19));
	results.push_back(std::async(startAlphaBeta, table, 0, 19));
	results.push_back(std::async(startAlphaBeta, table, 0, 19 * 19));

	std::tuple<Point, Point, int> max(Point(0,0),
									  Point(0,0),
									  Constants::FLOOR);
	for(auto& it : results)
	{	
		auto current = it.get();

		if(std::get<2>(current) > std::get<2>(max))
		{
			std::get<0>(max) = std::move(std::get<0>(current));
			std::get<1>(max) = std::move(std::get<1>(current));
			std::get<2>(max) = std::get<2>(current);
		}
	}

	return std::pair<Point, Point>(std::move(std::get<0>(max)),
								   std::move(std::get<1>(max)));
}


std::tuple<Point, Point, int>
AlphaBeta::startAlphaBeta(AlphaBeta::Table table,
						  int start,
						  int end)
{
	
	std::tuple<Point, Point, int>  max
		(Point(0,0), Point(0,0), Constants::FLOOR);

	int score = 0;
	for(int i = start; i < end; ++i)
	{
		if(table.table[i] != 0)
			continue;

		table.table[i] = static_cast<IDENTIFIER>(1);

		for(int j = start; j < end; ++j)
		{
			if(table.table[i] != 0)
				continue;

			table.table[j] = static_cast<IDENTIFIER>(1);

			score = alphaBeta(table,
							  Constants::DEPTH,
							  Constants::FLOOR,
							  Constants::CEILING,
							  OPONENT);

			table.table[j] = static_cast<IDENTIFIER>(0);
				
			if(std::get<2>(max) < score)
			{
				std::get<0>(max) = std::move(decode(i));
				std::get<1>(max) = std::move(decode(j));
				std::get<2>(max) = score;
			}
		}
		table.table[i] = static_cast<IDENTIFIER>(0);
	}
	return max;
}


int AlphaBeta::alphaBeta(Table& table,
						 int depth,
						 int alpha,
						 int beta,
						 IDENTIFIER current)
{
	
	if(depth == 0)
		return heuristic(table); // must add additional stop conditions
	// such as "no more move available"

	int v;

	if(current == ME)
	{
		v = Constants::FLOOR;

		for(int i = 0; i < 19 * 19; ++i)
		{
			if(table.table[i] != 0)
				continue;

			table.table[i] = ME;

			for(int j = 0; j < 19 * 19; ++j)
			{
				if(table.table[j] != 0)
					continue;

				table.table[j] = ME;

				v = std::max(v, alphaBeta(
								 table,
								 depth - 1,
								 alpha,
								 beta,
								 OPONENT));
				// revert
				table.table[i] = NOTHING;

				alpha = std::max(alpha, v);

				if(beta <= alpha)
					break;
			}

			table.table[i] = NOTHING;
		}
		return v;
	}
	else
	{
		for(int i = 0; i < 19 * 19; ++i)
		{
			if(table.table[i] != 0)
				continue;

			table.table[i] = OPONENT;

			for(int j = 0; j < 19 * 19; ++j)
			{
				if(table.table[j] != 0)
					continue;

				table.table[j] = OPONENT;

				v = std::max(v, alphaBeta(
								 table,
								 depth - 1,
								 alpha,
								 beta,
								 ME));
				// revert
				table.table[i] = NOTHING;

				alpha = std::max(alpha, v);

				if(beta <= alpha)
					break;
			}

			table.table[i] = NOTHING;
		}
		return v;
	}

	return 0;
}
