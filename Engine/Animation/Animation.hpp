#pragma once

#include <vector>

struct AnimFrame
{
public:
	AnimFrame(const int _spriteId, const float _frameTime) :
		spriteId{ _spriteId }, frameTime{ _frameTime } {}

	const int spriteId;
	const float frameTime;
};

class Animation 
{
public:
	Animation() = default;
	~Animation() = default;

	// Move constructor
	Animation(Animation&& other) noexcept : steps(std::move(other.steps)) {}

public:
	void AddFrame(const int spriteId, const float frameTime);
	const AnimFrame& GetStep(size_t index) const;
	inline size_t StepCount() const { return steps.size(); }
	void Clear();

private:
	std::vector<AnimFrame> steps;
};