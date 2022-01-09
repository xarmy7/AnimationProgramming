#pragma once

#include "Maths/maths.hpp"
#include "Maths/transform.hpp"

#include <string>
#include <vector>

#define WALK_ANIM "ThirdPersonWalk.anim"
#define RUN_ANIM "ThirdPersonRun.anim"


class Skeleton;

struct AnimationFrame
{
	int keyFrameIndex = 0;
	std::vector<Transform> boneTransforms;
	AnimationFrame* parent = nullptr;

	AnimationFrame(Skeleton* sk, const std::string& animationName, int keyFrame);
};


class SkeletonAnimation
{
private:

	int curAnimFrameIndex = 0;
	int nxtAnimFrameIndex = 0;

public:
	float animationFrameTime = 0.05f;
	float curAnimFrameTime = 0;

	float duration = 0.f;
	float timeScale = 1.f;

	Skeleton* skeleton = nullptr;
	std::string animationName = "";
	std::vector<AnimationFrame> animationFrames;

	std::vector<Transform> lerpTransforms;
	std::vector<Maths::mat4> skelModels;
	std::vector<Maths::mat4> meshModels;

	SkeletonAnimation() = default;
	SkeletonAnimation(Skeleton* sk, std::string animName);

	inline const AnimationFrame& GetCurrentAnimationFrame() const { return animationFrames[curAnimFrameIndex]; }

	mat4 UpdateAnimMatrices(int boneIndex);

	void Update(float frameTime);
	void Draw();
};