#include <BlackWhiteFilterDialog.h>

BlackWhiteFilterDialog::BlackWhiteFilterDialog(BlackWhiteFilterConfig& config, IVDXFilterPreview *ifp):mifp(ifp), mConfigNew(config){
}

bool BlackWhiteFilterDialog::Show(HWND parent) {
	return 0 != VDXVideoFilterDialog::Show(NULL, MAKEINTRESOURCE(IDD_DIALOG_BLACKWHITE_SETTING), parent);
};

INT_PTR BlackWhiteFilterDialog::DlgProc(UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_INITDIALOG:
		return !OnInit();

	case WM_DESTROY:
		OnDestroy();
		break;

	case WM_COMMAND:
		if (OnCommand(LOWORD(wParam)))
			return TRUE;
		break;

	case WM_HSCROLL:
		if (mifp && SaveToConfig())
			mifp->RedoFrame();
		return TRUE;
	}

	return FALSE;
}

bool BlackWhiteFilterDialog::OnInit() {
	mConfigOld = mConfigNew;
	// Set up slider to range 0-255
	SendDlgItemMessage(mhdlg, IDC_SLIDER_THRESHOLD, TBM_SETRANGE, TRUE, MAKELONG(0, 255));
	LoadFromConfig();
	// gain focus to slide control
	HWND hwndFirst = GetDlgItem(mhdlg, IDC_SLIDER_THRESHOLD);
	if (hwndFirst)
		SendMessage(mhdlg, WM_NEXTDLGCTL, (WPARAM)hwndFirst, TRUE);
	// init preview button
	HWND hwndPreview = GetDlgItem(mhdlg, IDC_PREVIEW);
	if (hwndPreview && mifp) {
		EnableWindow(hwndPreview, TRUE);
		mifp->InitButton((VDXHWND)hwndPreview);
	}
	return false;
}

void BlackWhiteFilterDialog::OnDestroy() {
	if (mifp)
		mifp->InitButton(NULL);
}

bool BlackWhiteFilterDialog::OnCommand(int cmd) {
	switch (cmd) {
		case IDOK:
			SaveToConfig();
			EndDialog(mhdlg, true);
			return true;
		case IDCANCEL:
			mConfigNew = mConfigOld;
			EndDialog(mhdlg, false);
			return true;
		case IDC_PREVIEW:
			if (mifp)
				mifp->Toggle((VDXHWND)mhdlg);
			return true;
		case IDC_CHECK_INVERTED:
			if (mifp && SaveToConfig())
				mifp->RedoFrame();
			return true;
	}
	return false;
}

void BlackWhiteFilterDialog::LoadFromConfig() {
	SendDlgItemMessage(mhdlg, IDC_SLIDER_THRESHOLD, TBM_SETPOS, TRUE, mConfigNew.mTreshold);
	SendMessage(mhdlg, IDC_CHECK_INVERTED, mConfigNew.mInvert, 0);
}

bool BlackWhiteFilterDialog::SaveToConfig() {
	int threshold = SendDlgItemMessage(mhdlg, IDC_SLIDER_THRESHOLD, TBM_GETPOS, 0, 0);
	int inverted = SendDlgItemMessage(mhdlg, IDC_CHECK_INVERTED, BM_GETCHECK, 0, 0);

	if (threshold != mConfigNew.mTreshold || inverted!= mConfigNew.mInvert)
	{
		mConfigNew.mTreshold = threshold;
		mConfigNew.mInvert = inverted;
		return true;
	}
	return false;
}