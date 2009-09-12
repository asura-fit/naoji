#include <signal.h>

#include "alxplatform.h"
#include <fstream>
#include <sstream>
#include <albroker.h>
#include <almodule.h>
#include <altools.h>

#include "altypes.h"
#include "alptr.h"
#include "albrokermanager.h"

#include "NaojiModule.hpp"

using namespace std;
using namespace AL;
using namespace Naoji;

void _terminationHandler(int signum) {
	ALBrokerManager::getInstance()->killAllBroker();
	ALBrokerManager::kill();
	exit(0);
}

int usage(char* progName) {
	std::cout << progName << ", a remote module of naoqi !" << std::endl

	<< "USAGE :" << std::endl
			<< "-b\t<ip> : binding ip of the server. Default is 127.0.0.1"
			<< std::endl
			<< "-p\t<port> : binding port of the server. Default is 9559"
			<< std::endl
			<< "-pip\t<ip> : ip of the parent broker. Default is 127.0.0.1"
			<< std::endl
			<< "-pport\t<ip> : port of the parent broker. Default is 9559"
			<< std::endl << "-h\t: Display this help\n" << std::endl;
	return 0;
}

int main(int argc, char *argv[]) {
	std::cout << "..::: starting NAOJI" << std::endl;
	std::cout << "Copyright (c) 2009, Asura-FIT" << std::endl;
	std::cout << "Copyright (c) 2007, Aldebaran-robotics" << std::endl
			<< std::endl;

	int i = 1;
	std::string brokerName = "naoji_main";
	std::string brokerIP = "127.0.0.1";
	int brokerPort = 0;
	// Default parent broker IP
	std::string parentBrokerIP = "127.0.0.1";
	// Default parent broker port
	int parentBrokerPort = kBrokerPort;

	// checking options
	while (i < argc) {
		if (argv[i][0] != '-')
			return usage(argv[0]);
		else if (std::string(argv[i]) == "-b")
			brokerIP = std::string(argv[++i]);
		else if (std::string(argv[i]) == "-p")
			brokerPort = atoi(argv[++i]);
		else if (std::string(argv[i]) == "-pip")
			parentBrokerIP = std::string(argv[++i]);
		else if (std::string(argv[i]) == "-pport")
			parentBrokerPort = atoi(argv[++i]);
		else if (std::string(argv[i]) == "-h")
			return usage(argv[0]);
		i++;
	}

	std::cout << "Try to connect to parent Broker at ip :" << parentBrokerIP
			<< " and port : " << parentBrokerPort << std::endl;
	std::cout << "Start the server bind on this ip :  " << brokerIP
			<< " and port : " << brokerPort << std::endl;

	  // Starting Broker
	 ALPtr<ALBroker> pBroker = ALBroker::createBroker(brokerName, brokerIP, brokerPort, parentBrokerIP,  parentBrokerPort);

	// Starting Broker ALPtr<ALBroker> pBroker = ALBroker::createBroker(brokerName, brokerIP, brokerPort, parentBrokerIP,  parentBrokerPort);
	pBroker->setBrokerManagerInstance(ALBrokerManager::getInstance());

	ALModule::createModule<NaojiModule>(pBroker, "NaojiModule");

	struct sigaction new_action;
	/* Set up the structure to specify the new action. */
	new_action.sa_handler = _terminationHandler;
	sigemptyset(&new_action.sa_mask);
	new_action.sa_flags = 0;

	sigaction(SIGINT, &new_action, NULL);

	pBroker.reset(); // because of while( 1 ), broker counted by brokermanager
	while (1) {
		SleepMs(100);
	}
}
