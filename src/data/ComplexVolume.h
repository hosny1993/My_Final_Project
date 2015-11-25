#ifndef COMPLEXVOLUME_H
#define COMPLEXVOLUME_H

#include <Volume.h>
#include <ComplexImage.h>

template< class T >
class ComplexVolume : public Volume< T >
{
public:
    ComplexVolume();

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
};

#endif // COMPLEXVOLUME_H
