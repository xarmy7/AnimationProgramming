#pragma once

#include <string>
#include <vector>

#include "Maths/transform.hpp"

struct Bone
{
	Transform trs = Transform();

	int index = 0;
	std::string name = "";

	Bone* parent = nullptr;
	bool isParent = false;

	Bone() = default;
	Bone(int index);

	int	 GetParentIndex() const;
	void SetParent(Bone* futurParent);
	void Draw() const;
};

Transform BuildTransformFromBoneIndex(int boneIndex);
Transform BuildTransformFromAnimIndex(const char* animName, int boneIndex, int keyFrameIndex, const Transform& baseTrs);
int GetBoneParentIndex(int thisID);
