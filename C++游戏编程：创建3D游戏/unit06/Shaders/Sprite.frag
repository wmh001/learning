//  �汾����
#version 330

//  ��ɫ��������ͼ��
in vec2 fragTexCoord;

//  �������
out vec4 outColor;

//  ȫ�ֱ������������
uniform sampler2D uTexture;

void main()
{
	//  ��ֵ
	outColor = texture(uTexture, fragTexCoord);
}
