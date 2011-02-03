/* mapviewer.cpp
 * 2011-01-26 the program is created by Yang jinzhu
 */

#include "mapviewer.h"
#include <QPainter>
//Q_EXPORT_PLUGIN2 ( PluginName, ClassName )
//The value of PluginName should correspond to the TARGET specified in the plugin's project file.
Q_EXPORT_PLUGIN2(mapviewer, MAPiewerPlugin);

//plugin funcs
const QString title = "Map Viewer";
QStringList MAPiewerPlugin::menulist() const
{
    return QStringList() << tr("load Image")
						 << tr("help");
}

void MAPiewerPlugin::domenu(const QString &menu_name, V3DPluginCallback &callback, QWidget *parent)
{
    if (menu_name == tr("load Image"))
    {
    	iViewer(callback, parent);
    }
	else if (menu_name == tr("help"))
	{
		
	}
}
void MAPiewerPlugin::iViewer(V3DPluginCallback &callback, QWidget *parent)
{
	// load indexed data file
	QString m_FileName = QFileDialog::getOpenFileName(parent, QObject::tr("Open profile"), "", QObject::tr("Supported file (*.tc)"));
	
	if(m_FileName.isEmpty())	
		return;
	// tiled images path
	QString curFilePath = QFileInfo(m_FileName).path();
	curFilePath.append("/");
	
	ImageSetWidget *inw = new ImageSetWidget(callback, parent,m_FileName, curFilePath, 4);
	inw->show();
	
}
void XMapView::setImgData(ImagePlaneDisplayType ptype,V3DLONG *sz_compressed,V3DLONG cz0, V3DLONG cz1, V3DLONG cz2,unsigned char *pdata, ImageDisplayColorType ctype)
{
	//Ptype = ptype; //
    cur_focus_pos = 1;
	imgData = pdata; //
	Ctype = ctype; //
	
	cx=sz_compressed[0], cy=sz_compressed[1], cz=sz_compressed[2], cc=sz_compressed[3];
	
	channel_compressed_sz = cx*cy*cz;
	
	Ptype = ptype;
	
	start_x = cur_x = cz0;
	cur_y = cz1;
	cur_z = cz2;
	
	//qDebug()<<"setimagedata ..."<<cur_x<<cur_y<<cur_z;
	pixmap = copyRaw2QPixmap((const unsigned char *)imgData,cx,cy,cz,cc,cur_x,cur_y,cur_z,Ptype,0,0);
	
}




template <class T> QPixmap copyRaw2QPixmap_xPlanes(const T * pada,
												   V3DLONG sz0,
												   V3DLONG sz1,
												   V3DLONG sz2,
												   V3DLONG sz3,
												   V3DLONG cz0, V3DLONG cz1, V3DLONG cz2,
												   double *p_vmax,
												   double *p_vmin)
{
	QImage tmpimg = QImage(sz2, sz1, QImage::Format_RGB32);//zy
	int channel_compressed_sz = sz0*sz1*sz2;
	for (long j = 0; j < sz1; j ++) 
	{
		long offset = j*sz0 + cz0;
		for (long k =0; k < sz2; k++) 
		{
			long idx = offset + k*sz0*sz1;
			
			tmpimg.setPixel(k,j,qRgb(pada[idx], pada[idx+channel_compressed_sz], pada[idx+2*channel_compressed_sz]));
		}
	}
	
	//painter.setCompositionMode(QPainter::CompositionMode_Source);
	//painter.drawImage(0,0, xy_image);
	
	return QPixmap::fromImage(tmpimg);	
	
}


template <class T> QPixmap copyRaw2QPixmap_yPlanes(const T * pada,
												   V3DLONG sz0,
												   V3DLONG sz1,
												   V3DLONG sz2,
												   V3DLONG sz3,
												    V3DLONG cz0, V3DLONG cz1, V3DLONG cz2,
												   double *p_vmax,
												   double *p_vmin)//xz
{
	
	QImage tmpimg = QImage(sz0, sz2, QImage::Format_RGB32);
	int channel_compressed_sz = sz0*sz1*sz2;
	for (long k = 0; k < sz2; k ++) 
	{
		long offset = k*sz0*sz1 + cz1*sz0;
		for (long i =0; i < sz0; i++) 
		{
			long idx = offset + i;
			
			tmpimg.setPixel(i,k,qRgb(pada[idx], pada[idx+channel_compressed_sz], pada[idx+2*channel_compressed_sz]));
		}
	}
	return QPixmap::fromImage(tmpimg);
}

template <class T> QPixmap copyRaw2QPixmap_zPlanes(const T * pdata,
												   V3DLONG sz0,
												   V3DLONG sz1,
												   V3DLONG sz2,
												   V3DLONG sz3,
												    V3DLONG cz0, V3DLONG cz1, V3DLONG cz2,
												   double *p_vmax,
												   double *p_vmin)//xy
{
	QImage tmpimg = QImage(sz0, sz1, QImage::Format_RGB32);
	int channel_compressed_sz = sz0*sz1*sz2;
	for (long j = 0; j < sz1; j ++) 
	{
		long offset = cz2*sz0*sz1 + j*sz0;
		for (long i=0; i<sz0; i++) 
		{
			long idx = offset + i;
			
			tmpimg.setPixel(i,j,qRgb(pdata[idx], pdata[idx+channel_compressed_sz], pdata[idx+2*channel_compressed_sz]));
		}
	}
	return QPixmap::fromImage(tmpimg);
	
}
void XMapView::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.save();
    
	painter.setRenderHint(QPainter::Antialiasing);
    
	painter.setRenderHint(QPainter::SmoothPixmapTransform);
		
	int pwid = disp_width; //changed to disp_height/disp_width 
	int phei = disp_height;
    
	QPointF center(pwid/2.0, phei/2.0);
	if (m_scale>1)
		painter.translate(curDisplayCenter - center);
	else
		curDisplayCenter = center;
	
    painter.translate(center);
    painter.scale(m_scale, m_scale);
    painter.translate(-center);
	
    painter.scale(disp_scale, disp_scale);

    painter.drawPixmap(QPointF(0, 0), pixmap);
	
	painter.setPen(Qt::white );
	painter.setBrush(Qt::NoBrush);
	if (QApplication::keyboardModifiers()==Qt::ControlModifier)
	{
		if (bMouseCurorIn )
		{
			QRect r ( dragStartPosition, curMousePos );
			painter.drawRect(r);
			qDebug()<<"ee-xyz...."<<end_x<<end_y<<cz;
			qDebug()<<"ss-xyz...."<<start_x<<start_y<<cur_z;
		}
	}
}

void ImageSetWidget::update_v3dviews(V3DPluginCallback *callback, long start_x, long start_y, long start_z, long end_x, long end_y, long end_z)
{
	// visualize in v3d tri-view
	
	size_t start_t = clock();
	
	//virtual image
	long vx, vy, vz, vc;
	
	vx = end_x - start_x + 1; // suppose the size same of all tiles
	vy = end_y - start_y + 1;
	vz = end_z - start_z + 1;
	vc = vim.sz[3];
	
	qDebug()<<"3dxyzc ..."<<start_x<<start_y<<start_z<<end_x<<end_y<<end_z;
	
	long pagesz_vim = vx*vy*vz*vc;
	
	unsigned char *pVImg = 0;
	
	try
	{
		pVImg = new unsigned char [pagesz_vim];
	}
	catch (...) 
	{
		printf("Fail to allocate memory.\n");
		return;
	}
	
	// init
	for(long i=0; i<pagesz_vim; i++)
	{
		pVImg[i] = 0;
	}

	long x_s = start_x + vim.min_vim[0];
	long y_s = start_y + vim.min_vim[1];
	long z_s = start_z + vim.min_vim[2];
	
	long x_e = end_x + vim.min_vim[0];
	long y_e = end_y + vim.min_vim[1];
	long z_e = end_z + vim.min_vim[2];
	
	qDebug()<<"min ..."<<vim.min_vim[0]<<vim.min_vim[1]<<vim.min_vim[2];
	
	ImagePixelType datatype;
	
	cout << "satisfied image: "<< vim.lut[0].fn_img << endl;
	
	//
	char * curFileSuffix = getSurfix(const_cast<char *>(vim.lut[0].fn_img.c_str()));
	
	cout << "suffix ... " << curFileSuffix << endl; // tif lsm
	
	QString curPath = curFilePath;
	
	string fn = curPath.append( QString(vim.lut[0].fn_img.c_str()) ).toStdString();
	
	
	qDebug()<<"testing..."<<curFilePath<< fn.c_str();
	//
	char * imgSrcFile = const_cast<char *>(fn.c_str());
	
	size_t s1_t = clock();
	
	// loading relative imagg files
	V3DLONG *sz_relative = 0; 
	int datatype_relative = 0;
	unsigned char* relative1d = 0;
	
	loadImage(imgSrcFile, relative1d, sz_relative, datatype_relative); //
	
	long rx=sz_relative[0], ry=sz_relative[1], rz=sz_relative[2], rc=sz_relative[3];
	
	if(datatype_relative==1)
		datatype = V3D_UINT8;
	
	size_t e1_t = clock();
	
	cout<<"time elapse for read tmpstack ... "<<e1_t-s1_t<<endl;
	for(long c=0; c<rc; c++)
	{
		long o_c = c*vx*vy*vz;
		long o_r_c = c*rx*ry*rz;
		for(long k=z_s; k<z_e; k++)
		{
			long o_k = o_c + (k-z_s)*vx*vy;
			long o_r_k = o_r_c + (k)*rx*ry;
			
			for(long j=y_s; j<y_e; j++)
			{
				long o_j = o_k + (j-y_s)*vx;
				long o_r_j = o_r_k + (j)*rx;
				for(long i=x_s; i<x_e; i++)
				{
					long idx = o_j + i-x_s;
					long idx_r = o_r_j + (i);
					pVImg[idx] = relative1d[idx_r];
				}
			}
		}
	}
	
	if(relative1d) {delete []relative1d; relative1d=0;}
	
	size_t end1_t = clock();
	
	cout<<"time elapse ... "<<end1_t-start_t<<endl;
	
	//display
	Image4DSimple p4DImage;
	
	p4DImage.setData((unsigned char*)pVImg, vx, vy, vz, vc, datatype);
	
	v3dhandle curwin;
	
	if(!callback->currentImageWindow())
		curwin = callback->newImageWindow();
	else
		curwin = callback->currentImageWindow();
	
	callback->setImage(curwin, &p4DImage);
	callback->setImageName(curwin, "Image");
	callback->updateImageWindow(curwin);
	
	callback->pushImageIn3DWindow(curwin);
	
	// time consumption
	size_t end_t = clock();
	
	cout<<"time elapse after loading configuration info ... "<<end_t-start_t<<endl;
}
XMapView::XMapView(QWidget *parent)
:QWidget(parent)
{		
	Gtype = PixmapType;
	m_scale = 1.0;
	//  m_shear = 0.0;
	//  m_rotation = 0.0;
	myCursor = QCursor(Qt::OpenHandCursor);
	
	b_displayFocusCrossLine = true;
		
	Ptype = imgPlaneUndefined; 
	cur_focus_pos = 1;
	compressed = 0; 
	Ctype = colorRGB; 
	
	// set a default map
	pixmap = QPixmap(256, 256);
	pixmap.fill(Qt::red);
	
	focusPosInWidth = pixmap.width()/2.0;
	focusPosInHeight = pixmap.height()/2.0;
	
	bMouseCurorIn = false;
	b_mouseend = true;
	
	curDisplayCenter = QPoint(pixmap.width()/2.0, pixmap.height()/2.0);
	
	b_moveCurrentLandmark = false; //reset it initially
	
	disp_scale = 1;
	disp_width = disp_scale * pixmap.width();
	disp_height = disp_scale * pixmap.height();
		
}
void ImageSetWidget::drawdata()
{
	 Bcopy = true;
	//qDebug()<<"draw";
	long s_x = xy_view->start_x;
	long s_y = xy_view->start_y;
	long s_z = xy_view->start_z;
	
    long e_x = xy_view->end_x;
	long e_y = xy_view->end_y;
	long e_z = xy_view->end_z;	
	long tem;
	if (s_x > e_x)
	{
		tem =e_x;
		e_x = s_x;
		s_x = tem ;
	}
	if (s_y > e_y)
	{
		tem =e_y;
		e_y = s_y;
		s_y = tem;
	}
	
	qDebug()<<"mapview_ImageN"<<s_x<<s_y<<s_z<<e_x<<e_y<<e_z;
	
	update_v3dviews(callback1, s_x*scaleFactor, s_y*scaleFactor, s_z*scaleFactor,e_x*scaleFactor, e_y*scaleFactor, e_z*scaleFactor);
	
	Bcopy = true;

}
void ImageSetWidget::updateGUI()
{
	
    cur_x = xValueSpinBox->text().toInt(); // / scaleFactor;
	cur_y = yValueSpinBox->text().toInt(); // / scaleFactor;
	cur_z = zValueSpinBox->text().toInt(); // / scaleFactor;
	
	update_triview();
	
	xy_view->update();
	xy_view->repaint();
	
	yz_view->update();
	yz_view->repaint();
	
	zx_view->update();
	zx_view->repaint();
	
	
}
void ImageSetWidget::createGUI()
{
	/* Set up the data related GUI */
	dataGroup = new QGroupBox(this);
	dataGroup->setTitle("Compressed data");
	
	viewGroup = new QGroupBox(dataGroup);
	viewGroup->setTitle("Map Views ");
	
	xy_view = new XMapView(viewGroup);
	long x = cx/2;
	long y = cy/2;
	long z = cz/2;
 	
	//qDebug()<<"xyviewcurx ..."<<x/2<<y/2<<z/2;	
	
	xy_view->setImgData(imgPlaneZ,sz_compressed,x,y,z,compressed1d,colorRGB); //because the second parameter is 0 (NULL pointer), then just load the default maps for this view
	
	xy_view->set_disp_width(cx);
	xy_view->set_disp_height(cy);
	xy_view->set_disp_scale(1);
	xy_view->setFixedWidth(xy_view->get_disp_width());
	xy_view->setFixedHeight(xy_view->get_disp_height());
	xy_view->setFocusPolicy(Qt::ClickFocus);
	
	yz_view = new XMapView(viewGroup);

	yz_view->setImgData(imgPlaneX, sz_compressed,x,y,z,compressed1d,  colorRGB); //because the second parameter is 0 (NULL pointer), then just load the default maps for this view
	
	yz_view->set_disp_width(cz);
	yz_view->set_disp_height(cy);
	yz_view->set_disp_scale(1);
	yz_view->setFixedWidth(yz_view->get_disp_width());
	yz_view->setFixedHeight(yz_view->get_disp_height());
	yz_view->setFocusPolicy(Qt::ClickFocus);
	
	zx_view = new XMapView(viewGroup);
	zx_view->setImgData(imgPlaneY, sz_compressed,x,y,z,compressed1d,  colorRGB); //because the second parameter is 0 (NULL pointer), then just load the default maps for this view
	
	zx_view->set_disp_width(cx);
	zx_view->set_disp_height(cz);
	zx_view->set_disp_scale(1);
	zx_view->setFixedWidth(zx_view->get_disp_width());
	zx_view->setFixedHeight(zx_view->get_disp_height());
	zx_view->setFocusPolicy(Qt::ClickFocus);
	
	//qDebug()<<"disp_x_y ..."<<xy_view->get_disp_width()<<xy_view->get_disp_height();		// setup the control panel
	
	mainGroup = new QGroupBox(this);
	mainGroup->setFixedWidth(300);
	mainGroup->setTitle("Options");
	
	//qDebug()<<"options ...";
	
	// focus planes group
	
	coordGroup = new QGroupBox(mainGroup);
	coordGroup->setAttribute(Qt::WA_ContentsPropagated);
	coordGroup->setTitle("Focus Coordinates");
	
	xSliderLabel = new QLabel("X", coordGroup);
	
	xValueSpinBox = new QSpinBox;
	
	xValueSpinBox->setMaximum(cx-1); xValueSpinBox->setMinimum(0); xValueSpinBox->setValue(cx/2); xValueSpinBox->setSingleStep(int(scaleFactor));
	
	ySliderLabel = new QLabel("Y", coordGroup);
	
	yValueSpinBox = new QSpinBox;
	
	yValueSpinBox->setMaximum(cy-1); yValueSpinBox->setMinimum(0); yValueSpinBox->setValue(cy/2); yValueSpinBox->setSingleStep(int(scaleFactor));
	
	zSliderLabel = new QLabel("Z", coordGroup);
	zValueSpinBox = new QSpinBox;
	
	zValueSpinBox->setMaximum(cz-1); zValueSpinBox->setMinimum(0); zValueSpinBox->setValue(cz/2); zValueSpinBox->setSingleStep(int(scaleFactor));

	// focus draw group
	
	QGroupBox * landmarkGroup = new QGroupBox(mainGroup);
	landmarkGroup->setTitle("draw data");
	
	dataCopyButton = new QPushButton(landmarkGroup);
	dataCopyButton->setText("draw");
	
	//qDebug()<<"Coordinates ...";
	
	// All layouts
	allLayout = new QHBoxLayout(this);
	allLayout->addWidget(dataGroup);
	allLayout->addWidget(mainGroup);
	
	xyzViewLayout = new QGridLayout(viewGroup);
	xyzViewLayout->addWidget(xy_view, 0, 0, 1, 1, Qt::AlignRight | Qt::AlignBottom);
	xyzViewLayout->addWidget(yz_view, 0, 1, 1, 1, Qt::AlignLeft | Qt::AlignBottom);
	xyzViewLayout->addWidget(zx_view, 1, 0, 1, 1, Qt::AlignRight | Qt::AlignTop);
	xyzViewLayout->update();
	
	dataGroupLayout = new QVBoxLayout(dataGroup);
	dataGroupLayout->addWidget(viewGroup);
	dataGroupLayout->addStretch(0);
	
	// layout for focus planes
	coordGroupLayout = new QGridLayout(coordGroup);
	coordGroupLayout->addWidget(zSliderLabel, 0, 0, 1, 1);
	coordGroupLayout->addWidget(zValueSpinBox, 0, 13, 1, 4);
	
	coordGroupLayout->addWidget(xSliderLabel, 1, 0, 1, 1);
	coordGroupLayout->addWidget(xValueSpinBox, 1, 13, 1, 4);
	
	coordGroupLayout->addWidget(ySliderLabel, 2, 0, 1, 1);
	coordGroupLayout->addWidget(yValueSpinBox, 2, 13, 1, 4);
	
	datacopyGroupLayout = new QGridLayout(landmarkGroup);
	datacopyGroupLayout->addWidget(dataCopyButton, 0, 0, 1, 4);
	
	// main control panel layout
	mainGroupLayout = new QVBoxLayout(mainGroup);
	mainGroupLayout->addWidget(coordGroup);
	mainGroupLayout->addWidget(landmarkGroup); 

	setLayout(allLayout);
	updateGeometry();
	allLayout->update();
	
	Bcopy = false;
	
	update_triview();
	
	//update_v3dviews(callback, start_x, start_y, start_z,end_x,end_y,end_z);
	
	connect(xValueSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateGUI()));
	connect(yValueSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateGUI()));
	connect(zValueSpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateGUI()));	
	connect(dataCopyButton, SIGNAL(clicked()), this, SLOT(drawdata()));
	
}	//
ImageSetWidget::ImageSetWidget(V3DPluginCallback &callback, QWidget *parent, QString m_FileName, QString curFilePathInput, float scaleFactorInput)
{
	callback1 = &callback;
	
	curFilePath = curFilePathInput;
	string filename = m_FileName.toStdString();
	
	qDebug()<<"filename ..."<<filename.c_str();
	vim.y_load(filename);
	scaleFactor = scaleFactorInput;
	long sx=vim.sz[0], sy=vim.sz[1], sz=vim.sz[2];
	
	qDebug()<<"sxyx ..."<<sx<<sy<<sz;
	//****************************************************************
	// suppose compressed image saved as .tif
	QString m_FileName_compressed = m_FileName;
	
	m_FileName_compressed.chop(3); // ".tc"
	m_FileName_compressed.append(".tif");
	// loading compressed image files
	sz_compressed = 0; 
	int datatype_compressed = 0;
	compressed1d = 0;
	loadImage(const_cast<char *>(m_FileName_compressed.toStdString().c_str()), compressed1d, sz_compressed, datatype_compressed); //careful
	cx=sz_compressed[0], cy=sz_compressed[1], cz=sz_compressed[2], cc=sz_compressed[3];
	channel_compressed_sz = cx*cy*cz;
	init_x = cx/2, init_y = cy/2, init_z = cz/2; 
	qDebug()<<"compressedsxyx ..."<<cx<<cy<<cz;			
	createGUI();			
}
void ImageSetWidget::update_triview()
{
	cur_x = xValueSpinBox->text().toInt(); // / scaleFactor;
	cur_y = yValueSpinBox->text().toInt(); // / scaleFactor;
	cur_z = zValueSpinBox->text().toInt(); // / scaleFactor;
	
	xy_view->setImgData(imgPlaneZ, sz_compressed,cur_x,cur_y,cur_z, compressed1d, colorRGB);
	
	yz_view->setImgData(imgPlaneX, sz_compressed,cur_x,cur_y,cur_z,compressed1d, colorRGB);
	
	zx_view->setImgData(imgPlaneY, sz_compressed,cur_x,cur_y,cur_z,compressed1d, colorRGB);
		
}

template <class T> QPixmap copyRaw2QPixmap(const T * pada, V3DLONG sz0, V3DLONG sz1, V3DLONG sz2, V3DLONG sz3, 
										   V3DLONG cz0, V3DLONG cz1, V3DLONG cz2,ImagePlaneDisplayType disType, 
										   double *p_vmax, double *p_vmin)
{
	switch (disType)
	{
		case imgPlaneX:
			return copyRaw2QPixmap_xPlanes(pada, sz0, sz1, sz2, sz3, cz0,cz1,cz2,p_vmax, p_vmin);
			break;
			
		case imgPlaneY:
			return copyRaw2QPixmap_yPlanes(pada, sz0, sz1, sz2, sz3,cz0,cz1,cz2, p_vmax, p_vmin);
			break;
			
		case imgPlaneZ:
			return copyRaw2QPixmap_zPlanes(pada, sz0, sz1, sz2, sz3,cz0,cz1,cz2, p_vmax, p_vmin);
			break;
			
		default:
			printf("Undefined ImagePlaneDisplayType. Check your code.\n");
			return QPixmap(0,0); //return an empty image for this prohibited case
			break;
	}
}

void XMapView::mousePressEvent(QMouseEvent *e)
{
	switch (e->button())
	{
		case Qt::LeftButton:
			mouseLeftButtonPressEvent(e);
			break;
		case Qt::RightButton:
			mouseRightButtonPressEvent(e);
		default:
			break;
	}
}
void XMapView::mouseReleaseEvent(QMouseEvent * e)
{
	flag_syn = false;
//	 if (QApplication::keyboardModifiers()==Qt::ControlModifier)
//	 {
//		dragEndPosition = e->pos();
//		b_mouseend = false;
//		setCursor(Qt::ArrowCursor);
//	 }
}
void XMapView::mouseRightButtonPressEvent(QMouseEvent *e)
{
	//flag_syn = true;
	if (QApplication::keyboardModifiers()==Qt::ControlModifier)
	{
		dragEndPosition = e->pos();
		b_mouseend = false;
		setCursor(Qt::ArrowCursor);
		flag_syn = true;
		end_x = dragEndPosition.x();
		end_y = dragEndPosition.y();
		end_z = cz ;
		qDebug()<<"rrrexyz...."<<end_x<<end_y<<end_z;
		//update_v3dviews(mapCallback, dragStartPosition.x(),dragStartPosition.y(),cur_z, dragEndPosition.x(), dragEndPosition.y(),cz);
		
	}
}
void XMapView::mouseLeftButtonPressEvent(QMouseEvent *e) //080101
{
	//flag_syn = false;
	if (bMouseCurorIn && QApplication::keyboardModifiers()==Qt::ControlModifier)
	{
		b_mouseend = true;
		dragStartPosition = e->pos();
		
		start_x = dragStartPosition.x();
		start_y = dragStartPosition.y();
		start_z = cur_z;
		setCursor(Qt::CrossCursor);
		//setCursor(myCursor);		
		update();
		
		qDebug()<<"LLLLsxyz...."<<start_x<<start_y<<start_z;
	}
}

void XMapView::mouseMoveEvent (QMouseEvent * e)
{
	//curMousePos = e->pos()/disp_scale;
	
	if (QApplication::keyboardModifiers()==Qt::ControlModifier) 
	{
		curMousePos = e->pos();
		//dragEndPosition= e->pos();
		end_x = curMousePos.x();
		end_y = curMousePos.y();
		end_z = cz ;
		
	}
	update();
}

void XMapView::enterEvent (QEvent * e)
{
	bMouseCurorIn = true;
}

void XMapView::leaveEvent (QEvent * e)
{
	//bMouseCurorIn = false;
	//update();
}

void XMapView::drawROI(QPainter *painter)
{
	if (bMouseCurorIn && b_mouseend)
	{
		painter->setPen(Qt::white );
		painter->setBrush(Qt::NoBrush);
		
		QRect r( dragStartPosition, curMousePos );
		painter->drawRect( r );
		//painter->drawRect(QRect(dragStartPosition.x(),dragStartPosition.y(),curMousePos.x(),curMousePos.y());
	}

}



