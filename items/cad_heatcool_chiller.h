#ifndef CAD_HEATCOOL_CHILLER_H
#define CAD_HEATCOOL_CHILLER_H

#include "caditem.h"

class CAD_heatcool_chiller : public CADitem
{
public:
    CAD_heatcool_chiller();
    virtual void calculate();
};

#endif // CAD_HEATCOOL_CHILLER_H