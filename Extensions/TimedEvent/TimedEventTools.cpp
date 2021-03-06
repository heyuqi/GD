/**

GDevelop - Timed Event Extension
Copyright (c) 2011-2014 Florian Rival (Florian.Rival@gmail.com)
This project is released under the MIT License.
*/

#include "GDCpp/RuntimeScene.h"
#include "TimedEventTools.h"
#include "TimedEventsManager.h"

namespace GDpriv
{
namespace TimedEvents
{

signed long long GD_EXTENSION_API UpdateAndGetTimeOf(RuntimeScene & scene, std::string timedEventName)
{
    TimedEventsManager & manager = TimedEventsManager::managers[&scene];
    manager.timedEvents[timedEventName].UpdateTime(scene.GetElapsedTime());
    return manager.timedEvents[timedEventName].GetTime();
}

void GD_EXTENSION_API Reset(RuntimeScene & scene, std::string timedEventName)
{
    TimedEventsManager & manager = TimedEventsManager::managers[&scene];
    manager.timedEvents[timedEventName].Reset();
}

}
}

