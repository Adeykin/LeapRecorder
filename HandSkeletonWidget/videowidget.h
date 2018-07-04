#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include "framehandler.h"
#include <QLabel>
#include <vector>

class VideoWidget : public QWidget, public IFrameHanler {
    //Q_OBJECT
public:
    VideoWidget(int windth, int height, QWidget* parent);
    void setFrame(const Leap::Frame& frame) override;
protected:
    void paintEvent(QPaintEvent* event) override;
private:
    //std::unique_ptr<Leap::Image> frameImage = nullptr;
    //std::shared_ptr<uint8_t> buf;
    //QImage image;
    //QPixmap pixmap;

    QImage image;
    //uint8_t buf[640*240];
    std::vector<uint8_t> buf;
};

#endif // VIDEOWIDGET_H

