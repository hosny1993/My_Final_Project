#include "ComplexImage.h"

template< class T >
ComplexImage< T >::ComplexImage(const Dimensions2D dimensions, T *data)
{
    this->dimensions_ = dimensions;
    this->data_ = data;
}

template< class T >
uint64_t ComplexImage< T >::getSizeInBytes() const
{
    // 2 (complex = real(float) + imaginary(float))
    return this->dimensions_.imageSize() * sizeof(T) * 2;
}

template< class T >
T* ComplexImage< T >::getValue( const uint64_t x, const uint64_t y ) const
{
    const uint64_t index = this->get1DIndex( x, y );
    T* value = new T[ 2 ];
    value[0] = this->data_[ ( 2 * index ) ];
    value[1] = this->data_[ ( 2 * index ) + 1 ];
    return value;
}

template< class T >
T* ComplexImage< T >::getValue( const Pixel2DIndex xy ) const
{
    const uint64_t index = this->get1DIndex( xy );
    T* value = new T[ 2 ];
    value[0] = this->data_[ ( 2 * index ) ];
    value[1] = this->data_[ ( 2 * index ) + 1 ];
    return value;
}
