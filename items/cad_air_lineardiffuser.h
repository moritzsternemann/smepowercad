#ifndef CAD_AIR_LINEARDIFFUSER_H
#define CAD_AIR_LINEARDIFFUSER_H

#include "caditem.h"
#include "cad_basic_duct.h"
#include "cad_basic_box.h"
#include "cad_basic_circle.h"

class CAD_air_lineardiffuser : public CADitem
{
public:
    CAD_air_lineardiffuser();
    virtual ~CAD_air_lineardiffuser();
    virtual QList<CADitemTypes::ItemType> flangable_items(int flangeIndex);
    virtual QImage wizardImage();
    virtual QString iconPath();
    virtual QString domain();
    virtual QString description();
    virtual void calculate();
    virtual void processWizardInput();
    virtual QMatrix4x4 rotationOfFlange(quint8 num);

    qreal l, a, a1, b, b1, dist, n, d;
    CAD_basic_box* upper;
    CAD_basic_duct* lower;

};

#endif // CAD_AIR_LINEARDIFFUSER_H
