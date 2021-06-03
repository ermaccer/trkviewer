// trkviewer.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "trkviewer.h"
#include <xors3d.h>
#include <iostream>
#include "code/eApp.h"
#include "code/eCamera.h"
#include "code/eWorld.h"
#include "code/eTrk.h"
#include "code/eTrkParser.h"
#include "code/eCamera.h"
#include <CommCtrl.h>
#include <shlobj.h>
#include <Windows.h>
#include <commdlg.h>

const char * SetSavePathFromButton(const char * filter, const char* ext, HWND hWnd)
{
	char szBuffer[MAX_PATH] = {};
	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFilter = (LPCSTR)filter;
	ofn.lpstrFile = (LPSTR)szBuffer;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = (LPCSTR)ext;
	if (GetOpenFileName(&ofn))
	{
		return szBuffer;
	}
	else
		return nullptr;
}

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	eApp::Init();

	std::string path = SetSavePathFromButton("PolEngine Track (*.trk)\0*.trk\0All Files (*.*)\0*.*\0", "trk", 0);
	if (path.length() > 0)
	{
		eTrkParser trk;
		TheCamera.Initialize();
		trk.ParseFile((char*)path.c_str());
		trk.SetupWorld();
		trk.GenerateFlats();
		trk.GenerateMeshes();



		while (!(xKeyHit(KEY_ESCAPE) || xWinMessage("WM_CLOSE")))
		{
			TheCamera.UpdateCamera();
			xRenderWorld();
			xText(10, 10, "TRKViewer Alpha");

			xFlip();
		}
	}
	
	return 0;
}