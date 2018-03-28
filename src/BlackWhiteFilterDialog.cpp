#include <BlackWhiteFilterDialog.h>

BlackWhiteFilterDialog::BlackWhiteFilterDialog(IVDXFilterPreview *ifp):mifp(ifp){
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
		if (mifp)
			mifp->RedoFrame();
		return TRUE;
	}

	return FALSE;
}

bool BlackWhiteFilterDialog::OnInit() {
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
			EndDialog(mhdlg, true);
			return true;

		case IDCANCEL:
			EndDialog(mhdlg, false);
			return true;
		case IDC_PREVIEW:
			if (mifp)
				mifp->Toggle((VDXHWND)mhdlg);
			return true;
	}
	return false;
}