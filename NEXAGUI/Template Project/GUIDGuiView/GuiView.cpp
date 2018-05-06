
// GuiViewD.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "GuiView.h"
#include "GuiViewDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGuiViewApp

BEGIN_MESSAGE_MAP(CGuiViewApp, CWinApp)
// Start TSDV-HoangPQ 20150822\ - Fix bug No.9: Prevent F1 button
#if 0
     ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
#endif
// End TSDV-HoangPQ 20150822
END_MESSAGE_MAP()


// CGuiViewApp construction

CGuiViewApp::CGuiViewApp() : CWinApp()
{
    // TODO: add construction code here,
    // Place all significant initialization in InitInstance
// Start TrungLV 20150820
    m_bShowCursor = FALSE;
// End TrungLV 20150820
}


// The one and only CGuiViewApp object

CGuiViewApp theApp;


// CGuiViewApp initialization

BOOL CGuiViewApp::InitInstance()
{
    // InitCommonControlsEx() is required on Windows XP if an application
    // manifest specifies use of ComCtl32.dll version 6 or later to enable
    // visual styles.  Otherwise, any window creation will fail.
    INITCOMMONCONTROLSEX InitCtrls;
    InitCtrls.dwSize = ( DWORD ) sizeof(InitCtrls);
    // Set this to include all the common control classes you want to use
    // in your application.
    InitCtrls.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&InitCtrls);

    CWinApp::InitInstance();

// Start TrungLV 20150820
    // Load setting file
    LoadInitFile( );
    ShowCursor( m_bShowCursor );
// End TrungLV 20150820
    AfxEnableControlContainer();

    // Create the shell manager, in case the dialog contains
    // any shell tree view or shell list view controls.
    //CShellManager *pShellManager = new CShellManager;

    // Activate "Windows Native" visual manager for enabling themes in MFC controls
    CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

    // Standard initialization
    // If you are not using these features and wish to reduce the size
    // of your final executable, you should remove from the following
    // the specific initialization routines you do not need
    // Change the registry key under which our settings are stored
    // TODO: You should modify this string to be something appropriate
    // such as the name of your company or organization
    SetRegistryKey(_T("Local AppWizard-Generated Applications"));

    CGuiViewDlg dlg;
    m_pMainWnd = &dlg;
    INT_PTR nResponse = dlg.DoModal();
    if (nResponse == IDOK)
    {
        // TODO: Place code here to handle when the dialog is
        //  dismissed with OK
    }
    else if (nResponse == IDCANCEL)
    {
        // TODO: Place code here to handle when the dialog is
        //  dismissed with Cancel
    }
    else if (nResponse == -1)
    {
        TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
        TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
    }

    // Delete the shell manager created above.
    //delete pShellManager;

    // Since the dialog has been closed, return FALSE so that we exit the
    //  application, rather than start the application's message pump.
    return FALSE;
}

VOID CGuiViewApp::LoadInitFile( )
{
    // Initialize
    BOOL         bRet            = FALSE;                   // Return value
    DWORD        dwErrCode       = GUI_VALUE_ZERO_DWORD;    // Error code
    WORD         wResult         = GUI_VALUE_ZERO_WORD;    // Result
    string       sSettingFile    = "";                      // INI file path
    CHAR         cBuffer[256];
    CString      csBuff;
    memset( cBuffer, 0x00, sizeof( cBuffer ));

    sSettingFile =  GUI_MONI_INIT_FILEPATH  + string("\\") + GUI_MONI_INI ;

    // Check file path
    bRet  = CheckFilePath( sSettingFile , &wResult, &dwErrCode );
    if ( bRet == GUI_RET_NG ) 
    {
        m_bShowCursor = FALSE;
        return ;
    }
    else
    {
        if ( wResult != GUI_U_CFIP_PATH_OK )
        {
            m_bShowCursor = FALSE;
            return ;
        }
    }
    // Get CursorOff_Flag value from setting file
    GetPrivateProfileString( GENERAL_SECTION, "CursorOff_Flag", "", cBuffer, MAX_PATH, CString(sSettingFile.c_str() ));
    csBuff = CString(cBuffer);
    csBuff.Trim();
    if ( csBuff == CURSOR_ON )
    {
        m_bShowCursor = TRUE;
        return;
    }

    m_bShowCursor = FALSE;
    return ;
}