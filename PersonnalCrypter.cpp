#include "PersonnalCrypter.h"

File file;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hDlg;
	MSG uMsg;

	hDlg = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, (DLGPROC)DlgProc);

    ShowWindow(hDlg, nCmdShow);
	UpdateWindow(hDlg);
	SetFocus(hDlg);

	while(GetMessage(&uMsg, NULL, 0, 0))
	{
		TranslateMessage(&uMsg);
		DispatchMessage(&uMsg);
	}

	return uMsg.wParam;
}


LRESULT CALLBACK DlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HWND DlgControl;
	PAINTSTRUCT ps;
	OPENFILENAME open_params = {0};
	char file_path[MAX_CHARS];
	char password[MAX_CHARS];

	switch(uMsg)
    {
		case WM_INITDIALOG:
			SetWindowPos(hDlg, HWND_TOP, 320, 240, 0, 0, SWP_NOSIZE);
			DlgControl = GetDlgItem(hDlg, IDC_PASSWORD);
			SendMessage(DlgControl, WM_SETTEXT, 0, (LONG) (LPSTR) "<Mot de passe : entre 8 et 56 caractères>");
			DlgControl = GetDlgItem(hDlg, IDC_PATH);
			SendMessage(DlgControl, WM_SETTEXT, 0, (LONG) (LPSTR) "<Chemin complet du fichier à crypter ou décrypter>");
			DlgControl = GetDlgItem(hDlg, IDC_INFO_TEXT);
			SendMessage(DlgControl, WM_SETTEXT, 0, (LONG) (LPSTR) "Veuillez sélectionner un fichier à crypter ou décrypter en appuyant sur le bouton <...>");
			break;
		case WM_PAINT:
			BeginPaint(hDlg, &ps);
			EndPaint(hDlg, &ps);
		    break;
		case WM_COMMAND:
			{
				switch(LOWORD(wParam))
				{
				case ID_CRYPT:
					{
						DlgControl = GetDlgItem(hDlg, IDC_PASSWORD);
						SendMessage(DlgControl, WM_GETTEXT, MAX_CHARS, (LONG) (LPSTR) password);
						
						DlgControl = GetDlgItem(hDlg, IDC_INFO_TEXT);
						if(!strlen(password))
						{
							SendMessage(DlgControl, WM_SETTEXT, 0, (LONG) (LPSTR) "Vous devez obligatoirement entrer un mot de passe et il doit être compris entre 8 et 56 caractères!");
						}
						else if((strlen(password) < 8) || (strlen(password) > 56))
						{
							SendMessage(DlgControl, WM_SETTEXT, 0, (LONG) (LPSTR) "Le mot de passe doit être compris entre 8 et 56 caractères!");
						}
						else
						{
							SendMessage(DlgControl, WM_SETTEXT, 0, (LONG) (LPSTR) "Cryptage en cours...");

							switch(file.Crypt())
							{
							case FALSE:
								SendMessage(DlgControl, WM_SETTEXT, 0, (LONG) (LPSTR) "Erreur de cryptage!");
								break;
							case TRUE:
								SendMessage(DlgControl, WM_SETTEXT, 0, (LONG) (LPSTR) "Fichier crypté.");
								break;
							case FILE_NOT_FOUND_OR_OPENING_ERROR:
								SendMessage(DlgControl, WM_SETTEXT, 0, (LONG) (LPSTR) "Erreur de lecture ou d'ouverture de fichier!");
								break;
							case FILE_CRYPT_ERROR:
								SendMessage(DlgControl, WM_SETTEXT, 0, (LONG) (LPSTR) "Erreur de cryptage!");
								break;
							case FILE_OPENNING_ERROR:
								SendMessage(DlgControl, WM_SETTEXT, 0, (LONG) (LPSTR) "Erreur d'ouverture de fichier!");
								break;
							case FILE_SAVING_ERROR:
								SendMessage(DlgControl, WM_SETTEXT, 0, (LONG) (LPSTR) "Erreur de sauvegarde de fichier!");
								break;
							default:
								break;
							}
						}
						break;
					}
				case ID_UNCRYPT:
					{
						DlgControl = GetDlgItem(hDlg, IDC_PASSWORD);
						SendMessage(DlgControl, WM_GETTEXT, MAX_CHARS, (LONG) (LPSTR) password);

						DlgControl = GetDlgItem(hDlg, IDC_INFO_TEXT);
						if(!strlen(password))
						{
							SendMessage(DlgControl, WM_SETTEXT, 0, (LONG) (LPSTR) "Vous devez obligatoirement entrer un mot de passe et il doit être compris entre 8 et 56 caractères!");
						}
						else if((strlen(password) < 8) || (strlen(password) > 56))
						{
							SendMessage(DlgControl, WM_SETTEXT, 0, (LONG) (LPSTR) "Le mot de passe doit être compris entre 8 et 56 caractères!");
						}
						else
						{
							SendMessage(DlgControl, WM_SETTEXT, 0, (LONG) (LPSTR) "Décryptage en cours...");

							switch(file.Uncrypt())
							{
							case FALSE:
								SendMessage(DlgControl, WM_SETTEXT, 0, (LONG) (LPSTR) "Erreur de décryptage!");
								break;
							case TRUE:
								SendMessage(DlgControl, WM_SETTEXT, 0, (LONG) (LPSTR) "Fichier décrypté.");
								break;
							case FILE_NOT_FOUND_OR_OPENING_ERROR:
								SendMessage(DlgControl, WM_SETTEXT, 0, (LONG) (LPSTR) "Erreur de lecture ou d'ouverture de fichier!");
								break;
							case BAD_CRYPTED_FILE_FORMAT:
								SendMessage(DlgControl, WM_SETTEXT, 0, (LONG) (LPSTR) "Fichier non crypter par PersonnalCrypter!");
								break;
							case FILE_UNCRYPT_ERROR:
								SendMessage(DlgControl, WM_SETTEXT, 0, (LONG) (LPSTR) "Erreur de décryptage!");
								break;
							case FILE_OPENNING_ERROR:
								SendMessage(DlgControl, WM_SETTEXT, 0, (LONG) (LPSTR) "Erreur d'ouverture de fichier!");
								break;
							case FILE_SAVING_ERROR:
								SendMessage(DlgControl, WM_SETTEXT, 0, (LONG) (LPSTR) "Erreur de sauvegarde de fichier!");
								break;
							default:
								break;
							}
						}
						break;
					}
				case IDC_OPEN:
					{
						FillOpenParams(open_params, hDlg, file_path);

						if(GetOpenFileName(&open_params))
						{
							file = File(file_path);
							DlgControl = GetDlgItem(hDlg, IDC_PATH);
							SendMessage(DlgControl, WM_SETTEXT, 0, (LONG) (LPSTR) file_path);
							DlgControl = GetDlgItem(hDlg, IDC_INFO_TEXT);
							SendMessage(DlgControl, WM_SETTEXT, 0, (LONG) (LPSTR) "Entrez un mot de passe compris entre 8 et 56 caractères, puis appuyez sur <crypter> ou <décrypter>");
						}
						break;
					}
				}
				break;
			}
		case WM_CLOSE:
		case WM_DESTROY:
			{
				PostQuitMessage(0);
				break;
			}
        default:
			break;
    }

	return false;
}


void FillOpenParams(OPENFILENAME &open_params, HWND hDlg, char* file_path)
{
	ZeroMemory(&open_params, sizeof(open_params));
	open_params.lStructSize = sizeof(OPENFILENAME);
	open_params.hwndOwner = hDlg;
	open_params.lpstrFile = file_path;
	open_params.lpstrFile[0] = '\0';
	open_params.nMaxFile = MAX_CHARS;
	open_params.lpstrFilter = "Tous les fichiers (*.*)\0*.*\0";
	open_params.nFilterIndex = 1;
	open_params.lpstrFileTitle = NULL;
	open_params.nMaxFileTitle = 0;
	open_params.lpstrInitialDir = NULL;
	open_params.lpstrTitle = "Veuillez sélectionner un fichier à crypter ou à décrypter";
	open_params.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
}