#ifndef COMPLEXIMAGE_H
#define COMPLEXIMAGE_H

#include <Image.h>

template< class T >
class ComplexImage : public Image< T >
{
public:

    /**
     * @brief ComplexImage
     * @param dimensions
     * @param data
     */
    ComplexImage( const Dimensions2D dimensions, T* data );

    /**
     * @brief getSizeInBytes
     * @return Size of the image in bytes.
     */
    uint64_t getSizeInBytes() const;

    /**
     * @brief getValue
     * Gets the value of a pixel in the volume specified by the XY coordinates.
     * @param x
     * @param y
     * @return Pixel value at the given coordinates.
     */
    T* getValue( const uint64_t x, const uint64_t y ) const;

    /**
     * @brief getValue
     * @param xy
     * @return Pixel value at the given pixel index.
     */
    T* getValue( const Pixel2DIndex xy ) const;

    /**
     * @brief getRealValue
     * @param x
     * @param y
     * @return
     */
    T getRealValue( const uint64_t x, const uint64_t y ) const;

    T getRealValue( const Pixel2DIndex xy ) const;

    T getImaginaryValue( const uint64_t x, const uint64_t y ) const;

    T getImaginaryValue( const Pixel2DIndex xy ) const;

    T getMagnitudeValue( const uint64_t x, const uint64_t y ) const;

    T getMagnitudeValue( const Pixel2DIndex xy ) const;

    T getPhaseValue( const uint64_t x, const uint64_t y ) const;

    T getPhaseValue( const Pixel2DIndex xy ) const;


};

/**
 * @brief ComplexImage8
 * An unsigned 8-bit ComplexImage.
 */
typedef ComplexImage< u_int8_t > ComplexImage8;

/**
 * @brief ComplexImage16
 * An unsigned 16-bit ComplexImage.
 */
typedef ComplexImage< u_int16_t > ComplexImage16;

/**
 * @brief ComplexImage32
 * An unsigned 32-bit ComplexImage.
 */
typedef ComplexImage< u_int32_t > ComplexImage32;

/**
 * @brief ComplexImage64
 * An unsigned 64-bit ComplexImage.
 */
typedef ComplexImage< u_int64_t > ComplexImage64;

/**
 * @brief ComplexImageF
 * An single precision ComplexImage.
 */
typedef ComplexImage< float > ComplexImageF;

/**
 * @brief ComplexImageD
 * An double precision ComplexImage.
 */
typedef ComplexImage< double > ComplexImageD;

#endif // COMPLEXIMAGE_H
