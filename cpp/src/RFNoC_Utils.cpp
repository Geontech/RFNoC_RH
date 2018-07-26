// Header Include
#include "RFNoC_Utils.h"

// Standard C++ Include(s)
#include <string>
#include <vector>

// UHD Include(s)
#include <uhd/rfnoc/sink_block_ctrl_base.hpp>
#include <uhd/rfnoc/source_block_ctrl_base.hpp>

namespace RFNoC_RH
{
	/*
	 * Block Descriptor Constructor(s) and/or Destructor
	 */
	BlockDescriptor::BlockDescriptor() :
			port(uhd::rfnoc::ANY_PORT)
	{
	}

	/*
	 * Block Descriptor Public Method(s)
	 */
	bool BlockDescriptor::operator==(const BlockDescriptor &rhs)
	{
		return (this->blockId == rhs.blockId and this->port == rhs.port);
	}

	/*
	 * Helper Function(s)
	 */
	BlockDescriptor findAvailableChannel(const uhd::device3::sptr usrp, const std::string &blockId)
	{
		std::vector<uhd::rfnoc::block_id_t> blockIds = usrp->find_blocks(blockId);
		BlockDescriptor blockDescriptor;

		for (size_t i = 0; i < blockIds.size(); ++i)
		{
			uhd::rfnoc::sink_block_ctrl_base::sptr sinkBlock;
			uhd::rfnoc::source_block_ctrl_base::sptr sourceBlock;

			try
			{
				sinkBlock = usrp->get_block_ctrl<uhd::rfnoc::sink_block_ctrl_base>(blockId);
			}
			catch(uhd::value_error &e)
			{
				continue;
			}

			try
			{
				sourceBlock = usrp->get_block_ctrl<uhd::rfnoc::source_block_ctrl_base>(blockId);
			}
			catch(uhd::value_error &e)
			{
				continue;
			}

			size_t numFullChannels = std::min(sinkBlock->get_input_ports().size(), sourceBlock->get_output_ports().size());

			for (size_t j = 0; j < numFullChannels; ++j)
			{
				try
				{
					sinkBlock->get_upstream_port(j);
				}
				catch(uhd::value_error &e)
				{
					try
					{
						sourceBlock->get_downstream_port(j);
					}
					catch(uhd::value_error &e)
					{
						blockDescriptor.blockId = blockIds[i];
						blockDescriptor.port = j;

						return blockDescriptor;
					}
				}
			}
		}

		return blockDescriptor;
	}

	BlockDescriptor findAvailableSink(const uhd::device3::sptr usrp, const std::string &blockId)
	{
		std::vector<uhd::rfnoc::block_id_t> blockIds = usrp->find_blocks(blockId);
		BlockDescriptor blockDescriptor;

		for (size_t i = 0; i < blockIds.size(); ++i)
		{
			uhd::rfnoc::sink_block_ctrl_base::sptr block = usrp->get_block_ctrl<uhd::rfnoc::sink_block_ctrl_base>(blockId);
			std::vector<size_t> inputPorts = block->get_input_ports();

			for (size_t j = 0; j < inputPorts.size(); ++j)
			{
				try
				{
					block->get_upstream_port(j);
				}
				catch(uhd::value_error &e)
				{
					blockDescriptor.blockId = blockIds[i];
					blockDescriptor.port = j;

					return blockDescriptor;
				}
			}
		}

		return blockDescriptor;
	}

	BlockDescriptor findAvailableSource(const uhd::device3::sptr usrp, const std::string &blockId)
	{
		std::vector<uhd::rfnoc::block_id_t> blockIds = usrp->find_blocks(blockId);
		BlockDescriptor blockDescriptor;

		for (size_t i = 0; i < blockIds.size(); ++i)
		{
			uhd::rfnoc::source_block_ctrl_base::sptr block = usrp->get_block_ctrl<uhd::rfnoc::source_block_ctrl_base>(blockId);
			std::vector<size_t> outputPorts = block->get_output_ports();

			for (size_t j = 0; j < outputPorts.size(); ++j)
			{
				try
				{
					block->get_downstream_port(j);
				}
				catch(uhd::value_error &e)
				{
					blockDescriptor.blockId = blockIds[i];
					blockDescriptor.port = j;

					return blockDescriptor;
				}
			}
		}

		return blockDescriptor;
	}
}
