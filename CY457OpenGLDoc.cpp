// CY457OpenGLDoc.cpp : implementation of the CCY457OpenGLDoc class
//

#include "stdafx.h"
#include "CY457OpenGL.h"

#include "CY457OpenGLDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCY457OpenGLDoc

IMPLEMENT_DYNCREATE(CCY457OpenGLDoc, CDocument)

BEGIN_MESSAGE_MAP(CCY457OpenGLDoc, CDocument)
	//{{AFX_MSG_MAP(CCY457OpenGLDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCY457OpenGLDoc construction/destruction

CCY457OpenGLDoc::CCY457OpenGLDoc()
{
	// TODO: add one-time construction code here

}

CCY457OpenGLDoc::~CCY457OpenGLDoc()
{
}

BOOL CCY457OpenGLDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCY457OpenGLDoc serialization

void CCY457OpenGLDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CCY457OpenGLDoc diagnostics

#ifdef _DEBUG
void CCY457OpenGLDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCY457OpenGLDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCY457OpenGLDoc commands
