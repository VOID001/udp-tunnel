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
unsigned count[3] = {0, 0, 0}; // assertions, failures, errors

int main() {
    printf("\n\033[1;38;5;4mRunning tests\n");
    init_logger("stderr", DEBUG);

    void (*pf[])() = {
        &test_example,
        &test_tun_alloc,
        &test_read_ip_header
    };
    
    // Run tests
    freopen("/tmp/test.log", "w", stderr);
    run_test(pf, sizeof(pf));
    freopen( "/dev/tty", "a", stderr);
    
    // Make conclusions
    printf("\n\n");
    if (count[1] == 0 && count[2] == 0) {
        printf("\033[1;38;5;82mAll tests passed.");
    } else {
        printf("\033[1;38;5;9m%d Failures, %d Errors.", count[1], count[2]);
    }
    printf(" (%lu Tests, %d Assertions)\n\n", sizeof(pf) / sizeof(void(*)()), count[0]);
    
    // Print logs
    FILE *fp;
    if((fp = fopen("/tmp/test.log", "r"))) {
        int c;
        while((c = fgetc(fp)) != EOF)
            fprintf(stderr, "%c", c);
        fclose(fp);
    }
    
    // Claim conclusion again for convenience. :)
    if (count[1] == 0 && count[2] == 0) {
        printf("\033[1;38;5;82mAll tests passed.");
    } else {
        printf("\033[1;38;5;9m%d Failures, %d Errors.", count[1], count[2]);
    }
    printf(" (%lu Tests, %d Assertions)\n\n", sizeof(pf) / sizeof(void(*)()), count[0]);
    
    if (count[1] == 0 && count[2] == 0)
        return 0;
    else
        return -1;
}

void run_test(void (*pf[])(), size_t size) {
    unsigned i;
    for(i = 0; i < size / sizeof(void(*)()); ++i) {
        log_infof(__func__, "Running test #%d...\n", i);
        pf[i]();
        log_infof(__func__, "Run test #%d done.\n", i);
        if (test_ret_temp)
            printProcess(pass);
        test_ret_temp = 1;
    }
}

void assertTrue(int expr) {
    count[0]++;
    if (!expr) {
        // TODO: This __func__ is meaningless.
        // We shall at least show the function name of the caller
        log_errorf(__func__, "Assert Failure.");
        printProcess(failure);
    }
}

void printProcess(run_state state) {
    switch(state) {
        case pass:
            printf("\033[1;38;5;4m.");
            break;
        case failure:
            test_ret_temp = 0;
            count[1]++;
            printf("\033[1;38;5;9mF");
            break;
        case error:
            test_ret_temp = 0;
            count[2]++;
            printf("\033[1;38;5;9mE");
            break;
    }
}
