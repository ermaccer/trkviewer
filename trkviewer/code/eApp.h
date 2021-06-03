#pragma once

struct RGB {
	char r, g, b;
};

class eApp {
public:
	static void Init();
	static void Begin3D();
	static unsigned char CovertColorToChar(float color);
};