#pragma once
#include "Math.h"
#include <vector>

//  �߶�
struct LineSegment
{
	//  ����ȷ���߶�
	LineSegment(const Vector3& start, const Vector3& end);
	//  ȡ��
	Vector3 PointOnSegment(float t) const;
	//  ����㵽�߶���̾����ƽ��
	float MinDistSq(const Vector3& point) const;
	//  ���������߶�֮������ƽ��
	static float MinDistSq(const LineSegment& s1, const LineSegment& s2);
	//  ���
	Vector3 mStart;
	//  �е�
	Vector3 mEnd;
};

//  ƽ��
struct Plane
{
	//  ������ԭ��๹��ƽ��
	Plane(const Vector3& normal, float d);
	//  ����ȷ��ƽ��
	Plane(const Vector3& a, const Vector3& b, const Vector3& c);
	//  ����㵽ƽ��ľ���
	float SignedDist(const Vector3& point) const;
	//  ����
	Vector3 mNormal;
	//  ƽ�浽ԭ��ĵ��������
	float mD;
};

//  ��
struct Sphere
{
	//  ���İ뾶ȷ����
	Sphere(const Vector3& center, float radius);
	//  �Ƿ������
	bool Contains(const Vector3& point) const;
	//  ����
	Vector3 mCenter;
	//  �뾶
	float mRadius;
};

//  ������Χ��
struct AABB
{
	//  ����ȷ��������Χ��
	AABB(const Vector3& min, const Vector3& max);
	//  �µ��������������С��
	void UpdateMinMax(const Vector3& point);
	//  ������Ԫ����ת
	void Rotate(const Quaternion& q);
	//  �Ƿ������
	bool Contains(const Vector3& point) const;
	//  ����㵽��Գư�Χ��ľ���
	float MinDistSq(const Vector3& point) const;
	//  x,y,z��С�ĵ�
	Vector3 mMin;
	//  x,y,z���ĵ�
	Vector3 mMax;
};

//  �����Χ��
struct OBB
{
	//  ���ĵ�
	Vector3 mCenter;
	//  ��ת״̬
	Quaternion mRotation;
	//  ��Χ
	Vector3 mExtents;
};

//  ������
struct Capsule
{
	Capsule(const Vector3& start, const Vector3& end, float radius);
	//  ȡ��
	Vector3 PointOnSegment(float t) const;
	bool Contains(const Vector3& point) const;
	//  ����
	LineSegment mSegment;
	//  �뾶
	float mRadius;
};

//  ͹�����
struct ConvexPolygon
{
	bool Contains(const Vector2& point) const;
	//  ������������˳ʱ��˳��
	std::vector<Vector2> mVertices;
};

//  �������Ƿ��ཻ
bool Intersect(const Sphere& a, const Sphere& b);
//  ������Χ������Գư�Χ���Ƿ��ཻ
bool Intersect(const AABB& a, const AABB& b);
//  �������뽺�����Ƿ��ཻ
bool Intersect(const Capsule& a, const Capsule& b);
//  ������������Χ���Ƿ��ཻ
bool Intersect(const Sphere& s, const AABB& box);
//  �߶������Ƿ��ཻ
bool Intersect(const LineSegment& l, const Sphere& s, float& outT);
//  �߶���ƽ���Ƿ��ཻ
bool Intersect(const LineSegment& l, const Plane& p, float& outT);
//  �߶�����Գư�Χ���Ƿ��ཻ
bool Intersect(const LineSegment& l, const AABB& b, float& outT, Vector3& outNorm);
//  ɨ�����彻���ཻ����
bool SweptSphere(const Sphere& P0, const Sphere& P1, const Sphere& Q0, const Sphere& Q1, float& t);

