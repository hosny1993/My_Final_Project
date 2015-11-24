#ifndef VOLUME_H
#define VOLUME_H

#include <Headers.hh>
#include <Typedefs.hh>

template < class T >
class Volume
{
public:

    /**
     * @brief Volume
     */
    Volume();

    /**
     * @brief Volume
     * @param coordinates
     * @param dimensions
     */
    Volume( const Coordinates coordinates,
            const Dimensions dimensions,
            const bool drawBoundingBox = false );

    /**
     * @brief Volume
     * @param coordinates
     * @param dimensions
     * @param data
     */
    Volume( const Coordinates coordinates,
            const Dimensions dimensions,
            const Coordinates unitCubeCenter,
            const Coordinates unitCubeScaleFactors,
            T* data,
            const bool drawBoundingBox = false );

    /**
     * @brief Volume
     * @param prefix
     */
    Volume( const std::string prefix, const bool drawBoundingBox = false );

    /**
     * @brief getDimensions
     * @return The XYZ dimensions of the volume.
     */
    Dimensions getDimensions() const;

    /**
     * @brief getSizeX
     * @return Width of the volume.
     */
    uint64_t getSizeX() const;

    /**
     * @brief getSizeY
     * @return Height of the volume.
     */
    uint64_t getSizeY() const;

    /**
     * @brief getSizeZ
     * @return Depth of the volume.
     */
    uint64_t getSizeZ() const;

    /**
     * @brief getSizeInBytes
     * @return Size of the volume in bytes.
     */
    uint64_t getSizeInBytes() const;

    /**
     * @brief getValue
     * Gets the value of a voxel in the volume specified by the XYZ coordinates.
     * @param x
     * @param y
     * @param z
     * @return Voxel value.
     */
    T getValue( const uint64_t x, const uint64_t y, const uint64_t z ) const;

    /**
     * @brief getValue
     * @param c
     * @return
     */
    T getValue( const Coordinates xyz ) const;

    /**
     * @brief getData
     * @return A pointer to the data of the volume.
     */
    const T* getData() const;

    /**
     * @brief get1DIndex
     * Computes the 1D index of a voxel in a 3D volume given by the XYZ
     * coordinates.
     * @param x
     * @param y
     * @param z
     * @return 1D index of the requested voxel.
     */
    uint64_t get1DIndex( const uint64_t x,
                         const uint64_t y,
                         const uint64_t z ) const;

    /**
     * @brief get1DIndex
     * Computes the 1D index of a voxel in a 3D volume given by the XYZ
     * coordinates.
     * @param index
     * @return
     */
    uint64_t get1DIndex( const Voxel3DIndex index ) const;

    /**
     * @brief getBrick
     * Extracts a smaller volume block from this volume that is specified by its
     * XYZ coordinates.
     * @param xi
     * @param xf
     * @param yi
     * @param yf
     * @param zi
     * @param zf
     * @return A brick of the volume specified by its dimensions.
     */
    Volume* getBrick( const u_int64_t xi, const u_int64_t xf,
                      const u_int64_t yi, const u_int64_t yf,
                      const u_int64_t zi, const u_int64_t zf );

    /**
     * @brief isEmpty
     * Indicates if the volume contains data or is empty.
     * @return
     */
    bool isEmpty() const;

protected:

    /**
     * @brief loadHeaderData_
     *      * Loads a meta file that contains all the meta data of the volume
     * including its type and dimensions.
     * @param prefix
     */
    void loadHeaderData_( const std::string prefix );

    /**
     * @brief loadVolumeData_
     * Loads the content of the volume from the HDD into an array on the CPU
     * memory.
     * @param prefix
     */
    void loadVolumeData_( const std::string prefix );

    /**
     * @brief addBoundingBox_
     * Adds the bounding box to the data
     */
    void addBoundingBox_();

protected:

    /**
     * @brief dimensions_
     */
    Dimensions dimensions_;

    /**
     * @brief sizeInBytes_
     */
    u_int64_t sizeInBytes_;

    /**
     * @brief data_
     */
    T* data_;

    /**
     * @brief drawBoundingBox_
     */
    bool drawBoundingBox_;

    /**
     * @brief empty_
     * Indicates of the volume is empty or filled with data.
     */
    bool empty_;

};

/**
 * @brief Volume8
 * An unsigned 8-bit volume.
 */
typedef Volume< u_int8_t > Volume8;

/**
 * @brief Volume16
 * An unsigned 16-bit volume.
 */
typedef Volume< u_int16_t > Volume16;

/**
 * @brief Volume32
 * An unsigned 32-bit volume.
 */
typedef Volume< u_int32_t > Volume32;

/**
 * @brief Volume64
 * An unsigned 64-bit volume.
 */
typedef Volume< u_int64_t > Volume64;

/**
 * @brief VolumeF
 * An single precision volume.
 */
typedef Volume< float > VolumeF;

/**
 * @brief VolumeD
 * An double precision volume.
 */
typedef Volume< double > VolumeD;

#include <Volume.ipp>

#endif // VOLUME_H
