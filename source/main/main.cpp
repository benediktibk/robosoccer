#include "layer/abstraction/storageimpl.h"
#include "layer/main/application.h"
#include "common/logging/loggerimpl.h"

using namespace std;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Layer::Main;
using namespace RoboSoccer::Common::Logging;

int main(int /*argc*/, char **/*argv*/)
{
	StorageImpl storage;
	LoggerImpl logger;
	Application application(storage, logger);
	application.run();
	return 0;
}
