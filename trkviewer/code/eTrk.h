#pragma once
struct trk_header {
	char   header[8]; // MTRACK01
	int    SizeX;
	int    SizeY;
	int    Flats;
	int    Maps;
	int    Sprites;
	int    Borders;
	int    Meshes;
	char   pad[20];
	int    BackgroundMaps[4];
	char   _pad[24];
};

struct map_entry {
	char mapName[72];
};

struct flat_entry {
	int		MapID;
	int		Type;
	int		Orientation;
	short	BaseLevel;
	short	Height;
	char	pad[4];
};

struct sprite_entry {
	char	pad[4];
	int		IsFace;
	char	_pad[4];
	int     PosX;
	int		PosY;
	int		PosZ;
	int     ScaleX;
	int     ScaleY;
	char    __pad[8];
	int     Angle;
	char    ___pad[4];
	int     MapID;
};

struct border_entry {
	char   pad[4];
	int    Type;
	int    PosX;
	int    PosZ;
	int    PosX2;
	int    PosZ2;
	int    Top;
	int    Bottom;
	char   _pad[4];
};

struct mesh_entry {
	char  Name[64];
	char  pad[4];
	int   PosX;
	int   PosY;
	int   PosZ;
	int   ScaleX;
	int   ScaleY;
	int   ScaleZ;
	char  _pad[4];
	int   AngleY;
	char  __pad[8];

};

struct light_data {
	float Red;
	float Green;
	float Blue;
	int   X;
	int   Y;
	int   Z;
};


enum eFlatRotation {
	ROTATION_0,
	ROTATION_90,
	ROTATION_180,
	ROTATION_270
};

enum eFlatTypes {
	FLAT,
	TYPE_1,
	SLOPE,
	CORNER_1,
	CORNER_2
};