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
#include "version.h"

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


/////////////////
//             //
//  Functions  //
//             //
/////////////////
#ifdef __LIBREOTP_PMARK
#pragma mark - Functions
#endif

const char * libreotp_api(uint32_t * pcur, uint32_t * prev, uint32_t * page)
{
   if (pcur != NULL)
      *pcur = LIB_VERSION_CURRENT;
   if (page != NULL)
      *page = LIB_VERSION_REVISION;
   if (prev != NULL)
      *prev = LIB_VERSION_AGE;
   return(LIB_VERSION_INFO);
}


const char * libreotp_version(uint32_t * pmaj, uint32_t * pmin,
   uint32_t * ppat, const char ** pbuild)
{
   if (pmaj != NULL)
      *pmaj = GIT_PACKAGE_MAJOR;
   if (pmin != NULL)
      *pmin = GIT_PACKAGE_MINOR;
   if (ppat != NULL)
      *ppat = GIT_PACKAGE_PATCH;
   if (pbuild != NULL)
      *pbuild = GIT_PACKAGE_BUILD;
   return(GIT_PACKAGE_VERSION_BUILD);
}


/* end of source */
