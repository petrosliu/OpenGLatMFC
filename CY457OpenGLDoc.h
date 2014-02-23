// CY457OpenGLDoc.h : interface of the CCY457OpenGLDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CY457OPENGLDOC_H__726D7346_8E3A_4618_A4BA_2B799D561E8B__INCLUDED_)
#define AFX_CY457OPENGLDOC_H__726D7346_8E3A_4618_A4BA_2B799D561E8B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCY457OpenGLDoc : public CDocument
{
protected: // create from serialization only
	CCY457OpenGLDoc();
	DECLARE_DYNCREATE(CCY457OpenGLDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCY457OpenGLDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCY457OpenGLDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCY457OpenGLDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CY457OPENGLDOC_H__726D7346_8E3A_4618_A4BA_2B799D561E8B__INCLUDED_)
