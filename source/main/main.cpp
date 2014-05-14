#include "layer/abstraction/storageimpl.h"
#include "layer/main/application.h"
#include "common/logging/loggerimpl.h"
#include "common/time/watchimpl.h"

using namespace std;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Layer::Main;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::Time;

int main(int /*argc*/, char **/*argv*/)
{
	Application application(TeamColorRed);
	application.run();
	return 0;
}
