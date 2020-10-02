//  �汾����
#version 330

//  ��ɫ��������ͼ��
in vec2 fragTexCoord;

//  ����
in vec3 fragNormal;

//  λ��
in vec3 fragWorldPos;

//  ����ƽ�й�Ľṹ��
struct DirectionalLight
{
	//  ����
	vec3 mDirection;
	//  ������
	vec3 mDiffuseColor;
	//  ���淴��
	vec3 mSpecColor;
};

//  �������
out vec4 outColor;

//  ȫ�ֱ������������
uniform sampler2D uTexture;

//  ������������λ��
uniform vec3 uCameraPos;
//  ������ľ��淴�书��
uniform float uSpecPower;
//  �������ն�
uniform vec3 uAmbientLight;

//  ƽ�й�
uniform DirectionalLight uDirLight;

void main()
{
	//  ���淨��
	vec3 N = normalize(fragNormal);
	//  ���浽��Դ
	vec3 L = normalize(-uDirLight.mDirection);
	//  ���浽���
	vec3 V = normalize(uCameraPos - fragWorldPos);
	//  �������
	vec3 R = normalize(reflect(-L, N));

	//  ���㷴��
	vec3 Phong = uAmbientLight;
	float NdotL = dot(N, L);
	if (NdotL > 0)
	{
		vec3 Diffuse = uDirLight.mDiffuseColor * NdotL;
		vec3 Specular = uDirLight.mSpecColor * pow(max(0.0, dot(R, V)), uSpecPower);
		Phong += Diffuse + Specular;
	}

	//  ������ɫ��������ɫ����phong�ƹ⣨alpha=1��
    outColor = texture(uTexture, fragTexCoord) * vec4(Phong, 1.0f);
}
