#include "bone.hpp"

#include "Engine.h"


Bone::Bone(int id)
{
	index = id;
	name = GetSkeletonBoneName(index);
	trs = BuildTransformFromBoneIndex(index);
}

void Bone::Draw() const
{
	vec3 position = trs.GetGlobalPosition();

	if (parent)
	{
		vec3 parentPos = parent->trs.GetGlobalPosition();
		DrawLine(position.x, position.y, position.z, parentPos.x, parentPos.y, parentPos.z, 1, 0, 0);
	}
}

void Bone::SetParent(Bone* futurParent)
{
	if (!futurParent)
		return;

	parent = futurParent;
	trs.SetParent(&futurParent->trs);
	futurParent->isParent = true;
}

int	 Bone::GetParentIndex() const
{
	if (parent)
		return parent->index;
	return -1;
}

Transform BuildTransformFromBoneIndex(int boneIndex)
{
	Transform trs = Transform();

	GetSkeletonBoneLocalBindTransform(boneIndex,
									trs.position.x, trs.position.y, trs.position.z,
									trs.rotation.w, trs.rotation.x, trs.rotation.y, trs.rotation.z);

	trs.rotation = quaternionNormalize(trs.rotation);

	return trs;
}

Transform BuildTransformFromAnimIndex(const char* animName, int boneIndex, int keyFrameIndex, const Transform& baseTrs)
{
	Transform newTrs;

	GetAnimLocalBoneTransform(animName, boneIndex, keyFrameIndex,
		newTrs.position.x, newTrs.position.y, newTrs.position.z,
		newTrs.rotation.w, newTrs.rotation.x, newTrs.rotation.y, newTrs.rotation.z);

	newTrs.position = baseTrs.position + newTrs.position;
	newTrs.rotation = quaternionMultiply(baseTrs.rotation, newTrs.rotation);

	return newTrs;
}

int GetBoneParentIndex(int thisID)
{
	return GetSkeletonBoneParentIndex(thisID);
}
