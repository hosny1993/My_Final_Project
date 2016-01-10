#ifndef COMPLEXVOLUME_H
#define COMPLEXVOLUME_H

#include <Headers.hh>
#include <Typedefs.hh>
#include <Volume.h>
#include <ComplexImage.h>

template< class T >
class ComplexVolume : public Volume< T >
{
public:
    ComplexVolume(const Dimensions3D dimensions, T* data);

    /**
     * @brief getSliceX
     * Extracts an orthogonal slice from the volume along spefific x coordinate.
     * @param x
     * @return
     */
    ComplexImage<T>* getSliceX( const u_int64_t x ) const;

    /**
     * @brief getSliceY
     * Extracts an orthogonal slice from the volume along spefific y coordinate.
     * @param y
     * @return
     */
    ComplexImage<T>* getSliceY( const u_int64_t y ) const;

    /**
     * @brief getSliceZ
     * Extracts an orthogonal slice from the volume along spefific z coordinate.
     * @param z
     * @return
     */
    ComplexImage<T>* getSliceZ( const u_int64_t z ) const;

    uint64_t getSizeInBytes() const;

};

/**
 * @brief ComplexVolume8
 * An unsigned 8-bit ComplexVolume.
 */
typedef ComplexVolume< u_int8_t > ComplexVolume8;

/**
 * @brief ComplexVolume16
 * An unsigned 16-bit ComplexVolume.
 */
typedef ComplexVolume< u_int16_t > ComplexVolume16;

/**
 * @brief ComplexVolume32
 * An unsigned 32-bit ComplexVolume.
 */
typedef ComplexVolume< u_int32_t > ComplexVolume32;

/**
 * @brief ComplexVolume64
 * An unsigned 64-bit ComplexVolume.
 */
typedef ComplexVolume< u_int64_t > ComplexVolume64;

/**
 * @brief ComplexVolumeF
 * An single precision ComplexVolume.
 */
typedef ComplexVolume< float > ComplexVolumeF;

/**
 * @briefComplexVolumeD
 * An double precision ComplexVolume.
 */
typedef ComplexVolume< double > ComplexVolumeD;

#endif // COMPLEXVOLUME_H
