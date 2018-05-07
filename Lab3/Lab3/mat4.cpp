#include "mat4.h"

namespace egc
{
	mat4& mat4::operator =(const mat4& srcMatrix)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				this->at(i, j) = srcMatrix.at(i, j);
			}
		}

		return *this;
	}

	mat4 mat4::operator *(float scalarValue) const
	{
		mat4 m;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m.at(i, j) = this->at(i, j) * scalarValue;
			}
		}

		return m;
	}

	mat4 mat4::operator *(const mat4& srcMatrix) const
	{
		mat4 m;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m.at(i, j) = 0;
				for (int k = 0; k < 4; k++)
				{
					m.at(i, j) += this->at(i, k) * srcMatrix.at(k, j);
				}
			}
		}

		return m;
	}

	vec4 mat4::operator *(const vec4& srcVector) const
	{
		vec4 v;
		v.x = this->at(0, 0) * srcVector.x + this->at(0, 1) * srcVector.y + this->at(0, 2) * srcVector.z + this->at(0, 3) * srcVector.w;
		v.y = this->at(1, 0) * srcVector.x + this->at(1, 1) * srcVector.y + this->at(1, 2) * srcVector.z + this->at(1, 3) * srcVector.w;
		v.z = this->at(2, 0) * srcVector.x + this->at(2, 1) * srcVector.y + this->at(2, 2) * srcVector.z + this->at(2, 3) * srcVector.w;
		v.w = this->at(3, 0) * srcVector.x + this->at(3, 1) * srcVector.y + this->at(3, 2) * srcVector.z + this->at(3, 3) * srcVector.w;


		return v;
	}

	mat4 mat4::operator +(const mat4& srcMatrix) const
	{
		mat4 m;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m.at(i, j) = this->at(i, j) + srcMatrix.at(i, j);
			}
		}

		return m;
	}

	float& mat4::at(int i, int j)
	{
		return this->matrixData[j * 4 + i];
	}

	const float& mat4::at(int i, int j) const
	{
		return this->matrixData[j * 4 + i];
	}

	float mat4::determinant() const
	{
		float v = 0;
		mat3 m;

		for (int k = 0; k < 4; k++)
		{
			int p = 0;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 1; j < 4; j++)
				{
					if (i == k)
					{
						continue;
					}

					m.matrixData[p++] = this->at(j, i);
				}
			}
			v += pow(-1, k) * m.determinant() * this->at(0, k);
		}
		return v;
	}

	mat4 mat4::inverse() const
	{
		mat3 m;
		mat4 res;
		float det = this->determinant();

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				int p = 0;
				for (int l = 0; l < 4; l++)
				{
					for (int k = 0; k < 4; k++)
					{
						if (l == j || k == i)
						{
							continue;
						}

						m.matrixData[p++] = this->at(k, l);
					}
				}
				res.at(i, j) = pow(-1, i + j) * m.determinant() / det;
			}
		}
		res = res.transpose();

		return res;
	}

	mat4 mat4::transpose() const
	{
		mat4 m;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m.at(i, j) = this->at(j, i);
			}
		}

		return m;
	}
}