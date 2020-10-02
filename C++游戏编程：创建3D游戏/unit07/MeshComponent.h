#pragma once
#include "Component.h"
#include <cstddef>

class MeshComponent :
    public Component
{
public:
	MeshComponent(class Actor* owner);
	~MeshComponent();
	//  ������������
	virtual void Draw(class Shader* shader);
	//  �޸�����
	virtual void SetMesh(class Mesh* mesh) { mMesh = mesh; }
	//  �޸�ͼ������
	void SetTextureIndex(size_t index) { mTextureIndex = index; }
protected:
	//  ����
	class Mesh* mMesh;
	//  ͼ������
	size_t mTextureIndex;
};

