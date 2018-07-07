#ifndef RFNOC_PERSONA_H
#define RFNOC_PERSONA_H

// CORBA Include(s)
#include <omniORB4/CORBA.h>

// UHD Include(s)
#include <uhd.h>

// Local Include(s)
#include "RFNoC_Programmable.h"
#include "RFNoC_Utils.h"

namespace RFNoC_Utils
{
	// Forward Declaration(s)
	class RFNoC_Programmable;

	class RFNoC_Persona
	{
		// Constructor(s) and/or Destructor
		public:
			RFNoC_Persona() : programmable(NULL) {}

			virtual ~RFNoC_Persona() {}

		// Public Method(s)
		public:
			/*
			 * This method should return an RF-NoC block to the caller.
			 */
			virtual void getBlock(const BlockDescriptor &blockDescriptor) = 0;

			/*
			 * This method should return the block descriptor corresponding to the
			 * given port hash.
			 */
			virtual BlockDescriptor getBlockDescriptorFromHash(PortHashType portHash) = 0;

			virtual void incomingConnectionAdded(const std::string &resourceId, PortHashType portHash) = 0;

			virtual void incomingConnectionRemoved(const std::string &resourceId, PortHashType portHash) = 0;

			virtual void outgoingConnectionAdded(const std::string &resourceId,
												 const std::string &connectionId,
												 PortHashType portHash) = 0;

			virtual void outgoingConnectionRemoved(const std::string &resourceId,
												   const std::string &connectionId,
												   PortHashType portHash) = 0;

			virtual void setProgrammable(RFNoC_Programmable *programmable) { this->programmable = programmable; }

		// Protected Member(s)
		protected:
			RFNoC_Programmable *programmable;
	};
}

#endif
