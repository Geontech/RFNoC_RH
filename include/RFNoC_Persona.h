#ifndef RFNOC_PERSONA_H
#define RFNOC_PERSONA_H

#include <boost/function.hpp>
#include <omniORB4/CORBA.h>

#include <RFNoC_Programmable.h>
#include <RFNoC_Utils.h>

class RFNoC_Programmable;

class RFNoC_Persona
{
    public:
        RFNoC_Persona() : programmable(NULL) {};
        virtual ~RFNoC_Persona() {};

        virtual BlockInfo getBlockInfoFromHash(const CORBA::ULong &portHash) = 0;
        virtual void setProgrammable(RFNoC_Programmable *programmable) { this->programmable = programmable; };

    protected:
        RFNoC_Programmable *programmable;
};

#endif
