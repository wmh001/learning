//  �汾����
#version 330

//  ��������ȫ�־������
uniform mat4 uWorldTransform;
uniform mat4 uViewProj;

//  ���������λ����������������
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexCoord;

//  �������
out vec2 fragTexCoord;

void main()
{
	//  ת��Ϊ4*4����
	vec4 pos = vec4(inPosition, 1.0);
	//  ������任����˼�������任�������ռ�
	gl_Position = pos * uWorldTransform * uViewProj;
	//  ����
	fragTexCoord = inTexCoord;
}