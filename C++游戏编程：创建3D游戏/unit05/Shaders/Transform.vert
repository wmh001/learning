//  ��opengl3.3��Ӧ��GLSL�汾
#version 330

//  ��������ȫ�־������
uniform mat4 uWorldTransform;
uniform mat4 uViewProj;

//  �������
in vec3 inPosition;

void main()
{
	//  ת��Ϊ4*4����
	vec4 pos = vec4(inPosition, 1.0);
	//  ������任����˼�������任�������ռ�
	gl_Position = pos * uWorldTransform * uViewProj;
}