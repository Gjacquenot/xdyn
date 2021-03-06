/*
 * A custom base64/91 encoder/decoder (TSV, XML and JSON friendly).
 * Copyright (c) 2011-2015 Mario 'rlyeh' Rodriguez, zlib/libpng licensed.

 * Base64 is based on code by René Nyffenegger (zlib/libpng licensed)
 *
 * Base91 is based on code by Joachim Henke.
 * Copyright (c) 2000-2006 Joachim Henke
 * http://base91.sourceforge.net/ (v0.6.0)
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *  - Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *  - Neither the name of Joachim Henke nor the names of his contributors may
 *    be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.

 * - rlyeh
 */

#pragma once
#include <string>

//#define USE_RLYEH_MODIFIED_DICT

namespace {

    /* Public API */

    template<unsigned N> struct base {
        static std::string encode( const size_t lenData, void const * const data);
        static std::string encode( const std::string &binary );
        static std::string decode( const std::string &text );
    };

    typedef base<64> base64;
    typedef base<91> base91;

    /* API details */
    template<>
    std::string base<91>::encode( const size_t lenData, void const * const data)
    {

        const unsigned char enctab[91] = {
            #ifndef USE_RLYEH_MODIFIED_DICT
            // Henke's original
            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', //00..12
            'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', //13..25
            'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', //26..38
            'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', //39..51
            '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '!', '#', '$', //52..64
            '%', '&', '(', ')', '*', '+', ',', '.', '/', ':', ';', '<', '=', //65..77
            '>', '?', '@', '[', ']', '^', '_', '`', '{', '|', '}', '~', '"'  //78..90
            #else
            // rlyeh's modification
            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', //00..12
            'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', //13..25
            'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', //26..38
            'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', //39..51
            '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '!', '#', '$', //52..64
            '%', '&', '(', ')', '*', '+', ',', '.', '/', ':', ';', '-', '=', //65..77
            '\\','?', '@', '[', ']', '^', '_', '`', '{', '|', '}', '~', '\'' //78..90
            #endif
        };
        std::string ob;
        const unsigned char *ib = (unsigned char *) data;

        unsigned long queue = 0;
        unsigned int nbits = 0;

        size_t len = lenData;
        for(; len--; ) {
            queue |= *ib++ << nbits;
            nbits += 8;
            if (nbits > 13) {   /* enough bits in queue */
                unsigned int val = queue & 8191;

                if (val > 88) {
                    queue >>= 13;
                    nbits -= 13;
                } else {    /* we can take 14 bits */
                    val = queue & 16383;
                    queue >>= 14;
                    nbits -= 14;
                }
                ob.push_back( enctab[val % 91] );
                ob.push_back( enctab[val / 91] );
            }
        }

        /* process remaining bits from bit queue; write up to 2 bytes */
        if (nbits) {
            ob.push_back( enctab[queue % 91] );
            if (nbits > 7 || queue > 90)
                ob.push_back( enctab[queue / 91] );
        }

        /* return text data */
        return ob;
    }

    template<>
    std::string base<91>::encode( const std::string &binary ) {
        return encode((const size_t) binary.size(), (void const * const) binary.c_str());
    }

    template<>
    std::string base<91>::decode( const std::string &text ) {

        const unsigned char dectab[256] = {
            #ifndef USE_RLYEH_MODIFIED_DICT
            // Henke's original
            91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, //000..015
            91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, //016..031
            91, 62, 90, 63, 64, 65, 66, 91, 67, 68, 69, 70, 71, 91, 72, 73, //032..047
            52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 74, 75, 76, 77, 78, 79, //048..063
            80,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, //064..079
            15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 81, 91, 82, 83, 84, //080..095
            85, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, //096..111
            41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 86, 87, 88, 89, 91, //112..127
            91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, //128..143
            91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, //144..159
            91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, //160..175
            91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, //176..191
            91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, //192..207
            91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, //208..223
            91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, //224..239
            91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91  //240..255
            #else
            // rlyeh's modification
            91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, //000..015
            91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, //016..031
            91, 62, 91, 63, 64, 65, 66, 90, 67, 68, 69, 70, 71, 76, 72, 73, //032..047 // @34: ", @39: ', @45: -
            52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 74, 75, 91, 77, 91, 79, //048..063 // @60: <, @62: >
            80,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, //064..079
            15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 81, 78, 82, 83, 84, //080..095 // @92: slash
            85, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, //096..111
            41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 86, 87, 88, 89, 91, //112..127
            91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, //128..143
            91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, //144..159
            91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, //160..175
            91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, //176..191
            91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, //192..207
            91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, //208..223
            91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, //224..239
            91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91, 91  //240..255
            #endif
        };

        std::string ob;
        const unsigned char *ib = (unsigned char *) text.c_str();

        unsigned long queue = 0;
        unsigned int nbits = 0;
        int val = -1;

        for( size_t len = text.size(); len--; ) {
            unsigned int d = dectab[*ib++];
            if (d == 91)
                continue;   /* ignore non-alphabet chars */
            if (val == -1)
                val = d;    /* start next value */
            else {
                val += d * 91;
                queue |= val << nbits;
                nbits += (val & 8191) > 88 ? 13 : 14;
                do {
                    ob.push_back( char( queue ) );
                    queue >>= 8;
                    nbits -= 8;
                } while (nbits > 7);
                val = -1;   /* mark value complete */
            }
        }

        /* process remaining bits; write at most 1 byte */
        if (val != -1)
            ob.push_back( char( queue | val << nbits ) );

        /* return original binary data */
        return ob;
    }


    template<>
    std::string base<64>::encode( const size_t lenData, void const * const data)
    {

        const std::string chars =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz"
            "0123456789+/";

        unsigned char const* bytes_to_encode = (unsigned char const *)data;
        size_t in_len = lenData;
        std::string ret;
        int i = 0;
        int j = 0;
        unsigned char char_array_3[3];
        unsigned char char_array_4[4];

        while( in_len-- ) {
            char_array_3[i++] = *(bytes_to_encode++);
            if( i == 3 ) {
                char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
                char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
                char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
                char_array_4[3] = char_array_3[2] & 0x3f;

                for( i = 0; (i <4) ; i++ )
                    ret += chars[char_array_4[i]];
                i = 0;
            }
        }

        if( i ) {
            for( j = i; j < 3; j++ )
                char_array_3[j] = '\0';

            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for( j = 0; (j < i + 1); j++ )
                ret += chars[char_array_4[j]];

            while( (i++ < 3) )
                ret += '=';
        }

        return ret;
    }

    template<>
    std::string base<64>::encode( const std::string &text ) {
        return encode(text.size(), text.c_str());
    }

    template<>
    std::string base<64>::decode( const std::string &encoded ) {

        const std::string chars =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz"
            "0123456789+/";

        int in_len = encoded.size();
        int i = 0;
        int j = 0;
        int in_ = 0;
        unsigned char char_array_4[4], char_array_3[3];
        std::string ret;

        while (in_len-- && ( encoded[in_] != '=') && //is_base64(encoded[in_])) {
            (isalnum(encoded[in_]) || encoded[in_] == '+' || encoded[in_] == '/')) {
            char_array_4[i++] = encoded[in_]; in_++;
            if (i ==4) {
                for (i = 0; i <4; i++)
                    char_array_4[i] = chars.find(char_array_4[i]);

                char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
                char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
                char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

                for (i = 0; (i < 3); i++)
                    ret += char_array_3[i];
                i = 0;
            }
        }

        if (i) {
            for (j = i; j <4; j++)
                char_array_4[j] = 0;

            for (j = 0; j <4; j++)
                char_array_4[j] = chars.find(char_array_4[j]);

            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

            for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
        }

        return ret;
    }
}
