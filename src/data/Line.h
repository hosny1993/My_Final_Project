#ifndef LINE_H
#define LINE_H

#include <Headers.hh>

template< class T >
class Line
{
public: // Constructors

    /**
     * @brief Line
     * @param x
     * @param data
     */
    Line( const u_int64_t x, T* data );

public: // Public functions

    /**
     * @brief getSizeX
     * @return Length of the line (or 1D signal).
     */
    uint64_t getSizeX() const;

    /**
     * @brief getSizeInBytes
     * @return Size of the line (or 1D signal) in bytes.
     */
    virtual uint64_t getSizeInBytes() const;

    /**
     * @brief getData
     * @return A pointer to the data of the line (or 1D signal).
     */
    T* getData() const;

    /**
     * @brief getValue
     * Gets the value of a sample in the line (or 1D signal) specified by the
     * x coordinates.
     * @param x
     * @return Sample value at the given x coordinate.
     */
    virtual T* getValue( const uint64_t x ) const;

    /**
     * @brief saveToFile
     * @param fileName
     */
    virtual void saveToFile( const std::string fileName ) const;

protected: // Protected (private) member variables

    /**
     * @brief x_
     */
    u_int64_t x_;

    /**
     * @brief sizeInBytes_
     */
    u_int64_t sizeInBytes_;

    /**
     * @brief data_
     */
    T* data_;
};

/**
 * @brief Line8
 * An unsigned 8-bit Line (or 1D signal).
 */
typedef Line< u_int8_t > Line8;

/**
 * @brief Line16
 * An unsigned 16-bit Line (or 1D signal).
 */
typedef Line< u_int16_t > Line16;

/**
 * @brief Line32
 * An unsigned 32-bit Line (or 1D signal).
 */
typedef Line< u_int32_t > Line32;

/**
 * @brief Line64
 * An unsigned 64-bit Line (or 1D signal).
 */
typedef Line< u_int64_t > Line64;

/**
 * @brief LineF
 * An single precision Line (or 1D signal).
 */
typedef Line< float > LineF;

/**
 * @brief LineD
 * An double precision Line (or 1D signal).
 */
typedef Line< double > LineD;

#endif // LINE_H
