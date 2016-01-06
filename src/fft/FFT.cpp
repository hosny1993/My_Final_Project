#include "FFT.h"


FFT::oclFFT::oclFFT()
{
    err_ = 0;
    numPlatoforms_= 0;
    numDevices_ = 0;

    // Setup Platform
    err_ = clGetPlatformIDs (0, NULL, &numPlatoforms_);
    platformID_ = (cl_platform_id*) malloc (sizeof(cl_platform_id) * (numPlatoforms_));
    err_   = clGetPlatformIDs ( numPlatoforms_, platformID_, NULL);

    // Setup devices
    err_ = clGetDeviceIDs(platformID_[0], CL_DEVICE_TYPE_ALL, 0, NULL, &numDevices_);
    deviceID_ = (cl_device_id*) malloc (sizeof(cl_device_id) * (numDevices_));
    err_ = clGetDeviceIDs(platformID_[0], CL_DEVICE_TYPE_ALL, numDevices_, deviceID_, NULL);

    context_ = clCreateContext(NULL, numDevices_, deviceID_, NULL, NULL, &err_);
    commandQueue_ = clCreateCommandQueue(context_, deviceID_[0], 0, &err_);
}


float* FFT::oclFFT::clFFT1D( clfftPrecision precision,
                            clfftLayout layout,
                            clfftDirection direction,
                            size_t sizeOfData,
                            float* input)
{
    size_t N = sizeOfData ;
    float* ret = (float*) malloc (2 * N * sizeof(input));

    /* Setup clFFT */
    clfftStatus status;
    clfftSetupData setupData;
    status = clfftInitSetupData(&setupData);
    status = clfftSetup(&setupData);

    /* planhande clFFT */
    clfftPlanHandle planHandle;
    size_t length[1] = {N};

    /* create memory */
    inputBuffer_ = clCreateBuffer(context_, CL_MEM_READ_WRITE,
                                        2 * N * sizeof(input), NULL, &err_);
    err_ = clEnqueueWriteBuffer(commandQueue_, inputBuffer_, CL_TRUE, 0,
            2 * N * sizeof(input), input, 0, NULL, NULL);

    /* create plane  */
    status = clfftCreateDefaultPlan(&planHandle, context_, CLFFT_1D, length);
    status = clfftSetPlanPrecision(planHandle, precision);
    status = clfftSetLayout(planHandle, layout , layout);
    status = clfftSetResultLocation(planHandle, CLFFT_INPLACE);

    /* bake plane */
    status = clfftBakePlan(planHandle, 1, &commandQueue_, NULL, NULL);
    status = clfftEnqueueTransform(planHandle, direction, 1, &commandQueue_, 0,
                                   NULL, NULL, &inputBuffer_, NULL, NULL);
    clFinish(commandQueue_);
    clEnqueueReadBuffer(commandQueue_, inputBuffer_, CL_TRUE, 0,
                        2 * N * sizeof(ret), ret, 0, NULL, NULL);

    /* Free system */
    clfftDestroyPlan(&planHandle);
    clfftTeardown();
    free(input);
    return ret;
}


float* FFT::oclFFT::clFFT2D( clfftPrecision precision,
                            clfftLayout layout,
                            clfftDirection direction,
                            size_t N1,
                            size_t N2,
                            float* input)
{
    float* ret = (float*) malloc (2 * N1 * N2 * sizeof(input));

    /* Setup clFFT */
    clfftStatus status;
    clfftSetupData setupData;
    status = clfftInitSetupData(&setupData);
    status = clfftSetup(&setupData);

    /* planhande clFFT */
    clfftPlanHandle planHandle;
    size_t length[2] = {N1, N2};

    /* create memory */
    inputBuffer_ = clCreateBuffer(context_, CL_MEM_READ_WRITE,
                                        2 * N1 * N2 * sizeof(input), NULL, &err_);
    err_ = clEnqueueWriteBuffer(commandQueue_, inputBuffer_, CL_TRUE, 0,
            2 * N1 * N2 * sizeof(input), input, 0, NULL, NULL);

    /* create plane */
    status = clfftCreateDefaultPlan(&planHandle, context_, CLFFT_2D, length);
    status = clfftSetPlanPrecision(planHandle, precision);
    status = clfftSetLayout(planHandle, layout , layout );
    status = clfftSetResultLocation(planHandle, CLFFT_INPLACE);

    /* bake plane */
    status = clfftBakePlan(planHandle, 1, &commandQueue_, NULL, NULL);
    status = clfftEnqueueTransform(planHandle, direction, 1, &commandQueue_, 0,
                                   NULL, NULL, &inputBuffer_, NULL, NULL);
    clFinish(commandQueue_);
    clEnqueueReadBuffer(commandQueue_, inputBuffer_, CL_TRUE, 0,
                        2 * N1 * N2 * sizeof(ret), ret, 0, NULL, NULL);

    /* Free system */
    clfftDestroyPlan(&planHandle);
    clfftTeardown();
    free(input);

    return ret;
}

float* FFT::oclFFT::clFFT3D( clfftPrecision precision,
                            clfftLayout layout,
                            clfftDirection direction,
                            size_t N1,
                            size_t N2,
                            size_t N3,
                            float* input)
{
    float* ret = (float*) malloc (2 * N1 * N2 * N3 * sizeof(input));

    /* Setup clFFT */

    clfftStatus status;
    clfftSetupData setupData;
    status = clfftInitSetupData(&setupData);
    status = clfftSetup(&setupData);

    /* planhande clFFT */
    clfftPlanHandle planHandle;
    size_t length[3] = {N1, N2, N3};

    /* create memory */

    inputBuffer_ = clCreateBuffer(context_, CL_MEM_READ_WRITE,
                                        2 * N1 * N2 * N3 * sizeof(input), NULL, &err_);
    err_ = clEnqueueWriteBuffer(commandQueue_, inputBuffer_, CL_TRUE, 0,
            2 * N1 * N2 * N3 * sizeof(input), input, 0, NULL, NULL);

    /* create plane */
    status = clfftCreateDefaultPlan(&planHandle, context_, CLFFT_3D, length);
    status = clfftSetPlanPrecision(planHandle, precision);
    status = clfftSetLayout(planHandle, layout , layout );
    status = clfftSetResultLocation(planHandle, CLFFT_INPLACE);

    /* bake plane */
    status = clfftBakePlan(planHandle, 1, &commandQueue_, NULL, NULL);
    status = clfftEnqueueTransform(planHandle, direction, 1, &commandQueue_, 0,
                                   NULL, NULL, &inputBuffer_, NULL, NULL);
    clFinish(commandQueue_);
    clEnqueueReadBuffer(commandQueue_, inputBuffer_, CL_TRUE, 0,
                        2 * N1 * N2 * N3 * sizeof(ret), ret, 0, NULL, NULL);


    /* Free system */

    clfftDestroyPlan(&planHandle);
    clfftTeardown();
    free(input);

    return ret;
}

FFT::oclFFT::~oclFFT()
{
    clReleaseMemObject(inputBuffer_);
    clReleaseContext(context_);
    clReleaseDevice(deviceID_[0]);
    clReleaseCommandQueue(commandQueue_);
}

