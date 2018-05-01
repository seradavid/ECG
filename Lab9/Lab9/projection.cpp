//
//  projection.cpp
//  Lab8_TODO
//
//  Copyright © 2016 CGIS. All rights reserved.
//

#include "projection.h"

namespace egc {
	mat4 defineViewTransformMatrix(int startX, int startY, int width, int height)
	{
		mat4 viewTransformMatrix;

		viewTransformMatrix.at(0, 0) = (startX + width) / 2;
		viewTransformMatrix.at(1, 1) = (startY + height) / 2;
		viewTransformMatrix.at(0, 3) = (startX + width) / 2;
		viewTransformMatrix.at(1, 3) = (startY + height) / 2;

		return viewTransformMatrix;
	}

	mat4 defineCameraMatrix(Camera myCamera)
	{
		mat4 cameraMatrix;



		return cameraMatrix;
	}

	mat4 definePerspectiveProjectionMatrix(float fov, float aspect, float zNear, float zFar)
	{
		mat4 perspectiveMatrix;

		return perspectiveMatrix;
	}

	void perspectiveDivide(vec4 &inputVertex)
	{

	}
}