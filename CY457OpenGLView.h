// CY457OpenGLView.h : interface of the CCY457OpenGLView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CY457OPENGLVIEW_H__9A61131F_807D_42D5_984F_987D8B25F5B1__INCLUDED_)
#define AFX_CY457OPENGLVIEW_H__9A61131F_807D_42D5_984F_987D8B25F5B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct SCamera{
	GLfloat x,y,z,x0,y0,z0;
}Camera;

class CCY457OpenGLView : public CView
{
protected: // create from serialization only
	CCY457OpenGLView();
	DECLARE_DYNCREATE(CCY457OpenGLView)

// Attributes
public:
	CCY457OpenGLDoc* GetDocument();

	HGLRC m_hRC;	//Rendering Context
	CDC* m_pDC;		//Device Context
// Operations
public:
    BOOL m_cube;
	BOOL m_axia;
	BOOL m_table;
	BOOL m_ground;
	BOOL m_camera;
	
	GLfloat m_xAngle;
    GLfloat m_yAngle;
    GLfloat m_xPos;
    GLfloat m_yPos;
	GLfloat m_zPos;
    CPoint m_MouseDownPoint;

	Camera m_cameraData[20];
	int m_cameraCount;

    GLdouble m_texWrap, m_texFilter, m_texMode;  
    //All Texture Names
    GLuint m_Texture[3]; //保存纹理对象的名称

	BOOL InitializeOpenGL();	//Initialize OpenGL
	BOOL SetupPixelFormat();	//Set up the Pixel Format
	void RenderScene();			//Render the Scene
 
	void LoadGLTextures();
	void LoadTexture (CString fileName, int texName);

	void drawCamera(Camera* cam);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCY457OpenGLView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCY457OpenGLView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCY457OpenGLView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLoadspt();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnClean();
	afx_msg void OnWithdraw();
	afx_msg void OnCubeswitch();
	afx_msg void OnAxiaswitch();
	afx_msg void OnTableswitch();
	afx_msg void OnGroundswitch();
	afx_msg void OnCameraswitch();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CY457OpenGLView.cpp
inline CCY457OpenGLDoc* CCY457OpenGLView::GetDocument()
   { return (CCY457OpenGLDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CY457OPENGLVIEW_H__9A61131F_807D_42D5_984F_987D8B25F5B1__INCLUDED_)
