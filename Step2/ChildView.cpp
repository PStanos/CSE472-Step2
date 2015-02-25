
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "Step2.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_wood.LoadFile(L"textures/plank01.bmp");
	m_spinAngle = 0;
	m_spinTimer = 0;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, COpenGLWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_STEP_SPIN, &CChildView::OnStepSpin)
	ON_WM_TIMER()
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!COpenGLWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

//
//        Name : Quad()
// Description : Inline function for drawing 
//               a quadralateral.
//
inline void Quad(GLdouble *v1, GLdouble *v2, GLdouble *v3, GLdouble *v4)
{
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3dv(v1);
	glTexCoord2f(1, 0);
	glVertex3dv(v2);
	glTexCoord2f(1, 1);
	glVertex3dv(v3);
	glTexCoord2f(0, 1);
	glVertex3dv(v4);
	glEnd();
}

//
//        Name : CChildView::Box()
// Description : Draw an arbitrary size box. p_x, 
//               p_y, an p_z are the height of
//               the box. We will use this 
//               as a common primitive.
//      Origin : The back corner is at 0, 0, 0, and
//               the box is entirely in the
//               positive octant.
//
void CChildView::Box(GLdouble p_x, GLdouble p_y, GLdouble p_z, const GLdouble *p_color)
{
	GLdouble a[] = { 0., 0., p_z };
	GLdouble b[] = { p_x, 0., p_z };
	GLdouble c[] = { p_x, p_y, p_z };
	GLdouble d[] = { 0., p_y, p_z };
	GLdouble e[] = { 0., 0., 0. };
	GLdouble f[] = { p_x, 0., 0. };
	GLdouble g[] = { p_x, p_y, 0. };
	GLdouble h[] = { 0., p_y, 0. };

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, m_wood.TexName());

	// I'm going to mess with the colors a bit so
	// the faces will be visible in solid shading
	glColor3d(p_color[0], p_color[1], p_color[2]);
	glNormal3d(0., 0., 1.);
	Quad(a, b, c, d); // Front

	glColor3d(p_color[0] * 0.95, p_color[1] * 0.95, p_color[2] * 0.95);
	glNormal3d(1., 0., 0.);
	Quad(c, b, f, g); // Right

	glColor3d(p_color[0] * 0.85, p_color[1] * 0.85, p_color[2] * 0.85);
	glNormal3d(0., 0., -1.);
	Quad(h, g, f, e); // Back

	glColor3d(p_color[0] * 0.90, p_color[1] * 0.90, p_color[2] * 0.90);
	glNormal3d(-1., 0., 0.);
	Quad(d, h, e, a); // Left

	glColor3d(p_color[0] * 0.92, p_color[1] * 0.92, p_color[2] * 0.92);
	glNormal3d(0., 1., 0.);
	Quad(d, c, g, h); // Top

	glColor3d(p_color[0] * 0.80, p_color[1] * 0.80, p_color[2] * 0.80);
	glNormal3d(0., -1., 0.);
	Quad(e, f, b, a); // Bottom

	glDisable(GL_TEXTURE_2D);
}

void CChildView::OnGLDraw(CDC* pDC)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//
	// Set up the camera
	//

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Determine the screen size so we can determine the aspect ratio
	int width, height;
	GetSize(width, height);
	GLdouble aspectratio = GLdouble(width) / GLdouble(height);

	// Set the camera parameters
	gluPerspective(25.,         // Vertical FOV degrees.
		aspectratio, // The aspect ratio.
		10.,         // Near clipping 40/130
		200.);       // Far clipping

	// Set the camera location
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(20., 10., 50.,    // eye x,y,z
		0., 0., 0.,       // center x,y,z
		0., 1., 0.);      // Up direction

	//
	// Some standard parameters
	//

	// Enable depth test
	glEnable(GL_DEPTH_TEST);

	// Cull backfacing polygons
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	// Enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat lightpos[] = { 0.5, 2.0, 1.0, 0. };
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

	GLfloat white[] = { 1.f, 1.f, 1.f, 1.f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);

	glDisable(GL_LIGHTING);

	// Draw a coordinate axis
	glColor3d(0., 1., 1.);

	glBegin(GL_LINES);
	glVertex3d(0., 0., 0.);
	glVertex3d(12., 0., 0.);
	glVertex3d(0., 0., 0.);
	glVertex3d(0., 12., 0.);
	glVertex3d(0., 0., 0.);
	glVertex3d(0., 0., 12.);
	glEnd();

	glEnable(GL_LIGHTING);

	const double RED[] = { 0.7, 0.0, 0.0 };
	glPushMatrix();
	glTranslated(1.5, 1.5, 1.5);
	glRotated(m_spinAngle, 0., 0., 1.);
	glTranslated(-1.5, -1.5, -1.5);
	Box(3., 3., 3., RED);
	glPopMatrix();
}


void CChildView::OnStepSpin()
{
	if (m_spinTimer == 0)
	{
		// Create the timer
		m_spinTimer = SetTimer(1, 30, NULL);
	}
	else
	{
		// Destroy the timer
		KillTimer(m_spinTimer);
		m_spinTimer = 0;
	}
}


void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	m_spinAngle += 5;       // 5 degrees every 30ms about
	Invalidate();

	COpenGLWnd::OnTimer(nIDEvent);
}
