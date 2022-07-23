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
	static struct mk_uint32_s const s_crc32_constant = mk_uint32_c(0xedb88320ul);

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
	static struct mk_uint32_s const s_crc32_table[256] =
	{
		mk_uint32_c(0x00000000ul), mk_uint32_c(0x77073096ul), mk_uint32_c(0xee0e612cul), mk_uint32_c(0x990951baul), mk_uint32_c(0x076dc419ul), mk_uint32_c(0x706af48ful), mk_uint32_c(0xe963a535ul), mk_uint32_c(0x9e6495a3ul),
		mk_uint32_c(0x0edb8832ul), mk_uint32_c(0x79dcb8a4ul), mk_uint32_c(0xe0d5e91eul), mk_uint32_c(0x97d2d988ul), mk_uint32_c(0x09b64c2bul), mk_uint32_c(0x7eb17cbdul), mk_uint32_c(0xe7b82d07ul), mk_uint32_c(0x90bf1d91ul),
		mk_uint32_c(0x1db71064ul), mk_uint32_c(0x6ab020f2ul), mk_uint32_c(0xf3b97148ul), mk_uint32_c(0x84be41deul), mk_uint32_c(0x1adad47dul), mk_uint32_c(0x6ddde4ebul), mk_uint32_c(0xf4d4b551ul), mk_uint32_c(0x83d385c7ul),
		mk_uint32_c(0x136c9856ul), mk_uint32_c(0x646ba8c0ul), mk_uint32_c(0xfd62f97aul), mk_uint32_c(0x8a65c9ecul), mk_uint32_c(0x14015c4ful), mk_uint32_c(0x63066cd9ul), mk_uint32_c(0xfa0f3d63ul), mk_uint32_c(0x8d080df5ul),
		mk_uint32_c(0x3b6e20c8ul), mk_uint32_c(0x4c69105eul), mk_uint32_c(0xd56041e4ul), mk_uint32_c(0xa2677172ul), mk_uint32_c(0x3c03e4d1ul), mk_uint32_c(0x4b04d447ul), mk_uint32_c(0xd20d85fdul), mk_uint32_c(0xa50ab56bul),
		mk_uint32_c(0x35b5a8faul), mk_uint32_c(0x42b2986cul), mk_uint32_c(0xdbbbc9d6ul), mk_uint32_c(0xacbcf940ul), mk_uint32_c(0x32d86ce3ul), mk_uint32_c(0x45df5c75ul), mk_uint32_c(0xdcd60dcful), mk_uint32_c(0xabd13d59ul),
		mk_uint32_c(0x26d930acul), mk_uint32_c(0x51de003aul), mk_uint32_c(0xc8d75180ul), mk_uint32_c(0xbfd06116ul), mk_uint32_c(0x21b4f4b5ul), mk_uint32_c(0x56b3c423ul), mk_uint32_c(0xcfba9599ul), mk_uint32_c(0xb8bda50ful),
		mk_uint32_c(0x2802b89eul), mk_uint32_c(0x5f058808ul), mk_uint32_c(0xc60cd9b2ul), mk_uint32_c(0xb10be924ul), mk_uint32_c(0x2f6f7c87ul), mk_uint32_c(0x58684c11ul), mk_uint32_c(0xc1611dabul), mk_uint32_c(0xb6662d3dul),
		mk_uint32_c(0x76dc4190ul), mk_uint32_c(0x01db7106ul), mk_uint32_c(0x98d220bcul), mk_uint32_c(0xefd5102aul), mk_uint32_c(0x71b18589ul), mk_uint32_c(0x06b6b51ful), mk_uint32_c(0x9fbfe4a5ul), mk_uint32_c(0xe8b8d433ul),
		mk_uint32_c(0x7807c9a2ul), mk_uint32_c(0x0f00f934ul), mk_uint32_c(0x9609a88eul), mk_uint32_c(0xe10e9818ul), mk_uint32_c(0x7f6a0dbbul), mk_uint32_c(0x086d3d2dul), mk_uint32_c(0x91646c97ul), mk_uint32_c(0xe6635c01ul),
		mk_uint32_c(0x6b6b51f4ul), mk_uint32_c(0x1c6c6162ul), mk_uint32_c(0x856530d8ul), mk_uint32_c(0xf262004eul), mk_uint32_c(0x6c0695edul), mk_uint32_c(0x1b01a57bul), mk_uint32_c(0x8208f4c1ul), mk_uint32_c(0xf50fc457ul),
		mk_uint32_c(0x65b0d9c6ul), mk_uint32_c(0x12b7e950ul), mk_uint32_c(0x8bbeb8eaul), mk_uint32_c(0xfcb9887cul), mk_uint32_c(0x62dd1ddful), mk_uint32_c(0x15da2d49ul), mk_uint32_c(0x8cd37cf3ul), mk_uint32_c(0xfbd44c65ul),
		mk_uint32_c(0x4db26158ul), mk_uint32_c(0x3ab551ceul), mk_uint32_c(0xa3bc0074ul), mk_uint32_c(0xd4bb30e2ul), mk_uint32_c(0x4adfa541ul), mk_uint32_c(0x3dd895d7ul), mk_uint32_c(0xa4d1c46dul), mk_uint32_c(0xd3d6f4fbul),
		mk_uint32_c(0x4369e96aul), mk_uint32_c(0x346ed9fcul), mk_uint32_c(0xad678846ul), mk_uint32_c(0xda60b8d0ul), mk_uint32_c(0x44042d73ul), mk_uint32_c(0x33031de5ul), mk_uint32_c(0xaa0a4c5ful), mk_uint32_c(0xdd0d7cc9ul),
		mk_uint32_c(0x5005713cul), mk_uint32_c(0x270241aaul), mk_uint32_c(0xbe0b1010ul), mk_uint32_c(0xc90c2086ul), mk_uint32_c(0x5768b525ul), mk_uint32_c(0x206f85b3ul), mk_uint32_c(0xb966d409ul), mk_uint32_c(0xce61e49ful),
		mk_uint32_c(0x5edef90eul), mk_uint32_c(0x29d9c998ul), mk_uint32_c(0xb0d09822ul), mk_uint32_c(0xc7d7a8b4ul), mk_uint32_c(0x59b33d17ul), mk_uint32_c(0x2eb40d81ul), mk_uint32_c(0xb7bd5c3bul), mk_uint32_c(0xc0ba6cadul),
		mk_uint32_c(0xedb88320ul), mk_uint32_c(0x9abfb3b6ul), mk_uint32_c(0x03b6e20cul), mk_uint32_c(0x74b1d29aul), mk_uint32_c(0xead54739ul), mk_uint32_c(0x9dd277aful), mk_uint32_c(0x04db2615ul), mk_uint32_c(0x73dc1683ul),
		mk_uint32_c(0xe3630b12ul), mk_uint32_c(0x94643b84ul), mk_uint32_c(0x0d6d6a3eul), mk_uint32_c(0x7a6a5aa8ul), mk_uint32_c(0xe40ecf0bul), mk_uint32_c(0x9309ff9dul), mk_uint32_c(0x0a00ae27ul), mk_uint32_c(0x7d079eb1ul),
		mk_uint32_c(0xf00f9344ul), mk_uint32_c(0x8708a3d2ul), mk_uint32_c(0x1e01f268ul), mk_uint32_c(0x6906c2feul), mk_uint32_c(0xf762575dul), mk_uint32_c(0x806567cbul), mk_uint32_c(0x196c3671ul), mk_uint32_c(0x6e6b06e7ul),
		mk_uint32_c(0xfed41b76ul), mk_uint32_c(0x89d32be0ul), mk_uint32_c(0x10da7a5aul), mk_uint32_c(0x67dd4accul), mk_uint32_c(0xf9b9df6ful), mk_uint32_c(0x8ebeeff9ul), mk_uint32_c(0x17b7be43ul), mk_uint32_c(0x60b08ed5ul),
		mk_uint32_c(0xd6d6a3e8ul), mk_uint32_c(0xa1d1937eul), mk_uint32_c(0x38d8c2c4ul), mk_uint32_c(0x4fdff252ul), mk_uint32_c(0xd1bb67f1ul), mk_uint32_c(0xa6bc5767ul), mk_uint32_c(0x3fb506ddul), mk_uint32_c(0x48b2364bul),
		mk_uint32_c(0xd80d2bdaul), mk_uint32_c(0xaf0a1b4cul), mk_uint32_c(0x36034af6ul), mk_uint32_c(0x41047a60ul), mk_uint32_c(0xdf60efc3ul), mk_uint32_c(0xa867df55ul), mk_uint32_c(0x316e8eeful), mk_uint32_c(0x4669be79ul),
		mk_uint32_c(0xcb61b38cul), mk_uint32_c(0xbc66831aul), mk_uint32_c(0x256fd2a0ul), mk_uint32_c(0x5268e236ul), mk_uint32_c(0xcc0c7795ul), mk_uint32_c(0xbb0b4703ul), mk_uint32_c(0x220216b9ul), mk_uint32_c(0x5505262ful),
		mk_uint32_c(0xc5ba3bbeul), mk_uint32_c(0xb2bd0b28ul), mk_uint32_c(0x2bb45a92ul), mk_uint32_c(0x5cb36a04ul), mk_uint32_c(0xc2d7ffa7ul), mk_uint32_c(0xb5d0cf31ul), mk_uint32_c(0x2cd99e8bul), mk_uint32_c(0x5bdeae1dul),
		mk_uint32_c(0x9b64c2b0ul), mk_uint32_c(0xec63f226ul), mk_uint32_c(0x756aa39cul), mk_uint32_c(0x026d930aul), mk_uint32_c(0x9c0906a9ul), mk_uint32_c(0xeb0e363ful), mk_uint32_c(0x72076785ul), mk_uint32_c(0x05005713ul),
		mk_uint32_c(0x95bf4a82ul), mk_uint32_c(0xe2b87a14ul), mk_uint32_c(0x7bb12baeul), mk_uint32_c(0x0cb61b38ul), mk_uint32_c(0x92d28e9bul), mk_uint32_c(0xe5d5be0dul), mk_uint32_c(0x7cdcefb7ul), mk_uint32_c(0x0bdbdf21ul),
		mk_uint32_c(0x86d3d2d4ul), mk_uint32_c(0xf1d4e242ul), mk_uint32_c(0x68ddb3f8ul), mk_uint32_c(0x1fda836eul), mk_uint32_c(0x81be16cdul), mk_uint32_c(0xf6b9265bul), mk_uint32_c(0x6fb077e1ul), mk_uint32_c(0x18b74777ul),
		mk_uint32_c(0x88085ae6ul), mk_uint32_c(0xff0f6a70ul), mk_uint32_c(0x66063bcaul), mk_uint32_c(0x11010b5cul), mk_uint32_c(0x8f659efful), mk_uint32_c(0xf862ae69ul), mk_uint32_c(0x616bffd3ul), mk_uint32_c(0x166ccf45ul),
		mk_uint32_c(0xa00ae278ul), mk_uint32_c(0xd70dd2eeul), mk_uint32_c(0x4e048354ul), mk_uint32_c(0x3903b3c2ul), mk_uint32_c(0xa7672661ul), mk_uint32_c(0xd06016f7ul), mk_uint32_c(0x4969474dul), mk_uint32_c(0x3e6e77dbul),
		mk_uint32_c(0xaed16a4aul), mk_uint32_c(0xd9d65adcul), mk_uint32_c(0x40df0b66ul), mk_uint32_c(0x37d83bf0ul), mk_uint32_c(0xa9bcae53ul), mk_uint32_c(0xdebb9ec5ul), mk_uint32_c(0x47b2cf7ful), mk_uint32_c(0x30b5ffe9ul),
		mk_uint32_c(0xbdbdf21cul), mk_uint32_c(0xcabac28aul), mk_uint32_c(0x53b39330ul), mk_uint32_c(0x24b4a3a6ul), mk_uint32_c(0xbad03605ul), mk_uint32_c(0xcdd70693ul), mk_uint32_c(0x54de5729ul), mk_uint32_c(0x23d967bful),
		mk_uint32_c(0xb3667a2eul), mk_uint32_c(0xc4614ab8ul), mk_uint32_c(0x5d681b02ul), mk_uint32_c(0x2a6f2b94ul), mk_uint32_c(0xb40bbe37ul), mk_uint32_c(0xc30c8ea1ul), mk_uint32_c(0x5a05df1bul), mk_uint32_c(0x2d02ef8dul),
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
	static struct mk_uint32_s s_crc32_init = mk_uint32_c(0xfffffffful);

	mk_assert(self);

	self->m_state = s_crc32_init;
}

mk_jumbo void mk_hash_base_hash_crc32_append_blocks(struct mk_hash_base_hash_crc32_s* self, void const* pblocks, int nblocks)
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
