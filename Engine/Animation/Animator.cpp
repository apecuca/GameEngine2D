#include "Animator.hpp"

#include "Animation.hpp"
#include "Managers/Time.hpp"
#include "Behaviour/GameObject.hpp"
#include "Rendering/Rendersource.hpp"

Animator::Animator(GameObject& parent) : Component(parent),
	state{ AnimatorState::PAUSED }
{
	rnd = parent.GetComponent<RenderSource>();
}

void Animator::Update() 
{
	if (animations.size() < 1) return;
	if (!curAnimation) return;
	if (curAnimation->StepCount() < 1) return;
	if (state != PLAYING) return;

	stepTimer += 1.0f * Time::deltaTime;
	const AnimFrame& currentFrame = curAnimation->GetStep(currentStep);
	if (stepTimer < currentFrame.frameTime)
		return;

	stepTimer -= currentFrame.frameTime;
	currentStep++;
	if (currentStep >= curAnimation->StepCount())
		currentStep = 0;

	// Update 
	if (rnd)
		rnd->currentSpriteId = curAnimation->GetStep(currentStep).spriteId;
}

size_t Animator::AddAnimation(Animation& animation)
{
	animations.reserve(1);
	animations.push_back(std::make_unique<Animation>(std::move(animation)));
	return animations.size() - 1;
}

void Animator::SetAnimation(const size_t index)
{
	if (index >= animations.size())
		throw std::runtime_error("SetAnimation out of bounds");

	currentStep = 0;
	stepTimer = 0.0f;
	curAnimation = animations.at(index).get();

	// Update 
	if (rnd)
		rnd->currentSpriteId = curAnimation->GetStep(currentStep).spriteId;
}