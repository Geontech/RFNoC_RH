#ifndef RFNOC_PROGRAMMABLE_H
#define RFNOC_PROGRAMMABLE_H

// OSSIE Include(s)
#include <ossie/Resource_impl.h>

// Standard C++ Include(s)
#include <map>
#include <string>

// Local Include(s)
#include "RFNoC_Component.h"
#include "RFNoC_Persona.h"
#include "RFNoC_Utils.h"

namespace RFNoC_RH
{
	// Forward Declaration(s)
	class RFNoC_Persona;

	// Type Definition(s)
	typedef Resource_impl* (*RFNoC_Component_Constructor_Ptr)(int, char*[], RFNoC_Persona *persona);

	class RFNoC_Programmable
	{
		// Constructor(s) and/or Destructor
		public:
			RFNoC_Programmable() {}

			virtual ~RFNoC_Programmable() {}

		// Public Method(s)
		public:
			virtual bool connectBlocks(const BlockDescriptor &outputDescriptor, const BlockDescriptor &inputDescriptor) = 0;

			virtual Resource_impl* generateResource(int argc, char* argv[], RFNoC_Component_Constructor_Ptr fnptr, const char* libraryName) = 0;

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

			virtual void setPersonaMapping(const std::string &deviceId, RFNoC_Persona *persona) = 0;

			virtual void setRxStreamDescriptor(const std::string &resourceId, const StreamDescriptor &streamDescriptor) = 0;

			virtual void setTxStreamDescriptor(const std::string &resourceId, const StreamDescriptor &streamDescriptor) = 0;

		protected:
			std::map<std::string, RFNoC_Persona *> deviceIdToPersona;
	};
}

#endif
