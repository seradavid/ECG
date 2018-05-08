#include "clip.h"
#include <algorithm>

namespace egc {
	int lineClip_CyrusBeck(std::vector<vec3> clipWindow, vec3& p1, vec3& p2)
	{
		vec3 d = p2 - p1;
		int n = clipWindow.size();
		std::vector<vec3> normals;
		for (int i = 0; i < n; i++)
		{
			vec3 norm;
			vec3 z = vec3(0, 0, 1);
			norm = clipWindow[(i + 1) % n] - clipWindow[i];
			norm = crossProduct(norm, z);
			normals.push_back(norm);
		}

		if (p1 == p2)
		{
			// point
			return 0;
		}
		else
		{
			float te = 0;
			float tl = 1;

			for (int i = 0; i < n; i++)
			{
				float v = dotProduct(normals[i], d);
				if (v != 0)
				{
					float t = -(dotProduct(normals[i], p1 - clipWindow[i])) / (v);
					if (v < 0)
					{
						te = std::max(te, t);
					}
					if (v > 0)
					{
						tl = std::min(tl, t);
					}
				}
			}

			if (te > tl)
			{
				return -1;
			}
			else
			{
				p2 = p1 + d * tl;
				p1 = p1 + d * te;
				return 0;
			}
		}
		return -1;
	}

	float getMaxx(std::vector<vec3> clipWindow)
	{
		float m = clipWindow.at(0).x;
		for (unsigned i = 0; i < clipWindow.size(); ++i)
		{
			m = m > clipWindow.at(i).x ? m : clipWindow.at(i).x;
		}
		return m;
	}

	float getMaxy(std::vector<vec3> clipWindow)
	{
		float m = clipWindow.at(0).y;
		for (unsigned i = 0; i < clipWindow.size(); ++i)
		{
			m = m > clipWindow.at(i).y ? m : clipWindow.at(i).y;
		}
		return m;
	}

	float getMinx(std::vector<vec3> clipWindow)
	{
		float m = clipWindow.at(0).x;
		for (unsigned i = 0; i < clipWindow.size(); ++i)
		{
			m = m < clipWindow.at(i).x ? m : clipWindow.at(i).x;
		}
		return m;
	}

	float getMiny(std::vector<vec3> clipWindow)
	{
		float m = clipWindow.at(0).y;
		for (unsigned i = 0; i < clipWindow.size(); ++i)
		{
			m = m < clipWindow.at(i).y ? m : clipWindow.at(i).y;
		}
		return m;
	}

	std::vector<int> computeCSCode(std::vector<vec3> clipWindow, const vec3 p)
	{
		std::vector<int> vec;

		if (p.y > getMaxy(clipWindow))
		{
			vec.push_back(1);
			vec.push_back(0);
		}
		else if (p.y < getMiny(clipWindow))
		{
			vec.push_back(0);
			vec.push_back(1);
		}
		else
		{
			vec.push_back(0);
			vec.push_back(0);
		}

		if (p.x > getMaxx(clipWindow))
		{
			vec.push_back(1);
			vec.push_back(0);
		}
		else if (p.x < getMinx(clipWindow))
		{
			vec.push_back(0);
			vec.push_back(1);
		}
		else
		{
			vec.push_back(0);
			vec.push_back(0);
		}

		return vec;
	}

	bool simpleRejection(std::vector<int> cod1, std::vector<int> cod2)
	{
		for (int i = 0; i < 4; i++)
		{
			if (cod1.at(i) && cod2.at(i))
			{
				return true;
			}
		}

		return false;
	}

	bool simpleAcceptance(std::vector<int> cod1, std::vector<int> cod2)
	{
		bool result = true;

		for (int i = 0; i < 4; i++)
		{
			result = result && (cod1.at(i) == cod2.at(i) && cod1.at(i) == 0);
		}

		return result;
	}

	int lineClip_CohenSutherland(std::vector<vec3> clipWindow, vec3& p1, vec3& p2)
	{
		std::vector<int> cod1 = computeCSCode(clipWindow, p1);
		std::vector<int> cod2 = computeCSCode(clipWindow, p2);

		while (1) {
			if (simpleRejection(cod1, cod2))
			{
				return -1;
			}
			else if (simpleAcceptance(cod1, cod2))
			{
				return 0;
			}
			else
			{
				std::vector<int> cod = cod1.at(0) || cod1.at(1) || cod1.at(2) || cod1.at(3) ? cod1 : cod2;
				float x;
				float y;

				if (cod.at(0)) // top
				{
					x = p1.x + ((p2.x - p1.x) * (getMaxy(clipWindow) - p1.y) / (p2.y - p1.y));
					y = getMaxy(clipWindow);
				}
				else if (cod.at(1)) // bottom
				{
					x = p1.x + ((p2.x - p1.x) * (getMiny(clipWindow) - p1.y) / (p2.y - p1.y));
					y = getMiny(clipWindow);
				}
				else if (cod.at(2)) // right
				{
					x = getMaxx(clipWindow);
					y = p1.y + ((p2.y - p1.y) * (getMaxx(clipWindow) - p1.x) / (p2.x - p1.x));
				}
				else if (cod.at(3)) // left
				{
					x = getMinx(clipWindow);
					y = p1.y + ((p2.y - p1.y) * (getMinx(clipWindow) - p1.x) / (p2.x - p1.x));
				}

				if (cod == cod1)
				{
					p1.x = x;
					p1.y = y;
					cod1 = computeCSCode(clipWindow, p1);
				}
				else
				{
					p2.x = x;
					p2.y = y;
					cod2 = computeCSCode(clipWindow, p2);
				}
			}
		}
	}
}