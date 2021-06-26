#include <stdlib.h>
#include <stdint.h>
#include <libft.h>
#define MMURMURHASH 0x5bd1e995
#define RMURMURHASH 24

static int	hash2(uint32_t k, uint32_t *h, const unsigned char **data, int len)
{
	static const uint32_t	m = MMURMURHASH;
	static const int		r = RMURMURHASH;

	k *= m;
	k ^= k >> r;
	k *= m;
	*h *= m;
	*h ^= k;
	*data += 4;
	len -= 4;
	return (len);
}

static uint32_t	murmurhash2(const void *key, int len, unsigned int seed )
{
	static const uint32_t	m = MMURMURHASH;
	unsigned int			h;
	const unsigned char		*data;
	unsigned int			k;

	h = seed ^ len;
	data = (const unsigned char *)key;
	k = *(unsigned int *)data;
	while (len >= 4)
		len = hash2(k, &h, &data, len);
	if (len == 3 || len == 2 || len == 1)
	{
		if (len == 3)
			h ^= data[2] << 16;
		if (len > 1)
			h ^= data[1] << 8;
		h ^= data[0];
	}
	h *= m;
	h ^= h >> 13;
	h *= m;
	h ^= h >> 15;
	return (h);
}

uint32_t	ft_random(uint32_t seed)
{
	static uint8_t	key[256];
	static uint32_t	j = 0;
	int32_t			ret;
	uint8_t			idx;

	if (seed == 0)
		seed = 99;
	idx = 0;
	while (idx < 0xFF)
	{
		if (j > idx)
			key[idx] = (uint8_t)(j - idx);
		else
			key[idx] = (uint8_t)(idx - j);
		idx++;
	}
	ret = murmurhash2 (key, j, seed);
	if (j < UINT32_MAX)
		j++;
	else
		j = 0;
	return (ret);
}
