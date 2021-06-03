#pragma once
#include <vector>
#include "eTrk.h"

class eTrkParser {
private:
public:
	std::vector<map_entry> vMaps;
	std::vector<mesh_entry> vMeshes;
	std::vector<sprite_entry> vSprites;
	std::vector<border_entry> vBorders;
	std::vector<flat_entry> vFlats;
	std::vector<int>        pFlats;
	light_data   pLight;
	trk_header   pTrack;
	bool ParseFile(char* file);
	void SetupWorld();
	void GenerateFlats();
	void GenerateMeshes();
};