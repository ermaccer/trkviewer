#include "eApp.h"
#include <xors3d.h>

void eApp::Init()
{
	xAppTitle("trkviewer");
	xSetEngineSetting("Splash::TilingTime", "0");
	xSetEngineSetting("Splash::AfterTilingTime", "0");
	xSetEngineSetting("LoadMesh::RelativePaths", "false");
	Begin3D();
}

void eApp::Begin3D()
{
	xGraphics3D(1280, 720, 32, false, true);
}

unsigned char eApp::CovertColorToChar(float color)
{
	return (unsigned char)(color * 255.0f);
}
