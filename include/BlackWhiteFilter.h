#include <vd2/VDXFrame/VideoFilter.h>
#include <vd2/VDXFrame/VideoFilterEntry.h>

#ifndef FILTER_VD_BLACK_WHITE
#define FILTER_VD_BLACK_WHITE

extern int g_VFVAPIVersion;

class BlackWhiteFilter : public VDXVideoFilter {
public:
	virtual uint32 GetParams();
	virtual void Start();
	virtual void Run();

protected:
	void ToBlackAndWhite(void *dst, ptrdiff_t dstpitch, const void *src, ptrdiff_t srcpitch, uint32 w, uint32 h);
};

#endif 
