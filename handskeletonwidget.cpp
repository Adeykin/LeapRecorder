#include "handskeletonwidget.h"

#include <QLabel>
#include <QVBoxLayout>
#include <vector>

HandSkeletonWidget::HandSkeletonWidget(QWidget *parent)
    : QGLWidget(parent),
      lastFrame(nullptr),
      updateFrame(false)
{
    //QLabel *label = new QLabel(this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    //label->setText("Hand skeleton");
    //layout->addWidget(label);
    //setLayout(layout);
}

void HandSkeletonWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-300.0, 300.0, -50.0, 450.0, -300.0, 350.0);

    glRotatef(-30, 1.0f, 0.0f, 0.0f);
    glRotatef(30, 0.0f, 1.0f, 0.0f);

    drawGrid();

    if(!lastFrame)
        return;

    drawHand();

    updateFrame = false;
}

void HandSkeletonWidget::drawHand()
{
    glMatrixMode(GL_MODELVIEW);
    glLineWidth(2.0f);
    glPointSize(4);
    glColor3d(1.0, 0.0, 0.0);
    Leap::HandList hands = lastFrame->hands();
    for (auto hl = hands.begin(); hl != hands.end(); ++hl)
    {
        const Leap::Hand hand = *hl;
        if( !hand.isRight() )
            continue;
        Leap::Vector palmPos = hand.palmPosition();

        glBegin(GL_POINTS);
            glVertex3d(palmPos.x, palmPos.y, -palmPos.z);
            glVertex3d(palmPos.x, palmPos.y, 200);
            glVertex3d(-200, palmPos.y, -palmPos.z);
            glVertex3d(palmPos.x, 0, -palmPos.z);
        glEnd();

        // Get fingers
        const Leap::FingerList fingers = hand.fingers();
        for (auto fl = fingers.begin(); fl != fingers.end(); ++fl)
        {
            std::vector<Leap::Vector> fingerSkelet;
            fingerSkelet.push_back(palmPos);
            const Leap::Finger finger = *fl;
            for (int b = 0; b < 4; ++b)
            {
                Leap::Bone::Type boneType = static_cast<Leap::Bone::Type>(b);
                Leap::Bone bone = finger.bone(boneType);

                if(b == 0)
                    fingerSkelet.push_back(bone.prevJoint());
                fingerSkelet.push_back(bone.nextJoint());
            }

            glBegin(GL_LINE_STRIP);
            for(int i = 0; i < fingerSkelet.size(); i++)
                glVertex3d(fingerSkelet[i].x, fingerSkelet[i].y, -fingerSkelet[i].z);
            glEnd();

        }
    }
}

void HandSkeletonWidget::drawGrid()
{
    glLineWidth(1.0f);
    glColor3d(0.0, 1.0, 0.0);

    int gridStep = 20;
    int xMin = -200, xMax = 200;
    int yMin = 0, yMax = 400;
    int zMin = -200, zMax = 200;

    glBegin(GL_LINES);
        // xOy
        for(int x = xMin; x <= xMax; x+=gridStep)
        {
            glVertex3d(x, yMin, zMax);
            glVertex3d(x, yMax, zMax);
        }
        for(int y = yMin; y <= yMax; y+=gridStep)
        {
            glVertex3d(xMin, y, zMax);
            glVertex3d(xMax, y, zMax);
        }

        // xOz
        for(int x = xMin; x <= xMax; x+=gridStep)
        {
            glVertex3d(x, yMin, zMin);
            glVertex3d(x, yMin, zMax);
        }
        for(int z = zMin; z <= zMax; z+=gridStep)
        {
            glVertex3d(xMin, yMin, z);
            glVertex3d(xMax, yMin, z);
        }

        // yOz
        for(int y = yMin; y <= yMax; y+=gridStep)
        {
            glVertex3d(xMin, y, zMin);
            glVertex3d(xMin, y, zMax);
        }
        for(int z = zMin; z <= zMax; z+=gridStep)
        {
            glVertex3d(xMin, yMin, z);
            glVertex3d(xMin, yMax, z);
        }
    glEnd();


    glColor3d(1.0,0.0,0.0);
    glBegin(GL_LINES);
        glVertex3d(0,0,0);
        glVertex3d(100,0,0);
    glEnd();
    glColor3d(0.0,1.0,0.0);
    glBegin(GL_LINES);
        glVertex3d(0,0,0);
        glVertex3d(0,100,0);
    glEnd();
    glColor3d(0.0,0.0,1.0);
    glBegin(GL_LINES);
        glVertex3d(0,0,0);
        glVertex3d(0,0,100);
    glEnd();
}

void HandSkeletonWidget::setFrame(Leap::Frame frame)
{
    std::cout << "Frame id: " << frame.id()
              << ", timestamp: " << frame.timestamp()
              << ", hands: " << frame.hands().count()
              << ", extended fingers: " << frame.fingers().extended().count()
              << ", tools: " << frame.tools().count()
              << ", gestures: " << frame.gestures().count() << std::endl;
    lastFrame.reset( new Leap::Frame(frame));
    updateFrame = true;
    update();
}

void HandSkeletonWidget::resizeGL(int width, int height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-300.0, 300.0, -50.0, 450.0, -300.0, 350.0);
    glViewport(0, 0, (GLint)width, (GLint)height);
}

void HandSkeletonWidget::initializeGL()
{
}

