
#include "math/vector.h"

namespace raytracing
{
    struct CameraData
    {
        CameraData(const Vector& position, float workingDistance, float fieldOfView)
            : Position(position), WorkingDistance(workingDistance), FieldOfView(fieldOfView) {}

        Vector Position;
        float WorkingDistance;
        float FieldOfView;
    };

    struct SphereData
    {
        SphereData(const Vector& origin, float radius, const Vector& color)
            : Origin(origin), Radius(radius), Color(color) {}

        Vector Origin;
        float Radius;

        Vector Color;
    };

    struct LightData
    {
        LightData(const Vector& direction) : Direction(direction) {} 
        Vector Direction;
    };
}