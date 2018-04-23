#include "mat3.h"

namespace egc
{
	mat3& mat3::operator =(const mat3& srcMatrix)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				this->at(i, j) = srcMatrix.at(i, j);
			}
		}

		return *this;
	}


	mat3 mat3::operator *(float scalarValue) const
	{
		mat3 m;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				m.at(i, j) = this->at(i, j) * scalarValue;
			}
		}

		return m;
	}


	mat3 mat3::operator *(const mat3& srcMatrix) const
	{
		mat3 m;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				m.at(i, j) = 0;
				for (int k = 0; k < 3; k++)
				{
					m.at(i, j) += this->at(i, k) * srcMatrix.at(k, j);
				}
			}
		}

		return m;
	}

	vec3 mat3::operator *(const vec3& srcVector) const
	{
		vec3 v;
		v.x = this->at(0, 0) * srcVector.x + this->at(0, 1) * srcVector.y + this->at(0, 2) * srcVector.z;
		v.y = this->at(1, 0) * srcVector.x + this->at(1, 1) * srcVector.y + this->at(1, 2) * srcVector.z;
		v.z = this->at(2, 0) * srcVector.x + this->at(2, 1) * srcVector.y + this->at(2, 2) * srcVector.z;

		return v;
	}

	mat3 mat3::operator +(const mat3& srcMatrix) const
	{
		mat3 m;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				m.at(i, j) = this->at(i, j) + srcMatrix.at(i, j);
			}
		}

		return m;
	}

	float& mat3::at(int i, int j)
	{
		return this->matrixData[j * 3 + i];
	}

	const float& mat3::at(int i, int j) const
	{
		return this->matrixData[j * 3 + i];
	}

	float mat3::determinant() const
	{
		return (this->at(0, 0) * this->at(1, 1) * this->at(2, 2)
			+ this->at(1, 0) * this->at(2, 1) * this->at(0, 2)
			+ this->at(0, 1) * this->at(1, 2) * this->at(2, 0)
			- this->at(0, 2) * this->at(1, 1) * this->at(2, 0)
			- this->at(1, 0) * this->at(0, 1) * this->at(2, 2)
			- this->at(2, 1) * this->at(1, 2) * this->at(0, 0)
			);
	}

	mat3 mat3::inverse() const
	{
		mat3 m;
		float coef = 1 / determinant();
		m.at(0, 0) = coef * (this->at(1, 1) * this->at(2, 2) - this->at(1, 2) * this->at(2, 1));
		m.at(0, 1) = coef * (this->at(0, 2) * this->at(2, 1) - this->at(2, 2) * this->at(0, 1));
		m.at(0, 2) = coef * (this->at(0, 1) * this->at(1, 2) - this->at(1, 1) * this->at(0, 2));
		m.at(1, 0) = coef * (this->at(1, 2) * this->at(2, 0) - this->at(2, 2) * this->at(1, 0));
		m.at(1, 1) = coef * (this->at(0, 0) * this->at(2, 2) - this->at(2, 0) * this->at(0, 2));
		m.at(1, 2) = coef * (this->at(0, 2) * this->at(1, 0) - this->at(1, 2) * this->at(0, 0));
		m.at(2, 0) = coef * (this->at(1, 0) * this->at(2, 1) - this->at(2, 0) * this->at(1, 1));
		m.at(2, 1) = coef * (this->at(0, 1) * this->at(2, 0) - this->at(2, 1) * this->at(0, 0));
		m.at(2, 2) = coef * (this->at(0, 0) * this->at(1, 1) - this->at(1, 0) * this->at(0, 1));

		return m;
	}

	mat3 mat3::transpose() const
	{
		mat3 m;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				m.at(i, j) = this->at(j, i);
			}
		}

		return m;
	}
}