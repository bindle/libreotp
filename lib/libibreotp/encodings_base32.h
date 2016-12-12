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
#ifndef __LIBIBREOTP_ENCODINGS_BASE32_H
#define __LIBIBREOTP_ENCODINGS_BASE32_H 1

///////////////
//           //
//  Headers  //
//           //
///////////////
#ifdef __LIBREOTP_PMARK
#pragma mark - Headers
#endif

#include <libreotp.h>


//////////////////
//              //
//  Data Types  //
//              //
//////////////////
#ifdef __LIBREOTP_PMARK
#pragma mark - Data Types
#endif


//////////////////
//              //
//  Prototypes  //
//              //
//////////////////
#ifdef __LIBREOTP_PMARK
#pragma mark - Prototypes
#endif


/// Decodes string data into binary data using the specified encoding.
///
/// @param[in]  str        Encoded string of the specified encoding.
/// @param[in]  str_len    Length of string to be decoded
/// @param[out] bin        Binary buffer for holding decoded data
/// @param[in]  bin_len    Size of binary buffer
/// @param[out] str_off    Optional reference used to store the number
///                        of encoded bytes used to fill decoded buffer.
/// @return Returns the number of bytes written to output buffer if no
/// errors were encountered.  If the encoded data contained invalid characters
/// or the output buffer was not large enough to store the minimum unit size
/// of an encoding, the value zero is returned.
size_t lotp_decode_string_base32(char * str, size_t str_len, uint8_t * bin,
   size_t bin_len, size_t * str_off);


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
size_t lotp_encode_binary_base32(uint8_t * bin, size_t bin_len, char * str,
   size_t str_len, size_t * bin_off);

#endif /* end of header */
