#include "Animation.hpp"

void Animation::AddFrame(const int spriteId, const float frameTime)
{
	steps.reserve(1);
	steps.emplace_back(spriteId, frameTime);
}

void Animation::Clear()
{
	steps.clear();
	steps.shrink_to_fit();
}