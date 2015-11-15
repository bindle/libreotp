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
#ifndef __LIBIBREOTP_VERSION_H
#define __LIBIBREOTP_VERSION_H 1

///////////////
//           //
//  Headers  //
//           //
///////////////
#ifdef __LIBREOTP_PMARK
#pragma mark - Headers
#endif

#include "libreotp.h"


///////////////////
//               //
//  Definitions  //
//               //
///////////////////
#ifdef __LIBREOTP_PMARK
#pragma mark - Definitions
#endif

#ifndef GIT_PACKAGE_MAJOR
#   define GIT_PACKAGE_MAJOR 0
#endif
#ifndef GIT_PACKAGE_MINOR
#   define GIT_PACKAGE_MINOR 0
#endif
#ifndef GIT_PACKAGE_PATCH
#   define GIT_PACKAGE_PATCH 0
#endif
#ifndef GIT_PACKAGE_BUILD
#   define GIT_PACKAGE_BUILD "xxxxxx"
#endif


#ifndef LIB_VERSION_CURRENT
#define LIB_VERSION_CURRENT  0
#endif
#ifndef LIB_VERSION_REVISION
#define LIB_VERSION_REVISION 0xffffffff
#endif
#ifndef LIB_VERSION_AGE
#define LIB_VERSION_AGE      0xffffffff
#endif
#ifndef LIB_VERSION_INFO
#define LIB_VERSION_INFO NULL
#endif
#ifndef LIB_RELEASE_INFO
#define LIB_RELEASE_INFO NULL
#endif


#endif /* end of header */
