#ifndef CAD_SANITARY_SHOWER_H
#define CAD_SANITARY_SHOWER_H

#include "caditem.h"

class CAD_sanitary_shower : public CADitem
{
public:
    CAD_sanitary_shower();
    static QList<CADitem::ItemType> flangable_items();
    static QImage wizardImage();
    virtual void calculate();
    virtual void processWizardInput();
};

#endif // CAD_SANITARY_SHOWER_H