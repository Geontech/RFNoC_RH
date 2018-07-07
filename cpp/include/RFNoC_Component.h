#ifndef RFNOCCOMPONENT_H
#define RFNOCCOMPONENT_H

// Linux Include(s)
#include <stddef.h>

// Local Include(s)
#include "RFNoC_Persona.h"

namespace RFNoC_Utils
{
	// Forward Declaration(s)
	class RFNoC_Persona;

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
			/*
			 * This method should enable streaming from the component's last/only
			 * RF-NoC block. This includes converting the data to bulkio and
			 * creating appropriate SRI.
			 */
			virtual void setRxStreamer(bool enable) = 0;

			/*
			 * This method should enable streaming to the component's first/only
			 * RF-NoC block. This includes converting the bulkio data to the
			 * appropriate format for the block and responding to the upstream SRI.
			 */
			virtual void setTxStreamer(bool enable) = 0;

		protected:
			RFNoC_Persona *persona;
	};
}

#endif
