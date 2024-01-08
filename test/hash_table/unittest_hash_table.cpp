#include "bdc/core/core.h"
#include "unity.h"
#include <set>
#include <string>

void setUp()
{
}

void tearDown()
{
}

const char *quote_files[] = {
	"/data/history_quotes/ctp/csv/2023/202311/20231101.zip",
	"/data/history_quotes/ctp/csv/2023/202311/20231102.zip",
	"/data/history_quotes/ctp/csv/2023/202311/20231103.zip",
	"/data/history_quotes/ctp/csv/2023/202311/20231106.zip",
	"/data/history_quotes/ctp/csv/2023/202311/20231107.zip",
	"/data/history_quotes/ctp/csv/2023/202311/20231108.zip",
	"/data/history_quotes/ctp/csv/2023/202311/20231109.zip",
	"/data/history_quotes/ctp/csv/2023/202311/20231110.zip",
	"/data/history_quotes/ctp/csv/2023/202311/20231113.zip",
	"/data/history_quotes/ctp/csv/2023/202311/20231114.zip",
	"/data/history_quotes/ctp/csv/2023/202311/20231115.zip",
	"/data/history_quotes/ctp/csv/2023/202311/20231116.zip",
	"/data/history_quotes/ctp/csv/2023/202311/20231117.zip",
	"/data/history_quotes/ctp/csv/2023/202311/20231120.zip",
	"/data/history_quotes/ctp/csv/2023/202311/20231121.zip",
	"/data/history_quotes/ctp/csv/2023/202311/20231122.zip",
	"/data/history_quotes/ctp/csv/2023/202311/20231123.zip",
	"/data/history_quotes/ctp/csv/2023/202311/20231124.zip",
	"/data/history_quotes/ctp/csv/2023/202311/20231127.zip",
	"/data/history_quotes/ctp/csv/2023/202311/20231128.zip",
	"/data/history_quotes/ctp/csv/2023/202311/20231129.zip",
	"/data/history_quotes/ctp/csv/2023/202311/20231130.zip",
	"/data/history_quotes/ctp/csv/2023/202312/20231201.zip",
	"/data/history_quotes/ctp/csv/2023/202312/20231204.zip",
	"/data/history_quotes/ctp/csv/2023/202312/20231205.zip",
	"/data/history_quotes/ctp/csv/2023/202312/20231206.zip",
	"/data/history_quotes/ctp/csv/2023/202312/20231207.zip",
	"/data/history_quotes/ctp/csv/2023/202312/20231208.zip",
	"/data/history_quotes/ctp/csv/2023/202312/20231211.zip",
	"/data/history_quotes/ctp/csv/2023/202312/20231212.zip",
	"/data/history_quotes/ctp/csv/2023/202312/20231213.zip",
	"/data/history_quotes/ctp/csv/2023/202312/20231214.zip",
	"/data/history_quotes/ctp/csv/2023/202312/20231215.zip",
	"/data/history_quotes/ctp/csv/2023/202312/20231218.zip",
	"/data/history_quotes/ctp/csv/2023/202312/20231219.zip",
	"/data/history_quotes/ctp/csv/2023/202312/20231220.zip",
	"/data/history_quotes/ctp/csv/2023/202312/20231221.zip",
	"/data/history_quotes/ctp/csv/2023/202312/20231222.zip",
	"/data/history_quotes/ctp/csv/2023/202312/20231225.zip",
	"/data/history_quotes/ctp/csv/2023/202312/20231226.zip",
	"/data/history_quotes/ctp/csv/2023/202312/20231227.zip",
	"/data/history_quotes/ctp/csv/2023/202312/20231228.zip",
	"/data/history_quotes/ctp/csv/2023/202312/20231229.zip",
	"/data/history_quotes/ctp/csv/2024/202401/20240102.zip",
	"/data/history_quotes/ctp/csv/2024/202401/20240103.zip",
	"/data/history_quotes/ctp/csv/2024/202401/20240104.zip",
	"/data/history_quotes/ctp/csv/2024/202401/20240105.zip"
};

void test_hash_table_case01()
{
	bdc_hash_table_t *ht = bdc_hash_table_create(BDC_HASH_TABLE_SIZE_10007);
	TEST_ASSERT_NOT_NULL(ht);

	for (size_t i = 0; i < sizeof(quote_files) / sizeof(quote_files[0]); i++) {
		const char *filepath = quote_files[i];
		bdc_hash_table_node_t *node =
			bdc_hash_table_add(ht, filepath, filepath);
		TEST_ASSERT_NOT_NULL(node);
	}

	for (size_t i = 0; i < sizeof(quote_files) / sizeof(quote_files[0]); i++) {
		const char *filepath = quote_files[i];
		bdc_hash_table_node_t *node = bdc_hash_table_find(ht, filepath);
		TEST_ASSERT_NOT_NULL(node);
		TEST_ASSERT_EQUAL_STRING(node->k, filepath);
		TEST_ASSERT_EQUAL_STRING(node->v, filepath);
	}

	bdc_hash_table_destroy(ht);
}

void test_hash_table_case02()
{
	bdc_hash_table_t *ht = bdc_hash_table_create(BDC_HASH_TABLE_SIZE_10007);
	TEST_ASSERT_NOT_NULL(ht);

	for (size_t i = 0; i < sizeof(quote_files) / sizeof(quote_files[0]); i++) {
		const char *filepath = quote_files[i];
		bdc_hash_table_node_t *node =
			bdc_hash_table_add(ht, filepath, filepath);
		TEST_ASSERT_NOT_NULL(node);
	}

	std::set<std::string> file_set;
	bdc_hash_table_iter_t it;
	bdc_hash_table_iter_begin(ht, &it);
	for (; !bdc_hash_table_iter_is_end(&it); bdc_hash_table_iter_next(&it)) {
		file_set.insert(it.node->k);
	}

	TEST_ASSERT_EQUAL(file_set.size(),
					  sizeof(quote_files) / sizeof(quote_files[0]));
	for (size_t i = 0; i < sizeof(quote_files) / sizeof(quote_files[0]); i++) {
		const char *filepath = quote_files[i];
		TEST_ASSERT_NOT_EQUAL(file_set.find(filepath), file_set.end());
	}

	bdc_hash_table_destroy(ht);
}

int main()
{
	UNITY_BEGIN();

	RUN_TEST(test_hash_table_case01);
	RUN_TEST(test_hash_table_case02);

	return UNITY_END();
}
