#include <BlackWhiteFilter.h>

uint32 BlackWhiteFilter::GetParams() {
	if (g_VFVAPIVersion >= 12) {
		switch (fa->src.mpPixmapLayout->format) {
		case nsVDXPixmap::kPixFormat_XRGB8888:
			break;
		default:
			return FILTERPARAM_NOT_SUPPORTED;
		}
	}

	fa->dst.offset = 0;
	return FILTERPARAM_SWAP_BUFFERS | FILTERPARAM_PURE_TRANSFORM;
}

void BlackWhiteFilter::Start() {
	// Do here some check before filter running, detect SSE or AMD64 for example
}

void BlackWhiteFilter::Run() {
	if (g_VFVAPIVersion >= 12) {
		const VDXPixmap& pxdst = *fa->dst.mpPixmap;
		const VDXPixmap& pxsrc = *fa->src.mpPixmap;

		switch (pxdst.format) {
		case nsVDXPixmap::kPixFormat_XRGB8888:
			ToBlackAndWhite(pxdst.data, pxdst.pitch, pxsrc.data, pxsrc.pitch, pxsrc.w, pxsrc.h);
			break;
		}
	}
	else {
		ToBlackAndWhite(fa->dst.data, fa->dst.pitch, fa->src.data, fa->src.pitch, fa->dst.w, fa->dst.h);
	}
}

void BlackWhiteFilter::ToBlackAndWhite(void *dst0, ptrdiff_t dstpitch, const void *src0, ptrdiff_t srcpitch, uint32 w, uint32 h) {
	char *dst = (char *)dst0;
	const char *src = (const char *)src0;
	for (uint32 y = 0; y<h; ++y) {
		// Get scanline
		uint32 *srcline = (uint32 *)src;
		uint32 *dstline = (uint32 *)dst;
		for (uint32 x = 0; x<w; ++x) {
			// Process pixels
			uint32 data = srcline[x];
			float gray = 0.299f * (data & 0x000000ff) + 0.587f * ((data & 0x0000ff00) >> 8) + 0.114f *((data & 0x00ff0000) >> 16);
			dstline[x] = gray < 128 ? 0x00000000 : 0x00ffffff;
		}
		src += srcpitch;
		dst += dstpitch;
	}
}