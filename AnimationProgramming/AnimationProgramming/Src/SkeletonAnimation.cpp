
#include "Engine.h"

#include "Maths/transform.hpp"
#include "Skeleton.hpp"
#include "SkeletonAnimation.hpp"

using namespace Maths;

inline int GetNextIndex(int curr, int arraySize)
{
	if (curr >= arraySize - 1)
		return 0;
	else
		return ++curr;
}

////////// ANIMATION FRAME (struct)

AnimationFrame::AnimationFrame(Skeleton* sk, const std::string& animationName, int keyFrame)
	:keyFrameIndex(keyFrame)
{
	for (int i = 0; i < sk->bonesCount; i++)
	{
		Transform trs;
		vec3& p = trs.position;
		Quaternion& q = trs.rotation;

		GetAnimLocalBoneTransform(animationName.c_str(), i, keyFrameIndex, p.x, p.y, p.z, q.w, q.x, q.y, q.z);
		boneTransforms.push_back(trs);
	}
}

////////// SKELETON ANIMATION (class)

SkeletonAnimation::SkeletonAnimation(Skeleton* sk, std::string animName)
	:skeleton(sk), animationName(animName)
{
	int count = GetAnimKeyCount(animationName.c_str());
	nxtAnimFrameIndex = curAnimFrameIndex + 1;

	for (int i = 0; i < count; i++)
		animationFrames.push_back(AnimationFrame(skeleton, animationName, i));

	for (int i = 0; i < sk->bonesCount; i++)
	{
		lerpTransforms.push_back(Transform());
		skelModels.push_back(M4x4::identity());
		meshModels.push_back(M4x4::identity());
	}

	duration = animationFrames.size() * animationFrameTime;
}

void SkeletonAnimation::Update(float frameTime)
{
	curAnimFrameTime += frameTime * timeScale;

	if (curAnimFrameTime >= animationFrameTime)
	{
		// Loop animation
		curAnimFrameIndex = GetNextIndex(curAnimFrameIndex, (int)animationFrames.size());
		nxtAnimFrameIndex = GetNextIndex(nxtAnimFrameIndex, (int)animationFrames.size());

		curAnimFrameTime = 0.f;
	}
	
	for (int i = 0; i < (int)skeleton->bones.size(); i++)
		UpdateAnimMatrices(i);
}

mat4 SkeletonAnimation::UpdateAnimMatrices(int boneIndex)
{
	AnimationFrame& curFrame = animationFrames[curAnimFrameIndex];
	Transform& curTrs = curFrame.boneTransforms[boneIndex];

	AnimationFrame& nxtFrame = animationFrames[nxtAnimFrameIndex];
	Transform& nxtTrs = nxtFrame.boneTransforms[boneIndex];

	// LERP CURRENT FRAME'S TRS WITH NEXT FRAME'S TRS
	Transform& lerpTrs = lerpTransforms[boneIndex];
	float lerpFactor = curAnimFrameTime / animationFrameTime;
	lerpTrs.position = Maths::lerp(curTrs.position, nxtTrs.position, curAnimFrameTime / animationFrameTime);
	lerpTrs.rotation = Maths::slerp(curTrs.rotation, nxtTrs.rotation, curAnimFrameTime / animationFrameTime);

	// FIND ANIMATION'S PARENT BONE
	int parentIndex = skeleton->GetBoneAt(boneIndex)->GetParentIndex();
	
	// COMPUTE SKELETON ANIMATION MATRIX
	mat4& skelModel = skelModels[boneIndex];
	const mat4 skelLocalModel = skeleton->GetBoneAt(boneIndex)->trs.GetLocalModel();
	const mat4 animLocalModel = lerpTrs.GetLocalModel();

	skelModel = skelLocalModel * animLocalModel;
	skelModel = parentIndex > 0 ? skelModels[parentIndex] * skelModel : skelModel;

	// COMPUTE MESH ANIMATION MATRIX
	mat4& meshModel = meshModels[boneIndex];
	meshModel = skelModel * M4x4::inverse(skeleton->GetBoneAt(boneIndex)->trs.GetGlobalModel());

	return skelModel;
}

void SkeletonAnimation::Draw()
{
	for (int i = 0; i < (int)skeleton->bones.size(); i++)
	{
		// TODO: get the 'i' bone position and its parent position
		int parentIndex = skeleton->GetBoneAt(i)->GetParentIndex();
		if (parentIndex <= 0)
			continue;

		vec3 pos = M4x4::position(skelModels[i]);
		vec3 parentPos = M4x4::position(skelModels[parentIndex]);

		DrawLine(pos.x + 150.f, pos.y, pos.z, parentPos.x + 150.f, parentPos.y, parentPos.z, 1, 0, 0);

		//Joint anim
		for (auto bone : skeleton->bones)
		{
			if (bone->isParent)
			{
				DrawLine(parentPos.x - 1.f + 150.f, parentPos.y - 1.f, parentPos.z, parentPos.x + 1.f + 150.f, parentPos.y + 1.f, parentPos.z, 1, 0.498039216, 0);
				DrawLine(parentPos.x - 1.f + 150.f, parentPos.y + 1.f, parentPos.z, parentPos.x + 1.f + 150.f, parentPos.y - 1.f, parentPos.z, 1, 0.498039216, 0);
			}
		}
	}
}



