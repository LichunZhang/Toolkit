/*=========================================================================
   Program:   MultiViewVisualization
   FileName:  QVTKImageView.cpp
   Author:	  Lichun Zhang from Soochow University
   Date:      2017/02/15
   Describe:	  
   Version:   v2.0
   Copyright: 2016-Now MIPAV Lab. All rights reserved.
=========================================================================*/

#include "QVTKImageView.h"

#include <QFocusEvent>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkViewImage.h>
//#include <vtkViewImage3D.h>

QVTKImageView::QVTKImageView(QWidget * parent /*= 0*/, Qt::WindowFlags f /*= 0*/)
	:QVTKWidget(parent,f),
	_render(nullptr),
	_viewimage(nullptr),
	_imgtype(ImgUnknown)
{
	setFocusPolicy(Qt::ClickFocus);

	//vtkViewImage3D *view = vtkViewImage3D::New();
	//QString str = QString(view->GetClassName());
}

QVTKImageView::~QVTKImageView()
{
	if (_viewimage) _viewimage->Delete();
	if (_render) _render->Delete();
}

void QVTKImageView::SetViewImage(vtkViewImage* viewImage)
{
	if (_viewimage == viewImage || !viewImage)
		return;
	else if (_viewimage) {
		_viewimage->Detach();
		_viewimage->Delete();
		_render->Delete();
	}
	_viewimage = viewImage;
	_render = vtkRenderer::New();
	vtkRenderWindow *window = GetRenderWindow();
	window->AddRenderer(_render);
	_viewimage->SetRenderer(_render);
	_viewimage->SetRenderWindow(window);

	if (_viewimage->IsA("vtkViewImage2D")) 
		_imgtype = Img2D;
	else if (_viewimage->IsA("vtkViewImage3D"))
		_imgtype = Img3D;
	else
		_imgtype = ImgUnknown;
		
}

void QVTKImageView::focusInEvent(QFocusEvent * event)
{
	if (event->reason() == Qt::MouseFocusReason) {
		emit focusIn(_imgtype, true);
		//setStyleSheet(QString::fromUtf8("border-width:5px;border-style:solid;border-color:rgb(255,0,0)"));
	}
	
}

void QVTKImageView::focusOutEvent(QFocusEvent * event)
{
	if (event->reason() == Qt::MouseFocusReason) {
		//setStyleSheet(QString::fromUtf8("border:0px"));
		emit focusIn(_imgtype, false);
	}	
}
