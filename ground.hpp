#pragma once
#include <vector>

class Ground
{
public:
	void InitializeGround();
	void Draw();
	void Explode(int position);
	Ground(size_t s);

	std::vector<int> ground;
};
