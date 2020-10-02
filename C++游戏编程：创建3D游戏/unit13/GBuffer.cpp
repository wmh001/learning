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
	//  创建帧缓冲区对象
	glGenFramebuffers(1, &mBufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, mBufferID);
	//  添加深度缓冲区目标
	GLuint depthBuffer;
	glGenRenderbuffers(1, &depthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
	//  创建每种数据类型的图像
	for (int i = 0; i < NUM_GBUFFER_TEXTURES; i++)
	{
		//  创建图像
		Texture* tex = new Texture();
		//  请求GL_RGB32F数据格式
		tex->CreateForRendering(width, height, GL_RGB32F);
		//  进入容器
		mTextures.emplace_back(tex);
		// Attach this texture to a color output
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, tex->GetTextureID(), 0);
	}
	//  创建颜色附件容器
	std::vector<GLenum> attachments;
	for (int i = 0; i < NUM_GBUFFER_TEXTURES; i++)
	{
		attachments.emplace_back(GL_COLOR_ATTACHMENT0 + i);
	}
	//  设置图像附件
	glDrawBuffers(static_cast<GLsizei>(attachments.size()), attachments.data());
	//  检测状态机失败处理
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		Destroy();
		return false;
	}
	return true;
}

void GBuffer::Destroy()
{
	//  删除缓冲区
	glDeleteFramebuffers(1, &mBufferID);
	//  删除图像
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
		//  激活并绑定索引
		mTextures[i]->SetActive(i);
	}
}
