/*
 * Copyright (c) 1997 - 2008 Kungliga Tekniska Högskolan
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

/* Functions which are used by both single and triple DES enctypes */

#include "krb5_locl.h"

/*
 * A = A xor B. A & B are 8 bytes.
 */

void
_krb5_xor (unsigned char *key, const unsigned char *b)
{
    key[0] ^= b[0];
    key[1] ^= b[1];
    key[2] ^= b[2];
    key[3] ^= b[3];
    key[4] ^= b[4];
    key[5] ^= b[5];
    key[6] ^= b[6];
    key[7] ^= b[7];
}

#if defined(DES3_OLD_ENCTYPE) || defined(HEIM_KRB5_DES) || defined(HEIM_KRB5_DES3)
krb5_error_code
_krb5_des_checksum(krb5_context context,
		   CCDigestAlg alg,
		   struct key_data *key,
		   const void *data,
		   size_t len,
		   Checksum *cksum)
{
    struct evp_schedule *ctx = key->schedule->data;
    CCDigestRef m;
    unsigned char ivec[8];
    unsigned char *p = cksum->checksum.data;

    krb5_generate_random_block(p, 8);

    m = CCDigestCreate(alg);
    if (m == NULL) {
	krb5_set_error_message(context, ENOMEM, N_("malloc: out of memory", ""));
	return ENOMEM;
    }

    CCDigestUpdate(m, p, 8);
    CCDigestUpdate(m, data, len);
    CCDigestFinal(m, p + 8);
    CCDigestDestroy(m);
    memset (&ivec, 0, sizeof(ivec));
    EVP_CipherInit_ex(&ctx->ectx, NULL, NULL, NULL, (void *)ivec, -1);
    EVP_Cipher(&ctx->ectx, p, p, 24);

    return 0;
}

krb5_error_code
_krb5_des_verify(krb5_context context,
		 CCDigestAlg alg,
		 struct key_data *key,
		 const void *data,
		 size_t len,
		 Checksum *C)
{
    struct evp_schedule *ctx = key->schedule->data;
    CCDigestRef m;
    unsigned char tmp[24];
    unsigned char res[16];
    unsigned char ivec[8];
    krb5_error_code ret = 0;

    m = CCDigestCreate(alg);
    if (m == NULL) {
	krb5_set_error_message(context, ENOMEM, N_("malloc: out of memory", ""));
	return ENOMEM;
    }

    memset(ivec, 0, sizeof(ivec));
    EVP_CipherInit_ex(&ctx->dctx, NULL, NULL, NULL, (void *)ivec, -1);
    EVP_Cipher(&ctx->dctx, tmp, C->checksum.data, 24);

    CCDigestUpdate(m, tmp, 8); /* confounder */
    CCDigestUpdate(m, data, len);
    CCDigestFinal(m, res);
    CCDigestDestroy(m);
    if(ct_memcmp(res, tmp + 8, sizeof(res)) != 0) {
	krb5_clear_error_message (context);
	ret = KRB5KRB_AP_ERR_BAD_INTEGRITY;
    }
    memset(tmp, 0, sizeof(tmp));
    memset(res, 0, sizeof(res));
    return ret;
}

#endif

static krb5_error_code
RSA_MD5_checksum(krb5_context context,
		 struct key_data *key,
		 const void *data,
		 size_t len,
		 unsigned usage,
		 Checksum *C)
{
    if (CCDigest(kCCDigestMD5, data, len, C->checksum.data) != 0)
	krb5_abortx(context, "md5 checksum failed");
    return 0;
}

struct checksum_type _krb5_checksum_rsa_md5 = {
    CKSUMTYPE_RSA_MD5,
    "rsa-md5",
    64,
    16,
    F_CPROOF,
    RSA_MD5_checksum,
    NULL
};
