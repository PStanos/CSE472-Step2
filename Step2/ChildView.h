
// ChildView.h : interface of the CChildView class
//


#pragma once

#include "graphics/OpenGLWnd.h"
#include "graphics/GrTexture.h"
#include "graphics/GrCamera.h"
#include "Sphere.h"
#include "Mesh.h"
#include "Torus.h"

// CChildView window

class CChildView : public COpenGLWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();
	void Box(GLdouble p_x, GLdouble p_y, GLdouble p_z, const GLdouble *p_color);

private:
	void CreateMesh();

	CGrTexture m_wood;
	CGrTexture m_worldmap;
	CGrTexture m_marble1;
	CGrTexture m_marble2;
	CGrTexture m_bluegill;
	double m_spinAngle;
	double m_lightAngle;
	UINT_PTR m_spinTimer;
	UINT_PTR m_lightSpinTimer;
	CGrCamera m_camera;
	int m_scene;
	CSphere m_sphere;
	CMesh m_mesh;
	CMesh m_surface;
	CMesh m_fish;
	CTorus m_torus1;
	CTorus m_torus2;

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	void OnGLDraw(CDC* pDC);

	afx_msg void OnStepSpin();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnStepSphere();
	afx_msg void OnStepMesh();
	afx_msg void OnStepSpinlight();
	afx_msg void OnStepTori();
};

