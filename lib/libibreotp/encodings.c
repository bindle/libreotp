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
#include "encodings.h"

///////////////
//           //
//  Headers  //
//           //
///////////////
#ifdef __LIBREOTP_PMARK
#pragma mark - Headers
#endif

#include "libibreotp.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "encodings_base32.h"


///////////////////
//               //
//  Definitions  //
//               //
///////////////////
#ifdef __LIBREOTP_PMARK
#pragma mark - Definitions
#endif


/////////////////
//             //
//  Functions  //
//             //
/////////////////
#ifdef __LIBREOTP_PMARK
#pragma mark - Functions
#endif

size_t lotp_decode_string(lotp_enc encoding, char * str, size_t str_len,
   uint8_t * bin, size_t bin_size, size_t * str_off)
{
   assert(str != NULL);
   assert(bin != NULL);

   switch(encoding)
   {
      case BASE32:
      return(lotp_decode_string_base32(str, str_len, bin, bin_size, str_off));

      default:
      break;
   };

   return(0);
}


size_t lotp_decode_len(lotp_enc encoding, size_t str_len)
{
   size_t bin_len;

   switch(encoding)
   {
      case BASE32:
      bin_len = (str_len / 8) * 5;
      if ((str_len & 0x07) != 0)
         bin_len += 5;
      break;


      case HEX:
      bin_len = str_len >> 1;
      if ((str_len & 0x01) != 0)
         bin_len += 2;
      break;


      default:
      bin_len = str_len;
      break;
   };

   return(bin_len);
}


size_t lotp_encode_binary(lotp_enc encoding, uint8_t * bin, size_t bin_len,
   char * str, size_t str_len, size_t * bin_off)
{
   assert(str != NULL);
   assert(bin != NULL);

   switch(encoding)
   {
      case BASE32:
      return(lotp_encode_binary_base32(bin, bin_len, str, str_len, bin_off));

      default:
      break;
   };

   return(0);
}


size_t lotp_encode_len(lotp_enc encoding, size_t bin_len)
{
   size_t str_len;

   switch(encoding)
   {
      case BASE32:
      str_len = (bin_len / 5) * 8;
      if ((bin_len % 5) != 0)
         str_len += 8;
      break;


      case HEX:
      str_len = bin_len * 2;
      break;


      case NONE:
      str_len = bin_len;
      break;


      default:
      str_len = bin_len * 8;
   };

   return(str_len+1);
}


/* end of source */
