#include "VertexArray.h"
#include <glew.h>

VertexArray::VertexArray(const void* verts, unsigned int numVerts, Layout layout, const unsigned int* indices, unsigned int numIndices)
	: mNumVerts(numVerts)
	, mNumIndices(numIndices)
{
	//  ���������������
	glGenVertexArrays(1, &mVertexArray);
	glBindVertexArray(mVertexArray);
	//  ��ͨ���㸴���ֽ���
	unsigned vertexSize = 8 * sizeof(float);
	//  ��Ƥ�������㸴���ֽ���
	if (layout == PosNormSkinTex)
	{
		vertexSize = 8 * sizeof(float) + 8 * sizeof(char);
	}
	//  �������㻺����
	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	//  �������ݵ����㻺����
	glBufferData(GL_ARRAY_BUFFER  //  Ҫ�����Ļ�����
		, numVerts * vertexSize  //  ���Ƶ��ֽ���
		, verts  //  ����Դ
		, GL_STATIC_DRAW);  //  ֻ����һ������
	//  ��������������
	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	//  �������ݵ�����������
	glBufferData(GL_ELEMENT_ARRAY_BUFFER
		, numIndices * sizeof(unsigned int)
		, indices
		, GL_STATIC_DRAW);
	//
	if (layout == PosNormTex)
	{
		//  ���õ�һ���������ԣ�λ��
		glEnableVertexAttribArray(0);
		//  ָ�����ԵĴ�С�����͡���ʽ
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize, 0);
		//  ���õڶ����������ԣ�����
		glEnableVertexAttribArray(1);
		//  ָ�����ԵĴ�С�����͡���ʽ
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexSize, reinterpret_cast<void*>(sizeof(float) * 3));  //  ת��Ϊƫ��ָ��
		//  ���õ������������ԣ�����
		glEnableVertexAttribArray(2);
		//  ָ�����ԵĴ�С�����͡���ʽ
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vertexSize, reinterpret_cast<void*>(sizeof(float) * 6));
	}
	else if (layout == PosNormSkinTex)
	{
		//  ���õ�һ���������ԣ�λ��
		glEnableVertexAttribArray(0);
		//  ָ�����ԵĴ�С�����͡���ʽ
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize, 0);
		//  ���õڶ����������ԣ�����
		glEnableVertexAttribArray(1);
		//  ָ�����ԵĴ�С�����͡���ʽ
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexSize, reinterpret_cast<void*>(sizeof(float) * 3));
		//  ���õ������������ԣ���Ƥ����
		glEnableVertexAttribArray(2);
		//  ָ�����ԵĴ�С�����͡���ʽ
		glVertexAttribIPointer(2, 4, GL_UNSIGNED_BYTE, vertexSize, reinterpret_cast<void*>(sizeof(float) * 6));  //  ֧���޷����ֽ�
		//  ���õ��ĸ��������ԣ���ƤȨ��
		glEnableVertexAttribArray(3);
		//  ָ�����ԵĴ�С�����͡���ʽ
		glVertexAttribPointer(3, 4, GL_UNSIGNED_BYTE, GL_TRUE, vertexSize, reinterpret_cast<void*>(sizeof(float) * 6 + sizeof(char) * 4));
		//  ���õ�����������ԣ�����
		glEnableVertexAttribArray(4);
		//  ָ�����ԵĴ�С�����͡���ʽ
		glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, vertexSize, reinterpret_cast<void*>(sizeof(float) * 6 + sizeof(char) * 8));
	}
	/*glVertexAttribPointer(0  //  ָ��Ҫ�޸ĵĶ������Ե�����ֵ
		, 3  //  ָ��ÿ���������Եķ�������
		, GL_FLOAT  //  ָ��������ÿ���������������
		, GL_FALSE  //  ��������ʱֱ��ת��Ϊ�̶���ֵ
		, sizeof(float) * 8  //  ָ��������������֮���ƫ����
		, 0);  //  ָ����һ�����������ĵ�һ�����������е�ƫ����
	*/
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
