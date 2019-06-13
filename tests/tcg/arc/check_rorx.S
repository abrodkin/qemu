#define ARCTEST_ARC32

#*****************************************************************************
# ror.S
#-----------------------------------------------------------------------------
#
# Test or instruction.
#

#include "test_macros.h"

ARCTEST_BEGIN

  #-------------------------------------------------------------
  # Logical tests
  #-------------------------------------------------------------
  TEST_RR_3OP( 2, ror , 0xdeadbeef, 0xdeadbeef, 0x00000000);
  TEST_RR_3OP( 3, ror , 0x00000001, 0x00000001, 0x00000000);
  TEST_RR_3OP( 4, ror , 0x80000000, 0x80000000, 0x00000000);
  TEST_RR_3OP( 5, ror , 0xbd5b7ddf, 0xdeadbeef, 0x0000001f);
  TEST_RR_3OP( 6, ror , 0x00000002, 0x00000001, 0x0000001f);
  TEST_RR_3OP( 7, ror , 0x00000001, 0x80000000, 0x0000001f);
  TEST_RR_2OP( 8, ror , 0x80000000, 0x00000001);
  TEST_RR_2OP( 9, ror , 0xdeadbeef, 0xbd5b7ddf);
  TEST_RR_2OP(10, ror8, 0x01000000, 0x00000001);
  
  TEST_RR_2OP(11, rol , 0xbd5b7ddf, 0xdeadbeef);
  TEST_RR_2OP(12, rol8, 0x00000001, 0x01000000);

  #-------------------------------------------------------------
  # Source/Destination tests
  #-------------------------------------------------------------
  TEST_RR_SRC1_EQ_DEST    (13, ror,  0xca000804, 0x000804ca, 0xfff80008);
  TEST_RR_2OP_SRC1_EQ_DEST(14, ror,  0x80040265, 0x000804cb);
  TEST_RR_2OP_SRC1_EQ_DEST(15, rol,  0x94001009, 0xca000804);

  #-------------------------------------------------------------
  # Flag tests
  #-------------------------------------------------------------
  TEST_2OP_CARRY   (16, ror , 0, 0x00000001, 0x02);
  TEST_2OP_CARRY   (17, ror , 1, 0x00000001, 0x01);
  TEST_2OP_ZERO    (18, ror , 0, 0x00000100, 0xbf);
  TEST_2OP_ZERO    (19, ror , 1, 0x00000000, 0xbf);
  TEST_2OP_NEGATIVE(20, ror , 0, 0x00000001, 0x02);
  TEST_2OP_NEGATIVE(21, ror , 1, 0x80000000, 0x00);
  TEST_2OP_CARRY   (22, ror , 1, 0x000000ff, 0x08);
  TEST_1OP_CARRY   (23, ror , 0, 0x00000002);
  TEST_1OP_CARRY   (24, ror , 1, 0x00000001);
  TEST_1OP_ZERO    (25, ror , 0, 0x00000100);
  TEST_1OP_ZERO    (26, ror , 1, 0x00000000);
  TEST_1OP_NEGATIVE(27, ror , 0, 0x80000000);
  TEST_1OP_NEGATIVE(28, ror , 1, 0x00000001);
  TEST_1OP_CARRY   (29, ror , 1, 0x80000001);
  #ror8 does not update carry
  TEST_1OP_CARRY   (30, ror8, 0, 0x000000ff);
  TEST_1OP_ZERO    (31, ror8, 0, 0x00001000);
  TEST_1OP_ZERO    (32, ror8, 1, 0x00000000);
  TEST_1OP_NEGATIVE(33, ror8, 0, 0x00000040);
  TEST_1OP_NEGATIVE(34, ror8, 1, 0x00000080);
  
  TEST_1OP_CARRY   (35, rol , 0, 0x40000000);
  TEST_1OP_CARRY   (36, rol , 1, 0x80000000);
  TEST_1OP_ZERO    (37, rol , 0, 0x00001000);
  TEST_1OP_ZERO    (38, rol , 1, 0x00000000);
  TEST_1OP_NEGATIVE(39, rol , 0, 0x80000000);
  TEST_1OP_NEGATIVE(40, rol , 1, 0x40000000);
  #rol8 does not update carry
  TEST_1OP_CARRY   (41, rol8, 0, 0x000000ff);
  TEST_1OP_ZERO    (42, rol8, 0, 0x00001000);
  TEST_1OP_ZERO    (43, rol8, 1, 0x00000000);
  TEST_1OP_NEGATIVE(44, rol8, 0, 0x00000040);
  TEST_1OP_NEGATIVE(45, rol8, 1, 0x00800000);

ARCTEST_END
