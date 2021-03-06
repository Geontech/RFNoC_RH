// Class Include
#include "GenericThreadedComponent.h"

// Boost Include(s)
#include <boost/make_shared.hpp>

namespace RFNoC_RH
{
	PREPARE_LOGGING(GenericThreadedComponent)

	/*
	 * Initialize the service function callback
	 */
	GenericThreadedComponent::GenericThreadedComponent(serviceFunction_t sf) :
		noopDelay(0.1),
		serviceFunctionMethod(sf)
	{
		LOG_TRACE(GenericThreadedComponent, __PRETTY_FUNCTION__);
	}

	GenericThreadedComponent::~GenericThreadedComponent()
	{
		stop();
	}

	/*
	 * Call the service function callback
	 */
	void GenericThreadedComponent::serviceFunction()
	{
		LOG_TRACE(GenericThreadedComponent, __PRETTY_FUNCTION__);

		// The returned value from the service function method
		int retValue;

		while (true)
		{
			if (this->thread->interruption_requested())
			{
				LOG_DEBUG(GenericThreadedComponent, "Interruption requested");
				break;
			}

			retValue = this->serviceFunctionMethod();

			if (retValue == NOOP)
			{
				boost::this_thread::sleep(boost::posix_time::seconds(this->noopDelay));
			}
			else if (retValue == NORMAL)
			{
				continue;
			}
			else
			{
				LOG_DEBUG(GenericThreadedComponent, "Service Function returned FINISH");
				break;
			}
		}
	}

	/*
	 * Start the thread
	 */
	void GenericThreadedComponent::start()
	{
		LOG_TRACE(GenericThreadedComponent, __PRETTY_FUNCTION__);

		if (not this->thread)
		{
			this->thread = boost::make_shared<boost::thread>(&GenericThreadedComponent::serviceFunction, this);
		}
	}

	/*
	 * Stop the thread
	 */
	bool GenericThreadedComponent::stop()
	{
		LOG_TRACE(GenericThreadedComponent, __PRETTY_FUNCTION__);

		if (this->thread)
		{
			this->thread->interrupt();
			this->thread->join();
			this->thread.reset();
		}

		return true;
	}
}
