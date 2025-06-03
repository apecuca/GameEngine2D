#pragma once

#include "Engine.hpp"

class Player : public Component
{
public:
	Player(GameObject& parent) : 
		Component(parent)
	{
		// Constructor example
	}
	~Player() = default;

	inline void Init()
	{
		RenderSource* rnd = gameObject.AddComponent<RenderSource>();
		rnd->InitShader("b_sprite.vert", "b_sprite.frag"); // Initializes the shader (vertex and fragment)
		int sprite_w1 = Rendering::PoolSprite("dino_w1.png", 25);
		int sprite_w2 = Rendering::PoolSprite("dino_w2.png", 25);
		int sprite_surp = Rendering::PoolSprite("dino_surp.png", 25);
		rnd->currentSpriteId = sprite_w1; // Update the current sprite to render

		anim = gameObject.AddComponent<Animator>();

		Animation walkAnim;
		walkAnim.AddFrame(sprite_w1, 0.25f);
		walkAnim.AddFrame(sprite_w2, 0.25f);

		Animation surpriseAnim;
		surpriseAnim.AddFrame(sprite_surp, 10.0f);

		walkAnimId = anim->AddAnimation(walkAnim);
		surpriseAnimId = anim->AddAnimation(surpriseAnim);

		anim->SetAnimation(walkAnimId);
		anim->state = AnimatorState::PLAYING;
	}

	inline void Update() override 
	{
		if (lastKnownInput != Input::horizontal && Input::horizontal != 0)
			lastKnownInput = Input::horizontal;

		if (resetTimer > 0) {
			resetTimer -= 1.0f * Time::deltaTime;
			if (resetTimer <= 0)
				anim->SetAnimation(walkAnimId);
			else
				return;
		}

		if (Input::GetKeyDown(GLFW_KEY_ENTER)) {
			resetTimer = 1.0f;
			anim->SetAnimation(surpriseAnimId);
		}

		gameObject.position.x += Input::horizontal * mvSpeed * Time::deltaTime;
		gameObject.position.y += Input::vertical * mvSpeed * Time::deltaTime;
		gameObject.scale.x = lastKnownInput;
	};

private:
	float mvSpeed = 5.0f;
	float lastKnownInput = 1.0f;
	float resetTimer = 0.0f;

	size_t walkAnimId, surpriseAnimId;

	Animator* anim;
};