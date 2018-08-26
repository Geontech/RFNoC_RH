#ifndef RFNOC_PERSONA_H
#define RFNOC_PERSONA_H

// CORBA Include(s)
#include <omniORB4/CORBA.h>

// UHD Include(s)
#include <uhd.h>

// Local Include(s)
#include "RFNoC_Programmable.h"
#include "RFNoC_Utils.h"

namespace RFNoC_RH
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
			virtual bool connectBlocks(const BlockDescriptor &outputDescriptor, const BlockDescriptor &inputDescriptor) = 0;

			/*
			 * This method should return an RF-NoC block to the caller. If the port was unset by the
			 * caller, the port used will be placed into blockDescriptor.
			 */
			virtual uhd::rfnoc::block_ctrl_base::sptr getBlock(BlockDescriptor &blockDescriptor) = 0;

			/*
			 * This method should return the block descriptor corresponding to the
			 * given port hash.
			 */
			virtual BlockDescriptor getBlockDescriptorFromHash(PortHashType portHash) = 0;

			virtual void incomingConnectionAdded(const std::string &resourceId,
												 const std::string &streamId,
												 PortHashType portHash) = 0;

			virtual void incomingConnectionRemoved(const std::string &resourceId,
												   const std::string &streamId,
												   PortHashType portHash) = 0;

			virtual void outgoingConnectionAdded(const std::string &resourceId,
												 const std::string &connectionId,
												 PortHashType portHash) = 0;

			virtual void outgoingConnectionRemoved(const std::string &resourceId,
												   const std::string &connectionId,
												   PortHashType portHash) = 0;

			virtual void setProgrammable(RFNoC_Programmable *programmable) { this->programmable = programmable; }

			virtual void setRxStreamDescriptor(const std::string &resourceId, const StreamDescriptor &streamDescriptor) = 0;

			virtual void setTxStreamDescriptor(const std::string &resourceId, const StreamDescriptor &streamDescriptor) = 0;

		// Protected Member(s)
		protected:
			RFNoC_Programmable *programmable;
	};
}

#endif
