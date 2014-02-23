// CY457OpenGLView.cpp : implementation of the CCY457OpenGLView class
//

#include "stdafx.h"
#include "CY457OpenGL.h"

#include "CY457OpenGLDoc.h"
#include "CY457OpenGLView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TIMES 0.01
#define CUBELINE 0.295
#define PI 3.141593
/////////////////////////////////////////////////////////////////////////////
// CCY457OpenGLView

IMPLEMENT_DYNCREATE(CCY457OpenGLView, CView)

BEGIN_MESSAGE_MAP(CCY457OpenGLView, CView)
	//{{AFX_MSG_MAP(CCY457OpenGLView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_LOADSPT, OnLoadspt)
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_CLEAN, OnClean)
	ON_COMMAND(ID_WITHDRAW, OnWithdraw)
	ON_COMMAND(ID_CUBESWITCH, OnCubeswitch)
	ON_COMMAND(ID_AXIASWITCH, OnAxiaswitch)
	ON_COMMAND(ID_TABLESWITCH, OnTableswitch)
	ON_COMMAND(ID_GROUNDSWITCH, OnGroundswitch)
	ON_COMMAND(ID_CAMERASWITCH, OnCameraswitch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCY457OpenGLView construction/destruction

CCY457OpenGLView::CCY457OpenGLView()
{
	// TODO: add construction code here
	m_cube = true;    
	m_axia = true;
	m_table = true;
	m_ground = true;
	m_camera = true;

    m_xPos = 0.0f;
    m_yPos = 0.0f;
	m_zPos = -10.0f;
    m_xAngle = 30.0f;
    m_yAngle = -45.0f;

    m_texWrap = GL_CLAMP;
    m_texMode = GL_DECAL;
    m_texFilter = GL_NEAREST;

	m_cameraCount=0;
}

CCY457OpenGLView::~CCY457OpenGLView()
{
}

BOOL CCY457OpenGLView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	//An OpenGL Window must be created with the following flags
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCY457OpenGLView drawing

void CCY457OpenGLView::OnDraw(CDC* pDC)
{
	CCY457OpenGLDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// Clear out the color & depth buffers
	::glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	RenderScene();
	// Tell OpenGL to flush its pipeline
	::glFinish();
	// Now Swap the buffers
	::SwapBuffers( m_pDC->GetSafeHdc() );
}

/////////////////////////////////////////////////////////////////////////////
// CCY457OpenGLView diagnostics

#ifdef _DEBUG
void CCY457OpenGLView::AssertValid() const
{
	CView::AssertValid();
}

void CCY457OpenGLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCY457OpenGLDoc* CCY457OpenGLView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCY457OpenGLDoc)));
	return (CCY457OpenGLDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCY457OpenGLView message handlers

int CCY457OpenGLView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	//Initialize OpenGL Here
	InitializeOpenGL();
	return 0;
}

void CCY457OpenGLView::OnDestroy() 
{
	CView::OnDestroy();
	//Make the RC non-current
	if(::wglMakeCurrent (0,0) == FALSE)
	{
		MessageBox("Could not make RC non-current");
	}
	
	//Delete the rendering context
	if(::wglDeleteContext (m_hRC)==FALSE)
	{
		MessageBox("Could not delete RC");
	}
	
	//Delete the DC
	if(m_pDC)
	{
		delete m_pDC;
	}
	//Set it to NULL
	m_pDC = NULL;
}

void CCY457OpenGLView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);

	GLdouble aspect_ratio; // width/height ratio
	
	if ( 0 >= cx || 0 >= cy )
	{
		return;
	}

	// select the full client area
    ::glViewport(0, 0, cx, cy);

	// compute the aspect ratio
	// this will keep all dimension scales equal
	aspect_ratio = (GLdouble)cx/(GLdouble)cy;

	// select the projection matrix and clear it
    ::glMatrixMode(GL_PROJECTION);
    ::glLoadIdentity();

	// select the viewing volume
	::gluPerspective(45.0f, aspect_ratio, .01f, 200.0f);
	
	// switch back to the modelview matrix and clear it
    ::glMatrixMode(GL_MODELVIEW);
    ::glLoadIdentity();
}

BOOL CCY457OpenGLView::OnEraseBkgnd(CDC* pDC) 
{
	//Tell Windows not to erase the background
	return TRUE;
}

BOOL CCY457OpenGLView::InitializeOpenGL()
{
		//Get a DC for the Client Area
	m_pDC = new CClientDC(this);

	//Failure to Get DC
	if(m_pDC == NULL)
	{
		MessageBox("Error Obtaining DC");
		return FALSE;
	}

	//Failure to set the pixel format
	if(!SetupPixelFormat())
	{
		return FALSE;
	}

	//Create Rendering Context
	m_hRC = ::wglCreateContext (m_pDC->GetSafeHdc ());

	//Failure to Create Rendering Context
	if(m_hRC == 0)
	{
		MessageBox("Error Creating RC");
		return FALSE;
	}
	
	//Make the RC Current
	if(::wglMakeCurrent (m_pDC->GetSafeHdc (), m_hRC)==FALSE)
	{
		MessageBox("Error making RC Current");
		return FALSE;
	}

	//Specify Black as the clear color
	::glClearColor(0.0f,0.0f,0.0f,0.0f);

	//Specify the back of the buffer as clear depth
	::glClearDepth(1.0f);

	//Enable Depth Testing
	::glEnable(GL_DEPTH_TEST);

	//¼ÓÔØÎÆÀí
    LoadGLTextures();

	return TRUE;
}

//Setup Pixel Format
/////////////////////////////////////////////////////////////////////////////
BOOL CCY457OpenGLView::SetupPixelFormat()
{
  static PIXELFORMATDESCRIPTOR pfd = 
	{
        sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd
        1,                              // version number
        PFD_DRAW_TO_WINDOW |            // support window
        PFD_SUPPORT_OPENGL |		    // support OpenGL
        PFD_DOUBLEBUFFER,				// double buffered
        PFD_TYPE_RGBA,                  // RGBA type
        24,                             // 24-bit color depth
        0, 0, 0, 0, 0, 0,               // color bits ignored
        0,                              // no alpha buffer
        0,                              // shift bit ignored
        0,                              // no accumulation buffer
        0, 0, 0, 0,                     // accum bits ignored
        16,                             // 16-bit z-buffer
        0,                              // no stencil buffer
        0,                              // no auxiliary buffer
        PFD_MAIN_PLANE,                 // main layer
        0,                              // reserved
        0, 0, 0                         // layer masks ignored
    };
    
    int m_nPixelFormat = ::ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);

	if ( m_nPixelFormat == 0 )
	{
       return FALSE;
	}

    if ( ::SetPixelFormat(m_pDC->GetSafeHdc(), m_nPixelFormat, &pfd) == FALSE)
    {
       return FALSE;
	}


    return TRUE;
}

void CCY457OpenGLView::RenderScene ()
{
	glLoadIdentity();
    glTranslatef(m_xPos, m_yPos, m_zPos);
    glRotatef(m_xAngle, 1.0f,0.0f,0.0f);
    glRotatef(m_yAngle, 0.0f,1.0f,0.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//ground
	if(m_ground){
		glBegin(GL_QUADS);	
			glColor4f(0.2f,0.2f,0.2f,1.0f);
			glVertex3f( 500.0f, -CUBELINE*10,-500.0f);
			glVertex3f(-500.0f, -CUBELINE*10,-500.0f);
			glVertex3f(-500.0f, -CUBELINE*10, 500.0f);
			glVertex3f( 500.0f, -CUBELINE*10, 500.0f);
		glEnd();
	}

//table
	if(m_table){
		glDepthMask(GL_FALSE);
			glBegin(GL_QUADS);	
				glColor4f(1.0f,1.0f,1.0f,0.5f);
				glVertex3f( CUBELINE*4, -0.01f,-CUBELINE*4);
				glVertex3f(-CUBELINE*4, -0.01f,-CUBELINE*4);
				glVertex3f(-CUBELINE*4, -0.01f, CUBELINE*4);
				glVertex3f( CUBELINE*4, -0.01f, CUBELINE*4);
			glEnd();	
		glDepthMask(GL_TRUE);
	}

//cube
	if(m_cube){
		glColor4f(0.8f,0.8f,0.8f,1.0f);
		glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D,m_Texture[1]);
			//Front Face
			glBegin(GL_POLYGON);
				glTexCoord2f(0,0);
				glVertex3f(0.0f, 0.0f,CUBELINE);
				glTexCoord2f(1,0);
				glVertex3f(CUBELINE, 0.0f,CUBELINE);
				glTexCoord2f(1,1);
				glVertex3f(CUBELINE, CUBELINE,CUBELINE);
				glTexCoord2f(0,1);
				glVertex3f(0.0f, CUBELINE,CUBELINE);
			glEnd();
			glBindTexture(GL_TEXTURE_2D,m_Texture[3]);
			//Back Face
			glBegin(GL_POLYGON);
				glTexCoord2f(1,0);
				glVertex3f(0.0f, 0.0f,0.0f);
				glTexCoord2f(1,1);
				glVertex3f(0.0f, CUBELINE,0.0f);
				glTexCoord2f(0,1);
				glVertex3f(CUBELINE, CUBELINE,0.0f);
				glTexCoord2f(0,0);
				glVertex3f(CUBELINE, 0.0f,0.0f);
			glEnd();
			glBindTexture(GL_TEXTURE_2D,m_Texture[2]);
			//Left Face
			glBegin(GL_POLYGON);
				glTexCoord2f(1,0);
				glVertex3f(0.0f, 0.0f, CUBELINE);
				glTexCoord2f(1,1);
				glVertex3f(0.0f, CUBELINE, CUBELINE);
				glTexCoord2f(0,1);
				glVertex3f(0.0f, CUBELINE, 0.0f);
				glTexCoord2f(0,0);
				glVertex3f(0.0f, 0.0f, 0.0f);
			glEnd();
			glBindTexture(GL_TEXTURE_2D,m_Texture[4]);
			//Right Face
			glBegin(GL_POLYGON);
				glTexCoord2f(0,0);
				glVertex3f(CUBELINE, 0.0f, CUBELINE);
				glTexCoord2f(1,0);
				glVertex3f(CUBELINE, 0.0f, 0.0f);
				glTexCoord2f(1,1);
				glVertex3f(CUBELINE, CUBELINE, 0.0f);
				glTexCoord2f(0,1);
				glVertex3f(CUBELINE, CUBELINE, CUBELINE);
			glEnd();
			glBindTexture(GL_TEXTURE_2D,m_Texture[5]);
			//Top Face
			glBegin(GL_POLYGON);
				glTexCoord2f(0,0);
				glVertex3f(0.0f, CUBELINE, CUBELINE);
				glTexCoord2f(1,0);
				glVertex3f(CUBELINE, CUBELINE, CUBELINE);
				glTexCoord2f(1,1);
				glVertex3f(CUBELINE, CUBELINE, 0.0f);
				glTexCoord2f(0,1);
				glVertex3f(0.0f, CUBELINE, 0.0f);
			glEnd();
			//Bottom Face
			glBindTexture(GL_TEXTURE_2D,m_Texture[0]);
			glBegin(GL_POLYGON);
				glTexCoord2f(0,0);
				glVertex3f(0.0f, 0.0f, CUBELINE);
				glTexCoord2f(1,0);
				glVertex3f(CUBELINE, 0.0f, CUBELINE);
				glTexCoord2f(1,1);
				glVertex3f(CUBELINE, 0.0f, 0.0f);
				glTexCoord2f(0,1);
				glVertex3f(0.0f, 0.0f, 0.0f);
			glEnd();
		glDisable(GL_TEXTURE_2D);
	}

//axia
	if(m_axia){
		float i;
		glColor4f(1.0f,0.0f,0.0f,1.0f);
		glBegin(GL_LINES);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(100.0f,0.0f,0.0f);
		glEnd();
		for(i=0;i<500;i++){
			glBegin(GL_LINES);
				glVertex3f(i/10,0.0f,0.0f);
				glVertex3f(i/10,0.0f,0.05f);
			glEnd();
		}
		glColor4f(0.0f,1.0f,0.0f,1.0f);
		glBegin(GL_LINES);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(0.0f,100.0f,0.0f);
		glEnd();
		for(i=0;i<500;i++){
			glBegin(GL_LINES);
				glVertex3f(0.0f,i/10,0.0f);
				glVertex3f(0.0f,i/10,0.05f);
			glEnd();
		}
		glColor4f(0.0f,0.0f,1.0f,1.0f);
		glBegin(GL_LINES);
			glVertex3f(0.0f,0.0f,0.0f);
			glVertex3f(0.0f,0.0f,100.0f);
		glEnd();
		for(i=0;i<500;i++){
			glBegin(GL_LINES);
				glVertex3f(0.0f,0.0f,i/10);
				glVertex3f(0.05f,0.0f,i/10);
			glEnd();
		}
	}

//camera
	if(m_camera){
		glDepthMask(GL_FALSE);
			int j;
			for(j=0;j<m_cameraCount;j++){
				drawCamera(m_cameraData+j);
			}
		glDepthMask(GL_TRUE);
	}
}

void CCY457OpenGLView::drawCamera(Camera* cam){
	glColor4f(1.0f,1.0f,0.0f,1.0f);
	glBegin(GL_LINES);
		glVertex3f(cam->x*TIMES,cam->y*TIMES,cam->z*TIMES);
		glVertex3f(cam->x0*TIMES,cam->y0*TIMES,cam->z0*TIMES);
	glEnd();

	int N = 360;  // Ô²×¶·Ö¸îÊý
	float THETA=40 * PI / 180;	//¶¥½Ç
	float D = sqrt((cam->x-cam->x0)*(cam->x-cam->x0)+(cam->y-cam->y0)*(cam->y-cam->y0)+(cam->z-cam->z0)*(cam->z-cam->z0));
	float R = D*tan(THETA);
	int i;
	glBegin(GL_LINES);
		for (i = 0; i < N; i++){
			glVertex3f(cam->x0*TIMES + R * cos(i * 2 * PI / N)*TIMES, cam->y0*TIMES, cam->z0*TIMES + R * sin(i * 2 * PI / N)*TIMES);
			glVertex3f(cam->x0*TIMES + R * cos((i + 1) * 2 * PI / N)*TIMES, cam->y0*TIMES, cam->z0*TIMES + R * sin((i + 1) * 2 * PI / N)*TIMES);
		}
	glEnd(); 

	glColor4f(1.0f,1.0f,0.0f,0.1f);
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(cam->x*TIMES, cam->y*TIMES, cam->z*TIMES);
		for (i = 0; i < N; i++){
			glVertex3f(cam->x0*TIMES + R * cos(i * 2 * PI / N)*TIMES, cam->y0*TIMES, cam->z0*TIMES + R * sin(i * 2 * PI / N)*TIMES);
			glVertex3f(cam->x0*TIMES + R * cos((i + 1) * 2 * PI / N)*TIMES, cam->y0*TIMES, cam->z0*TIMES + R * sin((i + 1) * 2 * PI / N)*TIMES);
		}
	glEnd(); 
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(cam->x0*TIMES, cam->y0*TIMES, cam->z0*TIMES);
		for (i = 0; i < N; i++){
			glVertex3f(cam->x0*TIMES + R * cos(i * 2 * PI / N)*TIMES, cam->y0*TIMES, cam->z0*TIMES + R * sin(i * 2 * PI / N)*TIMES);
			glVertex3f(cam->x0*TIMES + R * cos((i + 1) * 2 * PI / N)*TIMES, cam->y0*TIMES, cam->z0*TIMES + R * sin((i + 1) * 2 * PI / N)*TIMES);
		}
	glEnd(); 
}

void CCY457OpenGLView::OnLoadspt() 
{
	char strFilter[]="(*.spt)|*.spt||";
	CFileDialog fDlg(1,"spt","*.spt",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,strFilter);

	if(fDlg.DoModal()==IDOK)
	{
		CString sf=fDlg.GetPathName();
		FILE *fp=fopen(sf,"r");
		long float x,y,z,r11,r12,r13,r21,r22,r23,r31,r32,r33,tx,ty,tz;
		long float f,k,w,h,phi,omiga,kappa;
		fscanf(fp,"%lf",&f);
		fscanf(fp,"%lf",&k);

		fscanf(fp,"%lf %lf",&w,&h);
		fscanf(fp,"%lf %lf %lf",&x, &y, &z);
		fscanf(fp,"%lf %lf %lf",&phi,&omiga,&kappa);
		
		fscanf(fp,"%lf",&r11);
		fscanf(fp,"%lf",&r12);
		fscanf(fp,"%lf",&r13);
			
		fscanf(fp,"%lf",&r21);
		fscanf(fp,"%lf",&r22);
		fscanf(fp,"%lf",&r23);
			
		fscanf(fp,"%lf",&r31);
		fscanf(fp,"%lf",&r32);
		fscanf(fp,"%lf",&r33);
			
		fscanf(fp,"%lf",&tx);
		fscanf(fp,"%lf",&ty);
		fscanf(fp,"%lf",&tz);

		fclose(fp);

		////////////////////////////////

		float wx,wy,wz,ox,oy,oz;
		tx=-tx;
		ty=-ty;
		tz=1-tz;
		wx=r11*tx+r12*ty+r13*tz;
		wy=r21*tx+r22*ty+r23*tz;
		wz=r31*tx+r32*ty+r33*tz;
		ox=x-(z*(x-wx)/(z-wz));
		oy=y-(z*(y-wy)/(z-wz));
		oz=0.0;

		m_cameraData[m_cameraCount].x  = (float)y;
		m_cameraData[m_cameraCount].y  = (float)z;
		m_cameraData[m_cameraCount].z  = (float)x;
		m_cameraData[m_cameraCount].x0 = (float)oy;
		m_cameraData[m_cameraCount].y0 = (float)oz;
		m_cameraData[m_cameraCount].z0 = (float)ox;
		
		m_cameraCount++;
		m_camera=true;
	}
	
	InvalidateRect(NULL,FALSE);
}

void CCY457OpenGLView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	switch (nChar)
    {
        case VK_UP:        m_yPos = m_yPos + 0.1f;
                        break;
        case VK_DOWN:    m_yPos = m_yPos - 0.1f;
                        break;
        case VK_LEFT:    m_xPos = m_xPos - 0.1f;
                        break;
        case VK_RIGHT:  m_xPos = m_xPos + 0.1f;
                        break;
        default:        MessageBox("Press the arrow keys only");
                        break;
    }        

    InvalidateRect(NULL,FALSE);

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CCY457OpenGLView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_MouseDownPoint=point;
    SetCapture();

	CView::OnLButtonDown(nFlags, point);
}

void CCY457OpenGLView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_MouseDownPoint=CPoint(0,0);
    ReleaseCapture();
    
	CView::OnLButtonUp(nFlags, point);
}

void CCY457OpenGLView::OnMouseMove(UINT nFlags, CPoint point) 
{
    if (GetCapture()==this)
    {
        m_xAngle+=(point.y-m_MouseDownPoint.y)/3.6;
        m_yAngle+=(point.x-m_MouseDownPoint.x)/3.6;
        InvalidateRect(NULL,FALSE);
        m_MouseDownPoint=point;
    }
    
	CView::OnMouseMove(nFlags, point);
}

BOOL CCY457OpenGLView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	m_zPos+=zDelta/1500.0*m_zPos;
	if(-m_zPos<2.0*CUBELINE)m_zPos=-2.0*CUBELINE;
	InvalidateRect(NULL,FALSE);
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CCY457OpenGLView::OnClean() 
{
	m_cameraCount=0;
	InvalidateRect(NULL,FALSE);
}

void CCY457OpenGLView::OnWithdraw() 
{
	if(m_cameraCount)m_cameraCount--;
	InvalidateRect(NULL,FALSE);
}

void CCY457OpenGLView::OnCubeswitch() 
{
	m_cube=!m_cube;
	InvalidateRect(NULL,FALSE);
}

void CCY457OpenGLView::OnAxiaswitch() 
{
	m_axia=!m_axia;
	InvalidateRect(NULL,FALSE);
}

void CCY457OpenGLView::OnTableswitch() 
{
	m_table=!m_table;
	InvalidateRect(NULL,FALSE);
}

void CCY457OpenGLView::OnGroundswitch() 
{
	m_ground=!m_ground;
	InvalidateRect(NULL,FALSE);
}

void CCY457OpenGLView::OnCameraswitch() 
{
	m_camera=!m_camera;
	InvalidateRect(NULL,FALSE);
}

//Texture Mapping Functions
void CCY457OpenGLView::LoadGLTextures()
{
    //Create Texture Names
    glGenTextures(5, m_Texture);
    LoadTexture("0.bmp",0);
    LoadTexture("1.bmp",1);
    LoadTexture("2.bmp",2);
    LoadTexture("3.bmp",3);
    LoadTexture("4.bmp",4);
    LoadTexture("5.bmp",5);
}
void CCY457OpenGLView::LoadTexture (CString fileName, int texName)
{
    //Load Texture
    AUX_RGBImageRec* m_texture;
    m_texture = auxDIBImageLoad((const char*)fileName);
    if(!m_texture)
    {
        MessageBox("Picture could not be loaded");
        exit(1);
    }
    glBindTexture(GL_TEXTURE_2D, m_Texture[texName]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_texWrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_texWrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_texFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_texFilter);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, m_texMode);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, m_texture->sizeX,m_texture->sizeY, GL_RGB, GL_UNSIGNED_BYTE, m_texture->data);
}

