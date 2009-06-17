/**
 * @author sey
 *
 * Version : $Id$
 */

#ifndef NaojiNatives_H
#define NaojiNatives_H

#include <algorithm>
#include <string>
#include <vector>

#include "alptr.h"
#include "albroker.h"

#include "alerror.h"

#include "almotionproxy.h"
#include "almemoryproxy.h"
#include "dcmproxy.h"
#include "altexttospeechproxy.h"

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
	JALMemory(JALBroker *jbroker) :
		keys(32) {
		try {
			AL::ALPtr<AL::ALBroker> broker = jbroker->getALPtr();
			proxy = broker->getMemoryProxy();
		} catch (AL::ALError& e) {
			std::cout << "Error during initialization: " + e.toString()
					<< std::endl;
		}

		AL_ASSERT(proxy); // Assure that memoryproxy is not null
	}

	AL::ALPtr<AL::ALMemoryProxy> getProxy() {
		return proxy;
	}

	bool isDefinedKey(int id) {
		if (keys.size() <= id)
			return false;
		return keys[id].size() > 0;
	}

	std::string getKey(int id) {
		assert(isDefinedKey(id));
		return keys[id];
	}

	int defineKey(std::string key) {
		assert(key.size() > 0);
		// TODO reuse disposed entry.
		int id = keys.size();
		keys.resize(id + 1, key);
		return id;
	}

	void removeKey(int id) {
		assert(isDefinedKey(id));
		keys[id] = std::string();
	}

	int getLastTime() {
		return lastTime;
	}

	void setLastTime(int time) {
		lastTime = time;
	}

protected:
	AL::ALPtr<AL::ALMemoryProxy> proxy;
	std::vector<std::string> keys;
	int lastTime;
};

class JALMotion {
public:
	JALMotion(JALBroker *jbroker) {
		try {
			AL::ALPtr<AL::ALBroker> broker = jbroker->getALPtr();
			proxy = broker->getMotionProxy();
		} catch (AL::ALError& e) {
			std::cout << "Error during initialization: " + e.toString()
					<< std::endl;
		}

		AL_ASSERT(proxy); // Assure that motionproxy is not null

		vector<string> names = proxy->getBodyJointNames();
		jointNames.arraySetSize(names.size());
		for (int i = 0; i < names.size(); i++)
			jointNames[i] = names[i];

		headlessJointNames.arraySetSize(names.size() - 2);
		for (int i = 2; i < names.size(); i++)
			headlessJointNames[i - 2] = names[i];
	}

	AL::ALPtr<AL::ALMotionProxy> getProxy() {
		return proxy;
	}

	bool isDefinedJoint(int id) {
		assert(jointNames.isValid());
		assert(jointNames.isArray());
		if (jointNames.getSize() <= id)
			return false;
		return jointNames[id].getSize() > 0;
	}

	std::string getJointName(int id) {
		assert(jointNames.isValid());
		assert(isDefinedJoint(id));
		return jointNames[id];
	}

	AL::ALValue getJointNames() {
		return jointNames;
	}

	AL::ALValue getHeadlessJointNames() {
		return headlessJointNames;
	}

	std::string getChainName(int id) {
		switch (id) {
		case 0:
			return "Head";
		case 1:
			return "LArm";
		case 2:
			return "RArm";
		case 3:
			return "LLeg";
		case 4:
			return "RLeg";
		default:
			return "UNKNOWN";
		}
	}

protected:
	AL::ALPtr<AL::ALMotionProxy> proxy;

private:
	AL::ALValue jointNames;
	AL::ALValue headlessJointNames;
};

class Query {
public:
	Query(JALMemory *jmemory) {
		this->jmemory = jmemory;
	}

	void setNames(jobjectArray names) {
		// TODO implements.
	}

public:
	JALMemory *jmemory;
	ALValue names;
	jsize size;
	jlong bufferLength;
	union {
		jbyte *b;
		jobjectArray s;
	} buffer;
};

class JDCM {
public:
	JDCM(JALBroker *jbroker) :
		aliases(0) {
		try {
			AL::ALPtr<AL::ALBroker> broker = jbroker->getALPtr();
			proxy = broker->getDcmProxy();
		} catch (AL::ALError& e) {
			std::cout << "Error during initialization: " + e.toString()
					<< std::endl;
		}

		AL_ASSERT(proxy); // Assure that memoryproxy is not null
	}

	AL::ALPtr<AL::DCMProxy> getProxy() {
		return proxy;
	}

	std::string getMergeType(jint ordinal) {
		switch (ordinal) {
		case 0:
			return string("Merge");
		case 1:
			return string("ClearAll");
		case 2:
			return string("ClearAfter");
		case 3:
			return string("ClearBefore");
		default:
			return string("ClearAll");
		}
	}

	int aliases;

protected:
	AL::ALPtr<AL::DCMProxy> proxy;
};

class JALTextToSpeech {
public:
	JALTextToSpeech(JALBroker *jbroker) {
		try {
			AL::ALPtr<AL::ALBroker> broker = jbroker->getALPtr();
			proxy = AL::ALPtr<AL::ALTextToSpeechProxy>(
					new AL::ALTextToSpeechProxy(broker));
		} catch (AL::ALError& e) {
			std::cout << "Error during initialization: " + e.toString()
					<< std::endl;
		}

		AL_ASSERT(proxy); // Assure that memoryproxy is not null
	}

	AL::ALPtr<AL::ALTextToSpeechProxy> getProxy() {
		return proxy;
	}

protected:
	AL::ALPtr<AL::ALTextToSpeechProxy> proxy;
};

}

#endif // NaojiNatives_H
