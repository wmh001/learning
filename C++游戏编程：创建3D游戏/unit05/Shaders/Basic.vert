//  与opengl3.3对应的GLSL版本
#version 330

//  输入参数
in vec3 inPosition;

void main()
{
	//  直接传递
	gl_Position = vec4(inPosition, 1.0);
}