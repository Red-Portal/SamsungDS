
#include "dummy.hpp"
#include "heuristic.hpp"
#include <iostream>
#include <chrono>
#include <vector>

int vec[19][19] = {0};

int showBoard(int x, int y)
{
	return vec[x][y];
}

int main()
{

	vec[0][0] = 1;
	vec[0][1] = 1;
	vec[0][2] = 1;
	vec[0][3] = 1;
	vec[0][4] = 1;
	vec[0][5] = 1;

	for(int i = 0; i < 19; ++i)
		for(int j = 0; j < 19; ++j)
			std::cout << vec[i][j] << std::endl;

	int score;
	auto start = std::chrono::steady_clock::now();

	score = Heuristic::compute();

	auto end = std::chrono::steady_clock::now();
	auto time = std::chrono::duration<double, std::milli>(end - start);
	std::cout << "benchmark: " << time.count() << "ms" << std::endl;
	std::cout << "score: " << score << std::endl;
	return 0;
}
