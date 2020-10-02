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
	//  ���붥����ɫ����Ƭ����ɫ��������id
	if (!CompileShader(vertName,
		GL_VERTEX_SHADER,
		mVertexShader) ||
		!CompileShader(fragName,
			GL_FRAGMENT_SHADER,
			mFragShader))
	{
		return false;
	}
	//  ������ɫ�����򲢱���id
	mShaderProgram = glCreateProgram();
	//  ���
	glAttachShader(mShaderProgram, mVertexShader);
	glAttachShader(mShaderProgram, mFragShader);
	//  ����
	glLinkProgram(mShaderProgram);
	//  �����Ƿ�ɹ�
	if (!IsValidProgram())
	{
		return false;
	}
	return true;
}

void Shader::Unload()
{
	//  ɾ����ɫ������
	glDeleteProgram(mShaderProgram);
	//  ɾ��������ɫ��
	glDeleteShader(mVertexShader);
	//  ɾ��Ƭ����ɫ��
	glDeleteShader(mFragShader);
}

void Shader::SetActive()
{
	//  ����
	glUseProgram(mShaderProgram);
}

void Shader::SetMatrixUniform(const char* name, const Matrix4& matrix)
{
	//  Ѱ��ȫ�ֱ���
	GLuint loc = glGetUniformLocation(mShaderProgram, name);
	//  �����󴫸�ȫ�ֱ���
	glUniformMatrix4fv(
		loc  //  ȫ�ֱ���id
		, 1  //  ��������
		, GL_TRUE  //  ʹ��������
		, matrix.GetAsFloatPtr());  //  ����
}

bool Shader::CompileShader(const std::string& fileName,
	GLenum shaderType,
	GLuint& outShader)
{
	//  ���ļ�
	std::ifstream shaderFile(fileName);
	if (shaderFile.is_open())
	{
		//  �ļ����ݶ����ַ���
		std::stringstream sstream;
		sstream << shaderFile.rdbuf();
		std::string contents = sstream.str();
        //  ��ȡc��ʽ�ַ���ָ��
		const char* contentsChar = contents.c_str();
		//  ������ɫ�����󲢱���id
		outShader = glCreateShader(shaderType);
		//  ָ��Դ��
		glShaderSource(outShader, 1, &(contentsChar), nullptr);
		//  ����
		glCompileShader(outShader);
		//  ����ʧ�ܴ���
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
	//  ��ѯ����״̬
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	//  ʧ�ܴ���
	if (status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer, 0, 512);
		//  ��ȡ������Ϣ
		glGetShaderInfoLog(shader, 511, nullptr, buffer);
		SDL_Log("GLSL Compile Failed:\n%s", buffer);
		return false;
	}

	return true;
}

bool Shader::IsValidProgram()
{

	GLint status;
	//  ��ѯ����״̬
	glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &status);
	if (status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer, 0, 512);
		//  ��ȡ������Ϣ
		glGetProgramInfoLog(mShaderProgram, 511, nullptr, buffer);
		SDL_Log("GLSL Link Status:\n%s", buffer);
		return false;
	}
	return true;
}
