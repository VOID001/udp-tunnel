/*************************************************************************
    > File Name: test_log.c
    > Author: VOID_133
    > ################### 
    > Mail: ################### 
    > Created Time: Wed 16 Aug 2017 01:56:49 PM CST
 ************************************************************************/
#include <stdio.h>
#include "log.h"

void test_logging() {
    init_logger("stderr", INFO);
    log_infof("logger print info.");
    log_errorf("logger print error.");
    log_warnf("logger print warning.");
    log_debugf("logger print debug.");

    init_logger("/tmp/logfile", DEBUG);
    log_infof("logger print info.");
    log_errorf("logger print error.");
    log_warnf("logger print warning.");
    log_debugf("logger print debug.");

    return ;
}
