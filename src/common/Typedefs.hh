#ifndef TYPEDEFS_HH
#define TYPEDEFS_HH

#include <Vector3.h>

/**
 * @brief Coordinates
 * The XYZ coordinates of the volume;
 */
typedef Vector3F Coordinates;

/**
 * @brief Dimensions
 * The dimensions of the volume.
 */
typedef Vector3UI Dimensions;

/**
 * @brief Voxel3DIndex
 * An XYZ index of the voxel in a 3D volume.
 * The X, Y and Z components specify the location of the voxel in the volume.
 */
typedef Vector3UI Voxel3DIndex;

#endif // TYPEDEFS_HH

