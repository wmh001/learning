#pragma once
#include "Math.h"

//  最大骨骼数量
const size_t MAX_SKELETON_BONES = 96;

//  矩阵调色板
struct MatrixPalette
{
	Matrix4 mEntry[MAX_SKELETON_BONES];
};
