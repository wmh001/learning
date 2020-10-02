#pragma once
class VertexArray
{
public:
	VertexArray(const float* verts, unsigned int numVerts, const unsigned int* indices, unsigned int numIndices);
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

