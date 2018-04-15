#include "vec3.h"

namespace egc {
	vec3& vec3::operator =(const vec3 &srcVector)
	{
		this->x = srcVector.x;
		this->y = srcVector.y;
		this->z = srcVector.z;
		return *this;
	}

	vec3 vec3::operator +(const vec3& srcVector) const
	{
		return vec3(srcVector.x + this->x, srcVector.y + this->y, srcVector.z + this->z);
	}

	vec3& vec3::operator +=(const vec3& srcVector)
	{
		this->x += srcVector.x;
		this->y += srcVector.y;
		this->z += srcVector.z;
		return *this;
	}

	vec3 vec3::operator *(float scalarValue) const
	{
		return vec3(this->x * scalarValue, this->y * scalarValue, this->z * scalarValue);
	}

	vec3 vec3::operator -(const vec3& srcVector) const
	{
		return vec3(this->x - srcVector.x, this->y - srcVector.y, this->z - srcVector.z);
	}

	vec3& vec3::operator -=(const vec3& srcVector)
	{
		this->x -= srcVector.x;
		this->y -= srcVector.y;
		this->z -= srcVector.z;
		return *this;
	}

	vec3& vec3::operator -()
	{
		this->x = -this->x;
		this->y = -this->y;
		this->z = -this->z;
		return *this;
	}

	float vec3::length() const
	{
		return std::sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
	}

	vec3& vec3::normalize()
	{
		float l = length();
		this->x /= l;
		this->y /= l;
		this->z /= l;
		return *this;
	}

	float dotProduct(const vec3& v1, const vec3& v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	vec3 crossProduct(const vec3& v1, const vec3& v2)
	{
		vec3 v = vec3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v1.x);
		return v;
	}
}