#pragma once
#include <vector>

class Ground
{
public:
	void InitializeGround();
	void Draw();
	Ground(size_t s);

	std::vector<int> ground;
};
