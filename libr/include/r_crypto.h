#ifndef R2_CRYPTO_H
#define R2_CRYPTO_H

#include <r_types.h>
#include <r_list.h>

#ifdef __cplusplus
extern "C" {
#endif

R_LIB_VERSION_HEADER(r_crypto);

enum {
	R_CRYPTO_MODE_ECB,
	R_CRYPTO_MODE_CBC,
	R_CRYPTO_MODE_OFB,
	R_CRYPTO_MODE_CFB,
};

enum {
	R_CRYPTO_DIR_CIPHER,
	R_CRYPTO_DIR_DECIPHER,
};

typedef struct r_crypto_t {
	struct r_crypto_plugin_t* h;
	ut8 *key;
	ut8 *iv;
	int key_len;
	ut8 *output;
	int output_len;
	int output_size;
	void *user;
	RList *plugins;
} RCrypto;

typedef struct r_crypto_plugin_t {
	const char *name;
	int (*get_key_size)(RCrypto *cry);
	int (*set_iv)(RCrypto *cry, const ut8 *iv);
	int (*set_key)(RCrypto *cry, const ut8 *key, int keylen, int mode, int direction);
	int (*update)(RCrypto *cry, const ut8 *buf, int len, bool to_encrypt);
	int (*final)(RCrypto *cry, const ut8 *buf, int len, bool to_encrypt);
	bool (*use)(const char *algo);
	int (*fini)(RCrypto *cry);
} RCryptoPlugin;

#ifdef R_API
R_API RCrypto *r_crypto_init(RCrypto *cry, int hard);
R_API RCrypto *r_crypto_as_new(RCrypto *cry);
R_API int r_crypto_add(RCrypto *cry, RCryptoPlugin *h);
R_API RCrypto *r_crypto_new(void);
R_API RCrypto *r_crypto_free(RCrypto *cry);
R_API bool r_crypto_use(RCrypto *cry, const char *algo);
R_API int r_crypto_set_key(RCrypto *cry, const ut8* key, int keylen, int mode, int direction);
R_API int r_crypto_set_iv(RCrypto *cry, const ut8 *iv);
R_API int r_crypto_update(RCrypto *cry, const ut8 *buf, int len, bool to_encrypt);
R_API int r_crypto_final(RCrypto *cry, const ut8 *buf, int len, bool to_encrypt);
R_API int r_crypto_append(RCrypto *cry, const ut8 *buf, int len);
R_API ut8 *r_crypto_get_output(RCrypto *cry, int *size);
#endif

/* plugin pointers */
extern RCryptoPlugin r_crypto_plugin_aes;
extern RCryptoPlugin r_crypto_plugin_rc4;
extern RCryptoPlugin r_crypto_plugin_xor;
extern RCryptoPlugin r_crypto_plugin_blowfish;
extern RCryptoPlugin r_crypto_plugin_rc2;
extern RCryptoPlugin r_crypto_plugin_rot;
extern RCryptoPlugin r_crypto_plugin_rol;
extern RCryptoPlugin r_crypto_plugin_ror;
extern RCryptoPlugin r_crypto_plugin_base64;
extern RCryptoPlugin r_crypto_plugin_base91;

#ifdef __cplusplus
}
#endif

#endif
