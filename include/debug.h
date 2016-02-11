#ifndef DEBUG_H
#define DEBUG_H

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define BLU   "\x1B[34m"
#define RESET "\x1B[0m"

/* #define msg(COLOR, function) printf(COLOR "Testing %s\n" RESET, function); */
#define pss(function) printf(GRN "[PASS] " RESET "Testing %s\n", function);
#define err(function) printf(RED "[FAIL] " RESET "Testing %s\n", function);
#define inf(info) printf(BLU "[INFO] " RESET "%s\n", info);

#endif
