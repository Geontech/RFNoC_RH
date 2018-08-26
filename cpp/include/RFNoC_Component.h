#ifndef RFNOCCOMPONENT_H
#define RFNOCCOMPONENT_H

// Linux Include(s)
#include <stddef.h>

// OSSIE Include(s)
#include <ossie/Resource_impl.h>

// UHD Include(s)
#include <uhd/stream.hpp>

// Local Include(s)
#include "RFNoC_Persona.h"

namespace RFNoC_RH
{
	// Forward Declaration(s)
	class RFNoC_Persona;

	// Type Definition(s)
	typedef Resource_impl* (*RFNoC_Component_Constructor_Ptr)(int, char*[], RFNoC_Persona *persona);

	/*
	 * An abstract base class to be implemented by an RF-NoC component designer.
	 */
	class RFNoC_Component
	{
		// Constructor(s) and/or Destructor
		public:
			RFNoC_Component() : persona(NULL) {}

			virtual ~RFNoC_Component() {}

		public:
			virtual void setPersona(RFNoC_Persona *persona) { this->persona = persona; }

			/*
			 * This method should enable streaming from the component's last/only
			 * RF-NoC block. This includes converting the data to bulkio and
			 * creating appropriate SRI.
			 */
			virtual void setRxStreamer(uhd::rx_streamer::sptr rxStreamer) = 0;

			/*
			 * This method should enable streaming to the component's first/only
			 * RF-NoC block. This includes converting the bulkio data to the
			 * appropriate format for the block and responding to the upstream SRI.
			 */
			virtual void setTxStreamer(uhd::tx_streamer::sptr txStreamer) = 0;

		protected:
			RFNoC_Persona *persona;
	};
}

#endif
