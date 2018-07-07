#ifndef RFNOC_PROGRAMMABLE_H
#define RFNOC_PROGRAMMABLE_H

// CORBA Include(s)
#include <omniORB4/omniORB.h>

// Standard C++ Include(s)
#include <map>
#include <string>

// Local Include(s)
#include "RFNoC_Persona.h"
#include "RFNoC_Utils.h"

namespace RFNoC_Utils
{
	// Forward Declaration(s)
	class RFNoC_Persona;

	class RFNoC_Programmable
	{
		// Constructor(s) and/or Destructor
		public:
			RFNoC_Programmable() {}

			virtual ~RFNoC_Programmable() {}

		// Public Method(s)
		public:
			virtual bool connectRadioRX(PortHashType portHash, const BlockDescriptor &blockInfo) = 0;

			virtual bool connectRadioTX(const std::string &allocationId, const BlockDescriptor &blockInfo) = 0;

			virtual void setPersonaMapping(const std::string &deviceId, RFNoC_Persona *persona) = 0;

		protected:
			std::map<std::string, RFNoC_Persona *> deviceIdToPersona;
	};
}

#endif
