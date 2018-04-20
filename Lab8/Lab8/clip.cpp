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
				float v = -dotProduct(normals[i], d);
				if (v != 0)
				{
					float t = (dotProduct(normals[i], p1 - clipWindow[i])) / (v);
					if (v > 0)
					{
						te = std::max(te, t);
					}
					if (v < 0)
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
				p2 = p1 + d * te;
				p1 = p1 + d * tl;
				return 0;
			}
		}
		return - 1;
	}

	std::vector<int> computeCSCode(std::vector<vec3> clipWindow, const vec3 p)
	{
		std::vector<int> vec;
		return vec;
	}

	bool simpleRejection(std::vector<int> cod1, std::vector<int> cod2)
	{
		return false;
	}

	bool simpleAcceptance(std::vector<int> cod1, std::vector<int> cod2)
	{
		return false;
	}

	int lineClip_CohenSutherland(std::vector<vec3> clipWindow, vec3& p1, vec3& p2)
	{
		return -1;
	}
}