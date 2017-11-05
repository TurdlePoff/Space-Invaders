//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: "main.cpp"
// Description	: Implemention file for main
// Author		: Vivian Ngo
// Mail			: vivian.ngo7572@mediadesign.school.nz
//

//Local Includes
#include "game.h"
#include "resource.h"
#include "utils.h"
#include <windows.h>

#define WINDOW_CLASS_NAME L"BSENGGFRAMEWORK"

//global variables
HWND g_hDebugWindow, g_hScoreNameWindow;
CGame& g_rGame = CGame::GetInstance();

template<typename T>
std::wstring ToWideString(const T& _value)
{
	std::wstringstream theStream;
	theStream << _value << std::ends;
	return (theStream.str());
}

float ReadFromEditBox(HWND _hDlg, int _iResourceID)
{
	wchar_t _pcValue[10];
	ZeroMemory(_pcValue, 10);
	GetDlgItemText(_hDlg, _iResourceID, _pcValue, 10);
	if (_pcValue[0] == 0)
	{
		return 0.0f;
	}
	else
	{
		return static_cast<float>(_wtof(_pcValue));
	}
}

std::string ReadFromEditBoxToString(HWND _hDlg, int _iResourceID)
{
	wchar_t _pcValue[10];
	ZeroMemory(_pcValue, 10);
	GetDlgItemText(_hDlg, _iResourceID, _pcValue, 10);
	if (_pcValue[0] == 0)
	{
		return "";
	}
	else
	{
		std::string s = " ";
		for each(wchar_t& c in _pcValue)
		{
			s += c;
		}
		
		return s;
	}
}

void WriteToEditBox(HWND _hDlg, int _iResourceID, float _fValue)
{
	std::wstring _strValue = ToWideString(_fValue);
	SetDlgItemText(_hDlg, _iResourceID, _strValue.c_str());
}

LRESULT CALLBACK
WindowProc(HWND _hwnd, UINT _uiMsg, WPARAM _wParam, LPARAM _lParam)
{
	//level controller variables
	CLevel& m_rLevel = CGame::GetLevelInstance();

    switch (_uiMsg)
    {
		case WM_KEYDOWN:
		{
			switch (_wParam)
			{
			case VK_ESCAPE: //When player presses ESC button
			{
				if (g_rGame.GetGameState() == EGameState::GAME) //If the game state is in GAME mode
				{
					//Write all the current game variables into the dialog box
					WriteToEditBox(g_hDebugWindow, IDC_PMOVESPD, (m_rLevel.GetLevelController().GetLVLPlayerMovementSpeed()));
					WriteToEditBox(g_hDebugWindow, IDC_PBULSPD, m_rLevel.GetLevelController().GetLVLPlayerBulletSpeed());
					WriteToEditBox(g_hDebugWindow, IDC_EMOVESPD, m_rLevel.GetLevelController().GetLVLEnemyMoveDelay());
					WriteToEditBox(g_hDebugWindow, IDC_EBULSPD, m_rLevel.GetLevelController().GetLVLEnemyBulletSpeed());
					WriteToEditBox(g_hDebugWindow, IDC_ESHIPSPD, m_rLevel.GetLevelController().GetLVLEnemyShipSpeed());
					WriteToEditBox(g_hDebugWindow, IDC_EBULDELAY, m_rLevel.GetLevelController().GetLVLEnemyShootingDelay());

					ShowWindow(g_hDebugWindow, SW_NORMAL);
					g_rGame.SetPaused(true); //Pause the game when dialog box is open
				}
				break;
			}
			default:
				break;
			return (0);
			}
		}
		break;
        case WM_DESTROY:
        {
            PostQuitMessage(0);

            return(0);
        }
        break;

        default:
			break;
    } 

	if (g_rGame.GetGameState() == EGameState::LOST) //If the game state is in GAME mode
	{
		ShowWindow(g_hScoreNameWindow, SW_NORMAL);
	}

    return (DefWindowProc(_hwnd, _uiMsg, _wParam, _lParam));
}

//GET STUFF FROM DLG
LRESULT CALLBACK DebugDlgProc(HWND _hwnd,
	UINT _msg,
	WPARAM _wparam,
	LPARAM _lparam)
{
	CLevel& g_rLevel = CGame::GetLevelInstance();

	switch (_msg)
	{
		case WM_COMMAND:
		{

			switch (LOWORD(_wparam))
			{
				case IDOK:
				{
					//level stuff
					if (g_rGame.GetGameState() == EGameState::GAME)
					{
						g_rLevel.GetLevelController().SetLVLPlayerMovementSpeed(ReadFromEditBox(_hwnd, IDC_PMOVESPD));
						g_rLevel.GetLevelController().SetLVLPlayerBulletSpeed(ReadFromEditBox(_hwnd, IDC_PBULSPD));
						g_rLevel.GetLevelController().SetLVLPlayerInvincibility((IsDlgButtonChecked(g_hDebugWindow, IDC_PINV) == 1) ? true : false);

						g_rLevel.GetLevelController().SetLVLEnemyMoveDelay(ReadFromEditBox(_hwnd, IDC_EMOVEDELAY));
						g_rLevel.GetLevelController().SetLVLEnemyBulletSpeed(ReadFromEditBox(_hwnd, IDC_EBULSPD));
						g_rLevel.GetLevelController().SetLVLEnemyShipSpeed(ReadFromEditBox(_hwnd, IDC_ESHIPSPD));
						g_rLevel.GetLevelController().SetLVLEnemyShootingDelay(ReadFromEditBox(_hwnd, IDC_EBULDELAY));

						//GetLVLEnemyShootingDelay

						ShowWindow(_hwnd, SW_HIDE);
						g_rGame.SetPaused(false); //Unpause the game when dialog box is closed
					}
					return TRUE;
					break;
				}
				case IDCANCEL:
				{
					ShowWindow(_hwnd, SW_HIDE);
					g_rGame.SetPaused(false);  //Unpause the game when user cancels dialog changes
					return TRUE;
					break;
				}
				case IDC_RETURN: //When player clicks the main menu button in the dialog box, return to main menu
				{
					if (g_rGame.GetGameState() == EGameState::GAME) //If game mode is in GAME
					{
						g_rGame.SetGameState(EGameState::MENU); // Set gamestate to menu /switch to menu screen
						ShowWindow(_hwnd, SW_HIDE); 
						g_rGame.SetPaused(false); //Unpause the game and close dialog box when user returns to main menu
					}
					return TRUE;
					break;
				}
				default:
					break;
			}
			break;
		}
		case WM_CLOSE: //if user exits the dialog through the X button
		{
			ShowWindow(_hwnd, SW_HIDE); //hide dialog box and unpause
			g_rGame.SetPaused(false);
			return TRUE;
			break;
		}
	default:
		break;
	}
	return FALSE;
}


//GET STUFF FROM NAME DLG
LRESULT CALLBACK NameDlgProc(HWND _hwnd,
	UINT _msg,
	WPARAM _wparam,
	LPARAM _lparam)
{
	CLevel& g_rLevel = CGame::GetLevelInstance();

	switch (_msg)
	{
	case WM_COMMAND:
	{
		switch (LOWORD(_wparam))
		{
		case IDOK:
		{
			//level stuff
			//Check if player has lost instead of state OR send player to instructions 
			if (g_rGame.GetGameState() == EGameState::LOST)
			{
				g_rLevel.GetLevelController().SetLVLHighScoreName(ReadFromEditBoxToString(_hwnd, IDC_EDITNAME));
				
				g_rGame.SetPaused(false); //Unpause the game when dialog box is closed
				g_rGame.SetGameState(EGameState::HIGHSCORES);
				ShowWindow(_hwnd, SW_HIDE);
			}
			return TRUE;
			break;
		}
		
		default:
			break;
		}
		break;
	}
	//case WM_CLOSE: //if user exits the dialog through the X button
	//{
	//	ShowWindow(_hwnd, SW_HIDE); //hide dialog box and unpause
	//	g_rGame.SetPaused(false);
	//	return TRUE;
	//	break;
	//}
	default:
		break;
	}
	return FALSE;
}


HWND 
CreateAndRegisterWindow(HINSTANCE _hInstance, int _iWidth, int _iHeight, LPCWSTR _pcTitle)
{
    WNDCLASSEX winclass;

    winclass.cbSize = sizeof(WNDCLASSEX);
    winclass.style = CS_HREDRAW | CS_VREDRAW;
    winclass.lpfnWndProc = WindowProc;
    winclass.cbClsExtra = 0;
    winclass.cbWndExtra = 0;
    winclass.hInstance = _hInstance;
    winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    winclass.hbrBackground = static_cast<HBRUSH> (GetStockObject(WHITE_BRUSH));
    winclass.lpszMenuName = NULL;
    winclass.lpszClassName = WINDOW_CLASS_NAME;
    winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&winclass))
    {
        // Failed to register.
        return (0);
    }

    HWND hwnd; 
    hwnd = CreateWindowEx(NULL,
                  WINDOW_CLASS_NAME,
                  _pcTitle,
				  WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_VISIBLE, 
				  (GetSystemMetrics(SM_CXSCREEN) - _iWidth)/2, (GetSystemMetrics(SM_CYSCREEN) - _iHeight)/2, //Window position
                  _iWidth, _iHeight,
                  NULL,
                  NULL,
                  _hInstance,
                  NULL);
    
    if (!hwnd)
    {
        // Failed to create.
        return (0);
    }

    return (hwnd);
}

int WINAPI
WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdline, int _iCmdshow)
{
    MSG msg;
    ZeroMemory(&msg, sizeof(MSG));

    const int kiWidth = 1000;
    const int kiHeight = 800;

    HWND hwnd = CreateAndRegisterWindow(_hInstance, kiWidth, kiHeight, L"Vivian - Space Invaders");

	//Initialise debug window
	g_hDebugWindow = CreateDialog(_hInstance, MAKEINTRESOURCE(IDD_DEBUGWINDOW), hwnd, DebugDlgProc);
	g_hScoreNameWindow = CreateDialog(_hInstance, MAKEINTRESOURCE(IDD_NAMEBOX), hwnd, NameDlgProc);
    if (!g_rGame.Initialise(_hInstance, hwnd, kiWidth, kiHeight))
    {
        // Failed
        return (0);
    }

    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
			g_rGame.ExecuteOneFrame(); //HEREEEEEEEEEEEE is where the game stuff gets executed
        }
    }

    CGame::DestroyInstance();

    return (static_cast<int>(msg.wParam));
}
