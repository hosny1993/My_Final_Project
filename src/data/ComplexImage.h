#ifndef COMPLEXIMAGE_H
#define COMPLEXIMAGE_H

#include <Image.h>

template< class T >
class ComplexImage : public Image< T >
{
public:
    ComplexImage();
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
