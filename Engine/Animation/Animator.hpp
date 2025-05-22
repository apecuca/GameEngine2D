#pragma once

#include "../Behaviour/Component.hpp"
#include "Animation.hpp"
#include <memory>

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

	void Update() override;

	void SetAnimation(Animation& _animation);

public:
	std::unique_ptr<Animation> animation;
	AnimatorState state;
};