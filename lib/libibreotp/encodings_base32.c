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
#include "encodings_base32.h"

///////////////
//           //
//  Headers  //
//           //
///////////////
#ifdef __LIBREOTP_PMARK
#pragma mark - Headers
#endif

#include "encodings.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>


//////////////////
//               //
//  Definitions  //
//               //
///////////////////
#ifdef __LIBREOTP_PMARK
#pragma mark - Definitions
#endif


/////////////////
//             //
//  Variables  //
//             //
/////////////////
#ifdef __LIBREOTP_PMARK
#pragma mark - Variables
#endif


static const int8_t b32dec[256] =
{
//    This map cheats and interprets:
//       - the numeral zero as the letter "O" as in oscar
//       - the numeral one as the letter "L" as in lima
//       - the numeral eight as the letter "B" as in bravo
// 00  01  02  03  04  05  06  07  08  09  0A  0B  0C  0D  0E  0F
   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 0x00
   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 0x10
   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 0x20
   14, 11, 26, 27, 28, 29, 30, 31,  1, -1, -1, -1, -1,  0, -1, -1, // 0x30
   -1,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, // 0x40
   15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1, // 0x50
   -1,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, // 0x60
   15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, -1, -1, -1, -1, // 0x70
   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 0x80
   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 0x90
   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 0xA0
   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 0xB0
   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 0xC0
   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 0xD0
   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 0xE0
   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 0xF0
};


static const char * b32enc = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567=";


/////////////////
//             //
//  Functions  //
//             //
/////////////////
#ifdef __LIBREOTP_PMARK
#pragma mark - Functions
#endif

size_t lotp_decode_string_base32(char * str, size_t str_len, uint8_t * bin,
   size_t bin_size, size_t * str_off)
{
   size_t str_pos;
   size_t bin_len;

   str_pos = 0;
   bin_len = 0;

   // decodes base32 string to binary bytes
   while ((str_pos < (str_len-7)) && (bin_len < (bin_size - 5)))
   {
      // byte 0                                                01234567 01234567 01234567 01234567 01234567
      bin[bin_len]  = (b32dec[str[str_pos+0]] << 3) & 0xF8; // 11111000 00000000 00000000 00000000 00000000
      bin[bin_len] |= (b32dec[str[str_pos+1]] >> 2) & 0x07; // 00000111 00000000 00000000 00000000 00000000
      bin_len++;
      if (str[str_pos+2] == '=')
      {
         str_pos += 8;
         continue;
      };

      // byte 1                                                01234567 01234567 01234567 01234567 01234567
      bin[bin_len]  = (b32dec[str[str_pos+1]] << 6) & 0xC0; // 00000000 11000000 00000000 00000000 00000000
      bin[bin_len] |= (b32dec[str[str_pos+2]] << 1) & 0x3E; // 00000000 00111110 00000000 00000000 00000000
      bin[bin_len] |= (b32dec[str[str_pos+3]] >> 4) & 0x01; // 00000000 00000001 00000000 00000000 00000000
      bin_len++;
      if (str[str_pos+4] == '=')
      {
         str_pos += 8;
         continue;
      };

      // byte 2                                                01234567 01234567 01234567 01234567 01234567
      bin[bin_len]  = (b32dec[str[str_pos+3]] << 4) & 0xF0; // 00000000 00000000 11110000 00000000 00000000
      bin[bin_len] |= (b32dec[str[str_pos+4]] >> 1) & 0x0F; // 00000000 00000000 00001111 00000000 00000000
      bin_len++;
      if (str[str_pos+5] == '=')
      {
         str_pos += 8;
         continue;
      };

      // byte 3                                                01234567 01234567 01234567 01234567 01234567
      bin[bin_len]  = (b32dec[str[str_pos+4]] << 7) & 0x80; // 00000000 00000000 00000000 10000000 00000000
      bin[bin_len] |= (b32dec[str[str_pos+5]] << 2) & 0x7C; // 00000000 00000000 00000000 01111100 00000000
      bin[bin_len] |= (b32dec[str[str_pos+6]] >> 3) & 0x03; // 00000000 00000000 00000000 00000011 00000000
      bin_len++;
      if (str[str_pos+7] == '=')
      {
         str_pos += 8;
         continue;
      };

      // byte 4                                                01234567 01234567 01234567 01234567 01234567
      bin[bin_len]  = (b32dec[str[str_pos+6]] << 5) & 0xE0; // 00000000 00000000 00000000 00000000 11100000
      bin[bin_len] |= (b32dec[str[str_pos+7]] >> 0) & 0x1F; // 00000000 00000000 00000000 00000000 00011111
      bin_len++;

      str_pos += 8;
   };

   if (str_off != NULL)
      *str_off = str_pos;

   return(bin_len);
}


size_t lotp_encode_binary_base32(uint8_t * bin, size_t bin_len, char * str,
   size_t str_len, size_t * bin_off)
{
   uint8_t bits;
   size_t  str_pos;
   size_t  bin_pos;

   str_pos = 0;
   bin_pos = 0;

   while ( (str_pos < (str_len-9)) && (bin_pos < bin_len) )
   {
      // 01234567 01234567 01234567 01234567 01234567
      // 11111000 00000000 00000000 00000000 00000000
      bits = (bin[bin_pos] & 0xF8) >> 3;
      str[str_pos] = b32enc[ bits ];
      str_pos++;

      // 01234567 01234567 01234567 01234567 01234567
      // 00000111 11000000 00000000 00000000 00000000
      bits = (bin[bin_pos] & 0x07) << 2;
      bin_pos++;
      if (bin_pos >= bin_len)
      {
         str[str_pos] = b32enc[ bits ];
         str_pos++;
         continue;
      };
      bits |= (bin[bin_pos] & 0xC0) >> 6;
      str[str_pos] = b32enc[ bits ];
      str_pos++;

      // 01234567 01234567 01234567 01234567 01234567
      // 00000000 00111110 00000000 00000000 00000000
      bits = (bin[bin_pos] & 0x3E) >> 1;
      str[str_pos] = b32enc[ bits ];
      str_pos++;

      // 01234567 01234567 01234567 01234567 01234567
      // 00000000 00000001 11110000 00000000 00000000
      bits = (bin[bin_pos] & 0x01) << 4;
      bin_pos++;
      if (bin_pos >= bin_len)
      {
         str[str_pos] = b32enc[ bits ];
         str_pos++;
         continue;
      };
      bits |= (bin[bin_pos] & 0xF0) >> 4;
      str[str_pos] = b32enc[ bits ];
      str_pos++;

      // 01234567 01234567 01234567 01234567 01234567
      // 00000000 00000000 00001111 10000000 00000000
      bits = (bin[bin_pos] & 0x0F) << 1;
      bin_pos++;
      if (bin_pos >= bin_len)
      {
         str[str_pos] = b32enc[ bits ];
         str_pos++;
         continue;
      };
      bits |= (bin[bin_pos] & 0x01) >> 7;
      str[str_pos] = b32enc[ bits ];
      str_pos++;

      // 01234567 01234567 01234567 01234567 01234567
      // 00000000 00000000 00000000 01111100 00000000
      bits = (bin[bin_pos] & 0x7C) >> 2;
      str[str_pos] = b32enc[ bits ];
      str_pos++;

      // 01234567 01234567 01234567 01234567 01234567
      // 00000000 00000000 00000000 00000011 11100000
      bits = (bin[bin_pos] & 0x03) << 3;
      bin_pos++;
      if (bin_pos >= bin_len)
      {
         str[str_pos] = b32enc[ bits ];
         str_pos++;
         continue;
      };
      bits |= (bin[bin_pos] & 0xE0) >> 5;
      str[str_pos] = b32enc[ bits ];
      str_pos++;

      // 01234567 01234567 01234567 01234567 01234567
      // 00000000 00000000 00000000 00000000 00011111
      bits = bin[bin_pos] & 0x1F;
      str[str_pos] = b32enc[ bits ];
      str_pos++;
      bin_pos++;
   };

   // save binary offset
   if (bin_off != NULL)
      *bin_off = bin_pos;

   // padd and terminate string
   while((str_pos % 8) != 0)
   {
      str[str_pos] = '=';
      str_pos++;
   };
   str[str_pos] = '\0';


   return(str_pos);
}


int lotp_encoding_validate_base32(char * str, size_t str_len, size_t * bin_len)
{
   size_t pos;
   size_t rem;

   // validates base32 string length
   if (((str_len & 0xF) != 0) && ((str_len & 0xF) != 8))
      return(1);

   // validates syntax of base32 string
   for(pos = 0; (pos < str_len); pos++)
   {
      // validates padding rules
      if (str[pos] == '=')
      {
         // padding is never more than 6 characters
         if ((str_len - pos) > 6)
            return(1);

         // verify padding starts on correct string position
         rem = pos % 8;
         if ( (rem != 2) && (rem != 4) && (rem != 5) && (rem != 7) )
            return(1);

         // verify remainder of string is padding
         for(; (pos < str_len); pos++)
            if (str[pos] != '=')
               return(1);
      }

      // validates character is valid for base32 encoding
      else if (b32dec[str[pos]] == -1)
      {
         return(1);
      };
   };

   return(0);
}


/* end of source */
