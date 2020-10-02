#pragma once
class VertexArray
{
public:
	//  顶点属性类型
	enum Layout
	{
		PosNormTex,  //  普通顶点
		PosNormSkinTex  //  带有骨骼蒙皮属性的顶点
	};
	VertexArray(const void* verts, unsigned int numVerts, Layout layout, const unsigned int* indices, unsigned int numIndices);
	~VertexArray();
	//  激活
	void SetActive();
	//  访问索引数量和顶点数量
	unsigned int GetNumIndices() const { return mNumIndices; }
	unsigned int GetNumVerts() const { return mNumVerts; }
private:
	//  顶点缓冲区中顶点数量
	unsigned int mNumVerts;
	//  索引缓冲区中索引数量
	unsigned int mNumIndices;
	//  顶点缓冲区的opengl id
	unsigned int mVertexBuffer;
	//  索引缓冲区的opengl id
	unsigned int mIndexBuffer;
	//  顶点数组对象的opengl id
	unsigned int mVertexArray;
};
