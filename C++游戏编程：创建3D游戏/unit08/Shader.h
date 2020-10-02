#pragma once
#include <glew.h>
#include <string>
#include "Math.h"

class Shader
{
public:
	Shader();
	~Shader();
	//  加载顶点着色器和片段着色器
	bool Load(const std::string& vertName, const std::string& fragName);
	//  卸载着色器
	void Unload();
	//  激活
	void SetActive();
	//  传递矩阵全局变量
	void SetMatrixUniform(const char* name, const Matrix4& matrix);
private:
	//  尝试编译指定的着色器
	bool CompileShader(const std::string& fileName  //  着色器文件名称
		, GLenum shaderType  //  着色器类型
		, GLuint& outShader);  //  着色器id
	//  测试是否编译成功
	bool IsCompiled(GLuint shader);
	//  测试是否链接
	bool IsValidProgram();
private:
	//  顶点着色器id
	GLuint mVertexShader;
	//  片段着色器id
	GLuint mFragShader;
	//  着色器程序id
	GLuint mShaderProgram;
};

