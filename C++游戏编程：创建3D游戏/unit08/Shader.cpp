#include "Shader.h"
#include "Texture.h"
#include <SDL.h>
#include <fstream>
#include <sstream>

Shader::Shader()
	: mShaderProgram(0)
	, mVertexShader(0)
	, mFragShader(0)
{

}

Shader::~Shader()
{

}

bool Shader::Load(const std::string& vertName, const std::string& fragName)
{
	//  编译顶点着色器和片段着色器并保存id
	if (!CompileShader(vertName,
		GL_VERTEX_SHADER,
		mVertexShader) ||
		!CompileShader(fragName,
			GL_FRAGMENT_SHADER,
			mFragShader))
	{
		return false;
	}
	//  创建着色器程序并保存id
	mShaderProgram = glCreateProgram();
	//  组合
	glAttachShader(mShaderProgram, mVertexShader);
	glAttachShader(mShaderProgram, mFragShader);
	//  链接
	glLinkProgram(mShaderProgram);
	//  链接是否成功
	if (!IsValidProgram())
	{
		return false;
	}
	return true;
}

void Shader::Unload()
{
	//  删除着色器程序
	glDeleteProgram(mShaderProgram);
	//  删除顶点着色器
	glDeleteShader(mVertexShader);
	//  删除片段着色器
	glDeleteShader(mFragShader);
}

void Shader::SetActive()
{
	//  激活
	glUseProgram(mShaderProgram);
}

void Shader::SetMatrixUniform(const char* name, const Matrix4& matrix)
{
	//  寻找全局变量
	GLuint loc = glGetUniformLocation(mShaderProgram, name);
	//  将矩阵传给全局变量
	glUniformMatrix4fv(
		loc  //  全局变量id
		, 1  //  矩阵数量
		, GL_TRUE  //  使用行向量
		, matrix.GetAsFloatPtr());  //  矩阵
}

bool Shader::CompileShader(const std::string& fileName,
	GLenum shaderType,
	GLuint& outShader)
{
	//  打开文件
	std::ifstream shaderFile(fileName);
	if (shaderFile.is_open())
	{
		//  文件内容读入字符串
		std::stringstream sstream;
		sstream << shaderFile.rdbuf();
		std::string contents = sstream.str();
        //  获取c样式字符串指针
		const char* contentsChar = contents.c_str();
		//  创建着色器对象并保存id
		outShader = glCreateShader(shaderType);
		//  指定源码
		glShaderSource(outShader, 1, &(contentsChar), nullptr);
		//  编译
		glCompileShader(outShader);
		//  编译失败处理
		if (!IsCompiled(outShader))
		{
			SDL_Log("Failed to compile shader %s", fileName.c_str());
			return false;
		}
	}
	else
	{
		SDL_Log("Shader file not found: %s", fileName.c_str());
		return false;
	}

	return true;
}

bool Shader::IsCompiled(GLuint shader)
{
	GLint status;
	//  查询编译状态
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	//  失败处理
	if (status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer, 0, 512);
		//  获取错误信息
		glGetShaderInfoLog(shader, 511, nullptr, buffer);
		SDL_Log("GLSL Compile Failed:\n%s", buffer);
		return false;
	}

	return true;
}

bool Shader::IsValidProgram()
{

	GLint status;
	//  查询链接状态
	glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &status);
	if (status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer, 0, 512);
		//  获取错误信息
		glGetProgramInfoLog(mShaderProgram, 511, nullptr, buffer);
		SDL_Log("GLSL Link Status:\n%s", buffer);
		return false;
	}
	return true;
}
