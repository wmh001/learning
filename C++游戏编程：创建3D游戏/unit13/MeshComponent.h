#pragma once
#include "Component.h"
#include <cstddef>

class MeshComponent :
    public Component
{
public:
	MeshComponent(class Actor* owner, bool isSkeletal = false);
	~MeshComponent();
	//  ��������
	virtual void Draw(class Shader* shader);
	//  �޸�����
	virtual void SetMesh(class Mesh* mesh) { mMesh = mesh; }
	//  �޸�ͼ������
	void SetTextureIndex(size_t index) { mTextureIndex = index; }
	//  �޸Ŀɼ���
	void SetVisible(bool visible) { mVisible = visible; }
	//  ���ʿɼ���
	bool GetVisible() const { return mVisible; }
	//  �����Ƿ�Ϊ�����������
	bool GetIsSkeletal() const { return mIsSkeletal; }
protected:
	//  ����
	class Mesh* mMesh;
	//  ͼ������
	size_t mTextureIndex;
	//  �Ƿ�ɼ�
	bool mVisible;
	//  �Ƿ�Ϊ�����������
	bool mIsSkeletal;
};

