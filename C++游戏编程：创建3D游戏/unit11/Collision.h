#pragma once
#include "Math.h"
#include <vector>

//  线段
struct LineSegment
{
	//  两点确定线段
	LineSegment(const Vector3& start, const Vector3& end);
	//  取点
	Vector3 PointOnSegment(float t) const;
	//  计算点到线段最短距离的平方
	float MinDistSq(const Vector3& point) const;
	//  计算两条线段之间距离的平方
	static float MinDistSq(const LineSegment& s1, const LineSegment& s2);
	//  起点
	Vector3 mStart;
	//  中点
	Vector3 mEnd;
};

//  平面
struct Plane
{
	//  法线与原面距构造平面
	Plane(const Vector3& normal, float d);
	//  三点确定平面
	Plane(const Vector3& a, const Vector3& b, const Vector3& c);
	//  计算点到平面的距离
	float SignedDist(const Vector3& point) const;
	//  法线
	Vector3 mNormal;
	//  平面到原点的的有向距离
	float mD;
};

//  球
struct Sphere
{
	//  球心半径确定球
	Sphere(const Vector3& center, float radius);
	//  是否包含点
	bool Contains(const Vector3& point) const;
	//  球心
	Vector3 mCenter;
	//  半径
	float mRadius;
};

//  轴对齐包围框
struct AABB
{
	//  两点确定轴对齐包围框
	AABB(const Vector3& min, const Vector3& max);
	//  新点加入更新最大点或最小点
	void UpdateMinMax(const Vector3& point);
	//  根据四元数旋转
	void Rotate(const Quaternion& q);
	//  是否包含点
	bool Contains(const Vector3& point) const;
	//  计算点到轴对称包围框的距离
	float MinDistSq(const Vector3& point) const;
	//  x,y,z最小的点
	Vector3 mMin;
	//  x,y,z最大的点
	Vector3 mMax;
};

//  定向包围框
struct OBB
{
	//  中心点
	Vector3 mCenter;
	//  旋转状态
	Quaternion mRotation;
	//  范围
	Vector3 mExtents;
};

//  胶囊体
struct Capsule
{
	Capsule(const Vector3& start, const Vector3& end, float radius);
	//  取点
	Vector3 PointOnSegment(float t) const;
	bool Contains(const Vector3& point) const;
	//  轴线
	LineSegment mSegment;
	//  半径
	float mRadius;
};

//  凸多边形
struct ConvexPolygon
{
	bool Contains(const Vector2& point) const;
	//  顶点容器，按顺时针顺序
	std::vector<Vector2> mVertices;
};

//  球与球是否相交
bool Intersect(const Sphere& a, const Sphere& b);
//  轴对齐包围框与轴对称包围框是否相交
bool Intersect(const AABB& a, const AABB& b);
//  胶囊体与胶囊体是否相交
bool Intersect(const Capsule& a, const Capsule& b);
//  球体与轴对齐包围框是否相交
bool Intersect(const Sphere& s, const AABB& box);
//  线段与球是否相交
bool Intersect(const LineSegment& l, const Sphere& s, float& outT);
//  线段与平面是否相交
bool Intersect(const LineSegment& l, const Plane& p, float& outT);
//  线段与轴对称包围框是否相交
bool Intersect(const LineSegment& l, const AABB& b, float& outT, Vector3& outNorm);
//  扫掠球体交叉相交测试
bool SweptSphere(const Sphere& P0, const Sphere& P1, const Sphere& Q0, const Sphere& Q1, float& t);

