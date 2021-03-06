/**
 * PuTTYCSDialog.h - PuTTYCS Main Dialog header
 *
 * Copyright (c) 2005 - 2008 Jason Millard (jsm174@gmail.com)
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * REVISION HISTORY:
 *
 * 11/07/2005: Initial version                       J. Millard
 * 11/17/2005: Added UNICODE support                 J. Millard
 *             Added command cistory clear button          
 *             Added AltGr support                  
 * 11/18/2005: Fixed AltGr support                   J. Millard
 * 12/06/2005: Added mouse Copy/Paste emulation      J. Millard
 *             Navigation through command history
 *             moves cursor to end of command 
 * 12/15/2005: Added minimize to system tray         J. Millard
 *             Added tab completion
 * 12/19/2005: Added window opacity                  J. Millard
 * 05/27/2006: Improved system tray logic            J. Millard
 *             Added Windows XP style
 *             Added close, backspace, and          
 *             delete buttons
 * 11/20/2006: Added support for user defined        J. Millard
 *             cascade size.
 * 06/21/2007: Added Ctrl-R and Ctrl-D buttons       J. Millard
 *             Added {%CTRL%} command token 
 *             Added {%INC%} command token 
 *             Added scroll command history using 
 *             up/down arrow keys
 *             Added check for PuTTYCS update
 *             Added run on system startup   
 * 02/29/2008: Added horizontal/vertical tiling      J. Millard
 *             Updated cascade logic
 *             Added post send transition delay
 *             Added --script command line option
 */

#if !defined(AFX_PuTTYCSDLG_H__7BCAE5A7_75C4_4831_82FD_5A13F846FE61__INCLUDED_)
#define AFX_PuTTYCSDLG_H__7BCAE5A7_75C4_4831_82FD_5A13F846FE61__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef UNICODE
#define CommandLineToArgv CommandLineToArgvW
#else
#define CommandLineToArgv CommandLineToArgvT
LPTSTR *WINAPI CommandLineToArgvT(LPCTSTR lpCmdLine, int *lpArgc);
#endif

#include "CommandEdit.h"

class CPuTTYCSDialog : public CDialog
{
// Construction
public:

   CPuTTYCSDialog(CWnd* pParent = NULL);   // standard constructor
   ~CPuTTYCSDialog();
      
   CObArray* GetAllWindows();
   
// Dialog Data
   //{{AFX_DATA(CPuTTYCSDialog)
   enum { IDD = IDD_PUTTYCS_DIALOG };
   CCommandEdit   m_cceCommandEdit;
    //}}AFX_DATA

   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CPuTTYCSDialog)
	public:
   virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL DestroyWindow();
	protected:
   virtual void DoDataExchange(CDataExchange* pDX);   // DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

   HICON m_hIcon;

   bool m_bIsClosing;  
   bool m_bFindAll; 

   int m_iDialogHeight;

   /**
    * PuTTY Filters
    */

   CStringArray m_csaFilters;
   int m_iFilter;

    /**
    * Command history
    */

   CStringArray m_csaCmdHistory;
   int m_iCmdHistory;

   /**
    * Window
    */

   int m_iToolWindow;
   int m_iAlwaysOnTop;
   int m_iMinimizeToSysTray;
   int m_iOpacity;

   /**
    * Auto arrange 
    */
   
   int m_iAutoArrange;
   int m_iAutoMinimize;
   int m_iArrangeOnStartup;   
   int m_iUnhideOnExit;

   /**
    * Tile method
    */ 
   
   int m_iTileMethod;

   /**
    * Cascade dimensions
    */ 

   int m_iCascadeWidth;
   int m_iCascadeHeight;
  
   /**
    * Keyboard/Mouse
    */

   int m_iTabCompletion;
   int m_iCmdHistoryScrollThrough;
   int m_iEmulateCopyPaste;

   /**
    * Send CR
    */

   int m_iSendCR;

   /** 
    * Miscellaneous
    */
   
   int m_iSavePassword;
  
   CString m_csPassword;  
  
   int m_iRunOnSystemStartup;
   int m_iCheckForUpdates;

   /** 
    * Transition delays
    */

   int m_iTransition;
   int m_iPostSendDelay;

   /**
    * Fonts
    */

   CFont* m_pMarlettNormal;
   CFont* m_pMarlettSmall;
   CFont* m_pSymbolSmall;
    
   void sendCommand( CString csCommand, bool bTab );
   void sendBuffer( CString csBuffer, bool bParse = false, bool bTab = false );
   
   void LoadPreferences();
   void SavePreferences();

   void UpdateDialog();
   void RefreshDialog();

   void SendScript( CString csFilename );

   void MovePuttyWnd(CWnd* pWnd, int iX, int intY, int iSizeX, int iSizeY);

   void SetRunOnSystemStartup( bool bEnable = true );
   void CheckForUpdates(bool bInteractive = false);

   void ParseCmdLineOptions(LPTSTR pCmdLine = NULL);

   // Generated message map functions
   //{{AFX_MSG(CPuTTYCSDialog)
   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
   virtual BOOL OnInitDialog();
   afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
   afx_msg void OnPaint();
   afx_msg HCURSOR OnQueryDragIcon();
   afx_msg void OnAboutButton();
   afx_msg void OnSelChangeFiltersCombobox();   
   afx_msg void OnCascadeButton();      
   afx_msg void OnTileButton();
   afx_msg void OnMinimizeButton();
   afx_msg void OnHideButton();   
   afx_msg void OnFiltersButton();
   afx_msg void OnSendCRPushButton();      
   afx_msg void OnCmdHistoryUpButton();
   afx_msg void OnCmdHistoryDownButton();   
   afx_msg void OnUpButton();
   afx_msg void OnDownButton();
   afx_msg void OnRightButton();
   afx_msg void OnLeftButton();
   afx_msg void OnClearButton();
   afx_msg void OnBreakButton();
   afx_msg void OnEndTelnetButton();
   afx_msg void OnEscapeButton();
   afx_msg void OnEnterButton();   
   afx_msg void OnPasswordButton();
   afx_msg void OnPreferencesButton();      
   afx_msg void OnScriptButton();   
   afx_msg void OnSendButton();      
   afx_msg void OnTrayNotify(WPARAM wParam, LPARAM lParam);
   afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
   afx_msg void OnCmdHistoryClearButton();
   afx_msg void OnOpenMenuItem();  
	afx_msg void OnBackspaceButton();
	afx_msg void OnDeleteButton();
	afx_msg void OnCloseButton();
	afx_msg void OnCtrlButton();
   afx_msg void OnIncButton();
   afx_msg void OnCheckForUpdates();
	afx_msg void OnCtrlDButton();
	afx_msg void OnCtrlRButton();
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	//}}AFX_MSG
   DECLARE_MESSAGE_MAP()   

private:

   CSendKeys m_skSendKeys;
   CObArray  m_obaWindows;

   UINT m_uiTaskbarMessage;
   BOOL m_bDisablePopup;

   NOTIFYICONDATA* m_pTNI;
   void SetSysTrayTip( CString csTip = PUTTYCS_EMPTY_STRING );

   static BOOL CALLBACK enumwindowsProc(HWND hwnd, LPARAM lParam); 
   static int wildcmp(const TCHAR* wild, const TCHAR* string);
   
   void SortWindows();
   static int Compare(const void* pWndS1, const void* pWndS2);

   static CString GetAttributeValue(const CString, const CString);
   CMenu* m_pMenu;  
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PuTTYCSDLG_H__7BCAE5A7_75C4_4831_82FD_5A13F846FE61__INCLUDED_)
