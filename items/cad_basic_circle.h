#ifndef CAD_BASIC_CIRCLE_H
#define CAD_BASIC_CIRCLE_H

#include "caditem.h"
#include <QList>

class CAD_basic_circle : public CADitem
{
public:
    CAD_basic_circle();
    virtual ~CAD_basic_circle();
    static QList<CADitem::ItemType> flangable_items();
    static QImage wizardImage();
    virtual void calculate();
    virtual void processWizardInput();

    QVector3D center;
    qreal radius;
    qreal width;
    bool widthByLayer;
    bool widthByBlock;
    QList<QVector3D> circle;
};

#endif // CAD_BASIC_CIRCLE_H
