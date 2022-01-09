#pragma once

#include "Engine.h"
#include "bone.hpp"

#include <vector>


class Skeleton
{
public:
	Skeleton();

	void Draw();

	int ikBonesCount = 7;
	int bonesCount = 0;

	std::vector<std::shared_ptr<Bone>>bones = {};

	Bone* GetBoneAt(int index);
};