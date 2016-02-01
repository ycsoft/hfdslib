#ifndef CTEST_H
#define CTEST_H

#ifdef __cplusplus
extern "C"
{
#endif

void test_init(void);
void test_push_back(void);

void run_test(void);

void test_clock(void);
void test_list(void);
void test_cplus_list(void);
void test_std_list(void);
void test_hash(void);
void test_boost_map(void);
void test_rb_tree(void);
void test_rb_hash(void);
void test_hf_vector(void);
void test_cplus_vector(void);
void test_std_vector(void);

void test_malloc(void);
void test_realloc(void);

void base_rb_hash(void);


#ifdef __cplusplus
}
#endif

#endif // CTEST_H
