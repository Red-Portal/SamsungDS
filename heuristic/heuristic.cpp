#include "heuristic.hpp"

int Heuristic::compute()
{
	int score = 0;

	/********* horizontal rows *********/
	for(int i = 0; i < 19; ++i)
	{
		score += computeRow(Point(i, 0),
							Point(i, 19),
							[](Point& point){ ++point.y;});
	}
	/**********************************/


	/******** vertical rows **********/
	for(int i = 0; i < 19; ++i)
	{
		score += computeRow(Point(0, i),
							Point(19, i),
							[](Point& point){ ++point.x;});
	}
	/*********************************/


	/*********  / rows   ***********/
	for(int i = 6; i < 19; ++i)
	{
		score += computeRow(Point(0, i),
							Point(i, 0),
							[](Point& point){ ++point.x; --point.y;});

	}
	for(int i = 6; i < 19; ++i)
	{
		score += computeRow(Point(19 - i, 19),
							Point(19, 19 - i),
							[](Point& point){ ++point.x; --point.y;});
	}
	/*******************************/


	/*********** \ rows ***********/
	for(int i = 6; i < 19; ++i)
	{
		score += computeRow(Point(0, 19 - i),
							Point(i, 19),
							[](Point& point){ ++point.x; ++point.y;});
	
	}
	for(int i = 6; i < 19; ++i)
	{
		score += computeRow(Point(19 - i, 0),
							Point(19, i),
							[](Point& point){ ++point.x; ++point.y;});
	
	}
	/*****************************/
	return score;	
}




