#include "point.hpp"
#include "heuristic.hpp"

int Heuristic::compute()
{
	int score = 0;

	/********* horizontal rows *********/
	for(int i = 0; i < 19; ++i)
	{
		score += computeRow(Point(i, 0),
							Point(i, 18),
							[](Point& point){ ++point.y;});
	}
	/**********************************/

	if(score > Constants::CEILING || score < Constants::FLOOR)
		return score;


	/******** vertical rows **********/
	for(int i = 0; i < 19; ++i)
	{
		score += computeRow(Point(0, i),
							Point(18, i),
							[](Point& point){ ++point.x;});
	}
	/*********************************/


	/*********  / rows   ***********/
	for(int i = 5; i < 19; ++i)
	{
		score += computeRow(Point(0, i),
							Point(i, 0),
							[](Point& point){ ++point.x; --point.y;});

	}

	if(score > Constants::CEILING || score < Constants::FLOOR)
		return score;

	for(int i = 5; i < 19; ++i)
	{
		score += computeRow(Point(18 - i, 18),
							Point(18, 18 - i),
							[](Point& point){ ++point.x; --point.y;});
	}
	/*******************************/

	if(score > Constants::CEILING || score < Constants::FLOOR)
		return score;

	/*********** \ rows ***********/
	for(int i = 5; i < 19; ++i)
	{
		score += computeRow(Point(0, 18 - i),
							Point(i, 18),
							[](Point& point){ ++point.x; ++point.y;});
	
	}

	if(score > Constants::CEILING || score < Constants::FLOOR)
		return score;

	for(int i = 5; i < 19; ++i)
	{
		score += computeRow(Point(18 - i, 0),
							Point(18, i),
							[](Point& point){ ++point.x; ++point.y;});
	
	}
	/*****************************/
	return score;	
}
