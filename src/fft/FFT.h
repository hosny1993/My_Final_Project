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

        /**
         * @brief err_
         * error number return from open_cl
         */
        cl_int err_;

        /**
         * @brief numPlatoforms_
         * current number of platforms in this machine
         */
        cl_uint numPlatoforms_;

        /**
         * @brief numDevices_
         * current number of devices in this machine
         */
        cl_uint numDevices_;

        /**
         * @brief platformID_
         * platform id determine vendor specs
         */
        cl_platform_id* platformID_;

        /**
         * @brief deviceID_
         * device id give us information about device
         */
        cl_device_id* deviceID_;

        /**
         * @brief context_
         * context coordinates the mechanisms for host–device interaction
         */
        cl_context context_;

        /**
         * @brief commandQueue_
         * host uses command queue to request action by the device
         */
        cl_command_queue commandQueue_;

        /**
         * @brief inputBuffer_
         * buffers used to store data
         */
        cl_mem inputBuffer_;

    public:

        /**
         * @brief oclFFT
         * constructor
         */
        oclFFT();

        /**
         * @brief clFFT1D
         * @param precision
         * @param layout
         * @param direction
         * @param sizeOfData
         * @param input reference to data vector
         * @return reference to data vector
         */
        float* clFFT1D( clfftPrecision precision = CLFFT_SINGLE,
                        clfftLayout layout = CLFFT_COMPLEX_INTERLEAVED,
                        clfftDirection direction = CLFFT_FORWARD,
                        size_t sizeOfData = 0,
                        float* input = NULL );

        /**
         * @brief clFFT2D
         * @param precision
         * @param layout
         * @param direction
         * @param N1
         * @param N2
         * @param input
         * @return
         */
        float* clFFT2D( clfftPrecision precision = CLFFT_SINGLE,
                        clfftLayout layout = CLFFT_COMPLEX_INTERLEAVED,
                        clfftDirection direction = CLFFT_FORWARD,
                        size_t N1 = 0,
                        size_t N2 = 0,
                        float* input = NULL );
        /**
         * @brief clFFT3D
         * @param precision
         * @param layout
         * @param direction
         * @param N1
         * @param N2
         * @param N3
         * @param input reference to data vector
         * @return reference to data vector
         */
        float* clFFT3D( clfftPrecision precision = CLFFT_SINGLE,
                        clfftLayout layout = CLFFT_COMPLEX_INTERLEAVED,
                        clfftDirection direction = CLFFT_FORWARD,
                        size_t N1 = 0,
                        size_t N2 = 0,
                        size_t N3 = 0,
                        float* input = NULL );

        ~oclFFT();
    };
}

#endif // FFT_H
