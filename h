==129156== Memcheck, a memory error detector
==129156== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==129156== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==129156== Command: ./bin/*
==129156== Parent PID: 129155
==129156== 
==129156== 
==129156== HEAP SUMMARY:
==129156==     in use at exit: 1,118 bytes in 51 blocks
==129156==   total heap usage: 86 allocs, 35 frees, 527,412 bytes allocated
==129156== 
==129156== 8 bytes in 1 blocks are definitely lost in loss record 1 of 9
==129156==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==129156==    by 0x1097E8: main (main.c:127)
==129156== 
==129156== 555 (8 direct, 547 indirect) bytes in 1 blocks are definitely lost in loss record 8 of 9
==129156==    at 0x484DA83: calloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==129156==    by 0x109701: main (main.c:99)
==129156== 
==129156== 555 (8 direct, 547 indirect) bytes in 1 blocks are definitely lost in loss record 9 of 9
==129156==    at 0x484DA83: calloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==129156==    by 0x109725: main (main.c:102)
==129156== 
==129156== LEAK SUMMARY:
==129156==    definitely lost: 24 bytes in 3 blocks
==129156==    indirectly lost: 1,094 bytes in 48 blocks
==129156==      possibly lost: 0 bytes in 0 blocks
==129156==    still reachable: 0 bytes in 0 blocks
==129156==         suppressed: 0 bytes in 0 blocks
==129156== 
==129156== For lists of detected and suppressed errors, rerun with: -s
==129156== ERROR SUMMARY: 3 errors from 3 contexts (suppressed: 0 from 0)
