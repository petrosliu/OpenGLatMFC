// CY457OpenGL.h : main header file for the CY457OPENGL application
//

#if !defined(AFX_CY457OPENGL_H__4E50C946_C2BD_4DE2_9C27_E95F6D8C8263__INCLUDED_)
#define AFX_CY457OPENGL_H__4E50C946_C2BD_4DE2_9C27_E95F6D8C8263__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCY457OpenGLApp:
// See CY457OpenGL.cpp for the implementation of this class
//

class CCY457OpenGLApp : public CWinApp
{
public:
	CCY457OpenGLApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCY457OpenGLApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CCY457OpenGLApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CY457OPENGL_H__4E50C946_C2BD_4DE2_9C27_E95F6D8C8263__INCLUDED_)
