#include "VertexArray.h"
#include <glew.h>

VertexArray::VertexArray(const float* verts, unsigned int numVerts, const unsigned int* indices, unsigned int numIndices)
	: mNumVerts(numVerts)
	, mNumIndices(numIndices)
{
	//  ���������������
	glGenVertexArrays(1, &mVertexArray);
	glBindVertexArray(mVertexArray);
    //  �������㻺����
	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	//  �������ݵ����㻺����
	glBufferData(
		GL_ARRAY_BUFFER  //  Ҫ�����Ļ�����
		, numVerts * 5 * sizeof(float)  //  ���Ƶ��ֽ���
		, verts  //  ����Դ
		, GL_STATIC_DRAW);  //  ֻ����һ������
	//  ��������������
	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	//  �������ݵ�����������
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER
		, numIndices * sizeof(unsigned int)
		, indices
		, GL_STATIC_DRAW);
	//  ���õ�һ����������
	glEnableVertexAttribArray(0);
	//  ָ�����ԵĴ�С�����͡���ʽ
	glVertexAttribPointer(0  //  ָ��Ҫ�޸ĵĶ������Ե�����ֵ
		, 3  //  ָ��ÿ���������Եķ�������
		, GL_FLOAT  //  ָ��������ÿ���������������
		, GL_FALSE  //  ��������ʱֱ��ת��Ϊ�̶���ֵ
		, sizeof(float) * 5  //  ָ��������������֮���ƫ����
		, 0);  //  ָ����һ�����������ĵ�һ�����������е�ƫ����
	//  ���õڶ����������ԣ�����������
	glEnableVertexAttribArray(1);
	//  //  ָ�����ԵĴ�С�����͡���ʽ
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5
		, reinterpret_cast<void*>(sizeof(float) * 3));  //  ת��Ϊƫ��ָ��
}

VertexArray::~VertexArray()
{
	//  ���ٶ��㻺����
	glDeleteBuffers(1, &mVertexBuffer);
	//  ��������������
	glDeleteBuffers(1, &mIndexBuffer);
	//  ���ٶ����������
	glDeleteVertexArrays(1, &mVertexArray);
}

void VertexArray::SetActive()
{
	//  ָ����ǰ����ʹ�õĶ�������
	glBindVertexArray(mVertexArray);
}
