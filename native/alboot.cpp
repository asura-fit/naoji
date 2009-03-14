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

#define ALCALL

#ifdef __cplusplus
extern "C" {
#endif

ALCALL int _createModule(ALPtr<ALBroker> pBroker) {
	// init broker with the main broker inctance
	// from the parent executable
	ALBrokerManager::setInstance(pBroker->fBrokerManager.lock());
	ALBrokerManager::getInstance()->addBroker(pBroker);

	ALModule::createModule<NaojiModule>(pBroker, "NaojiModule");

	return 0;
}

ALCALL int _closeModule() {
	// Delete module instance

	return 0;
}

# ifdef __cplusplus
}
# endif
