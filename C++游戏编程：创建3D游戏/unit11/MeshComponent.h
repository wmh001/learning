#pragma once
#include "Component.h"
#include <cstddef>

class MeshComponent :
    public Component
{
public:
	MeshComponent(class Actor* owner);
	~MeshComponent();
	//  绘制网格属性
	virtual void Draw(class Shader* shader);
	//  修改网格
	virtual void SetMesh(class Mesh* mesh) { mMesh = mesh; }
	//  修改图像索引
	void SetTextureIndex(size_t index) { mTextureIndex = index; }
	//  修改可见性
	void SetVisible(bool visible) { mVisible = visible; }
	//  访问可见性
	bool GetVisible() const { return mVisible; }
protected:
	//  网格
	class Mesh* mMesh;
	//  图像索引
	size_t mTextureIndex;
	//  是否课件
	bool mVisible;
};

