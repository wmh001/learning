//  版本设置
#version 330

//  定义两个全局矩阵变量
uniform mat4 uWorldTransform;
uniform mat4 uViewProj;

//  输入参数，位置坐标与纹理坐标
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexCoord;

//  输出参数
out vec2 fragTexCoord;

void main()
{
	//  转化为4*4矩阵
	vec4 pos = vec4(inPosition, 1.0);
	//  乘世界变换矩阵乘剪辑矩阵变换到剪辑空间
	gl_Position = pos * uWorldTransform * uViewProj;
	//  复制
	fragTexCoord = inTexCoord;
}