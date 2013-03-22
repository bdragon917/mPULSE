#include <InGameObjects\Entities\Entities.h>

void Entities::clearAll()
{
        cars.clear();
        AIcars.clear();
        Obstacles.clear();
        StaticObjs.clear();
        DynamicObjs.clear();
        Track.clear();
}