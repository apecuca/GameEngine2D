#include "Animator.hpp"

Animator::Animator(GameObject& parent) : Component(parent),
	state{ AnimatorState::PLAYING }
{
	//
}

void Animator::Update() 
{
	//
}

void Animator::SetAnimation(Animation& _animation)
{
	animation = std::make_unique<Animation>(std::move(_animation));
}