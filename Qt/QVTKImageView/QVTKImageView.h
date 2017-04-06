/*=========================================================================
   Program:   MultiViewVisualization
   FileName:  QVTKImageView
   Author:	  Lichun Zhang from Soochow University
   Date:      2017/02/15
   describe:	  
   Version:   v2.0
   Copyright: 2016-Now MIPAV Lab. All rights reserved.
=========================================================================*/

#ifndef MULTIVIEWVISUALIZATION_QVTKIMAGEVIEW
#define MULTIVIEWVISUALIZATION_QVTKIMAGEVIEW

#include <QVTKWidget.h>

class vtkRenderer;
class vtkViewImage;


class QVTKImageView : public QVTKWidget
{
	Q_OBJECT;

public:

	typedef enum {
		ImgUnknown,
		Img2D,
		Img3D,
	} IMGTYPE;

	QVTKImageView(QWidget * parent = 0, Qt::WindowFlags f = 0);
	virtual ~QVTKImageView();

	void SetViewImage(vtkViewImage* viewImage);
	vtkViewImage* GetViewImage() const {return _viewimage;}

protected:
	virtual void focusInEvent (QFocusEvent * event);
	virtual void focusOutEvent (QFocusEvent * event);

signals:
	void focusIn(int, bool);

private:
	vtkRenderer*  _render;
	vtkViewImage* _viewimage;
	IMGTYPE _imgtype;
};

#endif	//MULTIVIEWVISUALIZATION_QVTKIMAGEVIEW
