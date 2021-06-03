#pragma once
#include <d3d9.h>

enum eCameraModes {
	CAMERA_MODE_FREE,
	CAMERA_MODE_VEHICLE,
	CAMERA_MODE_VEHICLE_FREE,
	CAMERA_MODE_INSIDE
};

class eCamera {
private:
	D3DMATRIX* cameraMatrix;
	int        iCameraMode;
	int        iCameraInstance;
	int        iCameraPivot;
	int        iCameraListener;
public:
	void Initialize();
	void UpdateCamera();
	void SetCameraMode(int mode);
	int  GetCameraInstance();
	int  GetCameraPivot();
	D3DMATRIX* GetCameraMatrix();
};


extern eCamera TheCamera;