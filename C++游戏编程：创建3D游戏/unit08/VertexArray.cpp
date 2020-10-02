#include "VertexArray.h"
#include <glew.h>

VertexArray::VertexArray(const float* verts, unsigned int numVerts, const unsigned int* indices, unsigned int numIndices)
	: mNumVerts(numVerts)
	, mNumIndices(numIndices)
{
	//  创建顶点数组对象
	glGenVertexArrays(1, &mVertexArray);
	glBindVertexArray(mVertexArray);
    //  创建顶点缓冲区
	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	//  复制数据到顶点缓冲区
	glBufferData(
		GL_ARRAY_BUFFER  //  要创建的缓冲区
		, numVerts * 5 * sizeof(float)  //  复制的字节数
		, verts  //  复制源
		, GL_STATIC_DRAW);  //  只加载一次数据
	//  创建索引缓冲区
	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	//  复制数据到索引缓冲区
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER
		, numIndices * sizeof(unsigned int)
		, indices
		, GL_STATIC_DRAW);
	//  启用第一个顶点属性
	glEnableVertexAttribArray(0);
	//  指定属性的大小、类型、格式
	glVertexAttribPointer(0  //  指定要修改的顶点属性的索引值
		, 3  //  指定每个顶点属性的分量数量
		, GL_FLOAT  //  指定数组中每个组件的数据类型
		, GL_FALSE  //  当被访问时直接转换为固定点值
		, sizeof(float) * 5  //  指定连续顶点属性之间的偏移量
		, 0);  //  指定第一个组件在数组的第一个顶点属性中的偏移量
	//  启用第二个顶点属性，即纹理坐标
	glEnableVertexAttribArray(1);
	//  //  指定属性的大小、类型、格式
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5
		, reinterpret_cast<void*>(sizeof(float) * 3));  //  转换为偏移指针
}

VertexArray::~VertexArray()
{
	//  销毁顶点缓冲区
	glDeleteBuffers(1, &mVertexBuffer);
	//  销毁索引缓冲区
	glDeleteBuffers(1, &mIndexBuffer);
	//  销毁顶点数组对象
	glDeleteVertexArrays(1, &mVertexArray);
}

void VertexArray::SetActive()
{
	//  指定当前正在使用的顶点数组
	glBindVertexArray(mVertexArray);
}
