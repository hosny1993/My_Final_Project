#ifndef FFT_H
#define FFT_H

#include <clFFT.h>
#include <stdlib.h>
#include <iostream>

namespace FFT
{

    class oclFFT
    {

    private:

        /*!
         * \brief setup opencl
         */

        cl_int err_;
        cl_uint numPlatoforms_;
        cl_uint numDevices_;

        cl_platform_id* platformID_;
        cl_device_id* deviceID_;
        cl_context context_;
        cl_command_queue commandQueue_;
        cl_mem inputBuffer_;

    public:
        /*!
         * \brief oclFFT
         */
        oclFFT();

        ~oclFFT();

        /*!
         * \brief clFFT1D
         * \param precision
         * \param layout
         * \param direction
         * \param sizeOfData
         * \param input reference to data vector
         * \return reference to data vector
         */
        float* clFFT1D(clfftPrecision precision = CLFFT_SINGLE,
                   clfftLayout layout = CLFFT_COMPLEX_INTERLEAVED,
                   clfftDirection direction = CLFFT_FORWARD,
                   size_t sizeOfData = 0,
                   float* input = NULL);

        /*!
         * \brief clFFT2D
         * \param precision
         * \param layout
         * \param direction
         * \param N1
         * \param N2
         * \param input
         * \return
         */
        float* clFFT2D(clfftPrecision precision = CLFFT_SINGLE,
                   clfftLayout layout = CLFFT_COMPLEX_INTERLEAVED,
                   clfftDirection direction = CLFFT_FORWARD,
                   size_t N1 = 0,
                   size_t N2 = 0,
                   float* input = NULL);
        /*!
         * \brief clFFT3D
         * \param precision
         * \param layout
         * \param direction
         * \param N1
         * \param N2
         * \param N3
         * \param input reference to data vector
         * \return reference to data vector
         */
        float* clFFT3D(clfftPrecision precision = CLFFT_SINGLE,
                   clfftLayout layout = CLFFT_COMPLEX_INTERLEAVED,
                   clfftDirection direction = CLFFT_FORWARD,
                   size_t N1 = 0,
                   size_t N2 = 0,
                   size_t N3 = 0,
                   float* input = NULL);

    };
}

#endif // FFT_H
