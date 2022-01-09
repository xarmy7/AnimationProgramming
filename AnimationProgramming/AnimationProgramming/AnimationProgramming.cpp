// AnimationProgramming.cpp : Defines the entry point for the console application.
//

#include <cstdlib> 

#include "stdafx.h"
#include "Engine.h"
#include "Simulation.h"

#include "bone.hpp"
#include "Skeleton.hpp"
#include "SkeletonAnimation.hpp"
#include "AnimationBlend.hpp"
#include "Maths/maths.hpp"

//#define ANIMATION
#define WALK_ANIM "ThirdPersonWalk.anim"
#define RUN_ANIM "ThirdPersonRun.anim"
#define BLEND

class CSimulation : public ISimulation
{
	float time = 0.f;

	const char* animName = WALK_ANIM;

	float sign = 1.f;

	std::shared_ptr<Skeleton> skel;

	std::shared_ptr<SkeletonAnimation> walkAnim;
	std::shared_ptr<SkeletonAnimation> runAnim;

	std::shared_ptr<AnimationBlend> moveBlend;

	SkeletonAnimation* curAnim = nullptr;

	virtual void Init() override
	{
		int spine01 =	GetSkeletonBoneIndex("spine_01");
		int spineParent = GetSkeletonBoneParentIndex(spine01);
		const char* spineParentName = GetSkeletonBoneName(spineParent);

		float posX, posY, posZ, quatW, quatX, quatY, quatZ;
		size_t keyCount = GetAnimKeyCount(animName);
		GetAnimLocalBoneTransform(animName, spineParent, keyCount, posX, posY, posZ, quatW, quatX, quatY, quatZ);
		
		printf("Spine parent bone : %s\n", spineParentName);
		printf("Anim key count : %ld\n", keyCount);
		printf("Anim key : pos(%.2f,%.2f,%.2f) rotation quat(%.10f,%.10f,%.10f,%.10f)\n", posX, posY, posZ, quatW, quatX, quatY, quatZ);

		skel = std::make_shared<Skeleton>();
		walkAnim = std::make_shared<SkeletonAnimation>(skel.get(), WALK_ANIM);
		runAnim = std::make_shared<SkeletonAnimation>(skel.get(), RUN_ANIM);
		moveBlend = std::make_shared<AnimationBlend>(walkAnim.get(), runAnim.get());
		curAnim = walkAnim.get();
	}

	virtual void Update(float frameTime) override
	{
		time += frameTime;

#ifdef BLEND
		moveBlend->blendFactor += sign * frameTime/2.f;

		if (moveBlend->blendFactor >= 1.f)
			sign = -1.f;
		else if (moveBlend->blendFactor <= 0.f)
			sign = 1.f;

		moveBlend->Update(frameTime);

		moveBlend->Draw();
		SetSkinningPose(moveBlend->GetModelSkinningPose(), skel->bonesCount);
#else
		curAnim->Update(frameTime);

		curAnim->Draw(); //AnimePos
		/////// SHADER
		float* boneMatrices = (float*)curAnim->meshModels.data();
		SetSkinningPose(boneMatrices, skel->bonesCount);
#endif

		// TPOSE
		//skel->Draw();

		// X axis
		DrawLine(0, 0, 0, 100, 0, 0, 1, 0, 0);

		// Y axis
		DrawLine(0, 0, 0, 0, 100, 0, 0, 1, 0);

		// Z axis
		DrawLine(0, 0, 0, 0, 0, 100, 0, 0, 1);
	}
};

int main()
{
	CSimulation simulation;
	Run(&simulation, 1400, 800);

    return 0;
}

