#include "videowidget.h"

#include <QRect>
#include <QPaintEvent>
#include <QPainter>

VideoWidget::VideoWidget(int width, int height, QWidget *parent) :
    QWidget(parent),
    buf(width*height)

{
    image = QImage(buf.data(), width, height, QImage::Format::Format_Grayscale8);
}

void VideoWidget::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    QRect rect = event->rect();
    painter.drawImage(rect, image, rect);
}

void VideoWidget::setFrame(const Leap::Frame& frame) {

    if(frame.images().count() != 2)
        return;

    Leap::Image frameImage = frame.images()[0];

    if( image.width() != frameImage.width() || image.height() != frameImage.height()) {
        std::cout << "ERROR: wrong frame size: " << frameImage.width() << ' ' << frameImage.height() << '\n';
        return;
    }

    memcpy(buf.data(), frameImage.data(), frameImage.width()*frameImage.height());

    update();
}
