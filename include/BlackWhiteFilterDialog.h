#include <windows.h>
#include <commctrl.h>
#include <resource.h>
#include <vd2/VDXFrame/VideoFilterDialog.h>
#include <vd2/VDXFrame/VideoFilter.h>
#include <BlackWhiteFilterConfig.h>

#ifndef FILTER_VD_BLACK_WHITE_DIALOG
#define FILTER_VD_BLACK_WHITE_DIALOG

class BlackWhiteFilterDialog : public VDXVideoFilterDialog {
public:
	BlackWhiteFilterDialog(BlackWhiteFilterConfig& config, IVDXFilterPreview *ifp);
	bool Show(HWND parent);
	virtual INT_PTR DlgProc(UINT msg, WPARAM wParam, LPARAM lParam);

protected:
	IVDXFilterPreview *const mifp;

	bool OnInit();
	bool OnCommand(int cmd);
	void OnDestroy();

	void LoadFromConfig();
	bool SaveToConfig();

	BlackWhiteFilterConfig& mConfigNew;
	BlackWhiteFilterConfig mConfigOld;
};

#endif 