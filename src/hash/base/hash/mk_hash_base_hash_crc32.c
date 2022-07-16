#include "mk_hash_base_hash_crc32.h"

#include "../../../utils/mk_assert.h"
#include "../../../utils/mk_jumbo.h"

#include "../../../../../mk_int/src/exact/mk_uint_32.h"


#define mk_hash_base_hash_crc32_table_small 2
#define mk_hash_base_hash_crc32_table_fast 3
#if !defined(mk_hash_base_hash_crc32_table)
#define mk_hash_base_hash_crc32_table mk_hash_base_hash_crc32_table_fast
#endif


static mk_inline void mk_hash_base_hash_crc32_detail_table_small(unsigned char idx, struct mk_uint32_s* out)
{
	static struct mk_uint32_s const s_crc32_constant = mk_uint32_c(0xedb88320l);

	struct mk_uint32_s num;
	int i;

	mk_assert(out);

	mk_uint32_from_int(&num, idx);
	for(i = 0; i != 8; ++i)
	{
		if((mk_uint32_to_int(&num) & 0x01) != 0)
		{
			mk_uint32_shr(&num, &num, 1);
			mk_uint32_xor(&num, &num, &s_crc32_constant);
		}
		else
		{
			mk_uint32_shr(&num, &num, 1);
		}
	}
	*out = num;
}

static mk_inline void mk_hash_base_hash_crc32_detail_table_fast(unsigned char idx, struct mk_uint32_s* out)
{
	static struct mk_uint32_s const s_crc32_table[] =
	{
		mk_uint32_c(0x00000000l), mk_uint32_c(0x77073096l), mk_uint32_c(0xee0e612cl), mk_uint32_c(0x990951bal), mk_uint32_c(0x076dc419l), mk_uint32_c(0x706af48fl), mk_uint32_c(0xe963a535l), mk_uint32_c(0x9e6495a3l),
		mk_uint32_c(0x0edb8832l), mk_uint32_c(0x79dcb8a4l), mk_uint32_c(0xe0d5e91el), mk_uint32_c(0x97d2d988l), mk_uint32_c(0x09b64c2bl), mk_uint32_c(0x7eb17cbdl), mk_uint32_c(0xe7b82d07l), mk_uint32_c(0x90bf1d91l),
		mk_uint32_c(0x1db71064l), mk_uint32_c(0x6ab020f2l), mk_uint32_c(0xf3b97148l), mk_uint32_c(0x84be41del), mk_uint32_c(0x1adad47dl), mk_uint32_c(0x6ddde4ebl), mk_uint32_c(0xf4d4b551l), mk_uint32_c(0x83d385c7l),
		mk_uint32_c(0x136c9856l), mk_uint32_c(0x646ba8c0l), mk_uint32_c(0xfd62f97al), mk_uint32_c(0x8a65c9ecl), mk_uint32_c(0x14015c4fl), mk_uint32_c(0x63066cd9l), mk_uint32_c(0xfa0f3d63l), mk_uint32_c(0x8d080df5l),
		mk_uint32_c(0x3b6e20c8l), mk_uint32_c(0x4c69105el), mk_uint32_c(0xd56041e4l), mk_uint32_c(0xa2677172l), mk_uint32_c(0x3c03e4d1l), mk_uint32_c(0x4b04d447l), mk_uint32_c(0xd20d85fdl), mk_uint32_c(0xa50ab56bl),
		mk_uint32_c(0x35b5a8fal), mk_uint32_c(0x42b2986cl), mk_uint32_c(0xdbbbc9d6l), mk_uint32_c(0xacbcf940l), mk_uint32_c(0x32d86ce3l), mk_uint32_c(0x45df5c75l), mk_uint32_c(0xdcd60dcfl), mk_uint32_c(0xabd13d59l),
		mk_uint32_c(0x26d930acl), mk_uint32_c(0x51de003al), mk_uint32_c(0xc8d75180l), mk_uint32_c(0xbfd06116l), mk_uint32_c(0x21b4f4b5l), mk_uint32_c(0x56b3c423l), mk_uint32_c(0xcfba9599l), mk_uint32_c(0xb8bda50fl),
		mk_uint32_c(0x2802b89el), mk_uint32_c(0x5f058808l), mk_uint32_c(0xc60cd9b2l), mk_uint32_c(0xb10be924l), mk_uint32_c(0x2f6f7c87l), mk_uint32_c(0x58684c11l), mk_uint32_c(0xc1611dabl), mk_uint32_c(0xb6662d3dl),
		mk_uint32_c(0x76dc4190l), mk_uint32_c(0x01db7106l), mk_uint32_c(0x98d220bcl), mk_uint32_c(0xefd5102al), mk_uint32_c(0x71b18589l), mk_uint32_c(0x06b6b51fl), mk_uint32_c(0x9fbfe4a5l), mk_uint32_c(0xe8b8d433l),
		mk_uint32_c(0x7807c9a2l), mk_uint32_c(0x0f00f934l), mk_uint32_c(0x9609a88el), mk_uint32_c(0xe10e9818l), mk_uint32_c(0x7f6a0dbbl), mk_uint32_c(0x086d3d2dl), mk_uint32_c(0x91646c97l), mk_uint32_c(0xe6635c01l),
		mk_uint32_c(0x6b6b51f4l), mk_uint32_c(0x1c6c6162l), mk_uint32_c(0x856530d8l), mk_uint32_c(0xf262004el), mk_uint32_c(0x6c0695edl), mk_uint32_c(0x1b01a57bl), mk_uint32_c(0x8208f4c1l), mk_uint32_c(0xf50fc457l),
		mk_uint32_c(0x65b0d9c6l), mk_uint32_c(0x12b7e950l), mk_uint32_c(0x8bbeb8eal), mk_uint32_c(0xfcb9887cl), mk_uint32_c(0x62dd1ddfl), mk_uint32_c(0x15da2d49l), mk_uint32_c(0x8cd37cf3l), mk_uint32_c(0xfbd44c65l),
		mk_uint32_c(0x4db26158l), mk_uint32_c(0x3ab551cel), mk_uint32_c(0xa3bc0074l), mk_uint32_c(0xd4bb30e2l), mk_uint32_c(0x4adfa541l), mk_uint32_c(0x3dd895d7l), mk_uint32_c(0xa4d1c46dl), mk_uint32_c(0xd3d6f4fbl),
		mk_uint32_c(0x4369e96al), mk_uint32_c(0x346ed9fcl), mk_uint32_c(0xad678846l), mk_uint32_c(0xda60b8d0l), mk_uint32_c(0x44042d73l), mk_uint32_c(0x33031de5l), mk_uint32_c(0xaa0a4c5fl), mk_uint32_c(0xdd0d7cc9l),
		mk_uint32_c(0x5005713cl), mk_uint32_c(0x270241aal), mk_uint32_c(0xbe0b1010l), mk_uint32_c(0xc90c2086l), mk_uint32_c(0x5768b525l), mk_uint32_c(0x206f85b3l), mk_uint32_c(0xb966d409l), mk_uint32_c(0xce61e49fl),
		mk_uint32_c(0x5edef90el), mk_uint32_c(0x29d9c998l), mk_uint32_c(0xb0d09822l), mk_uint32_c(0xc7d7a8b4l), mk_uint32_c(0x59b33d17l), mk_uint32_c(0x2eb40d81l), mk_uint32_c(0xb7bd5c3bl), mk_uint32_c(0xc0ba6cadl),
		mk_uint32_c(0xedb88320l), mk_uint32_c(0x9abfb3b6l), mk_uint32_c(0x03b6e20cl), mk_uint32_c(0x74b1d29al), mk_uint32_c(0xead54739l), mk_uint32_c(0x9dd277afl), mk_uint32_c(0x04db2615l), mk_uint32_c(0x73dc1683l),
		mk_uint32_c(0xe3630b12l), mk_uint32_c(0x94643b84l), mk_uint32_c(0x0d6d6a3el), mk_uint32_c(0x7a6a5aa8l), mk_uint32_c(0xe40ecf0bl), mk_uint32_c(0x9309ff9dl), mk_uint32_c(0x0a00ae27l), mk_uint32_c(0x7d079eb1l),
		mk_uint32_c(0xf00f9344l), mk_uint32_c(0x8708a3d2l), mk_uint32_c(0x1e01f268l), mk_uint32_c(0x6906c2fel), mk_uint32_c(0xf762575dl), mk_uint32_c(0x806567cbl), mk_uint32_c(0x196c3671l), mk_uint32_c(0x6e6b06e7l),
		mk_uint32_c(0xfed41b76l), mk_uint32_c(0x89d32be0l), mk_uint32_c(0x10da7a5al), mk_uint32_c(0x67dd4accl), mk_uint32_c(0xf9b9df6fl), mk_uint32_c(0x8ebeeff9l), mk_uint32_c(0x17b7be43l), mk_uint32_c(0x60b08ed5l),
		mk_uint32_c(0xd6d6a3e8l), mk_uint32_c(0xa1d1937el), mk_uint32_c(0x38d8c2c4l), mk_uint32_c(0x4fdff252l), mk_uint32_c(0xd1bb67f1l), mk_uint32_c(0xa6bc5767l), mk_uint32_c(0x3fb506ddl), mk_uint32_c(0x48b2364bl),
		mk_uint32_c(0xd80d2bdal), mk_uint32_c(0xaf0a1b4cl), mk_uint32_c(0x36034af6l), mk_uint32_c(0x41047a60l), mk_uint32_c(0xdf60efc3l), mk_uint32_c(0xa867df55l), mk_uint32_c(0x316e8eefl), mk_uint32_c(0x4669be79l),
		mk_uint32_c(0xcb61b38cl), mk_uint32_c(0xbc66831al), mk_uint32_c(0x256fd2a0l), mk_uint32_c(0x5268e236l), mk_uint32_c(0xcc0c7795l), mk_uint32_c(0xbb0b4703l), mk_uint32_c(0x220216b9l), mk_uint32_c(0x5505262fl),
		mk_uint32_c(0xc5ba3bbel), mk_uint32_c(0xb2bd0b28l), mk_uint32_c(0x2bb45a92l), mk_uint32_c(0x5cb36a04l), mk_uint32_c(0xc2d7ffa7l), mk_uint32_c(0xb5d0cf31l), mk_uint32_c(0x2cd99e8bl), mk_uint32_c(0x5bdeae1dl),
		mk_uint32_c(0x9b64c2b0l), mk_uint32_c(0xec63f226l), mk_uint32_c(0x756aa39cl), mk_uint32_c(0x026d930al), mk_uint32_c(0x9c0906a9l), mk_uint32_c(0xeb0e363fl), mk_uint32_c(0x72076785l), mk_uint32_c(0x05005713l),
		mk_uint32_c(0x95bf4a82l), mk_uint32_c(0xe2b87a14l), mk_uint32_c(0x7bb12bael), mk_uint32_c(0x0cb61b38l), mk_uint32_c(0x92d28e9bl), mk_uint32_c(0xe5d5be0dl), mk_uint32_c(0x7cdcefb7l), mk_uint32_c(0x0bdbdf21l),
		mk_uint32_c(0x86d3d2d4l), mk_uint32_c(0xf1d4e242l), mk_uint32_c(0x68ddb3f8l), mk_uint32_c(0x1fda836el), mk_uint32_c(0x81be16cdl), mk_uint32_c(0xf6b9265bl), mk_uint32_c(0x6fb077e1l), mk_uint32_c(0x18b74777l),
		mk_uint32_c(0x88085ae6l), mk_uint32_c(0xff0f6a70l), mk_uint32_c(0x66063bcal), mk_uint32_c(0x11010b5cl), mk_uint32_c(0x8f659effl), mk_uint32_c(0xf862ae69l), mk_uint32_c(0x616bffd3l), mk_uint32_c(0x166ccf45l),
		mk_uint32_c(0xa00ae278l), mk_uint32_c(0xd70dd2eel), mk_uint32_c(0x4e048354l), mk_uint32_c(0x3903b3c2l), mk_uint32_c(0xa7672661l), mk_uint32_c(0xd06016f7l), mk_uint32_c(0x4969474dl), mk_uint32_c(0x3e6e77dbl),
		mk_uint32_c(0xaed16a4al), mk_uint32_c(0xd9d65adcl), mk_uint32_c(0x40df0b66l), mk_uint32_c(0x37d83bf0l), mk_uint32_c(0xa9bcae53l), mk_uint32_c(0xdebb9ec5l), mk_uint32_c(0x47b2cf7fl), mk_uint32_c(0x30b5ffe9l),
		mk_uint32_c(0xbdbdf21cl), mk_uint32_c(0xcabac28al), mk_uint32_c(0x53b39330l), mk_uint32_c(0x24b4a3a6l), mk_uint32_c(0xbad03605l), mk_uint32_c(0xcdd70693l), mk_uint32_c(0x54de5729l), mk_uint32_c(0x23d967bfl),
		mk_uint32_c(0xb3667a2el), mk_uint32_c(0xc4614ab8l), mk_uint32_c(0x5d681b02l), mk_uint32_c(0x2a6f2b94l), mk_uint32_c(0xb40bbe37l), mk_uint32_c(0xc30c8ea1l), mk_uint32_c(0x5a05df1bl), mk_uint32_c(0x2d02ef8dl),
	};

	*out = s_crc32_table[idx];
}

static mk_inline void mk_hash_base_hash_crc32_detail_table(unsigned char idx, struct mk_uint32_s* out)
{
#if mk_hash_base_hash_crc32_table == mk_hash_base_hash_crc32_table_small
	mk_hash_base_hash_crc32_detail_table_small(idx, out);
#else
	mk_hash_base_hash_crc32_detail_table_fast(idx, out);
#endif
}


#undef mk_hash_base_hash_crc32_table_small
#undef mk_hash_base_hash_crc32_table_fast


mk_jumbo void mk_hash_base_hash_crc32_init(struct mk_hash_base_hash_crc32_s* self)
{
	static struct mk_uint32_s s_crc32_init = mk_uint32_c(0xffffffffl);

	mk_assert(self);

	self->m_state = s_crc32_init;
}

mk_jumbo void mk_hash_base_hash_crc32_append_blocks(struct mk_hash_base_hash_crc32_s* self, int nblocks, void const* pblocks)
{
	struct mk_uint32_s crc;
	unsigned char const* input;
	int i;
	unsigned char idx;
	struct mk_uint32_s table_element;

	mk_assert(self);
	mk_assert(pblocks || nblocks == 0);
	mk_assert(nblocks >= 0);

	crc = self->m_state;
	input = (unsigned char const*)pblocks;
	for(i = 0; i != nblocks; ++i, ++input)
	{
		idx = (mk_uint32_to_int(&crc) & 0xff) ^ (*input);
		mk_hash_base_hash_crc32_detail_table(idx, &table_element);
		mk_uint32_shr(&crc, &crc, 8);
		mk_uint32_xor(&crc, &crc, &table_element);
	}
	self->m_state = crc;
}

mk_jumbo void mk_hash_base_hash_crc32_finish(struct mk_hash_base_hash_crc32_s* self, void* block, int idx, void* digest)
{
	struct mk_uint32_s crc;

	mk_assert(self);
	(void)block;
	mk_assert(idx == 0);
	mk_assert(digest);

	mk_uint32_cmplmnt(&crc, &self->m_state);
	mk_uint32_to_buff_be(&crc, digest);
}
