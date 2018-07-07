#ifndef RFNOC_UTILS_H
#define RFNOC_UTILS_H

// Linux Include(s)
#include <stddef.h>

// OmniORB4 Include(s)
#include <omniORB4/CORBA.h>

// UHD Include(s)
#include <uhd/device3.hpp>

namespace RFNoC_Utils
{
	// Type Definition(s)
	typedef CORBA::ULong PortHashType;

	// Constant Declaration(s)
	const PortHashType HASH_SIZE = 1000000;

	// Structure(s)

	/*
	 * A structure describing an RF-NoC port
	 */
	struct BlockDescriptor
	{
		// Public Method(s)
		public:
			bool operator==(const BlockDescriptor &rhs);

		// Public Member(s)
		public:
			uhd::rfnoc::block_id_t blockId;
			size_t port;
	};

	// Helper Function(s)
	BlockDescriptor findAvailableChannel(const uhd::device3::sptr usrp, const uhd::rfnoc::block_id_t &blockID);

	BlockDescriptor findAvailableSink(const uhd::device3::sptr usrp, const uhd::rfnoc::block_id_t &blockID);

	BlockDescriptor findAvailableSource(const uhd::device3::sptr usrp, const uhd::rfnoc::block_id_t &blockID);
}

#endif
