/*
 * Copyright (c) 2007 Kungliga Tekniska Högskolan
 * (Royal Institute of Technology, Stockholm, Sweden).
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <config.h>

#include <stdio.h>
#include <stdlib.h>
#include <err.h>

#include "imath/imath.h"

static void
umr_exptmod(void)
{
    mp_result res;
    mpz_t tmp, z;

    res = mp_int_init(&tmp);
    if (res != MP_OK)
	errx(1, "ini_init");

    res = mp_int_init(&z);
    if (res != MP_OK)
	errx(1, "ini_init");

    res = mp_int_read_unsigned(&z, (void*)
"\x31\xD2\xA3\x66\xB0\x82\xD2\x61\x20\x85\xDF\xAE\x14\x73\x7C\x3A\xF5\x87\xCE\xED\xD6\x46\xBB\x45\x7C\xAF\x0F\x32\x56\xA7\x93\x87\x79\x36\xED\x29\xB8\xBF\x8B\xD8\x45\x6A\x87\x59\xDD\x03\x93\xD2\x8A\x61\xC0\x61\xA7\x7B\xA6\x24\x2A\xB6\x56\x80\x5D\xE9\x07\xD6\x1F\xF4\x00\xD7\xB4\x8B\xB0\xF9\xF5\x37\x52\xD2\x3A\xE5\xA5\xC4\x46\x65\x25\xEE\xE0\xCC\x12\x0A\x82\x68\x8B\xDF\x51\x92\xB5\x70\x87\xB5\x47\x3B\x40\xF7\x34\x35\x2E\x86\x08\x68\x6B\xAD\x2D\xB1\x12\x52\x9F\xF2\x1E\xB1\xFC\xA0\x19\x87\x7F\x6A\x1A\x35\xDA\xA1", 128);
    if (res != MP_OK)
	errx(1, "int_read");

    res = mp_int_exptmod_bvalue(3, &z, &z, &tmp);
    if (res != MP_OK)
	errx(1, "exptmod_bvalue");

    mp_int_clear(&tmp);
    mp_int_clear(&z);
}

static void
abr_mp_int_mul(void)
{
    mp_result res;
    mpz_t t1, in;

    res = mp_int_init(&t1);
    if (res != MP_OK)
	errx(1, "ini_init");

    res = mp_int_init(&in);
    if (res != MP_OK)
	errx(1, "ini_init");

    res = mp_int_read_unsigned(&t1, (void*)
			       "\x20\x12\xBB\x7C\xA7\x11\x2A\xF5\x4C\x17\xF5\x4B\x60\x6A\x02\x5C\xA8\x24\xBC\x9A\xDD\x94\x54\x99\xC9\x66\xCB\x45\x11\x5D\xA1\xD5\x69\x95\x0A\xE4\x23\x93\x24\x01\x55\x6F\xC6\xDC\xA1\x47\x54\xCC\x82\xCB\x07\xBD\x58\xCE\x31\x5E\x0E\x63\xEF\x9F\x04\xBB\xE2\xA0\xB5\x6B\x04\x58\x5E\xC6\x3D\xEE\x48\x57\x3A\x5C\x5E\xE3\xA7\xA9\xA3\x30\xE9\x76\x16\xCB\x70\xAF\x80\x01\xE1\xE0\xDD\xC0\x4F\x54\xA4\x76\xC4\x25\x30\x6A\x66\xC5\xCB\x47\xBE\x9F\xE9\x37\x72\xB5\x91\x3A\x0E\x24\xA6\xE6\xBB\x40\xB0\xDA\xE1\xAA\xB1\x0F\x1D\x9C\xD2\x63\x62\xD4\xFB\x2C\xD3\x46\xF1\x73\xB3\x48\xEF\x45\xC3\x00\xC9\xFA\x91\xB6\xB3\x58\x94\x25\x0C\xB4\xFA\x8B\x48\x70\xEF\x91\x04\x8C\x7C\xB6\x67\x82\x53\x42\xBD\xDB\x94\x7F\x77\x5A\xD5\x6D\x15\xB1\x6F\x44\x3A\x34\xE5\xCF\x99\x76\x11\xE5\x75\xBF\x19\xF4\x4A\x40\xAD\x2B\x72\xF1\x48\x3F\x2A\xE1\xFB\x9D\x8B\x43\x27\x6E\x99\x8F\x66\x99\xF5\x13\xE5\x16\x08\xAA\xBD\x99\x95\x30\xDB\x8D\xFA\x91\xAF\xD6\x2C\x28\x2C\xD2\xE9\xDE\x19\x7D\x2A\x99\x53\xD9\x6C\x07\x40\x99\x17\xE0\x22\xA0\x6F\x95\x65\xCC\x48\x4A\x8C\x56\x44\xBD",
			       258);
    if (res != MP_OK)
	errx(1, "int_read");

    res = mp_int_read_unsigned(&in, (void*)
			       "\x00\x01\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\x00\x68\x65\x6C\x6C\x6F\x2C\x20\x77\x6F\x72\x6C\x64\x21\x00",
			       258);
    if (res != MP_OK)
	errx(1, "int_read");

    mp_int_mul(&t1, &in, &in);

    mp_int_clear(&t1);
    mp_int_clear(&in);
}

int
main(int argc, char **argv)
{
    umr_exptmod();
    abr_mp_int_mul();

    return 0;
}
