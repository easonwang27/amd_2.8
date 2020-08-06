/**********************************************************************
Copyright �2012 Advanced Micro Devices, Inc. All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

�	Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
�	Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or
 other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
********************************************************************/


#ifndef SIMPLECONVOLUTION_H_
#define SIMPLECONVOLUTION_H_

/**
 * Header Files
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <SDKCommon.hpp>
#include <SDKApplication.hpp>
#include <SDKCommandArgs.hpp>
#include <SDKFile.hpp>

/**
 * SimpleConvolution 
 * Class implements OpenCL SimpleConvolution sample
 * Derived from SDKSample base class
 */

class SimpleConvolution : public SDKSample
{
    cl_uint      seed;               /**< Seed value for random number generation */
    cl_double    setupTime;          /**< Time for setting up OpenCL */
    cl_double    totalKernelTime;    /**< Time for kernel execution */
    cl_int       width;              /**< Width of the Input array */
    cl_int       height;             /**< Height of the Input array */
    cl_uint      *input;             /**< Input array */
    cl_uint      *output;            /**< Output array */
    cl_float     *mask;              /**< mask array */
    cl_uint      maskWidth;          /**< mask dimensions */
    cl_uint      maskHeight;         /**< mask dimensions */
    cl_uint      *verificationOutput;/**< Output array for reference implementation */
    cl_context   context;            /**< CL context */
    cl_device_id *devices;           /**< CL device list */
    cl_mem       inputBuffer;        /**< CL memory input buffer */
    cl_mem       outputBuffer;       /**< CL memory output buffer */
    cl_mem       maskBuffer;         /**< CL memory mask buffer */
    cl_command_queue commandQueue;   /**< CL command queue */
    cl_program   program;            /**< CL program  */
    cl_kernel    kernel;             /**< CL kernel */
    size_t       globalThreads[1];   /**< global NDRange */
    size_t       localThreads[1];    /**< Local Work Group Size */
    int          iterations;         /**< Number of iterations to execute kernel */
    streamsdk::SDKDeviceInfo deviceInfo;                /**< Structure to store device information*/
    streamsdk::KernelWorkGroupInfo kernelInfo;          /**< Structure to store kernel related info */

    public:
    /** 
     * Constructor 
     * Initialize member variables
     * @param name name of sample (string)
     */
    SimpleConvolution(std::string name)
        : SDKSample(name)   {
            seed = 123;
            input = NULL;
            output = NULL;
            mask   = NULL;
            verificationOutput = NULL;
            width = 64;
            height = 64;
            setupTime = 0;
            totalKernelTime = 0;
            iterations = 1;
        }

    /** 
     * Constructor 
     * Initialize member variables
     * @param name name of sample (const char*)
     */
    SimpleConvolution(const char* name)
        : SDKSample(name)   {
            seed = 123;
            input = NULL;
            output = NULL;
            mask   = NULL;
            verificationOutput = NULL;      
            width = 64;
            height = 64;
            setupTime = 0;
            totalKernelTime = 0;
            iterations = 1;
        }

    /**
     * Allocate and initialize host memory array with random values
     * @return SDK_SUCCESS on success and SDK_FAILURE0 on failure
     */
    int setupSimpleConvolution();

    /**
     * Calculates the value of WorkGroup Size based in global NDRange 
     * and kernel properties
     * @return 0 on success and nonzero on failure
     */
    int setWorkGroupSize();

    /**
     * OpenCL related initialisations. 
     * Set up Context, Device list, Command Queue, Memory buffers
     * Build CL kernel program executable
     * @return SDK_SUCCESS on success and SDK_FAILURE0 on failure
     */
    int setupCL();

    /**
     * Set values for kernels' arguments, enqueue calls to the kernels
     * on to the command queue, wait till end of kernel execution.
     * Get kernel start and end time if timing is enabled
     * @return SDK_SUCCESS on success and SDK_FAILURE0 on failure
     */
    int runCLKernels();

    /**
     * Reference CPU implementation of Simple Convolution 
     * for performance comparison
     * @param output Output matrix after performing convolution
     * @param input  Input  matrix on which convolution is to be performed
     * @param mask   mask matrix using which convolution was to be performed
     * @param inputDimensions dimensions of the input matrix
     * @param maskDimensions  dimensions of the mask matrix
     */
    void simpleConvolutionCPUReference(
            cl_uint  *output,
            const cl_uint  *input,
            const cl_float  *mask,
            const cl_uint  width,
            const cl_uint  height,
            const cl_uint maskWidth,
            const cl_uint maskHeight);
    /**
     * Override from SDKSample. Print sample stats.
     */
    void printStats();

    /**
     * Override from SDKSample. Initialize 
     * command line parser, add custom options
     * @return SDK_SUCCESS on success and SDK_FAILURE0 on failure
     */
    int initialize();

    /**
     * Override from SDKSample, Generate binary image of given kernel 
     * and exit application
     * @return SDK_SUCCESS on success and SDK_FAILURE0 on failure
     */
    int genBinaryImage();

    /**
     * Override from SDKSample, adjust width and height 
     * of execution domain, perform all sample setup
     * @return SDK_SUCCESS on success and SDK_FAILURE0 on failure
     */
    int setup();

    /**
     * Override from SDKSample
     * Run OpenCL Bitonic Sort
     * @return SDK_SUCCESS on success and SDK_FAILURE0 on failure
     */
    int run();

    /**
     * Override from SDKSample
     * Cleanup memory allocations
     * @return SDK_SUCCESS on success and SDK_FAILURE0 on failure
     */
    int cleanup();

    /**
     * Override from SDKSample
     * Verify against reference implementation
     * @return SDK_SUCCESS on success and SDK_FAILURE0 on failure
     */
    int verifyResults();
};



#endif