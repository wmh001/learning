//  与opengl3.3对应的GLSL版本
#version 330

//  定义两个全局矩阵变量
uniform mat4 uWorldTransform;
uniform mat4 uViewProj;

//  输入参数
in vec3 inPosition;

void main()
{
	//  转化为4*4矩阵
	vec4 pos = vec4(inPosition, 1.0);
	//  乘世界变换矩阵乘剪辑矩阵变换到剪辑空间
	gl_Position = pos * uWorldTransform * uViewProj;
}