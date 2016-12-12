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
   size_t pos;
   size_t bin_len;

   bin_len = 0;

   // decodes base32 string
   for(pos = 0; ((pos <= str_len) && (bin_len <= (bin_size - 5))); pos += 8)
   {
      // MSB is Most Significant Bits  (0x80 == 10000000 ~= MSB)
      // MB is middle bits             (0x7E == 01111110 ~= MB)
      // LSB is Least Significant Bits (0x01 == 00000001 ~= LSB)

      // byte 0
      bin[bin_len+0]  = (b32dec[str[pos+0]] << 3) & 0xF8; // 5 MSB 11111000 00000000 00000000 00000000 00000000
      bin[bin_len+0] |= (b32dec[str[pos+1]] >> 2) & 0x07; // 3 LSB 00000111 00000000 00000000 00000000 00000000
      if ((str[pos+2] == '=') || (str_len <= (pos+2))
      {
          bin_len += 1;
          break;
      };

      // byte 1
      bin[bin_len+1]  = (b32dec[str[pos+1]] << 6) & 0xC0; // 2 MSB 00000000 11000000 00000000 00000000 00000000
      bin[bin_len+1] |= (b32dec[str[pos+2]] << 1) & 0x3E; // 5  MB 00000000 00111110 00000000 00000000 00000000
      bin[bin_len+1] |= (b32dec[str[pos+3]] >> 4) & 0x01; // 1 LSB 00000000 00000001 00000000 00000000 00000000
      if (str[pos+4] == '=')
      {
          bin_len += 2;
          break;
      };

      // byte 2
      bin[bin_len+2]  = (b32dec[str[pos+3]] << 4) & 0xF0; // 4 MSB
      bin[bin_len+2] |= (b32dec[str[pos+4]] >> 1) & 0x0F; // 4 LSB
      if (str[pos+5] == '=')
      {
          bin_len += 3;
          break;
      };

      // byte 3
      bin[bin_len+3]  = (b32dec[str[pos+4]] << 7) & 0x80; // 1 MSB
      bin[bin_len+3] |= (b32dec[str[pos+5]] << 2) & 0x7C; // 5  MB
      bin[bin_len+3] |= (b32dec[str[pos+6]] >> 3) & 0x03; // 2 LSB
      if (str[pos+7] == '=')
      {
          bin_len += 4;
          break;
      };

      // byte 4
      bin[bin_len+4]  = (b32dec[str[pos+6]] << 5) & 0xE0; // 3 MSB
      bin[bin_len+4] |= (b32dec[str[pos+7]] >> 0) & 0x1F; // 5 LSB
      bin_len += 5;
   };
   pos -= 8;

   if (str_off != NULL)
      *str_off = pos;

   return(bin_len);
}


size_t lotp_encode_binary_base32(uint8_t * bin, size_t bin_len, char * str,
   size_t str_len, size_t * bin_off)
{
   uint8_t bits;
   size_t  spos;
   size_t  bpos;

   spos = 0;
   bpos = 0;

   while ( (spos < (str_len-9)) && (bpos < bin_len) )
   {
      // 01234567 01234567 01234567 01234567 01234567
      // 11111000 00000000 00000000 00000000 00000000
      bits = (bin[bpos] & 0xF8) >> 3;
      str[spos] = b32enc[ bits ];
      spos++;

      // 01234567 01234567 01234567 01234567 01234567
      // 00000111 11000000 00000000 00000000 00000000
      bits = (bin[bpos] & 0x07) << 2;
      bpos++;
      if (bpos >= bin_len)
      {
         str[spos] = b32enc[ bits ];
         spos++;
         continue;
      };
      bits |= (bin[bpos] & 0xC0) >> 6;
      str[spos] = b32enc[ bits ];
      spos++;

      // 01234567 01234567 01234567 01234567 01234567
      // 00000000 00111110 00000000 00000000 00000000
      bits = (bin[bpos] & 0x3E) >> 1;
      str[spos] = b32enc[ bits ];
      spos++;

      // 01234567 01234567 01234567 01234567 01234567
      // 00000000 00000001 11110000 00000000 00000000
      bits = (bin[bpos] & 0x01) << 4;
      bpos++;
      if (bpos >= bin_len)
      {
         str[spos] = b32enc[ bits ];
         spos++;
         continue;
      };
      bits |= (bin[bpos] & 0xF0) >> 4;
      str[spos] = b32enc[ bits ];
      spos++;

      // 01234567 01234567 01234567 01234567 01234567
      // 00000000 00000000 00001111 10000000 00000000
      bits = (bin[bpos] & 0x0F) << 1;
      bpos++;
      if (bpos >= bin_len)
      {
         str[spos] = b32enc[ bits ];
         spos++;
         continue;
      };
      bits |= (bin[bpos] & 0x01) >> 7;
      str[spos] = b32enc[ bits ];
      spos++;

      // 01234567 01234567 01234567 01234567 01234567
      // 00000000 00000000 00000000 01111100 00000000
      bits = (bin[bpos] & 0x7C) >> 2;
      str[spos] = b32enc[ bits ];
      spos++;

      // 01234567 01234567 01234567 01234567 01234567
      // 00000000 00000000 00000000 00000011 11100000
      bits = (bin[bpos] & 0x03) << 3;
      bpos++;
      if (bpos >= bin_len)
      {
         str[spos] = b32enc[ bits ];
         spos++;
         continue;
      };
      bits |= (bin[bpos] & 0xE0) >> 5;
      str[spos] = b32enc[ bits ];
      spos++;

      // 01234567 01234567 01234567 01234567 01234567
      // 00000000 00000000 00000000 00000000 00011111
      bits = bin[bpos] & 0x1F;
      str[spos] = b32enc[ bits ];
      spos++;
      bpos++;
   };

   // save binary offset
   if (bin_off != NULL)
      *bin_off = bpos;

   // padd and terminate string
   while((spos % 8) != 0)
   {
      str[spos] = '=';
      spos++;
   };
   str[spos] = '\0';


   return(spos -1);
}


int lotp_encoding_validate_base32(char * str, size_t str_len, size_t * bin_len)
{
   size_t pos;

   // validates base32 string length
   if (((str_len & 0xF) != 0) && ((str_len & 0xF) != 8))
   {
      return(1);
   };


   // validates syntax of base32 string
   for(pos = 0; (pos < str_len); pos++)
   {
      // validates character is valid for base32 encoding
      if (b32dec[str[pos]] == -1)
      {
         return(1);
      };

      // validates padding rules
      if (str[pos] == '=')
      {
         // verifies that padding does not start at beginning of 
         if (((pos & 0xF) == 0) || ((pos & 0xF) == 8))
         {
            return(1);
         }
         if ((str_len - pos) > 6)
         {
            return(1);
         };
         switch(pos%8)
         {
            case 2:
            case 4:
            case 5:
            case 7:
            break;

            default:
            return(1);
         };
         for(; (pos < str_len); pos++)
         {
            if (str[pos] != '=')
            {
               return(1);
            };
         };
      };
   };

   return(0);
}


/* end of source */
