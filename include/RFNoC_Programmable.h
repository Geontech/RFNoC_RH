/*
 * RFNoCProgrammable.h
 *
 *  Created on: Mar 19, 2017
 *      Author: pwolfram
 */

#ifndef RFNOC_PROGRAMMABLE_H_
#define RFNOC_PROGRAMMABLE_H_

#include <omniORB4/omniORB.h>
#include <uhd/device3.hpp>

#include <RFNoC_Persona.h>
#include <RFNoC_Utils.h>

typedef boost::function<BlockInfo(const CORBA::ULong &portHash)> getBlockInfoFromHashCallback;

typedef boost::function<void(const std::string &deviceID, getBlockInfoFromHashCallback getBlockFromHashCb)> setGetBlockInfoFromHashCallback;

class RFNoC_Persona;

class RFNoC_Programmable
{
    public:
        RFNoC_Programmable() {};
        virtual ~RFNoC_Programmable() {};

        virtual bool connectRadioRX(const CORBA::ULong &portHash, const BlockInfo &blockInfo) = 0;
        virtual bool connectRadioTX(const std::string &allocationId, const BlockInfo &blockInfo) = 0;
        virtual uhd::device3::sptr getUsrp() = 0;
        virtual void setPersonaMapping(const std::string &deviceId, RFNoC_Persona *persona) = 0;

    protected:
        std::map<std::string, RFNoC_Persona *> deviceIdToPersona;
};

#endif /* RFNOC_PROGRAMMABLE_H_ */
