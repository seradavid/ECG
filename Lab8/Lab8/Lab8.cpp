#include "clip.h"

int main()
{
	std::vector<egc::vec3> edges;
	edges.push_back(egc::vec3(1, 2, 0));
	edges.push_back(egc::vec3(1, 1, 0));
	edges.push_back(egc::vec3(3, 1, 0));
	edges.push_back(egc::vec3(3, 2, 0));
	egc::vec3 v1 = egc::vec3(2, 4, 0);
	egc::vec3 v2 = egc::vec3(2, 0, 0);
	//lineClip_CyrusBeck(edges, v1, v2);
	//lineClip_CohenSutherland(edges, v1, v2);

	std::cout << "v1: " << v1 << std::endl;
	std::cout << "v2: " << v2 << std::endl;

	std::getchar();

	return 0;
}

