#include "clip.h"

int main()
{
	std::vector<egc::vec3> edges;
	edges.push_back(egc::vec3(0, 1, 0));
	edges.push_back(egc::vec3(0, 0, 0));
	edges.push_back(egc::vec3(1, 0, 0));
	edges.push_back(egc::vec3(1, 1, 0));
	egc::vec3 v1 = egc::vec3(-1, 0.5, 0);
	egc::vec3 v2 = egc::vec3(2, 0.5, 0);
	lineClip_CyrusBeck(edges, v1, v2);

	return 0;
}

