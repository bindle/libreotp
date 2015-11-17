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

#include <libreotp_cdefs.h>


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
/// Calculates the required buffer size to decode data with the specified
/// encoding type.
///
/// @param[in] enctype  Encoding type
/// @param[in] enclen   Length of data to be encoded
/// @return Returns the size of the buffer required to hold the decoded data.
_LIBREOTP_F size_t lotp_decoded_len(lotp_enc enctype, size_t enclen);


/// @ingroup encodings
/// Calculates the required buffer size to encode data with the specified
/// encoding type.
///
/// @param[in] enctype  Encoding type
/// @param[in] data_len Length of data to be encoded
/// @return Returns the size of the buffer required to hold the encoded data.
_LIBREOTP_F size_t lotp_encoded_len(lotp_enc enctype, size_t binlen);


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
