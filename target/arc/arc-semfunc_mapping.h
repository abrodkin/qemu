
SEMANTIC_FUNCTION(ADD, 3, a, b, c)
SEMANTIC_FUNCTION(ADD1, 3, a, b, c)
SEMANTIC_FUNCTION(ADD2, 3, a, b, c)
SEMANTIC_FUNCTION(ADD3, 3, a, b, c)
SEMANTIC_FUNCTION(SUB, 3, a, b, c)
SEMANTIC_FUNCTION(MUL, 3, a, b, c)
SEMANTIC_FUNCTION(DIV, 3, a, b, c)
SEMANTIC_FUNCTION(AND, 3, a, b, c)
SEMANTIC_FUNCTION(OR, 3, a, b, c)
SEMANTIC_FUNCTION(XOR, 3, a, b, c)
SEMANTIC_FUNCTION(MOV, 2, a, b)
SEMANTIC_FUNCTION(ADC, 3, a, b, c)
SEMANTIC_FUNCTION(ASL, 3, a, b, c)
SEMANTIC_FUNCTION(ASR, 3, a, b, c)
SEMANTIC_FUNCTION(ASR16, 2, a, b)
SEMANTIC_FUNCTION(ASR8, 2, a, b)
SEMANTIC_FUNCTION(MPY, 3, a, b, c)
SEMANTIC_FUNCTION(ABS, 2, src, dest)
SEMANTIC_FUNCTION(B, 1, rd)
SEMANTIC_FUNCTION(B_S, 1, rd)
SEMANTIC_FUNCTION(J, 1, src)
SEMANTIC_FUNCTION(LD, 3, src1, src2, dest)


MAPPING(add, ADD)
MAPPING(add_s, ADD)
MAPPING(add1, ADD1)
MAPPING(add1_s, ADD1)
MAPPING(add2, ADD2)
MAPPING(add2_s, ADD2)
MAPPING(add3, ADD3)
MAPPING(add3_s, ADD3)
MAPPING(sub, SUB)
MAPPING(sub_s, SUB)
MAPPING(div, DIV)
MAPPING(and, AND)
MAPPING(and_s, AND)
MAPPING(or, OR)
MAPPING(or_s, OR)
MAPPING(xor, XOR)
MAPPING(xor_s, XOR)
MAPPING(mov, MOV)
MAPPING(mov_s, MOV)
MAPPING(adc, ADC)
MAPPING(asl, ASL)
MAPPING(asl_s, ASL)
MAPPING(asr, ASR)
MAPPING(asr_s, ASR)
MAPPING(asr16, ASR16)
MAPPING(asr8, ASR8)
MAPPING(mpy, MPY)
MAPPING(mpy_s, MPY)
MAPPING(abs, ABS)
MAPPING(abs_s, ABS)
MAPPING(b, B)
MAPPING(b_s, B_S)
MAPPING(j, J)
MAPPING(j_s, J)
MAPPING(ld, LD)
MAPPING(ld_s, LD)
MAPPING(ldb_s, LD)
MAPPING(ldh_s, LD)
MAPPING(ldw_s, LD)
MAPPING(ldd, LD)
MAPPING(ldi, LD)
MAPPING(ldi_s, LD)
MAPPING(ldm, LD)
MAPPING(st, ST)
