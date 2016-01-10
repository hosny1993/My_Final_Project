#include "ComplexImage.h"

template< class T >
ComplexImage< T >::ComplexImage (const Dimensions2D dimensions, T *data)
    : Image<T>(dimensions, NULL)
{
    this->dimensions_ = dimensions;
    this->data_ = data;
}

/* size of complex image = ( dimensions * 2 ) */
template< class T >
uint64_t ComplexImage< T >::getSizeInBytes() const
{
    // 2 (complex = real(float) + imaginary(float))
    return this->dimensions_.imageSize() * sizeof(T) * 2;
}

/* return complex pixel at the given coordinates */
template< class T >
T* ComplexImage< T >::getValue( const uint64_t x, const uint64_t y ) const
{
    const uint64_t index = this->get1DIndex( x, y );
    T* value = new T[ 2 ];
    value[0] = this->data_[ ( 2 * index ) ];
    value[1] = this->data_[ ( 2 * index ) + 1 ];
    return value;
}

/* return complex pixel at the given coordinates */
template< class T >
T* ComplexImage< T >::getValue( const Pixel2DIndex xy ) const
{
    const uint64_t index = this->get1DIndex( xy );
    T* value = new T[ 2 ];
    value[0] = this->data_[ ( 2 * index ) ];
    value[1] = this->data_[ ( 2 * index ) + 1 ];
    return value;
}

/* real value at even numbers at the given coordinates*/
template< class T >
T ComplexImage<T>::getRealValue( const uint64_t x, const uint64_t y ) const
{
    const uint64_t index = this->get1DIndex( x, y );
    T real = this->data_[ (2 * index) ];
    return real;
}

/* real value at even numbers at the given coordinates */
template< class T >
T ComplexImage<T>::getRealValue( const Pixel2DIndex xy  ) const
{
    const uint64_t index = this->get1DIndex( xy );
    T real = this->data_[ (2 * index) ];
    return real;
}

/* imaginary value at odd numbers at the given coordinates */
template< class T >
T ComplexImage<T>::getImaginaryValue( const uint64_t x, const uint64_t y ) const
{
    const uint64_t index = this->get1DIndex( x, y );
    T imag = this->data_[ (2 * index) + 1];
    return imag;
}

/* imaginary value at odd numbers at the given coordinates */
template< class T >
T ComplexImage<T>::getImaginaryValue( const Pixel2DIndex xy ) const
{
    const uint64_t index = this->get1DIndex( xy );
    T imag = this->data_[ (2 * index) + 1];
    return imag;
}

/* calculat sqrt(real^2 + imag^2) at the given coordinates */
template< class T >
T ComplexImage<T>::getMagnitudeValue( const uint64_t x, const uint64_t y ) const
{
    const uint64_t index = this->get1DIndex( x, y );
    T real = this->data_[ (2 * index) ];
    T imag = this->data_[ (2 * index) + 1];
    return sqrt( pow( real, 2 ) + pow( imag, 2 ) );
}

/* calculat sqrt(real^2 + imag^2) at the given coordinates */
template< class T >
T ComplexImage<T>::getMagnitudeValue(const Pixel2DIndex xy) const
{
    const uint64_t index = this->get1DIndex( xy );
    T real = this->data_[ (2 * index) ];
    T imag = this->data_[ (2 * index) + 1];
    return sqrt( pow( real, 2 ) + pow( imag, 2 ) );
}

/* calculat tan-1(imag , real) at the given coordinates */
template< class T >
T ComplexImage<T>::getPhaseValue(const uint64_t x, const uint64_t y) const
{
    const uint64_t index = this->get1DIndex( x, y );
    T real = this->data_[ (2 * index) ];
    T imag = this->data_[ (2 * index) + 1];
    return  atan( imag / real );
}

/* calculat tan-1(imag , real) at the given coordinates */
template< class T >
T ComplexImage<T>::getPhaseValue(const Pixel2DIndex xy) const
{
    const uint64_t index = this->get1DIndex( xy );
    T real = this->data_[ (2 * index) ];
    T imag = this->data_[ (2 * index) + 1];
    return  atan( imag / real );
}

#include <ComplexImage.ipp>
