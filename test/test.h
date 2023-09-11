#ifndef USER_TEST_H
#define USER_TEST_H
#define NULL 0
#define MAX_ARGV_NUM 14
typedef struct final_test{
    int argc;
    char * argv[14];
} final_test_t;

static char *test[] = {
    "exec busybox touch test.txt",
    "exec busybox echo \"hello world\" > test.txt",
    "exec busybox cat test.txt",
    "exec 7za a -mmt=1 test.7z test.txt",
    "exec 7za l test.7z",
    "exec busybox rm test.txt",
    "exec busybox ls",
    "exec 7za x -mmt=1 test.7z -aoa",
    "exec busybox cat test.txt",
    "exec readelf -h wzq",
    NULL
};
#endif