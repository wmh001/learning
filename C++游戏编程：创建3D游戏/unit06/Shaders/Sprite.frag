//  版本设置
#version 330

//  着色器产生的图像
in vec2 fragTexCoord;

//  输出参数
out vec4 outColor;

//  全局变量，纹理采样
uniform sampler2D uTexture;

void main()
{
	//  赋值
	outColor = texture(uTexture, fragTexCoord);
}
