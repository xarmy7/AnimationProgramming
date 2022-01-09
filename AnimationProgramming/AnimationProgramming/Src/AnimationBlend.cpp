#include "AnimationBlend.hpp"

#include "SkeletonAnimation.hpp"
#include "Skeleton.hpp"

AnimationBlend::AnimationBlend(SkeletonAnimation* a1, SkeletonAnimation* a2)
	:anim1(a1), anim2(a2) 
{
	skeleton = anim1->skeleton;
	// Copy a random animation vector, value will change later
	lerpTransforms = anim1->lerpTransforms;
	skelModels = anim1->skelModels;
	meshModels = anim1->meshModels;

	normalizedTimeScale = anim2->duration / anim1->duration;
}

void AnimationBlend::Update(float frameTime)
{
	blendFactor = Maths::clamp(blendFactor, 0.f, 1.f);

	anim2->timeScale = lerp(normalizedTimeScale, 1.f, blendFactor);

	if (blendFactor < 1.f)
		anim1->Update(frameTime);
	if (blendFactor > 0.f)
		anim2->Update(frameTime);

	if (blendFactor == 0.f || blendFactor == 1.f)
		return;

	for (int boneIndex = 0; boneIndex < (int)lerpTransforms.size(); boneIndex++)
		UpdateAnimMatrices(boneIndex);
}

void AnimationBlend::UpdateAnimMatrices(int boneIndex)
{
	Transform& trs1 = anim1->lerpTransforms[boneIndex];
	Transform& trs2 = anim2->lerpTransforms[boneIndex];

	// LERP CURRENT FRAME'S TRS WITH NEXT FRAME'S TRS
	Transform& lerpTrs = lerpTransforms[boneIndex];
	lerpTrs.position = Maths::lerp(trs1.position, trs2.position, blendFactor);
	lerpTrs.rotation = Maths::slerp(trs1.rotation, trs2.rotation, blendFactor);

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

}

void AnimationBlend::Draw()
{
	if (blendFactor == 0.f)
		anim1->Draw();
	else if (blendFactor == 1.f)
		anim2->Draw();
	else
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
}

float* AnimationBlend::GetModelSkinningPose() const
{
	if (blendFactor == 0.f)
		return (float*)anim1->meshModels.data();
	else if (blendFactor == 1.f)
		return (float*)anim2->meshModels.data();
	else
	{
		return (float*)meshModels.data();
	}
}
