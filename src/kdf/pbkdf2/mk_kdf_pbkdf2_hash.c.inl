#define mk_kdf_pbkdf2_hash_v1 1
#define mk_kdf_pbkdf2_hash_v2 2
#define mk_kdf_pbkdf2_hash_v3 3


#if !defined(mk_kdf_pbkdf2_hash_v) || mk_kdf_pbkdf2_hash_v == mk_kdf_pbkdf2_hash_v1
#include "mk_kdf_pbkdf2_hash_v1.c.inl"
#elif defined(mk_kdf_pbkdf2_hash_v) && mk_kdf_pbkdf2_hash_v == mk_kdf_pbkdf2_hash_v2
#include "mk_kdf_pbkdf2_hash_v2.c.inl"
#elif defined(mk_kdf_pbkdf2_hash_v) && mk_kdf_pbkdf2_hash_v == mk_kdf_pbkdf2_hash_v3
#include "mk_kdf_pbkdf2_hash_v3.c.inl"
#endif


#undef mk_kdf_pbkdf2_hash_v1
#undef mk_kdf_pbkdf2_hash_v2
#undef mk_kdf_pbkdf2_hash_v3
