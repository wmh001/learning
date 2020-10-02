#pragma once
#include <vector>
#include <string>

class Mesh
{
public:
	Mesh();
	~Mesh();
	//  ��������
	bool Load(const std::string& fileName, class Renderer* renderer);
	//  ɾ������
	void Unload();
	//  ������ض�������
	class VertexArray* GetVertexArray() { return mVertexArray; }
	//  ��ָ��������ȡ����
	class Texture* GetTexture(size_t index);
	//  ������ɫ������
	const std::string& GetShaderName() const { return mShaderName; }
	//  ��ȡ����ռ�߽�����뾶
	float GetRadius() const { return mRadius; }
	//  ��ȡ����ľ��淴������
	float GetSpecPower() const { return mSpecPower; }
private:
	//  �������
	std::vector<class Texture*> mTextures;
	//  ��������
	class VertexArray* mVertexArray;
	//  ��ɫ������
	std::string mShaderName;
	//  ��ȡ����ռ�߽�����뾶
	float mRadius;
	//  ����ľ��淴������
	float mSpecPower;
};
