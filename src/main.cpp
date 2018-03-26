#include <vd2/VDXFrame/VideoFilter.h>
#include <BlackWhiteFilter.h>

VDXFilterDefinition filterDef_blackWhite = VDXVideoFilterDefinition<BlackWhiteFilter>("Shadwork", "Black White filter", "Example for VirtualDub Plugin SDK: Applies a Black White filter to video.");

VDX_DECLARE_VIDEOFILTERS_BEGIN()
	VDX_DECLARE_VIDEOFILTER(filterDef_blackWhite)
VDX_DECLARE_VIDEOFILTERS_END()

VDX_DECLARE_VFMODULE()