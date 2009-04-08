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

protected:
	AL::ALPtr<AL::ALMemoryProxy> proxy;
	std::vector<std::string> keys;
};

class JALMotion {
public:
	JALMotion(JALBroker *jbroker) :
		jointNames(32) {
		try {
			AL::ALPtr<AL::ALBroker> broker = jbroker->getALPtr();
			proxy = broker->getMotionProxy();
		} catch (AL::ALError& e) {
			std::cout << "Error during initialization: " + e.toString()
					<< std::endl;
		}

		AL_ASSERT(proxy); // Assure that motionproxy is not null
	}

	AL::ALPtr<AL::ALMotionProxy> getProxy() {
		return proxy;
	}

	bool isDefinedJoint(int id) {
		if (jointNames.size() <= id)
			return false;
		return jointNames[id].size() > 0;
	}

	std::string getJointName(int id) {
		assert(isDefinedJoint(id));
		return jointNames[id];
	}

	void defineJoint(int id, std::string jointName) {
		assert(jointName.size() > 0);
		if (jointNames.size() <= id)
			jointNames.resize(id, std::string());
		jointNames[id] = jointName;
	}

	void removeJoint(int id) {
		assert(isDefinedJoint(id));
		jointNames[id] = std::string();
	}

protected:
	AL::ALPtr<AL::ALMotionProxy> proxy;

private:
	std::vector<std::string> jointNames;
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
		aliases(32), aliasLengths(32) {
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

	bool isDefinedAlias(int id) {
		if (aliasLengths.size() <= id)
			return false;
		return aliasLengths[id] > 0;
	}

	AL::ALValue getAlias(int id) {
		assert(isDefinedAlias(id));
		return aliases[id];
	}

	int getAliasLength(int id) {
		assert(isDefinedAlias(id));
		return aliasLengths[id];
	}

	int defineAlias(AL::ALValue alias, int length) {
		assert(aliases.size() > 0);
		assert(length > 0);
		// TODO reuse disposed entry.
		int id = aliases.size();
		aliases.resize(id + 1, alias);
		aliasLengths.resize(id + 1, length);
		return id;
	}

	void removeAlias(int id) {
		assert(isDefinedAlias(id));
		aliases[id] = ALValue();
		aliasLengths[id] = 0;
	}

protected:
	AL::ALPtr<AL::DCMProxy> proxy;
	std::vector<AL::ALValue> aliases;
	std::vector<int> aliasLengths;
};

}

#endif // NaojiNatives_H
