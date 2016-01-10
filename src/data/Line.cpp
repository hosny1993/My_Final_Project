#include "Line.h"

template< class T >
Line< T >::Line( const u_int64_t x, T* data )
{
    x_ = x;
    data_ = data;
}

template< class T >
uint64_t Line< T >::getSizeX() const
{
    return x_;
}

template< class T >
uint64_t Line< T >::getSizeInBytes() const
{
    return x_ * sizeof( T );
}

template< class T >
T* Line< T >::getData() const
{
    return data_;
}

template< class T >
T* Line< T >::getValue( const uint64_t x ) const
{
    T* value = new T[ 1 ];
    *value = data_[ x ];
    return value;
}

template< class T >
void Line< T >::saveToFile( const std::string fileName ) const
{

}

#include <Line.ipp>

