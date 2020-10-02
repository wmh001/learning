//  版本设置
#version 330

//  着色器产生的图像
in vec2 fragTexCoord;

//  法线
in vec3 fragNormal;

//  位置
in vec3 fragWorldPos;

//  创建平行光的结构体
struct DirectionalLight
{
	//  方向
	vec3 mDirection;
	//  漫反射
	vec3 mDiffuseColor;
	//  镜面反射
	vec3 mSpecColor;
};

//  输出参数
out vec4 outColor;

//  全局变量，纹理采样
uniform sampler2D uTexture;

//  世界坐标的相机位置
uniform vec3 uCameraPos;
//  此曲面的镜面反射功率
uniform float uSpecPower;
//  环境光照度
uniform vec3 uAmbientLight;

//  平行光
uniform DirectionalLight uDirLight;

void main()
{
	//  曲面法线
	vec3 N = normalize(fragNormal);
	//  曲面到光源
	vec3 L = normalize(-uDirLight.mDirection);
	//  曲面到相机
	vec3 V = normalize(uCameraPos - fragWorldPos);
	//  反射光线
	vec3 R = normalize(reflect(-L, N));

	//  计算反射
	vec3 Phong = uAmbientLight;
	float NdotL = dot(N, L);
	if (NdotL > 0)
	{
		vec3 Diffuse = uDirLight.mDiffuseColor * NdotL;
		vec3 Specular = uDirLight.mSpecColor * pow(max(0.0, dot(R, V)), uSpecPower);
		Phong += Diffuse + Specular;
	}

	//  最终颜色是纹理颜色乘以phong灯光（alpha=1）
    outColor = texture(uTexture, fragTexCoord) * vec4(Phong, 1.0f);
}
