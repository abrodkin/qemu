#*****************************************************************************
# ldst.S
#-----------------------------------------------------------------------------
#
# This test verifies that ld, ldb, ldw work as expected.
#

#define ARCTEST_ARC32
#include "test_macros.h"

ARCTEST_BEGIN

	TEST_CASE(2, r0, 0x40000000, ld r1,[@tdat]` ld r0,[r1,@tdat])
	TEST_CASE(3, r0, 0xbeef, mov r1, 16` ldw r0,[r1, @tdat])
	TEST_CASE(4, r0, 0xbe, mov r1, 20` ldb r0,[r1, @tdat])

ARCTEST_END
#  TEST_DATA

tdat:
.word 0x00000004
.word 0x40000000
.word 0x40400000
.word 0xc0800000
.word 0xdeadbeef
.word 0xcafebabe
.word 0xabad1dea
.word 0x1337d00d
