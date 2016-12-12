/*
 *  LibreOTP
 *  Copyright (c) 2015, Bindle Binaries
 *  All rights reserved.
 *
 *  @BINDLE_BINARIES_BSD_LICENSE_START@
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are
 *  met:
 *
 *     1. Redistributions of source code must retain the above copyright
 *        notice, this list of conditions and the following disclaimer.
 *
 *     2. Redistributions in binary form must reproduce the above copyright
 *        notice, this list of conditions and the following disclaimer in the
 *        documentation and/or other materials provided with the distribution.
 *
 *     3. Neither the name of the copyright holder nor the names of its
 *        contributors may be used to endorse or promote products derived from
 *        this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 *  IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 *  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 *  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  @BINDLE_BINARIES_BSD_LICENSE_END@
 */
/**
 *   @file libreotp.h
 *   LibreOTP Library public API
 */
#ifndef __LIBREOTP_H
#define __LIBREOTP_H 1
#undef __LIBREOTP_PMARK


///////////////
//           //
//  Headers  //
//           //
///////////////
#ifdef __LIBREOTP_PMARK
#pragma mark - Headers
#endif

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <inttypes.h>
#include <netinet/in.h>

#ifdef __APPLE__
#  include "TargetConditionals.h"
#  ifdef TARGET_OS_MAC
#     include <libkern/OSAtomic.h>
#  endif
#endif


//////////////
//          //
//  Macros  //
//          //
//////////////
#ifdef LIBREOTP_PMARK
#pragma mark - Macros
#endif

// Exports function type
#undef LIBREOTP_C_DECLS
#if defined(__cplusplus) || defined(c_plusplus)
#   define _LIBREOTP_I             extern "C" inline
#   define LIBREOTP_C_DECLS        "C"             ///< exports as C functions
#   define LIBREOTP_BEGIN_C_DECLS  extern "C" {    ///< exports as C functions
#   define LIBREOTP_END_C_DECLS    }               ///< exports as C functions
#else
#   define _LIBREOTP_I             inline
#   define LIBREOTP_C_DECLS        /* empty */     ///< exports as C functions
#   define LIBREOTP_BEGIN_C_DECLS  /* empty */     ///< exports as C functions
#   define LIBREOTP_END_C_DECLS    /* empty */     ///< exports as C functions
#endif
#ifdef WIN32
#   ifdef _LIB_LIBLIBREOTP_H
#      define _LIBREOTP_F   extern LIBREOTP_C_DECLS __declspec(dllexport)   ///< used for library calls
#      define _LIBREOTP_V   extern LIBREOTP_C_DECLS __declspec(dllexport)   ///< used for library calls
#   else
#      define _LIBREOTP_F   extern LIBREOTP_C_DECLS __declspec(dllimport)   ///< used for library calls
#      define _LIBREOTP_V   extern LIBREOTP_C_DECLS __declspec(dllimport)   ///< used for library calls
#   endif
#else
#   ifdef _LIB_LIBLIBREOTP_H
#      define _LIBREOTP_F   /* empty */                                     ///< used for library calls
#      define _LIBREOTP_V   extern LIBREOTP_C_DECLS                         ///< used for library calls
#   else
#      define _LIBREOTP_F   extern LIBREOTP_C_DECLS                         ///< used for library calls
#      define _LIBREOTP_V   extern LIBREOTP_C_DECLS                         ///< used for library calls
#   endif
#endif


//////////////////
//              //
//  Data Types  //
//              //
//////////////////
#ifdef __LIBREOTP_PMARK
#pragma mark - Data Types
#endif

typedef enum lotp_enc lotp_enc;
enum lotp_enc
{
   NONE        = 0,
   HEX         = 1,
   BASE32      = 2,  ///< RFC4648 compliant
   //ZBASE32     = 3,  ///< z-base-32
   //BASE32HEX   = 4,  ///< Triacontakaidecimal
   //CROCKFORD   = 5,  ///< Crockford's Base32
   //BASE64      = 6,  ///< RFC 2045
};


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////
#ifdef __LIBREOTP_PMARK
#pragma mark -
#endif

/**
 *  @defgroup encodings Encoding/Decoding Functions
 *  @brief Functions for encoding and decoding binary data.
 */
#ifdef __LIBREOTP_PMARK
#pragma mark Version Prototypes
#endif

/// @ingroup encodings
/// Calculates the maximum binary buffer size required to decode a string of
/// the specified length with the specified encoding.
///
/// @param[in] encoding  Encoding type
/// @param[in] str_len   Length of string to be decoded
/// @return Returns the maximum size of the buffer required to hold the
/// decoded data of the specified size.
_LIBREOTP_F size_t lotp_decode_len(lotp_enc encoding, size_t str_len);


/// @ingroup encodings
/// Decodes string data into binary data using the specified encoding.
///
/// @param[in]  encoding   Encoding type
/// @param[in]  str        Encoded string of the specified encoding.
/// @param[in]  str_len    Length of string to be decoded
/// @param[out] bin        Binary buffer for holding decoded data
/// @param[in]  bin_size   Size of binary buffer
/// @param[out] str_off    Optional reference used to store the number
///                        of encoded bytes used to fill decoded buffer.
/// @return Returns the number of bytes written to output buffer if no
/// errors were encountered.  If the encoded data contained invalid characters
/// or the output buffer was not large enough to store the minimum unit size
/// of an encoding, the value zero is returned.
_LIBREOTP_F size_t lotp_decode_string(lotp_enc encoding, char * str,
   size_t str_len, uint8_t * bin, size_t bin_size, size_t * str_off);


/// @ingroup encodings
/// Encodes binary data using the specified encoding.
///
/// @param[in]  encoding   Encoding type
/// @param[in]  bin        Pointer to binary data to encode.
/// @param[in]  bin_len    Length of binary data to encode.
/// @param[out] str        String buffer for holding encoded data
/// @param[in]  str_len    Size of string buffer.
/// @param[out] bin_off    Optional reference used to store the number
///                        of binary bytes encoded into the encoded string
///                        buffer.
/// @return Returns the size of the encoded data.
_LIBREOTP_F size_t lotp_encode_binary(lotp_enc encoding, uint8_t * bin,
   size_t bin_len, char * str, size_t str_len, size_t * bin_off);


/// @ingroup encodings
/// Calculates the required buffer size to encode data with the specified
/// encoding type.
///
/// @param[in] encoding    Encoding type
/// @param[in] bin_len     Length of binary data to be encoded
/// @return Returns the size of the buffer required to hold the encoded data.
_LIBREOTP_F size_t lotp_encode_len(lotp_enc encoding, size_t bin_len);


/**
 *  @defgroup version Version Functions
 *  @brief Functions for determine version and capabilities of library.
 */
#ifdef __LIBREOTP_PMARK
#pragma mark Version Prototypes
#endif

/// @ingroup version
/// Retrieve the API version implemented by the LibreOTP library.
///
/// @param[out] pcur    Pointer for storing the current API version.
/// @param[out] prev    Pointer for storing the current revision of the API
///                     implementation.
/// @param[out] page    Pointer for storing the number of previous API versions
///                     which are compatible with the current API version.
/// @return Returns an ASCII string of the API version for use by libtool.
_LIBREOTP_F const char * libreotp_api(uint32_t * pcur,
   uint32_t * prev, uint32_t * page);


/// @ingroup version
/// Retrieve the package release version of the LibreOTP library.
///
/// @param[out] pmaj    Returns reference to major version number.
/// @param[out] pmin    Returns reference to minor version number.
/// @param[out] ppat    Returns reference to patch level.
/// @param[out] pbuild  Returns reference to build commit.
/// @return Returns the full version information as a dot delimited string.
_LIBREOTP_F const char * libreotp_version(uint32_t * pmaj,
   uint32_t * pmin, uint32_t * ppat, const char ** pbuild);


#endif /* end of header */
