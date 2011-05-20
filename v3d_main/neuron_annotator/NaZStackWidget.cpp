#include "NaZStackWidget.h"
#include <QPaintEvent>
#include <QDebug>
#include <QPainter>
#include <cmath>

#define INF 1e9

// funcs for converting data and create pixmap
// func converting kernel
template <class Tpre, class Tpost>
void converting(Tpre *pre1d, Tpost *pPost, V3DLONG imsz) {
    for(V3DLONG i=0; i<imsz; i++)
        pPost[i] = (Tpost) pre1d[i];
}

template <class T> QPixmap getXYPlane(const T * pdata, V3DLONG sx, V3DLONG sy, V3DLONG sz, V3DLONG sc, V3DLONG curz, float *p_vmax, float *p_vmin)
{
    QImage tmpimg = QImage(sx, sy, QImage::Format_RGB32);

    // qDebug()<<curz;

    int tr,tg,tb;

    V3DLONG i,j;
    float tmpr,tmpg,tmpb;
    float tmpr_min, tmpg_min, tmpb_min;

    if (sc>=3)
    {
        tmpb = p_vmax[2]-p_vmin[2]; tmpb = (tmpb==0)?1:tmpb;
        tmpb_min = p_vmin[2];
    }

    if (sc>=2)
    {
        tmpg = p_vmax[1]-p_vmin[1]; tmpg = (tmpg==0)?1:tmpg;
        tmpg_min = p_vmin[1];
    }

    if (sc>=1)
    {
        tmpr = p_vmax[0]-p_vmin[0]; tmpr = (tmpr==0)?1:tmpr;
        tmpr_min = p_vmin[0];
    }
    int pagesz = sx*sy*sz;
    long offset_k = sx*sy;

    switch (sc)
    {
        case 1:

            // qDebug()<<"r ...";

            for (long j = 0; j < sy; j ++)
            {
                long offset = curz*offset_k + j*sx;
                for (long i=0; i<sx; i++)
                {
                    long idx = offset + i;

                    tb = tg = tr = floor((pdata[idx]-tmpr_min)/tmpr*255.0);
                    tmpimg.setPixel(i, j, qRgb(tr, tg, tb));
                }
            }
            break;

        case 2:

            // qDebug()<<"rg ...";

            tb = 0;
            for (long j = 0; j < sy; j ++)
            {
                long offset = curz*offset_k + j*sx;
                for (long i=0; i<sx; i++)
                {
                    long idx = offset + i;
                    tr = floor((pdata[idx]-tmpr_min)/tmpr*255.0);
                    tg = floor((pdata[idx+pagesz]-tmpg_min)/tmpg*255.0);
                    tmpimg.setPixel(i, j, qRgb(tr, tg, tb));
                }
            }
            break;

        case 3:
        case 4:

            // qDebug()<<"rgb ..."<<tmpr<<tmpg<<tmpb;

            for (long j = 0; j < sy; j ++)
            {
                long offset = curz*offset_k + j*sx;
                for (long i=0; i<sx; i++)
                {
                    long idx = offset + i;

                    tr = floor((pdata[idx]-tmpr_min)/tmpr*255.0);
                    tg = floor((pdata[idx+pagesz]-tmpg_min)/tmpg*255.0);
                    tb = floor((pdata[idx+2*pagesz]-tmpb_min)/tmpb*255.0);
                    tmpimg.setPixel(i, j, qRgb(tr, tg, tb));
                }
            }
            break;

        default:
            break;
    }
    return QPixmap::fromImage(tmpimg);

}

NaZStackWidget::NaZStackWidget(QWidget * parent)
    : QWidget(parent)
{
    pData1d = NULL;
    pDispData1d = NULL;

    pixmap = QPixmap(256, 256);
    pixmap.fill(Qt::black);

    scale_x = 1.0; scale_y = 1.0;
    // dispscale = 0.9;

    translateMouse_scale = 1;

    b_mouseleft = false;
    b_mouseright = false;
    b_mousemove = false;

    bMouseCurorIn = false;
    bMouseDone = false;

    m_square_pos.setX(sx/2);
    m_square_pos.setY(sy/2);
    cr = 25;

    // initHDRViewer(imgsz, data1d, datatype);
    cur_c = COLOR_RED;
    setFocusPolicy(Qt::ClickFocus);

    connect(this, SIGNAL(curColorChannelChanged(NaZStackWidget::Color)), this, SLOT(do_HDRfilter()));
    connect(this, SIGNAL(roiChanged()), this, SLOT(updatePixmap()));
}

NaZStackWidget::~NaZStackWidget() {}

void NaZStackWidget::paintEvent(QPaintEvent *event)
{
    // qDebug()<<"painting ...";

    QPainter painter(this);
    //painter.save()

    // Color background black

    painter.fillRect(0, 0, width(), height(), Qt::black);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    // TODO - these values do not need to be recalculated every paint.
    // ...but after either widget resize or image load.
    // scale image to to viewport
    float temp_scale_x = (float)width()/(float)sx;
    float temp_scale_y = (float)height()/(float)sy;
    // fit to window; keep aspect ratio
    float scale = temp_scale_x < temp_scale_y ? temp_scale_x : temp_scale_y;
    scale_x = scale;
    scale_y = scale;
    // translate to center image in viewport
    image_focus_x = sx/2;
    image_focus_y = sy/2;

//      float cx = 0.45*(float)dispwidth/dispscale;
//      float cy = 0.45*(float)dispheight/dispscale;
//
//      QPointF center(cx, cy);
    // QPointF center(width()/2, height()/2);

    painter.translate(width()/2 - scale_x*image_focus_x, height()/2 - scale_y*image_focus_y);
    // painter.translate(center);
    painter.scale(scale_x, scale_y);
    //painter.translate(-center);
    // painter.translate(width()/2 - scale_x * image_focus_x, height()/2 - scale_y * image_focus_y);

//      float translate_px = cx-(float)dispwidth/2.0;
//      float translate_py = cy-(float)dispheight/2.0;

    painter.drawPixmap(0, 0, pixmap);

    // ROI
    drawROI(&painter);
}

void NaZStackWidget::drawROI(QPainter *painter)
{
    if (bMouseCurorIn)
    {
        painter->setPen(Qt::yellow );
        painter->setBrush(Qt::NoBrush);

        if(b_mousemove)
        {
            if(b_mouseright)
            {
                QRect r( startMousePosR, curMousePosR );
                painter->drawRect( r );
            }
            else if(b_mouseleft)
            {
                if(bMouseDone)
                {
                    QSizeF sz(2*cr, 2*cr);
                    QRectF square = rectangle_around(m_square_pos, sz);
                    painter->drawRect(square);
                }
            }
        }
        else if(bMouseDone)
        {
            QSizeF sz(2*cr, 2*cr);
            QRectF square = rectangle_around(m_square_pos,sz);
            painter->drawRect(square);
        }

        if( checkROIchanged() )
        {
            do_HDRfilter();
        }
    }
    else
    {
        // qDebug()<<"initial a square roi ...";

        // init a square
        cx = sx/2;
        cy = sy/2;
        cr = 25;

        start_x = cx - cr;
        end_x = cx + cr;

        if(start_x<0) start_x = 0;
        if(end_x>=sx) end_x = sx-1;

        start_y = cy -cr;
        end_y = cy + cr;

        if(start_y<0) start_y = 0;
        if(end_y>=sy) end_y = sy-1;

        startMousePos.setX(start_x);
        startMousePos.setY(start_y);

        endMousePos.setX(end_x);
        endMousePos.setY(end_y);

        QSizeF sz(cr, cr);
        QRectF square = rectangle_around(m_square_pos,sz);
        painter->drawRect(square);
    }

}

void NaZStackWidget::enterEvent (QEvent * e) // mouse found
{
    bMouseCurorIn = true;
    update();
}

void NaZStackWidget::mouseLeftButtonPressEvent(QMouseEvent *e) // mouse left button
{
    if (bMouseCurorIn)
    {
        //if(cursorInRoi(e))
        {
            b_mouseleft = true;
            b_mouseright = false;
            b_mousemove = false;
            bMouseDone = true;

            startMousePosL = e->pos();

            startMousePosL = viewportXYToImageXY(startMousePosL);

            QRectF square = rectangle_around(m_square_pos);

            if (square.contains(startMousePosL))
            {
                m_offset = square.center() - startMousePosL;
            }

            // qDebug()<<"left press ..."<< startMousePosL.x() << startMousePosL.y();

            setCursor(Qt::CrossCursor);
            update();
        }
    }
}

void NaZStackWidget::mouseRightButtonPressEvent(QMouseEvent *e) // mouse right button
{
    if (bMouseCurorIn)
    {
        b_mouseright = true;
        b_mouseleft = false;
        b_mousemove = false;
        bMouseDone = false;

        startMousePosR = e->pos(); //

        startMousePosR = viewportXYToImageXY(startMousePosR);
        // startMousePosR.setX( startMousePosR.x()/scale_x );
        // startMousePosR.setY( startMousePosR.y()/scale_y );

        // qDebug()<<"right press ..."<< startMousePosR.x() << startMousePosR.y();

        setCursor(Qt::CrossCursor);
        update();
    }
}

int NaZStackWidget::getCurrentZSlice() {
    return cur_z + 1; // 1-based index for API; 0-based internal
}

int NaZStackWidget::getCurrentBoxSize() {
    return cr; //
}

void NaZStackWidget::setCurrentZSlice(int slice) {
    if (slice < 1) return; // value too small
    if (slice > sz) return; // value too big
    if (cur_z == slice - 1) return; // no change; ignore
    cur_z = slice - 1;
    do_HDRfilter();
    do_HDRfilter_zslice();
    update();
    // qDebug("Z slice updated");
    emit curZsliceChanged(slice);
}

void NaZStackWidget::wheelEvent(QWheelEvent * e) // mouse wheel
{
    // qDebug("wheel");
    b_mousemove = false;

    int numDegrees = e->delta()/8;
    int numTicks = numDegrees/15;
    // Some mouse wheels have a finer scroll increment; at least move a bit.
    if ((e->delta() != 0) && (numTicks == 0))
        numTicks = e->delta() > 0 ? 1 : -1;
    // qDebug() << "number of ticks = " << numTicks;

    setCurrentZSlice(getCurrentZSlice() + numTicks);
}

void NaZStackWidget::mouseMoveEvent (QMouseEvent * e) // mouse move
{
    if (bMouseCurorIn)
    {
        b_mousemove = true;

        if(b_mouseright)
        {
            bMouseDone = false;

            curMousePosR = e->pos();
            curMousePosR = viewportXYToImageXY(curMousePosR);

            if (curMousePosR.x() < 0)
            {
                curMousePosR.setX(0);
            }
            else if (curMousePosR.x() > sx)
            {
                curMousePosR.setX(sx);
            }

            if (curMousePosR.y()<0)
            {
                curMousePosR.setY(0);
            }
            else if (curMousePosR.y() > sy)
            {
                curMousePosR.setY(sy);
            }

            // curMousePosR.setX( curMousePosR.x()/scale_x );
            // curMousePosR.setY( curMousePosR.y()/scale_y );

            // qDebug()<<"right press move ..."<< curMousePosR.x() << curMousePosR.y();
        }

        if(b_mouseleft)
        {
            bMouseDone = true;

            curMousePosL = e->pos();
            curMousePosL = viewportXYToImageXY(curMousePosL);

            if (curMousePosL.x() < 0)
            {
                curMousePosL.setX(0);
            }
            else if (curMousePosL.x() > sx)
            {
                curMousePosL.setX(sx);
            }

            if (curMousePosL.y()<0)
            {
                curMousePosL.setY(0);
            }
            else if (curMousePosL.y() > sy)
            {
                curMousePosL.setY(sy);
            }

            // curMousePosL.setX( curMousePosL.x()/scale_x );
            // curMousePosL.setY( curMousePosL.y()/scale_y );

            setSquarePos(curMousePosL + m_offset);
        }

    }
    update();
}

void NaZStackWidget::mousePressEvent(QMouseEvent *e) // mouse button press
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

void NaZStackWidget::mouseReleaseEvent(QMouseEvent * e) // mouse button release
{
    b_mousemove = false;

    if (bMouseCurorIn)
    {
        if(b_mouseright)
        {
            endMousePosR = e->pos();
            endMousePosR = viewportXYToImageXY(endMousePosR);
            setCursor(Qt::ArrowCursor);

            if (endMousePosR.x() < 0)
            {
                endMousePosR.setX(0);
            }
            else if (endMousePosR.x() > sx)
            {
                endMousePosR.setX(sx);
            }

            if (endMousePosR.y()<0)
            {
                endMousePosR.setY(0);
            }
            else if (endMousePosR.y() > sy)
            {
                endMousePosR.setY(sy);
            }

            // endMousePosR.setX( endMousePosR.x()/scale_x );
            // endMousePosR.setY( endMousePosR.y()/scale_y );

            // qDebug()<<"right release ..."<< endMousePosR.x() << endMousePosR.y();

            // adjust pos
            float top_x, top_y, bottom_x, bottom_y;

            top_x = qMin( startMousePosR.x(), endMousePosR.x() );
            top_y = qMin( startMousePosR.y(), endMousePosR.y() );

            bottom_x = qMax( startMousePosR.x(), endMousePosR.x() );
            bottom_y = qMax( startMousePosR.y(), endMousePosR.y() );

            startMousePos.setX( top_x );
            startMousePos.setY( top_y );

            endMousePos.setX( bottom_x );
            endMousePos.setY( bottom_y );

            m_square_pos.setX( startMousePos.x() + (endMousePos.x() - startMousePos.x())/2 );
            m_square_pos.setY( startMousePos.y() + (endMousePos.y() - startMousePos.y())/2 );

            int old_cr = cr;
            cr = qMax((endMousePos.x() - startMousePos.x())/2, (endMousePos.y() - startMousePos.y())/2);

            bMouseDone = true;

            // qDebug()<<"x, y ..."<<startMousePos.x()<<startMousePos.y()<<endMousePos.x()<<endMousePos.y();

            //
            b_mouseright = false;
            if (old_cr != cr) emit boxSizeChanged(cr);
        }


        if(b_mouseleft)
        {
            setCursor(Qt::ArrowCursor);

            //
            b_mouseleft = false;
            bMouseDone = true;
        }

    }

    update();
}

void NaZStackWidget::setSquarePos(const QPointF &pos)
{
    // qDebug() << "square pos = " << pos.x() << ", " << pos.y();
    const QRect oldRect = rectangle_around(m_square_pos).toAlignedRect();
    m_square_pos = pos;

    //
    float top_x, top_y, bottom_x, bottom_y;

    top_x = m_square_pos.x() - cr;
    top_y = m_square_pos.y() - cr;

    bottom_x = m_square_pos.x() + cr;
    bottom_y = m_square_pos.y() + cr;

    if(top_x<1) top_x = 1;
    if(top_y<1) top_y = 1;

    if(bottom_x>sx) bottom_x = sx;
    if(bottom_y>sy) bottom_y = sy;

    startMousePos.setX( top_x );
    startMousePos.setY( top_y );

    endMousePos.setX( bottom_x );
    endMousePos.setY( bottom_y );

}

QRectF NaZStackWidget::rectangle_around(const QPointF &p, const QSizeF &size)
{
    QRectF rect(p, size);
    rect.translate(-size.width()/2, -size.height()/2);
    return rect;
}

//
bool NaZStackWidget::checkROIchanged()
{
    bool flag = false;

    if(start_x != startMousePos.x()-1)
    {
        start_x = startMousePos.x()-1;
        flag = true;
    }

    if(end_x != endMousePos.x()-1)
    {
        end_x = endMousePos.x()-1;
        flag = true;
    }

    if(start_y != startMousePos.y()-1)
    {
        start_y = startMousePos.y()-1;
        flag = true;
    }

    if(end_y != endMousePos.y()-1)
    {
        end_y = endMousePos.y()-1;
        flag = true;
    }

    //
    return flag;
}

// HDR filter
void NaZStackWidget::do_HDRfilter()
{
    // widget might not be initialized
    if (cur_c < 1) return;
    if (cur_c > 3) return;
    if (!pData1d) return;

    start_x = startMousePos.x()-1;
    end_x = endMousePos.x()-1;

    start_y = startMousePos.y()-1;
    end_y = endMousePos.y()-1;

    V3DLONG tmpsum = start_x + end_x;
    start_x = start_x<=end_x?start_x:end_x;
    end_x = tmpsum - start_x;

    tmpsum = start_y + end_y;
    start_y = start_y<=end_y?start_y:end_y;
    end_y = tmpsum - start_y;

    if(start_x<0) start_x = 0;
    if(start_y<0) start_y = 0;

    if(end_x>sx) end_x = sx-1;
    if(end_y>sy) end_y = sy-1;

    V3DLONG pagesz = sx*sy*sz;

    // min_max
    V3DLONG c = cur_c-1;

    min_roi[c] = INF;
    max_roi[c] = -INF;

    V3DLONG offset_c = c*pagesz;

    V3DLONG offset_z = cur_z * sx * sy; // current slice

    for(V3DLONG j=start_y; j<end_y; j++)
    {
        V3DLONG offset_j = offset_c + offset_z + j*sx;
        for(V3DLONG i=start_x; i<end_x; i++)
        {
            V3DLONG idx = offset_j + i;

            float curval = pData1d[idx];

            if(min_roi[c]>curval) min_roi[c] = curval;
            if(max_roi[c]<curval) max_roi[c] = curval;
        }
    }

    scale_roi[c] = max_roi[c] - min_roi[c];

    // filter
    do_HDRfilter_zslice();

    // restore roi min max
    for(V3DLONG ic=0; ic<sc; ic++)
    {
        if(ic==c) continue;

        min_roi[ic] = min_img[ic];
        max_roi[ic] = max_img[ic];
        scale_roi[ic] = scale_img[ic];
    }

    //
    emit roiChanged();

}

// z slice filter
void NaZStackWidget::do_HDRfilter_zslice()
{
    if (!pData1d) return; // data not initialized yet.
    if (!pDispData1d) return; // race condition?

    V3DLONG pagesz = sx*sy;
    V3DLONG channelsz = pagesz*sz;
    V3DLONG c = cur_c-1;
    V3DLONG offset_c = c*channelsz;
    V3DLONG offset_z = cur_z * pagesz;

    for(V3DLONG i=0; i<pagesz; i++)
    {
        V3DLONG idx = offset_c + offset_z + i;

        float curval = pData1d[idx];

        if(curval<min_roi[c])
        {
            pDispData1d[idx] = min_roi[c];
        }
        else if(curval>max_roi[c])
        {
            pDispData1d[idx] = max_roi[c];
        }
        else
        {
            pDispData1d[idx] = curval;
        }
    }

}

// copy data
void NaZStackWidget::copydata2disp()
{
    V3DLONG c = cur_c - 1;

    V3DLONG pagesz = sx*sy*sz;

    for(V3DLONG ic = 0; ic<sc; ic++)
    {
        if(ic==c) continue;

        V3DLONG offset_c = ic*pagesz;

        for(V3DLONG i=0; i<pagesz; i++)
        {
            V3DLONG idx = offset_c + i;
            pDispData1d[idx] = pData1d[idx];
        }

        min_roi[ic] = min_img[ic];
        max_roi[ic] = max_img[ic];
        scale_roi[ic] = scale_img[ic];

    }
}

// update pixelmap
void NaZStackWidget::updatePixmap()
{
    pixmap = getXYPlane((float *)pDispData1d, sx, sy, sz, sc, cur_z, max_roi, min_roi);
    update();
}

// Load image data from an in-memory image
bool NaZStackWidget::loadMy4DImage(const My4DImage* img, const My4DImage* neuronMaskImage)
{
    V3DLONG imageSize[4] = {img->getXDim(), img->getYDim(), img->getZDim(), img->getCDim()};
    initHDRViewer(imageSize, img->getRawData(), img->getDatatype());
    // dispheight = sx;
    // dispwidth = sy;
    return true;
}

void NaZStackWidget::initHDRViewer(const V3DLONG *imgsz, const unsigned char *data1d, ImagePixelType datatype)
{
    sx = imgsz[0];
    sy = imgsz[1];
    sz = imgsz[2];
    sc = imgsz[3];

    ratio_x2y = (float)sx/(float)sy;

    cur_z = sz/2; // init here

    V3DLONG pagesz = sx*sy*sz;
    V3DLONG imagesz = pagesz*sc;

    try
    {
        float *pFloatData = new float [imagesz];
        pDispData1d = new float [imagesz];

        //
        // qDebug()<<"run HDR filtering ...";

        if(datatype == V3D_UINT8)
        {
            converting<unsigned char, float>((unsigned char *)data1d, pFloatData, imagesz);

            // if(data1d) {delete []data1d; data1d = NULL;}

            pData1d = pFloatData; // keep original data in float datatype

            converting<float, float>(pData1d, pDispData1d, imagesz); // copy data

            // min_max
            for (V3DLONG c=0; c<sc; c++)
            {
                min_img[c] = INF;
                max_img[c] = -INF;

                V3DLONG offset_c = c*pagesz;
                for(V3DLONG i=0; i<pagesz; i++)
                {
                    if(min_img[c]>pFloatData[i+offset_c]) min_img[c] = pFloatData[i+offset_c];
                    if(max_img[c]<pFloatData[i+offset_c]) max_img[c] = pFloatData[i+offset_c];
                }
                scale_img[c] = max_img[c] - min_img[c];

                min_roi[c] = min_img[c];
                max_roi[c] = max_img[c];
                scale_roi[c] = scale_img[c];

                // qDebug()<<"max min ..."<<max_img[c] << min_img[c];
            }

            pixmap = getXYPlane((float *)pFloatData, sx, sy, sz, sc, cur_z, max_img, min_img); // initial focus plane

            update();
            // repaint();

        }
        else if(datatype == V3D_UINT16)
        {
            converting<unsigned short, float>((unsigned short *)data1d, pFloatData, imagesz);

            // if(data1d) {delete []data1d; data1d = NULL;}

            pData1d = pFloatData; // keep original data in float datatype

            converting<float, float>(pData1d, pDispData1d, imagesz); // copy data

            // min_max
            for (V3DLONG c=0; c<sc; c++)
            {
                min_img[c] = INF;
                max_img[c] = -INF;

                V3DLONG offset_c = c*pagesz;
                for(V3DLONG i=0; i<pagesz; i++)
                {
                    if(min_img[c]>pFloatData[i+offset_c]) min_img[c] = pFloatData[i+offset_c];
                    if(max_img[c]<pFloatData[i+offset_c]) max_img[c] = pFloatData[i+offset_c];
                }
                scale_img[c] = max_img[c] - min_img[c];

                min_roi[c] = min_img[c];
                max_roi[c] = max_img[c];
                scale_roi[c] = scale_img[c];

                // qDebug()<<"max min ..."<<max_img[c] << min_img[c];
            }

            pixmap = getXYPlane((float *)pFloatData, sx, sy, sz, sc, cur_z, max_img, min_img); // initial focus plane

            update();
            // repaint();

        }
        else if(datatype == V3D_FLOAT32)
        {
            converting<float, float>((float *)data1d, pFloatData, imagesz);

            // if(data1d) {delete []data1d; data1d = NULL;}
        }

    }
    catch(...)
    {
        printf("Error allocating memory. \n");
    }
}

void NaZStackWidget::setColorChannel(NaZStackWidget::Color col)
{
    // Ensure there are enough channels to support this color
    if ( (int)col > sc )
        return; // outside of range of available color channels
    cur_c = col;
    copydata2disp();
    emit curColorChannelChanged(col);
    update();
}

void NaZStackWidget::setRedChannel() {
    setColorChannel(COLOR_RED);
}

void NaZStackWidget::setGreenChannel() {
    setColorChannel(COLOR_GREEN);
}

void NaZStackWidget::setBlueChannel() {
    setColorChannel(COLOR_BLUE);
}

void NaZStackWidget::updateROIsize(int boxSize)
{
    if (cr == boxSize) return; // no change => ignore
    cr = boxSize;
    update();
    // repaint();
    emit boxSizeChanged(boxSize);
}

void NaZStackWidget::annotationModelUpdate(QString updateType) {
    // Stub
}
