#include "vec2.h"

namespace egc {
	vec2& vec2::operator =(const vec2 &srcVector)
	{
		this->x = srcVector.x;
		this->y = srcVector.y;
		return *this;
	}

	vec2 vec2::operator +(const vec2& srcVector) const
	{
		return vec2(srcVector.x + this->x, srcVector.y + this->y);
	}

	vec2& vec2::operator +=(const vec2& srcVector)
	{
		this->x += srcVector.x;
		this->y += srcVector.y;
		return *this;
	}

	vec2 vec2::operator *(float scalarValue) const
	{
		return vec2(this->x * scalarValue, this->y * scalarValue);
	}

	vec2 vec2::operator -(const vec2& srcVector) const
	{
		return vec2(this->x - srcVector.x, this->y - srcVector.y);
	}

	vec2& vec2::operator -=(const vec2& srcVector)
	{
		this->x -= srcVector.x;
		this->y -= srcVector.y;
		return *this;
	}

	vec2& vec2::operator -()
	{
		this->x = -this->x;
		this->y = -this->y;
		return *this;
	}

	float vec2::length() const
	{
		return std::sqrt((this->x * this->x) + (this->y * this->y));
	}

	vec2& vec2::normalize()
	{
		float l = length();
		this->x /= l;
		this->y /= l;
		return *this;
	}

	float dotProduct(const vec2& v1, const vec2& v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}
}