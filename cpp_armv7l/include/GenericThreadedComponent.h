#ifndef GENERIC_THREADED_COMPONENT_H
#define GENERIC_THREADED_COMPONENT_H

// Boost Include(s)
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>

// Ossie Include(s)
#include <ossie/debug.h>
#include <ossie/ThreadedComponent.h>

namespace RFNoC_RH
{
	/*
	 * A class for creating a service function thread
	 */
	class GenericThreadedComponent
	{
		ENABLE_LOGGING

		// Typedef(s)
		typedef boost::function<int()> serviceFunction_t;

		// Constructor(s) and/or Destructor
		public:
			GenericThreadedComponent(serviceFunction_t sf);

			virtual ~GenericThreadedComponent();

		// Getter(s) and/or Setter(s)
		public:
			float getThreadDelay() const { return this->noopDelay; }

			void setThreadDelay(float delay) { this->noopDelay = delay; }

		// Public Method(s)
		public:
			virtual void serviceFunction();

			virtual void start();

			virtual bool stop();

		// Protected Member(s)
		protected:
			float noopDelay;

			serviceFunction_t serviceFunctionMethod;

			boost::shared_ptr<boost::thread> thread;
	};
}

#endif
