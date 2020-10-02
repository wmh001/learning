#pragma once
#include <vector>
#include <string>
#include "Collision.h"

class Mesh
{
public:
	Mesh();
	~Mesh();
	//  加载网格
	bool Load(const std::string& fileName, class Renderer* renderer);
	//  删除网格
	void Unload();
	//  访问相关顶点数组
	class VertexArray* GetVertexArray() { return mVertexArray; }
	//  从指定索引获取纹理
	class Texture* GetTexture(size_t index);
	//  访问着色器名字
	const std::string& GetShaderName() const { return mShaderName; }
	//  获取对象空间边界球体半径
	float GetRadius() const { return mRadius; }
	//  访问轴对齐包围框
	const AABB& GetBox() const { return mBox; }
	//  获取网格的镜面反射能力
	float GetSpecPower() const { return mSpecPower; }
private:
	//  轴对齐包围框
	AABB mBox;
	//  相关纹理
	std::vector<class Texture*> mTextures;
	//  顶点数组
	class VertexArray* mVertexArray;
	//  着色器名字
	std::string mShaderName;
	//  获取对象空间边界球体半径
	float mRadius;
	//  网格的镜面反射能力
	float mSpecPower;
};