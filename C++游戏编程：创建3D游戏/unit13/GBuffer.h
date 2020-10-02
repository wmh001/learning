#pragma once
#include <vector>

class GBuffer
{
public:
	//  G�������Ĳ�ͬ��������
	enum Type
	{
		//  ��������ɫ
		EDiffuse = 0,
		//  ����
		ENormal,
		//  λ��
		EWorldPos,
		NUM_GBUFFER_TEXTURES
	};
	GBuffer();
	~GBuffer();
	//  ����G������
	bool Create(int width, int height);
	//  ɾ��G������
	void Destroy();
	//  �����ض��������ݵ�����
	class Texture* GetTexture(Type type);
	// Get the framebuffer object ID
	unsigned int GetBufferID() const { return mBufferID; }
	//  ����ͼ�񲢰�����
	void SetTexturesActive();
private:
	//  ��������
	std::vector<class Texture*> mTextures;
	//  ֡������id
	unsigned int mBufferID;
};

