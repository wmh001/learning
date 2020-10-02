#pragma once
#include <glew.h>
#include <string>
#include "Math.h"

class Shader
{
public:
	Shader();
	~Shader();
	//  ���ض�����ɫ����Ƭ����ɫ��
	bool Load(const std::string& vertName, const std::string& fragName);
	//  ɾ��
	void Unload();
	//  ����
	void SetActive();
	//  ��װ������
	//  �������ȫ�ֱ���
	void SetMatrixUniform(const char* name, const Matrix4& matrix);
	//
	void SetMatrixUniforms(const char* name, Matrix4* matrices, unsigned count);
	//  ��������ȫ�ֱ���
	void SetVectorUniform(const char* name, const Vector3& vector);
	//
	void SetVector2Uniform(const char* name, const Vector2& vector);
	//  ��������ȫ�ֱ���
	void SetFloatUniform(const char* name, float value);
	//
	void SetIntUniform(const char* name, int value);
private:
	//  ���Ա���ָ������ɫ��
	bool CompileShader(
		const std::string& fileName  //  ��ɫ���ļ�����
		, GLenum shaderType  //  ��ɫ������
		, GLuint& outShader);  //  ��ɫ��id
	//  �����Ƿ����ɹ�
	bool IsCompiled(GLuint shader);
	//  �����Ƿ�����
	bool IsValidProgram();
	//  ������ɫ��id
	GLuint mVertexShader;
	//  Ƭ����ɫ��id
	GLuint mFragShader;
	//  ��ɫ������id
	GLuint mShaderProgram;
};

