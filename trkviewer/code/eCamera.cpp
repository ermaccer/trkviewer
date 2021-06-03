#include "ECamera.h"
#include <iostream>
#include <xors3d.h>
#include "eCamera.h"


eCamera TheCamera;

float CurveValue(float newvalue, float oldvalue, float increments)
{
	if (increments >  1.0f) oldvalue = oldvalue - (oldvalue - newvalue) / increments;
	if (increments <= 1.0f) oldvalue = newvalue;
	return oldvalue;
}


void eCamera::Initialize()
{
	iCameraInstance = xCreateCamera();
	iCameraPivot = xCreatePivot();
	iCameraMode = CAMERA_MODE_FREE;

	xCameraEnableShadows(iCameraInstance);

	xCameraRange(iCameraInstance, 0.1, 3000.0);

	xEntityParent(iCameraInstance, iCameraPivot);
	iCameraListener = xCreateListener(iCameraInstance);

}

void eCamera::UpdateCamera()
{
	xResetEntity(iCameraInstance);
	cameraMatrix = (D3DMATRIX*)xGetEntityMatrix(iCameraInstance);

	if (iCameraMode == CAMERA_MODE_FREE)
	{
		// init camera variables
		static float mxs = 0;
		static float mys = 0;
		static float camxa = 0;
		static float camya = 0;
		static float mousespeed = 0.5;
		static float camerasmoothness = 4.5;

		// process movement
		mxs = CurveValue(xMouseXSpeed() / 2 * mousespeed, mxs, camerasmoothness);
		mys = CurveValue(xMouseYSpeed() / 2 * mousespeed, mys, camerasmoothness);

		camxa = fmodf(camxa - mxs, 360.0f);
		camya = camya + mys;

		xMoveMouse(xGraphicsWidth() / 2, xGraphicsHeight() / 2);
		xRotateEntity(iCameraPivot, camya, camxa, 0.0);

		if (xKeyDown(xKEY_W)) xMoveEntity(iCameraPivot, 0, 0, 1);
		if (xKeyDown(xKEY_S)) xMoveEntity(iCameraPivot, 0, 0, -1);
		if (xKeyDown(xKEY_A)) xMoveEntity(iCameraPivot, -1, 0, 0);
		if (xKeyDown(xKEY_D)) xMoveEntity(iCameraPivot, 1, 0, 0);

	}
	else if (iCameraMode == CAMERA_MODE_VEHICLE)
	{

	}
	else if (iCameraMode == CAMERA_MODE_VEHICLE_FREE)
	{
		xPositionEntity(iCameraListener, 0, 0, 7);
		// init camera variables
		static float mxs = 0;
		static float mys = 0;
		static float camxa = 0;
		static float camya = 0;
		static float mousespeed = 0.5;
		static float camerasmoothness = 4.5;

		//xEntityParent(iCameraPivot, TheGame->FindPlayerEntity()->pModelPivot);
		xPositionEntity(iCameraPivot, 0, 0, -5.55f);

		mxs = CurveValue(xMouseXSpeed() / 2 * mousespeed, mxs, camerasmoothness);
		mys = CurveValue(xMouseYSpeed() / 2 * mousespeed, mys, camerasmoothness);

		camxa = fmodf(camxa - mxs, 360.0f);
		camya = camya + mys;

		xMoveMouse(xGraphicsWidth() / 2, xGraphicsHeight() / 2);
		//xRotateEntity(TheGame->FindPlayerEntity()->pModelPivot, camya, camxa, 0.0);
	}
	else if (iCameraMode == CAMERA_MODE_INSIDE)
	{
		xPositionEntity(iCameraListener, 0, 0, 0);
		// init camera variables
		static float mxs = 0;
		static float mys = 0;
		static float camxa = 0;
		static float camya = 0;
		static float mousespeed = 0.5;
		static float camerasmoothness = 4.5;

		//xEntityParent(iCameraPivot, TheGame->FindPlayerEntity()->mModel);
		xPositionEntity(iCameraPivot, -0.2f, 0.55f, -0.30f);

		mxs = CurveValue(xMouseXSpeed() / 2 * mousespeed, mxs, camerasmoothness);
		mys = CurveValue(xMouseYSpeed() / 2 * mousespeed, mys, camerasmoothness);

		camxa = fmodf(camxa - mxs, 360.0f);
		camya = camya + mys;

		xMoveMouse(xGraphicsWidth() / 2, xGraphicsHeight() / 2);
		//xRotateEntity(TheGame->FindPlayerEntity()->pModelPivot, camya, camxa, 0.0);
	}

}

void eCamera::SetCameraMode(int mode)
{
	xResetEntity(iCameraPivot);
//	Frontend->SetHelpMessage("Camera set!");
	iCameraMode = mode;
}

int eCamera::GetCameraInstance()
{
	return iCameraInstance;
}

int eCamera::GetCameraPivot()
{
	return iCameraPivot;
}

D3DMATRIX * eCamera::GetCameraMatrix()
{
	return cameraMatrix;
}
