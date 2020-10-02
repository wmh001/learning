#include "GBuffer.h"
#include <glew.h>
#include "Texture.h"

GBuffer::GBuffer()
	:mBufferID(0)
{

}

GBuffer::~GBuffer()
{

}

bool GBuffer::Create(int width, int height)
{
	//  ����֡����������
	glGenFramebuffers(1, &mBufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, mBufferID);
	//  �����Ȼ�����Ŀ��
	GLuint depthBuffer;
	glGenRenderbuffers(1, &depthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
	//  ����ÿ���������͵�ͼ��
	for (int i = 0; i < NUM_GBUFFER_TEXTURES; i++)
	{
		//  ����ͼ��
		Texture* tex = new Texture();
		//  ����GL_RGB32F���ݸ�ʽ
		tex->CreateForRendering(width, height, GL_RGB32F);
		//  ��������
		mTextures.emplace_back(tex);
		// Attach this texture to a color output
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, tex->GetTextureID(), 0);
	}
	//  ������ɫ��������
	std::vector<GLenum> attachments;
	for (int i = 0; i < NUM_GBUFFER_TEXTURES; i++)
	{
		attachments.emplace_back(GL_COLOR_ATTACHMENT0 + i);
	}
	//  ����ͼ�񸽼�
	glDrawBuffers(static_cast<GLsizei>(attachments.size()), attachments.data());
	//  ���״̬��ʧ�ܴ���
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		Destroy();
		return false;
	}
	return true;
}

void GBuffer::Destroy()
{
	//  ɾ��������
	glDeleteFramebuffers(1, &mBufferID);
	//  ɾ��ͼ��
	for (Texture* t : mTextures)
	{
		t->Unload();
		delete t;
	}
}

Texture* GBuffer::GetTexture(Type type)
{
	if (mTextures.size() > 0)
	{
		return mTextures[type];
	}
	else
	{
		return nullptr;
	}
}

void GBuffer::SetTexturesActive()
{
	for (int i = 0; i < NUM_GBUFFER_TEXTURES; i++)
	{
		//  ���������
		mTextures[i]->SetActive(i);
	}
}
