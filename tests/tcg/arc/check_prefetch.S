#*****************************************************************************
# prefetch
#-----------------------------------------------------------------------------
#
# This test verifies that prefetch works as expected
#

#define ARCTEST_ARC32
#include "test_macros.h"

ARCTEST_BEGIN

	mov	r13, @tdat
	TEST_CASE(2, r0, 0x00000004, prefetch [r13]` ld r0,[r13])
	TEST_CASE(3, r0, 0x40000000, prefetch.aw [r13,4]` ld r0,[r13])
	TEST_CASE(4, r0, 0x40400000, prefetch.ab [r13,4]` ld r0,[r13])

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
