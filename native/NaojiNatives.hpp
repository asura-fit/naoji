/**
 * @author sey
 *
 * Version : $Id$
 */

#ifndef NaojiNatives_H
#define NaojiNatives_H
#include "alptr.h"
#include "albroker.h"

#include "alerror.h"

#include "almotionproxy.h"
#include "almemoryproxy.h"

#include <jni.h>       /* where everything is defined */
#include "NaojiModule.hpp"

/**
 * DESCRIBE YOUR CLASS HERE
 */
namespace Naoji {

class JALBroker {
public:
	JALBroker(AL::ALPtr<AL::ALBroker> broker) {
		this->broker = broker;
	}

	AL::ALPtr<AL::ALBroker> getALPtr() {
		return broker;
	}

private:
	AL::ALPtr<AL::ALBroker> broker;
};

class JALMemory {
public:
	JALMemory(JALBroker *jbroker) {
		try {
			AL::ALPtr<AL::ALBroker> broker = jbroker->getALPtr();
			memory = broker->getMemoryProxy();
		} catch (AL::ALError& e) {
			std::cout << "Error during initializaion: " + e.toString()
					<< std::endl;
		}

		AL_ASSERT(memory); // Assure that memoryproxy is not null
	}

protected:
	AL::ALPtr<AL::ALMemoryProxy> memory;
};

class JALMotion {
public:
	JALMotion(JALBroker *jbroker) {
		try {
			AL::ALPtr<AL::ALBroker> broker = jbroker->getALPtr();
			motion = broker->getMotionProxy();
		} catch (AL::ALError& e) {
			std::cout << "Error during initializaion: " + e.toString()
					<< std::endl;
		}

		AL_ASSERT(motion); // Assure that motionproxy is not null
	}

protected:
	AL::ALPtr<AL::ALMotionProxy> motion;
};

}

#endif // NaojiNatives_H
