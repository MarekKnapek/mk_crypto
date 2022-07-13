#define mk_xmacro_sep_comma ,
#define mk_xmacro_sep_nothing
#define mk_xmacro_expand(sep) \
	xcontent(md2) sep \
	xcontent(md4) sep \
	xcontent(md5) sep \
	xcontent(sha1) sep \
	xcontent(sha2_224) sep \
	xcontent(sha2_256) sep \
	xcontent(sha2_384) sep \
	xcontent(sha2_512) sep \
	xcontent(sha2_512224) sep \
	xcontent(sha2_512256) sep \
	xcontent(sha3_224) sep \
	xcontent(sha3_256) sep \
	xcontent(sha3_384) sep \
	xcontent(sha3_512)

#define xmacro mk_xmacro_expand(mk_xmacro_sep_nothing)
#define xmacro_comma mk_xmacro_expand(mk_xmacro_sep_comma)

#define concat_impl(a, b) a ## b
#define concat(a, b) concat_impl(a, b)
