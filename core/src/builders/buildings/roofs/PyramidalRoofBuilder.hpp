#ifndef BUILDERS_BUILDINGS_FACADES_PYRAMIDALROOFBUILDER_HPP_DEFINED
#define BUILDERS_BUILDINGS_FACADES_PYRAMIDALROOFBUILDER_HPP_DEFINED

#include "builders/buildings/roofs/RoofBuilder.hpp"
#include "utils/GeometryUtils.hpp"

#include <vector>

namespace utymap { namespace builders {

/// Builds flat roof in low poly.
class PyramidalRoofBuilder final : public RoofBuilder
{
public:
    PyramidalRoofBuilder(const utymap::builders::BuilderContext& builderContext,
                         utymap::builders::MeshContext& meshContext)
        : RoofBuilder(builderContext, meshContext)
    {
    }

    void build(utymap::meshing::Polygon& polygon) override
    {
        for (const auto& range : polygon.outers) {
            auto center = utymap::utils::getCentroid(polygon, range);
            auto lastPointIndex = range.second - 2;

            for (std::size_t i = range.first; i < range.second; i += 2) {
                auto nextIndex = i == lastPointIndex ? range.first : i + 2;

                utymap::meshing::Vector3 v0(polygon.points[i], minHeight_, polygon.points[i + 1]);
                utymap::meshing::Vector3 v1(center.x, minHeight_ + height_, center.y);
                utymap::meshing::Vector3 v2(polygon.points[nextIndex], minHeight_, polygon.points[nextIndex + 1]);

                builderContext_.meshBuilder.addTriangle(meshContext_.mesh, v0, v1, v2, 
                    meshContext_.geometryOptions, meshContext_.appearanceOptions);
            }
        }   
    }
};

}}

#endif // BUILDERS_BUILDINGS_FACADES_PYRAMIDALROOFBUILDER_HPP_DEFINED
