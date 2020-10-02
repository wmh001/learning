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
	//  ж����ɫ��
	void Unload();
	//  ����
	void SetActive();
	//  ���ݾ���ȫ�ֱ���
	void SetMatrixUniform(const char* name, const Matrix4& matrix);
private:
	//  ���Ա���ָ������ɫ��
	bool CompileShader(const std::string& fileName  //  ��ɫ���ļ�����
		, GLenum shaderType  //  ��ɫ������
		, GLuint& outShader);  //  ��ɫ��id
	//  �����Ƿ����ɹ�
	bool IsCompiled(GLuint shader);
	//  �����Ƿ�����
	bool IsValidProgram();
private:
	//  ������ɫ��id
	GLuint mVertexShader;
	//  Ƭ����ɫ��id
	GLuint mFragShader;
	//  ��ɫ������id
	GLuint mShaderProgram;
};

