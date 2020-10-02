#pragma once
class VertexArray
{
public:
	//  ������������
	enum Layout
	{
		PosNormTex,  //  ��ͨ����
		PosNormSkinTex  //  ���й�����Ƥ���ԵĶ���
	};
	VertexArray(const void* verts, unsigned int numVerts, Layout layout, const unsigned int* indices, unsigned int numIndices);
	~VertexArray();
	//  ����
	void SetActive();
	//  �������������Ͷ�������
	unsigned int GetNumIndices() const { return mNumIndices; }
	unsigned int GetNumVerts() const { return mNumVerts; }
private:
	//  ���㻺�����ж�������
	unsigned int mNumVerts;
	//  ��������������������
	unsigned int mNumIndices;
	//  ���㻺������opengl id
	unsigned int mVertexBuffer;
	//  ������������opengl id
	unsigned int mIndexBuffer;
	//  ������������opengl id
	unsigned int mVertexArray;
};
