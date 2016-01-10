#include "ComplexVolume.h"


template< class T >
ComplexVolume< T >::ComplexVolume(const Dimensions3D dimensions, T *data)
    : Volume<T> ("", NULL)
{
    /* initialize parent class( Volume ) with tiwce dimensions for real and imaginary */
    this->dimensions_ = dimensions ; // dimensions_ = 2 * dimension

    /* initialize parent class( Volume ) with data */
    this->data_ = data;
}

/* extract complex size orthognal to x direction by
 * get index of data when x fixed at specific value (slice)
 * then create image with y and z data
 */
template< class T >
ComplexImage<T>* ComplexVolume< T >::getSliceX(const u_int64_t x) const
{
    /* complex dimensions */
    Dimensions2D complexImageDim( this->dimensions_.y, this->dimensions_.z );
    T* sliceData = new T[ complexImageDim.imageSize()];

    /* get slice data */
    u_int64_t sliceIndex = 0;
    for( u_int64_t i = 0; i < this->dimensions_.y; i++ )
    {
        for( u_int64_t j = 0; j < this->dimensions_.z; j++ )
        {
            sliceData[sliceIndex] = this->data_[this->get1DIndex( x, i, j )]; // x constant
            sliceIndex++;
        }
    }

    /* create complex image */
    ComplexImage<T>* complexImage = new ComplexImage<T>(complexImageDim, sliceData);

    /* return poninter to complex image*/
    return complexImage;
}

/* extract complex size orthognal to y direction by
 * get index of data when y fixed at specific value (slice)
 * then create image with x and z data
 */
template< class T >
ComplexImage<T>* ComplexVolume< T >::getSliceY(const u_int64_t y) const
{
    /* complex dimensions */
    Dimensions2D complexImageDim( this->dimensions_.x, this->dimensions_.z );
    T* sliceData = new T[ complexImageDim.imageSize()];

    /* get slice data */
    u_int64_t sliceIndex = 0;
    for( u_int64_t i = 0; i < this->dimensions_.x; i++ )
    {
        for( u_int64_t j = 0; j < this->dimensions_.z; j++ )
        {
            sliceData[sliceIndex] = this->data_[this->get1DIndex( i, y, j )]; // y constant
            sliceIndex++;
        }
    }

    /* create complex image */
    ComplexImage<T>* complexImage = new ComplexImage<T>(complexImageDim, sliceData);

    /* return poninter to complex image*/
    return complexImage;
}

/* extract complex size orthognal to z direction by
 * get index of data when z fixed at specific value (slice)
 * then create image with x and y data
 */
template< class T >
ComplexImage<T>* ComplexVolume< T >::getSliceZ(const u_int64_t z) const
{
    /* complex dimensions */
    Dimensions2D complexImageDim( this->dimensions_.x, this->dimensions_.y );
    T* sliceData = new T[ complexImageDim.imageSize()];

    /* get slice data */
    u_int64_t sliceIndex = 0;
    for( u_int64_t i = 0; i < this->dimensions_.x; i++ )
    {
        for( u_int64_t j = 0; j < this->dimensions_.y; j++ )
        {
            sliceData[sliceIndex] = this->data_[this->get1DIndex( i, j, z )]; // z constant
            sliceIndex++;
        }
    }

    /* create complex image */
    ComplexImage<T>* complexImage = new ComplexImage<T>(complexImageDim, sliceData);

    /* return poninter to complex image*/
    return complexImage;
}

template< class T>
uint64_t ComplexVolume<T>::getSizeInBytes() const
{
    return this->dimensions_.volumeSize() * sizeof(T) * 2;
}


#include <ComplexVolume.ipp>
