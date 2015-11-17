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

size_t lotp_decoded_len(lotp_enc enctype, size_t enclen)
{
   size_t binlen;

   switch(enctype)
   {
      case BASE32:
      binlen = (enclen / 8) * 5;
      if ((enclen & 0x07) != 0)
         binlen += 5;
      break;


      case HEX:
      binlen = enclen >> 1;
      if ((enclen & 0x01) != 0)
         binlen += 2;
      break;


      default:
      binlen = enclen;
      break;
   };

   return(binlen);
}


size_t lotp_encoded_len(lotp_enc enctype, size_t binlen)
{
   size_t enclen;

   switch(enctype)
   {
      case BASE32:
      enclen = (binlen / 5) * 8;
      if ((binlen % 5) != 0)
         enclen += 8;
      break;


      case HEX:
      enclen = binlen * 2;
      break;


      case NONE:
      enclen = binlen;
      break;


      default:
      enclen = binlen * 8;
   };

   return(enclen+1);
}


/* end of source */
