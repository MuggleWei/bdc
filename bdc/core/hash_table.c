#include "hash_table.h"
#include "muggle/c/muggle_c.h"
#include "bdc/core/external/murmurhash.h"

#define BDC_HASH_TABLE_SEED 0xB0F57EE3

static bdc_hash_table_node_t *
bdc_hash_table_find_node(bdc_hash_table_t *ht, uint32_t hash_key, const char *k)
{
	uint32_t bucket_idx = hash_key % ht->cap;
	bdc_hash_table_node_t *node = ht->buckets[bucket_idx];
	while (node != NULL) {
		if (strcmp(node->k, k) == 0) {
			return node;
		}
		node = node->next;
	}

	return NULL;
}

bdc_hash_table_t *bdc_hash_table_create(uint32_t cap)
{
	bdc_hash_table_t *ht = NULL;

	MUGGLE_ASSERT_MSG(cap >= 7, "too small capacity: %u", cap);
	if (cap < 7) {
		LOG_ERROR("too small capacity: %u", cap);
		return NULL;
	}

	ht = (bdc_hash_table_t *)malloc(sizeof(bdc_hash_table_t));
	if (ht == NULL) {
		LOG_ERROR("failed allocate memory space for hash table");
		goto hash_table_create_exit;
	}
	memset(ht, 0, sizeof(*ht));

	ht->cap = cap;
	ht->buckets =
		(bdc_hash_table_node_t **)malloc(sizeof(bdc_hash_table_node_t *) * cap);
	if (ht->buckets == NULL) {
		free(ht);
		ht = NULL;
		LOG_ERROR("failed allocate memroy space for hash table buckets");
		goto hash_table_create_exit;
	}
	memset(ht->buckets, 0, sizeof(bdc_hash_table_node_t *) * cap);

hash_table_create_exit:
	return ht;
}

void bdc_hash_table_destroy(bdc_hash_table_t *ht)
{
	if (ht == NULL) {
		return;
	}

	if (ht->buckets) {
		for (uint32_t i = 0; i < ht->cap; ++i) {
			bdc_hash_table_node_t *node = ht->buckets[i];
			while (node) {
				bdc_hash_table_node_t *next = node->next;
				free(node);
				node = next;
			}
		}

		free(ht->buckets);
		ht->buckets = NULL;
	}
	ht->cap = 0;
}

bdc_hash_table_node_t *bdc_hash_table_add(bdc_hash_table_t *ht, const char *k, const char *v)
{
	uint32_t hash_key = 0;
	MurmurHash3_x86_32(k, strlen(k), BDC_HASH_TABLE_SEED, &hash_key);

	bdc_hash_table_node_t *node = bdc_hash_table_find_node(ht, hash_key, k);
	if (node != NULL) {
		return NULL;
	}

	node = (bdc_hash_table_node_t *)malloc(sizeof(bdc_hash_table_node_t));
	if (node == NULL) {
		LOG_ERROR("failed allocate memory space for new hash table node");
		return NULL;
	}
	memset(node, 0, sizeof(*node));

	uint32_t bucket_idx = hash_key % ht->cap;
	bdc_hash_table_node_t *next_node = ht->buckets[bucket_idx];
	if (next_node) {
		node->next = next_node;
		next_node->prev = node;
	}
	ht->buckets[bucket_idx] = node;

	node->bucket_idx = bucket_idx;
	node->k = k;
	node->v = v;

	return node;
}

void bdc_hash_table_del(bdc_hash_table_t *ht, const char *k)
{
	bdc_hash_table_node_t *node = bdc_hash_table_find(ht, k);
	if (node) {
		bdc_hash_table_del_node(ht, node);
	}
}

void bdc_hash_table_del_node(bdc_hash_table_t *ht, bdc_hash_table_node_t *node)
{
	if (node->prev) {
		node->prev->next = node->next;
	}
	if (node->next) {
		node->next->prev = node->prev;
	}

	if (ht->buckets[node->bucket_idx] == node) {
		ht->buckets[node->bucket_idx] = node->next;
	}

	free(node);
}

bdc_hash_table_node_t *bdc_hash_table_find(bdc_hash_table_t *ht, const char *k)
{
	uint32_t hash_key = 0;
	MurmurHash3_x86_32(k, strlen(k), BDC_HASH_TABLE_SEED, &hash_key);
	return bdc_hash_table_find_node(ht, hash_key, k);
}

void bdc_hash_table_iter_begin(bdc_hash_table_t *ht, bdc_hash_table_iter_t *it)
{
	memset(it, 0, sizeof(*it));
	it->ht = ht;

	uint32_t bucket_idx = 0;
	while (bucket_idx < ht->cap) {
		if (ht->buckets[bucket_idx]) {
			it->node = ht->buckets[bucket_idx];
			return;
		}
		++bucket_idx;
	}
}

bool bdc_hash_table_iter_is_end(bdc_hash_table_iter_t *it)
{
	return it->node == NULL;
}

void bdc_hash_table_iter_next(bdc_hash_table_iter_t *it)
{
	if (it->node == NULL) {
		return;
	}

	if (it->node->next) {
		it->node = it->node->next;
		return;
	}

	++it->node->bucket_idx;
	while (it->node->bucket_idx < it->ht->cap) {
		if (it->ht->buckets[it->node->bucket_idx]) {
			it->node = it->ht->buckets[it->node->bucket_idx];
			break;
		} else {
			++it->node->bucket_idx;
		}
	}

	if (it->node->bucket_idx >= it->ht->cap) {
		it->node = NULL;
	}
}
