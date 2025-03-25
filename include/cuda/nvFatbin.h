/*
 * NVIDIA_COPYRIGHT_BEGIN
 *
 * Copyright (c) 2023, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 *
 * NVIDIA_COPYRIGHT_END
 */

//
// nvFatbin.h
//

#include <stddef.h>

#ifndef nvFatbin_INCLUDED
#define nvFatbin_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

/**
 *
 * \defgroup error Error codes
 *
 */

/** \ingroup error
 *
 * \brief    The enumerated type nvFatbinResult defines API call result codes.
 *           nvFatbin APIs return nvFatbinResult codes to indicate the result.
 */

typedef enum
{
  NVFATBIN_SUCCESS = 0,
  NVFATBIN_ERROR_INTERNAL,
  NVFATBIN_ERROR_ELF_ARCH_MISMATCH,
  NVFATBIN_ERROR_ELF_SIZE_MISMATCH,
  NVFATBIN_ERROR_MISSING_PTX_VERSION,
  NVFATBIN_ERROR_NULL_POINTER,
  NVFATBIN_ERROR_COMPRESSION_FAILED,
  NVFATBIN_ERROR_COMPRESSED_SIZE_EXCEEDED,
  NVFATBIN_ERROR_UNRECOGNIZED_OPTION,
  NVFATBIN_ERROR_INVALID_ARCH,
  NVFATBIN_ERROR_INVALID_NVVM,
  NVFATBIN_ERROR_EMPTY_INPUT,
} nvFatbinResult;

/**
 * \ingroup error
 * \brief   nvFatbinGetErrorString returns an error description string for each error code.
 *
 * \param   [in] result       error code
 * \return
 *   - nullptr, if result is NVFATBIN_SUCCESS
 *   - a string, if result is not NVFATBIN_SUCCESS
 *
 */
const char *nvFatbinGetErrorString(nvFatbinResult result);

/**
 *
 * \defgroup creation Fatbinary Creation
 *
 */

/**
 * \ingroup creation
 * \brief   nvFatbinHandle is the unit of fatbin creation, and an opaque handle for
 *          a program.
 *
 * To create a fatbin, an instance of nvFatbinHandle must be created first with
 * nvFatbinCreate().
 */

typedef struct _nvFatbinHandle *nvFatbinHandle;

/**
 * \defgroup options Supported Options
 *
 * nvFatbin supports the options below.
 * Option names are prefixed with a single dash (\c -).
 * Options that take a value have an assignment operator (\c =)
 * followed by the option value, with no spaces, e.g. \c "-host=windows".
 *
 * The supported options are:
 * - \c -32 \n
 *   Make entries 32 bit.
 * - \c -64 \n
 *   Make entries 64 bit.
 * - \c -c \n
 *   Make relocatable fatbin.
 * - \c -compress=<bool\> \n
 *   Enable (true) / disable (false) compression (default: true).
 * - \c -compress-all \n
 *   Compress everything in the fatbin, even if it's small.
 * - \c -cuda \n
 *   Specify CUDA (rather than OpenCL).
 * - \c -g \n
 *   Generate debug information.
 * - \c -host=<name\> \n
 *   Specify host operating system. Valid options are "linux", "windows", and "mac" (deprecated).
 * - \c -opencl \n
 *   Specify OpenCL (rather than CUDA).
 */

/**
 * \ingroup creation
 * \brief   nvFatbinCreate creates a new handle
 *
 * \param    [out] handle_indirect  Address of nvFatbin handle
 * \param    [in] options       An array of strings, each containing a single option.
 * \param    [in] optionsCount  Number of options.
 * \return
 *   - \link #nvFatbinResult NVFATBIN_SUCCESS \endlink
 *   - \link #nvFatbinResult NVFATBIN_ERROR_NULL_POINTER \endlink
 *   - \link #nvFatbinResult NVFATBIN_ERROR_UNRECOGNIZED_OPTION \endlink
 *   - \link #nvFatbinResult NVFATBIN_ERROR_INTERNAL \endlink
 *
 */
nvFatbinResult nvFatbinCreate(nvFatbinHandle *handle_indirect, const char **options, size_t optionsCount);

/**
 * \ingroup creation
 * \brief   nvFatbinDestroy destroys the handle.
 *
 * \param    [in] handle_indirect  Pointer to the handle.
 * \return
 *   - \link #nvFatbinResult NVFATBIN_SUCCESS \endlink
 *   - \link #nvFatbinResult NVFATBIN_ERROR_NULL_POINTER \endlink
 *   - \link #nvFatbinResult NVFATBIN_ERROR_INTERNAL \endlink
 *
 * Use of any other pointers to the handle after calling this will result in undefined behavior.
 * The passed in handle will be set to nullptr.
 */
nvFatbinResult nvFatbinDestroy(nvFatbinHandle *handle_indirect);

/**
 * \ingroup creation
 * \brief   nvFatbinAddPtx adds PTX to the fatbinary.
 *
 * \param    [in] handle      nvFatbin handle.
 * \param    [in] code        The PTX code.
 * \param    [in] size        The size of the PTX code.
 * \param    [in] arch        The architecture that this PTX is for.
 * \param    [in] identifier  Name of the PTX, useful when extracting the fatbin with tools like cuobjdump.
 * \param    [in] optionsCmdLine  Options used during JIT compilation.
 *
 * \return
 *   - \link #nvFatbinResult NVFATBIN_SUCCESS \endlink
 *   - \link #nvFatbinResult NVFATBIN_ERROR_NULL_POINTER \endlink
 *   - \link #nvFatbinResult NVFATBIN_ERROR_INVALID_ARCH \endlink
 *   - \link #nvFatbinResult NVFATBIN_ERROR_MISSING_PTX_VERSION \endlink
 *   - \link #nvFatbinResult NVFATBIN_ERROR_COMPRESSION_FAILED, \endlink
 *   - \link #nvFatbinResult NVFATBIN_ERROR_UNRECOGNIZED_OPTION \endlink
 *   - \link #nvFatbinResult NVFATBIN_ERROR_COMPRESSED_SIZE_EXCEEDED \endlink
 *   - \link #nvFatbinResult NVFATBIN_ERROR_INTERNAL \endlink
 *
 * User is responsible for making sure all string are well-formed.
 * The size should be inclusive of the terminating null character ('\0').
 * If the final character is not '\0', one will be added automatically, but in
 * doing so, the code will be copied if it hasn't already been copied.
 */
nvFatbinResult nvFatbinAddPTX(nvFatbinHandle handle, const char *code, size_t size, const char *arch, const char *identifier, const char *optionsCmdLine);

/**
 * \ingroup creation
 * \brief   nvFatbinAddCubin adds a CUDA binary to the fatbinary.
 *
 * \param    [in] handle      nvFatbin handle.
 * \param    [in] code        The cubin.
 * \param    [in] size        The size of the cubin.
 * \param    [in] arch        The architecture that this cubin is for.
 * \param    [in] identifier  Name of the cubin, useful when extracting the fatbin with tools like cuobjdump.
 *
 * \return
 *   - \link #nvFatbinResult NVFATBIN_SUCCESS \endlink
 *   - \link #nvFatbinResult NVFATBIN_ERROR_INVALID_ARCH \endlink
 *   - \link #nvFatbinResult NVFATBIN_ERROR_ELF_ARCH_MISMATCH \endlink
 *   - \link #nvFatbinResult NVFATBIN_ERROR_ELF_SIZE_MISMATCH \endlink
 *   - \link #nvFatbinResult NVFATBIN_ERROR_COMPRESSION_FAILED, \endlink
 *   - \link #nvFatbinResult NVFATBIN_ERROR_UNRECOGNIZED_OPTION \endlink
 *   - \link #nvFatbinResult NVFATBIN_ERROR_COMPRESSED_SIZE_EXCEEDED \endlink
 *   - \link #nvFatbinResult NVFATBIN_ERROR_INTERNAL \endlink
 *
 * User is responsible for making sure all strings are well-formed.
 */
nvFatbinResult nvFatbinAddCubin(nvFatbinHandle handle, const void *code, size_t size, const char *arch, const char *identifier);

/**
 * \ingroup creation
 * \brief   nvFatbinAddLTOIR adds LTOIR to the fatbinary.
 *
 * \param    [in] handle      nvFatbin handle.
 * \param    [in] code        The LTOIR code.
 * \param    [in] size        The size of the LTOIR code.
 * \param    [in] arch        The architecture that this LTOIR is for.
 * \param    [in] identifier  Name of the LTOIR, useful when extracting the fatbin with tools like cuobjdump.
 * \param    [in] optionsCmdLine  Options used during JIT compilation.
 *
 * \return
 *   - \link #nvFatbinResult NVFATBIN_SUCCESS \endlink
 *   - \link #nvFatbinResult NVFATBIN_ERROR_NULL_POINTER \endlink
 *   - \link #nvFatbinResult NVFATBIN_ERROR_INVALID_ARCH \endlink
 *   - \link #nvFatbinResult NVFATBIN_ERROR_COMPRESSION_FAILED, \endlink
 *   - \link #nvFatbinResult NVFATBIN_ERROR_UNRECOGNIZED_OPTION \endlink
 *   - \link #nvFatbinResult NVFATBIN_ERROR_COMPRESSED_SIZE_EXCEEDED \endlink
 *   - \link #nvFatbinResult NVFATBIN_ERROR_INTERNAL \endlink
 *
 * User is responsible for making sure all strings are well-formed.
 */
nvFatbinResult nvFatbinAddLTOIR(nvFatbinHandle handle, const void *code, size_t size, const char *arch, const char *identifier, const char *optionsCmdLine);

/**
 * \ingroup creation
 * \brief   nvFatbinSize returns the fatbinary's size.
 *
 * \param    [in] handle      nvFatbin handle.
 * \param    [out] size       The fatbinary's size
 *
 * \return
 *   - \link #nvFatbinResult NVFATBIN_SUCCESS \endlink
 *   - \link #nvFatbinResult NVFATBIN_ERROR_NULL_POINTER \endlink
 *   - \link #nvFatbinResult NVFATBIN_ERROR_INTERNAL \endlink
 *
 */
nvFatbinResult nvFatbinSize(nvFatbinHandle handle, size_t *size);

/**
 * \ingroup creation
 * \brief   nvFatbinGet returns the completed fatbinary.
 *
 * \param    [in] handle      nvFatbin handle.
 * \param    [out] buffer     memory to store fatbinary.
 *
 * \return
 *   - \link #nvFatbinResult NVFATBIN_SUCCESS \endlink
 *   - \link #nvFatbinResult NVFATBIN_ERROR_NULL_POINTER \endlink
 *   - \link #nvFatbinResult NVFATBIN_ERROR_INTERNAL \endlink
 *
 * User is responsible for making sure the buffer is appropriately sized for the \p fatbinary.
 * You must call nvFatbinSize before using this, otherwise, it will return an error.
 * \see nvFatbinSize
 */
nvFatbinResult nvFatbinGet(nvFatbinHandle handle, void *buffer);

/**
 * \ingroup creation
 * \brief   nvFatbinVersion returns the current version of nvFatbin
 *
 * \param    [out] major        The major version.
 * \param    [out] minor        The minor version.
 * \return
 *   - \link #nvFatbinResult NVFATBIN_SUCCESS \endlink
 *   - \link #nvFatbinResult NVFATBIN_ERROR_NULL_POINTER \endlink
 *   - \link #nvFatbinResult NVFATBIN_ERROR_INTERNAL \endlink
 *
 */
nvFatbinResult nvFatbinVersion(unsigned int *major, unsigned int *minor);
#ifdef __cplusplus
}
#endif

#endif