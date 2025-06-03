#pragma once

#include "../Behaviour/Component.hpp"
#include <memory>
#include <vector>

class RenderSource;
class Animation;

enum AnimatorState 
{
	PLAYING,
	PAUSED
};

class Animator : public Component
{
public:
	Animator(GameObject& parent);
	~Animator() = default;

public:
	void Update() override;

	size_t AddAnimation(Animation& animation);
	void SetAnimation(const size_t index);

public:
	AnimatorState state;

private:
	std::vector< std::unique_ptr<Animation> > animations;

	size_t currentStep = 0;
	float stepTimer = 0.0f;
	Animation* curAnimation = nullptr;

	RenderSource* rnd = nullptr;
};