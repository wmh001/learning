#include "Collision.h"
#include <algorithm>
#include <array>

LineSegment::LineSegment(const Vector3& start, const Vector3& end)
	: mStart(start)
	, mEnd(end)
{

}

Vector3 LineSegment::PointOnSegment(float t) const
{
	//  返回比例为t的点
	return mStart + (mEnd - mStart) * t;
}

float LineSegment::MinDistSq(const Vector3& point) const
{
	//  起点到终点
	Vector3 ab = mEnd - mStart;
	//  终点到起点
	Vector3 ba = -1.0f * ab;
	//  起点到点
	Vector3 ac = point - mStart;
	//  中点到点
	Vector3 bc = point - mEnd;
	//  AC、AB夹角大于90度
	if (Vector3::Dot(ab, ac) < 0.0f)
	{
		return ac.LengthSq();
	}
	//  BC、BA夹角大于90度
	else if (Vector3::Dot(ba, bc) < 0.0f)
	{
		return bc.LengthSq();
	}
	//  C投影在线段上
	else
	{
		//  计算投影
		float scalar = Vector3::Dot(ac, ab) / Vector3::Dot(ab, ab);
		Vector3 p = scalar * ab;
		//  计算长度
		return (ac - p).LengthSq();
	}
}

float LineSegment::MinDistSq(const LineSegment& s1, const LineSegment& s2)
{
	//  s1起点到终点
	Vector3   u = s1.mEnd - s1.mStart;
	//  s2起点到终点
	Vector3   v = s2.mEnd - s2.mStart;
	//  s2起点到s1起点
	Vector3   w = s1.mStart - s2.mStart;
	//  uu点积
	float    a = Vector3::Dot(u, u);
	//  uv点积
	float    b = Vector3::Dot(u, v);
	//  vv点积
	float    c = Vector3::Dot(v, v);
	//  uw点积
	float    d = Vector3::Dot(u, w);
	//  vw点积
	float    e = Vector3::Dot(v, w);
	//
	float    D = a * c - b * b;
    // sc = sN / sD，默认 sD = D >= 0
	float    sc, sN, sD = D;
    // tc = tN / tD，默认 tD = D >= 0
	float    tc, tN, tD = D;
	//  两条线几乎平行
	if (Math::NearZero(D)) { // the lines are almost parallel
		sN = 0.0;         // force using point P0 on segment S1
		sD = 1.0;         // to prevent possible division by 0.0 later
		tN = e;
		tD = c;
	}
	else {                 // get the closest points on the infinite lines
		sN = (b * e - c * d);
		tN = (a * e - b * d);
		if (sN < 0.0) {        // sc < 0 => the s=0 edge is visible
			sN = 0.0;
			tN = e;
			tD = c;
		}
		else if (sN > sD) {  // sc > 1  => the s=1 edge is visible
			sN = sD;
			tN = e + b;
			tD = c;
		}
	}

	if (tN < 0.0) {            // tc < 0 => the t=0 edge is visible
		tN = 0.0;
		// recompute sc for this edge
		if (-d < 0.0)
			sN = 0.0;
		else if (-d > a)
			sN = sD;
		else {
			sN = -d;
			sD = a;
		}
	}
	else if (tN > tD) {      // tc > 1  => the t=1 edge is visible
		tN = tD;
		// recompute sc for this edge
		if ((-d + b) < 0.0)
			sN = 0;
		else if ((-d + b) > a)
			sN = sD;
		else {
			sN = (-d + b);
			sD = a;
		}
	}
	// finally do the division to get sc and tc
	sc = (Math::NearZero(sN) ? 0.0f : sN / sD);
	tc = (Math::NearZero(tN) ? 0.0f : tN / tD);

	// get the difference of the two closest points
	Vector3   dP = w + (sc * u) - (tc * v);  // =  S1(sc) - S2(tc)

	return dP.LengthSq();   // return the closest distance squared
}

Plane::Plane(const Vector3& normal, float d)
	: mNormal(normal)
	, mD(d)
{

}

Plane::Plane(const Vector3& a, const Vector3& b, const Vector3& c)
{
	//  a到b
	Vector3 ab = b - a;
	//  a到c
	Vector3 ac = c - a;
	//  求叉积
	mNormal = Vector3::Cross(ab, ac);
	//  单位化
	mNormal.Normalize();
	// d = -P 点乘 n
	mD = -Vector3::Dot(a, mNormal);
}

float Plane::SignedDist(const Vector3& point) const
{
	//  OC点乘n减d
	return Vector3::Dot(point, mNormal) - mD;
}

Sphere::Sphere(const Vector3& center, float radius)
	: mCenter(center)
	, mRadius(radius)
{

}

bool Sphere::Contains(const Vector3& point) const
{
	//  计算点心距的平方
	float distSq = (mCenter - point).LengthSq();
	return distSq <= (mRadius * mRadius);
}

AABB::AABB(const Vector3& min, const Vector3& max)
	: mMin(min)
	, mMax(max)
{

}

void AABB::UpdateMinMax(const Vector3& point)
{
	//  分别更新每个组件
	mMin.x = Math::Min(mMin.x, point.x);
	mMin.y = Math::Min(mMin.y, point.y);
	mMin.z = Math::Min(mMin.z, point.z);
	mMax.x = Math::Max(mMax.x, point.x);
	mMax.y = Math::Max(mMax.y, point.y);
	mMax.z = Math::Max(mMax.z, point.z);
}

void AABB::Rotate(const Quaternion& q)
{
	//  构造8个顶点
	std::array<Vector3, 8> points;
	//  最小点
	points[0] = mMin;
	//  最小点相邻的三个点
	points[1] = Vector3(mMax.x, mMin.y, mMin.z);
	points[2] = Vector3(mMin.x, mMax.y, mMin.z);
	points[3] = Vector3(mMin.x, mMin.y, mMax.z);
	//  最大点相邻的三个点
	points[4] = Vector3(mMin.x, mMax.y, mMax.z);
	points[5] = Vector3(mMax.x, mMin.y, mMax.z);
	points[6] = Vector3(mMax.x, mMax.y, mMin.z);
	//  最大点
	points[7] = Vector3(mMax);
	//  旋转第一个点
	Vector3 p = Vector3::Transform(points[0], q);
	//  重置最大最小点
	mMin = p;
	mMax = p;
	//  旋转其他点并更新最大最小点
	for (size_t i = 1; i < points.size(); i++)
	{
		p = Vector3::Transform(points[i], q);
		UpdateMinMax(p);
	}
}

bool AABB::Contains(const Vector3& point) const
{
	//  是否在最大点和最小点之间
	bool outside = point.x < mMin.x ||
		point.y < mMin.y ||
		point.z < mMin.z ||
		point.x > mMax.x ||
		point.y > mMax.y ||
		point.z > mMax.z;
	return !outside;
}

float AABB::MinDistSq(const Vector3& point) const
{
	//  计算各个维度上的差
	float dx = Math::Max(mMin.x - point.x, 0.0f);
	dx = Math::Max(dx, point.x - mMax.x);
	float dy = Math::Max(mMin.y - point.y, 0.0f);
	dy = Math::Max(dy, point.y - mMax.y);
	float dz = Math::Max(mMin.z - point.z, 0.0f);
	dz = Math::Max(dy, point.z - mMax.z);
	//  计算距离平方
	return dx * dx + dy * dy + dz * dz;
}

Capsule::Capsule(const Vector3& start, const Vector3& end, float radius)
	: mSegment(start, end)
	, mRadius(radius)
{

}

Vector3 Capsule::PointOnSegment(float t) const
{
	return mSegment.PointOnSegment(t);
}

bool Capsule::Contains(const Vector3& point) const
{
	//  计算点和线段最小距离的平方
	float distSq = mSegment.MinDistSq(point);
	return distSq <= (mRadius * mRadius);
}

bool ConvexPolygon::Contains(const Vector2& point) const
{
	float sum = 0.0f;
	Vector2 a, b;
	for (size_t i = 0; i < mVertices.size() - 1; i++)
	{
		//  点到第一个顶点的向量
		a = mVertices[i] - point;
		//  单位化
		a.Normalize();
		//  点到第二个顶点的向量
		b = mVertices[i + 1] - point;
		//  单位化
		b.Normalize();
		//  计算角度并加和
		sum += Math::Acos(Vector2::Dot(a, b));
	}
	// 点到最后一个顶点
	a = mVertices.back() - point;
	//  单位化
	a.Normalize();
	//  点到第一个顶点
	b = mVertices.front() - point;
	//  单位化
	b.Normalize();
	//  计算角度并加和
	sum += Math::Acos(Vector2::Dot(a, b));
	//  和是否接近2pei
	return Math::NearZero(sum - Math::TwoPi);
}

bool Intersect(const Sphere& a, const Sphere& b)
{
	//  球心距里的平方
	float distSq = (a.mCenter - b.mCenter).LengthSq();
	//  半径之和
	float sumRadii = a.mRadius + b.mRadius;
	//  比较
	return distSq <= (sumRadii * sumRadii);
}

bool Intersect(const AABB& a, const AABB& b)
{
	//  a最大点小于b最小点或b最大点小于a最大点
	bool no = a.mMax.x < b.mMin.x ||
		a.mMax.y < b.mMin.y ||
		a.mMax.z < b.mMin.z ||
		b.mMax.x < a.mMin.x ||
		b.mMax.y < a.mMin.y ||
		b.mMax.z < a.mMin.z;
	return !no;
}

bool Intersect(const Capsule& a, const Capsule& b)
{
	//  计算线线距离
	float distSq = LineSegment::MinDistSq(a.mSegment, b.mSegment);
	//  计算半径和
	float sumRadii = a.mRadius + b.mRadius;
	//  比较
	return distSq <= (sumRadii * sumRadii);
}

bool Intersect(const Sphere& s, const AABB& box)
{
	//  计算球心到轴对称包围框的距离平方
	float distSq = box.MinDistSq(s.mCenter);
	//  比较
	return distSq <= (s.mRadius * s.mRadius);
}

bool Intersect(const LineSegment& l, const Sphere& s, float& outT)
{
	//  变量代换
	Vector3 X = l.mStart - s.mCenter;
	Vector3 Y = l.mEnd - l.mStart;
	float a = Vector3::Dot(Y, Y);
	float b = 2.0f * Vector3::Dot(X, Y);
	float c = Vector3::Dot(X, X) - s.mRadius * s.mRadius;
	//  计算判别式
	float disc = b * b - 4.0f * a * c;
	//  无交点
	if (disc < 0.0f)
	{
		return false;
	}
	else
	{
		//  开平方
		disc = Math::Sqrt(disc);
		//  公式法求解
		float tMin = (-b - disc) / (2.0f * a);
		float tMax = (-b + disc) / (2.0f * a);
		//  t在0到1之间则相交，否则不相交
		if (tMin >= 0.0f && tMin <= 1.0f)
		{
			outT = tMin;
			return true;
		}
		else if (tMax >= 0.0f && tMax <= 1.0f)
		{
			outT = tMax;
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool Intersect(const LineSegment& l, const Plane& p, float& outT)
{
	//  计算分母
	float denom = Vector3::Dot(l.mEnd - l.mStart, p.mNormal);
	//  线面平行
	if (Math::NearZero(denom))
	{
		//  线在面上
		if (Math::NearZero(Vector3::Dot(l.mStart, p.mNormal) - p.mD))
		{
			return true;
		}
		//  现在面外
		else
		{
			return false;
		}
	}
	//  线面不平行
	else
	{
		//  计算t
		float numer = -Vector3::Dot(l.mStart, p.mNormal) - p.mD;
		outT = numer / denom;
		//  t在0到1之间则相交，否则不相交
		if (outT >= 0.0f && outT <= 1.0f)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

//  辅助函数
bool TestSidePlane(float start, float end, float negd, const Vector3& norm, std::vector<std::pair<float, Vector3>>& out)
{
	//  计算分母
	float denom = end - start;
	if (Math::NearZero(denom))
	{
		return false;
	}
	else
	{
		//  计算分子
		float numer = -start + negd;
		//  计算t值
		float t = numer / denom;
		//  t在0到1之间则相交，否则不相交
		if (t >= 0.0f && t <= 1.0f)
		{
			//  进入容器
			out.emplace_back(t, norm);
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool Intersect(const LineSegment& l, const AABB& b, float& outT, Vector3& outNorm)
{
	//  保存所有可能的t值，以及这些边的法线的容器
	std::vector<std::pair<float, Vector3>> tValues;
	//  测试x平面
	TestSidePlane(l.mStart.x, l.mEnd.x, b.mMin.x, Vector3::NegUnitX, tValues);
	TestSidePlane(l.mStart.x, l.mEnd.x, b.mMax.x, Vector3::UnitX, tValues);
	//  测试y平面
	TestSidePlane(l.mStart.y, l.mEnd.y, b.mMin.y, Vector3::NegUnitY, tValues);
	TestSidePlane(l.mStart.y, l.mEnd.y, b.mMax.y, Vector3::UnitY, tValues);
	//  测试z平面
	TestSidePlane(l.mStart.z, l.mEnd.z, b.mMin.z, Vector3::NegUnitZ, tValues);
	TestSidePlane(l.mStart.z, l.mEnd.z, b.mMax.z, Vector3::UnitZ, tValues);
	//  按t值升序进行排序
	std::sort(tValues.begin(), tValues.end(), [](
		const std::pair<float, Vector3>& a,
		const std::pair<float, Vector3>& b) {
			return a.first < b.first;
		});
	Vector3 point;
	for (auto& t : tValues)
	{
		//  取点
		point = l.PointOnSegment(t.first);
		//  是否包含
		if (b.Contains(point))
		{
			//  取第一个交点
			outT = t.first;
			outNorm = t.second;
			return true;
		}
	}
	//  不包含
	return false;
}

bool SweptSphere(const Sphere& P0, const Sphere& P1, const Sphere& Q0, const Sphere& Q1, float& outT)
{
	//  变量代换
	Vector3 X = P0.mCenter - Q0.mCenter;
	Vector3 Y = P1.mCenter - P0.mCenter - (Q1.mCenter - Q0.mCenter);
	float a = Vector3::Dot(Y, Y);
	float b = 2.0f * Vector3::Dot(X, Y);
	float sumRadii = P0.mRadius + Q0.mRadius;
	float c = Vector3::Dot(X, X) - sumRadii * sumRadii;
	//  计算判别式
	float disc = b * b - 4.0f * a * c;
	//  无解
	if (disc < 0.0f)
	{
		return false;
	}
	else
	{
		//  计算较小解
		disc = Math::Sqrt(disc);
		outT = (-b - disc) / (2.0f * a);
		if (outT >= 0.0f && outT <= 1.0f)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
