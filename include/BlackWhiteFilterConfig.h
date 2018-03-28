#ifndef FILTER_VD_BLACK_WHITE_CONFIG
#define FILTER_VD_BLACK_WHITE_CONFIG

class BlackWhiteFilterConfig {
public:
	BlackWhiteFilterConfig()
	{
		mTreshold = 128;
		mInvert = 0;
	}

public:
	int mTreshold;
	int mInvert;
};

#endif 