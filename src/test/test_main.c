/*************************************************************************
    > File Name: test_main.c
    > Author: VOID_133
    > ################### 
    > Mail: ################### 
    > Created Time: Wed 16 Aug 2017 02:03:37 PM CST
 ************************************************************************/
#include <stdio.h>
#include "test.h"
#include "log.h"

unsigned test_ret_temp = 1;

#define ASSERTION 0
#define FAILURE 1
#define ERROR 2
unsigned test_res_map[3] = {0, 0, 0};

int main() {
    printf("\n\033[1;38;5;4mRunning tests\n");
    init_logger("stderr", DEBUG);

    void (*pf[])() = {
        &test_example,
        &test_tun_alloc,
        &test_read_ip_header,
        &test_buf_read,
    };
    
    // Run tests
    freopen("/tmp/test.log", "w", stderr);
    run_test(pf, sizeof(pf));
    freopen( "/dev/tty", "a", stderr);
    
    // Make conclusions
    printf("\n\n");
    if (test_res_map[FAILURE] == 0 && test_res_map[ERROR] == 0) {
        printf("\033[1;38;5;82mAll tests passed.");
    } else {
        printf("\033[1;38;5;9m%d Failures, %d Errors.", test_res_map[FAILURE], test_res_map[ERROR]);
    }
    printf(" (%lu Tests, %d Assertions)\n\n", sizeof(pf) / sizeof(void(*)()), test_res_map[ASSERTION]);
    
    // Print logs
    FILE *fp;
    if((fp = fopen("/tmp/test.log", "r"))) {
        int c;
        while((c = fgetc(fp)) != EOF)
            fprintf(stderr, "%c", c);
        fclose(fp);
    }
    
    // Claim conclusion again for convenience. :)
    if (test_res_map[FAILURE] == 0 && test_res_map[ERROR] == 0) {
        printf("\033[1;38;5;82mAll tests passed.");
    } else {
        printf("\033[1;38;5;9m%d Failures, %d Errors.", test_res_map[FAILURE], test_res_map[ERROR]);
    }
    printf(" (%lu Tests, %d Assertions)\n\n", sizeof(pf) / sizeof(void(*)()), test_res_map[ASSERTION]);
    
    if (test_res_map[FAILURE] == 0 && test_res_map[ERROR] == 0)
        return 0;
    else
        return -1;
}

void run_test(void (*pf[])(), size_t size) {
    unsigned i;
    for(i = 0; i < size / sizeof(void(*)()); ++i) {
        log_infof("Running test #%d...\n", i);
        pf[i]();
        log_infof("Run test #%d done.\n", i);
        if (test_ret_temp)
            print_process(pass);
        test_ret_temp = 1;
    }

}

void assert_true(int expr) {
    test_res_map[ASSERTION]++;
    if (!expr) {
        // TODO: This __func__ is meaningless.
        // We shall at least show the function name of the caller
        log_errorf("Assert Failure.");
        print_process(failure);
    }
}

void print_process(run_state state) {
    switch(state) {
        case pass:
            printf("\033[1;38;5;4m.");
            break;
        case failure:
            test_ret_temp = 0;
            test_res_map[FAILURE]++;
            printf("\033[1;38;5;9mF");
            break;
        case error:
            test_ret_temp = 0;
            test_res_map[ERROR]++;
            printf("\033[1;38;5;9mE");
            break;
    }
}
