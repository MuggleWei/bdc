#ifndef BDC_CORE_HASH_TABLE_H_
#define BDC_CORE_HASH_TABLE_H_

#include "bdc/core/macro.h"
#include <stdint.h>
#include <stdbool.h>

BDC_EXTERN_C_BEGIN

typedef struct bdc_hash_table_node {
	struct bdc_hash_table_node *prev; //!< previous node
	struct bdc_hash_table_node *next; //!< next node
	uint32_t bucket_idx; //!< bucket index
	const char *k; //!< file name - key of hash node
	const char *v; //!< hash value - value of hash node
} bdc_hash_table_node_t;

typedef struct bdc_hash_table {
	uint32_t cap; //!< capacity of bucket in hash table
	bdc_hash_table_node_t **buckets; //!< hash table buckets
} bdc_hash_table_t;

typedef struct bdc_hash_table_iter {
	bdc_hash_table_t *ht; //!< hash table pointer
	bdc_hash_table_node_t *node; //!< current node
} bdc_hash_table_iter_t;

#define BDC_HASH_TABLE_SIZE_10007 10007

/**
 * @brief create hash table
 *
 * @param cap  capacity of hash table
 *
 * @return hash table pointer
 */
BDC_EXPORT
bdc_hash_table_t *bdc_hash_table_create(uint32_t cap);

/**
 * @brief destroy hash table
 *
 * @param ht  hash table pointer
 */
BDC_EXPORT
void bdc_hash_table_destroy(bdc_hash_table_t *ht);

/**
 * @brief add kv into hash table
 *
 * @param ht  hash table pointer
 * @param k   key
 * @param v   value
 *
 * @return hash table node pointer
 */
BDC_EXPORT
bdc_hash_table_node_t *bdc_hash_table_add(bdc_hash_table_t *ht, const char *k,
										  const char *v);

/**
 * @brief delete from hash table
 *
 * @param ht  hash table pointer
 * @param k   key
 */
BDC_EXPORT
void bdc_hash_table_del(bdc_hash_table_t *ht, const char *k);

/**
 * @brief delete from hash table
 *
 * @param ht    hash table pointer
 * @param node  node
 */
BDC_EXPORT
void bdc_hash_table_del_node(bdc_hash_table_t *ht, bdc_hash_table_node_t *node);

/**
 * @brief find node from hash table
 *
 * @param ht  hash table pointer
 * @param k   key
 *
 * @return
 *   - on success, return node
 *   - on failed, return NULL
 */
BDC_EXPORT
bdc_hash_table_node_t *bdc_hash_table_find(bdc_hash_table_t *ht, const char *k);

/**
 * @brief get iterator begin
 *
 * @param ht  hash table pointer
 * @param it  begin iterator
 */
BDC_EXPORT
void bdc_hash_table_iter_begin(bdc_hash_table_t *ht, bdc_hash_table_iter_t *it);

/**
 * @brief detect iterator is reach end
 *
 * @param it  hash table iterator
 */
BDC_EXPORT
bool bdc_hash_table_iter_is_end(bdc_hash_table_iter_t *it);

/**
 * @brief move iterator to next
 *
 * @param it  hash table iterator
 *
 * @return next iterator
 */
BDC_EXPORT
void bdc_hash_table_iter_next(bdc_hash_table_iter_t *it);

BDC_EXTERN_C_END

#endif // !BDC_CORE_HASH_TABLE_H_
