#ifndef CAD_AIR_DUCTYPIECE_H
#define CAD_AIR_DUCTYPIECE_H

#include "caditem.h"

class CAD_air_ductYpiece : public CADitem
{
public:
    CAD_air_ductYpiece();
    virtual void calculate();
    virtual void processWizardInput();
};

#endif // CAD_AIR_DUCTYPIECE_H
