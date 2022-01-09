#pragma once

#include <vector>

#include "Maths/maths.hpp"
#include "Maths/transform.hpp"

class SkeletonAnimation;
class Skeleton;

class AnimationBlend
{
private:
	Skeleton* skeleton = nullptr;
	SkeletonAnimation* anim1 = nullptr;
	SkeletonAnimation* anim2 = nullptr;

public:
	float normalizedTimeScale = 0.f;
	float blendFactor = 0.f;

	std::vector<Transform> lerpTransforms;
	std::vector<Maths::mat4> skelModels;
	std::vector<Maths::mat4> meshModels;

	AnimationBlend(SkeletonAnimation* a1, SkeletonAnimation* a2);

	float* GetModelSkinningPose() const;

	void Update(float frameTime);
	void UpdateAnimMatrices(int boneIndex);
	void Draw();
};
