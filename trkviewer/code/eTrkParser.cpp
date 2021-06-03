#include "eTrkParser.h"
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <xors3d.h>
#include "eApp.h"

bool eTrkParser::ParseFile(char * file)
{
	std::ifstream pFile(file, std::ifstream::binary);

	if (!pFile)
	{
		MessageBoxA(0, file, "Failed to open", MB_ICONERROR);
		return false;
	}

	if (pFile)
	{
		trk_header trk;
		pFile.read((char*)&trk, sizeof(trk_header));

		if (strcmp(trk.header, "MTRACK01") == 0)
		{
			MessageBoxA(0, "Not a valid TRK file!", 0, MB_ICONERROR);
			return false;
		}
		else
		{
			pTrack = trk;

			for (int i = 0; i < trk.Maps; i++)
			{
				map_entry map;
				pFile.read((char*)&map, sizeof(map_entry));
				vMaps.push_back(map);
			}

			pFile.seekg(-4, pFile.cur);

			for (int i = 0; i < trk.Flats; i++)
			{
				flat_entry flat;
				pFile.read((char*)&flat, sizeof(flat_entry));
				vFlats.push_back(flat);
			}

			pFile.seekg(-4, pFile.cur);
			for (int i = 0; i < trk.Sprites; i++)
			{
				sprite_entry sprite;
				pFile.read((char*)&sprite, sizeof(sprite_entry));
				vSprites.push_back(sprite);
			}

			for (int i = 0; i < trk.Borders; i++)
			{
				border_entry border;
				pFile.read((char*)&border, sizeof(border_entry));
				vBorders.push_back(border);
			}
			pFile.seekg(4, pFile.cur);

			for (int i = 0; i < trk.Meshes; i++)
			{
				mesh_entry mesh;

				pFile.read((char*)&mesh, sizeof(mesh_entry));
				vMeshes.push_back(mesh);
			}

			int unk[2];

			pFile.read((char*)&unk, sizeof(unk));

			light_data light;
			pFile.read((char*)&light, sizeof(light_data));
			pLight = light;

			char pad[36];

			pFile.read((char*)&pad, sizeof(pad));
		}
		

	}

}

void eTrkParser::SetupWorld()
{
	unsigned char r = eApp::CovertColorToChar(pLight.Red);
	unsigned char g = eApp::CovertColorToChar(pLight.Green);
	unsigned char b = eApp::CovertColorToChar(pLight.Blue);
	xAmbientLight(r,g,b);
}

void eTrkParser::GenerateFlats()
{
	int curX = 0;
	int curY = 0;
	int curZ = 0;
	float sizeX = 0;
	float sizeY = 0;
	float sizeZ = 0;

	// generate blocks
	for (int i = 0; i < pTrack.SizeY; i++)
	{
		for (int k = 0; k < pTrack.SizeX; k++)
		{
			int pCube = xCreateCube();
			xScaleEntity(pCube,5, 5,5);
			
			sizeX = xEntityScaleX(pCube);
			sizeY = xEntityScaleY(pCube);
			sizeZ = xEntityScaleZ(pCube);
		
	
			xScaleEntity(pCube, sizeX, 0.0, sizeY);

			xPositionEntity(pCube, curX + sizeX, curY, curZ + sizeZ);
			//xEntityColor(pCube, rand() % 255, rand() % 255, rand() % 255);
			curX += sizeX * 2;
			pFlats.push_back(pCube);
		}
		curX = 0;
		curZ += sizeZ * 2;
	}

	//int cone = xCreateCone();
	//xPositionEntity(cone, 0, 0, 0);

	// setup block data

	for (int i = 0; i < pFlats.size(); i++)
	{
		float angle = 0;

		switch (vFlats[i].Orientation)
		{
		case ROTATION_0:
			angle = 0;
			break;
		case ROTATION_90:
			angle = 90;
			break;
		case ROTATION_180:
			angle = 180;
			break;
		case ROTATION_270:
			angle = 270;
			break;
		}


		int texture = xLoadTexture(vMaps[vFlats[i].MapID].mapName);
		xRotateEntity(pFlats[i], 0.0, 360 - angle, 0.0);
		xEntityTexture(pFlats[i], texture);
		float x = xEntityX(pFlats[i]);
		float y = xEntityY(pFlats[i]);
		float z = xEntityZ(pFlats[i]);
		y = vFlats[i].BaseLevel * 0.1;
		y += vFlats[i].Height  / 2 * 0.1;
		xPositionEntity(pFlats[i],x, y, z);






		switch (vFlats[i].Type)
		{
		case SLOPE:
			//xRotateEntity(pFlats[i], (360 - (vFlats[i].Height / 2)), 360 - angle, 0.0);
			//y -= vFlats[i].BaseLevel * 0.1;
			
		//	xPositionEntity(pFlats[i], x, y, z);
			break;
		case CORNER_1:
			break;
		case CORNER_2:
			break;
		}
		


	}
		
}

void eTrkParser::GenerateMeshes()
{
	for (int i = 0; i < vMeshes.size(); i++)
	{
		int mesh = xLoadMesh(vMeshes[i].Name);
		float x = (float)vMeshes[i].PosX * 0.1;
		float y = (float)vMeshes[i].PosY * 0.1;
		float z = (float)vMeshes[i].PosZ * 0.1;

		xPositionEntity(mesh, x,y,z);
		xRotateEntity(mesh, 0, 360 - vMeshes[i].AngleY, 0);
		xScaleEntity(mesh, vMeshes[i].ScaleX * 0.01 , vMeshes[i].ScaleX* 0.01, vMeshes[i].ScaleX* 0.01);
	}

	// sky
}

