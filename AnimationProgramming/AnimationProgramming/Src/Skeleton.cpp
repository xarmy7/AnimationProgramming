#include "Skeleton.hpp"

Skeleton::Skeleton()
{
	bonesCount = GetSkeletonBoneCount() - ikBonesCount;

	// Create bones
	for (int i = 0; i < bonesCount; i++)
	{
		bones.push_back(std::make_shared<Bone>(i));
		printf("\n%i Bone :%s", bones.back()->index, bones.back()->name.c_str());
	}

	// Set parent (and childs)
	for (auto bone : bones)
	{
		int parentID = GetBoneParentIndex(bone->index);
		if (parentID >= 0)
			bone->SetParent(bones[parentID].get());
	}
}

void Skeleton::Draw()
{
	for (auto bone : bones)
	{
		bone->Draw();

		//joint TPose
		if (bone->isParent)
		{
			DrawLine(bone->trs.GetGlobalPosition().x - 1.f + 150.f, bone->trs.GetGlobalPosition().y - 1.f, bone->trs.GetGlobalPosition().z, bone->trs.GetGlobalPosition().x + 1.f + 150.f, bone->trs.GetGlobalPosition().y + 1.f, bone->trs.GetGlobalPosition().z, 1, 0.498039216f, 0.f);
			DrawLine(bone->trs.GetGlobalPosition().x - 1.f + 150.f, bone->trs.GetGlobalPosition().y + 1.f, bone->trs.GetGlobalPosition().z, bone->trs.GetGlobalPosition().x + 1.f + 150.f, bone->trs.GetGlobalPosition().y - 1.f, bone->trs.GetGlobalPosition().z, 1, 0.498039216f, 0.f);
		}
	}
}

Bone* Skeleton::GetBoneAt(int index)
{
	return bones[index].get();
}