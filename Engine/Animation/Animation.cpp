#include "Animation.hpp"

#include <stdexcept>

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

const AnimFrame& Animation::GetStep(const size_t index) const
{
	if (index >= steps.size() || index < 0)
		throw std::runtime_error("GetStep out of bounds");

	return steps.at(index);
}