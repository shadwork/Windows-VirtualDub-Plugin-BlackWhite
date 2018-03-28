#include <windows.h>

#ifndef FILTER_VD_BLACK_WHITE_CONFIG
#define FILTER_VD_BLACK_WHITE_CONFIG

class BlackWhiteFilterConfig {
public:
	BlackWhiteFilterConfig()
	{
		mTreshold = 128;
		mInvert = BST_UNCHECKED;
	}

public:
	int mTreshold;
	int mInvert;
};

#endif 