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

		viewTransformMatrix.at(0, 0) = (float)(width) / 2;
		viewTransformMatrix.at(1, 1) = (float)-(height) / 2;
		viewTransformMatrix.at(0, 3) = (float)startX + (width / 2);
		viewTransformMatrix.at(1, 3) = (float)startY + (height / 2);

		return viewTransformMatrix;
	}

	mat4 defineCameraMatrix(Camera myCamera)
	{
		mat4 cameraMatrix;

		vec3 w, u, v, tmp;

		w = myCamera.cameraPosition - myCamera.cameraTarget;
		w = w.normalize();	

		u = crossProduct(myCamera.cameraUp, w);
		u = u.normalize();

		v = crossProduct(w, u);

		mat4 mat1, mat2;

		mat1.at(0, 0) = u.x;
		mat1.at(0, 1) = u.y;
		mat1.at(0, 2) = u.z;
		mat1.at(1, 0) = v.x;
		mat1.at(1, 1) = v.y;
		mat1.at(1, 2) = v.z;
		mat1.at(2, 0) = w.x;
		mat1.at(2, 1) = w.y;
		mat1.at(2, 2) = w.z;

		mat2.at(0, 3) = -myCamera.cameraPosition.x;
		mat2.at(1, 3) = -myCamera.cameraPosition.y;
		mat2.at(2, 3) = -myCamera.cameraPosition.z;

		cameraMatrix = mat1 * mat2;

		return cameraMatrix;
	}

	mat4 definePerspectiveProjectionMatrix(float fov, float aspect, float zNear, float zFar)
	{
		mat4 perspectiveMatrix;

		perspectiveMatrix.at(0, 0) = (float)1 / (aspect * tan(fov / 2));
		perspectiveMatrix.at(1, 1) = (float)1 / tan(fov / 2);
		perspectiveMatrix.at(2, 2) = (float)(zFar + zNear) / (zNear - zFar);
		perspectiveMatrix.at(2, 3) = (float)(2 * zFar * zNear) / (zFar - zNear);
		perspectiveMatrix.at(3, 2) = 1;
		perspectiveMatrix.at(3, 3) = 0;

		return perspectiveMatrix;
	}

	void perspectiveDivide(vec4 &inputVertex)
	{
		inputVertex.x = inputVertex.x / inputVertex.w;
		inputVertex.y = inputVertex.y / inputVertex.w;
		inputVertex.z = inputVertex.z / inputVertex.w;
		inputVertex.w = inputVertex.w / inputVertex.w;
	}
}