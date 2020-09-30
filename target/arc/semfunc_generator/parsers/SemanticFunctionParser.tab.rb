#
# DO NOT MODIFY!!!!
# This file is automatically generated by Racc 1.4.12
# from Racc grammer file "".
#

require 'racc/parser.rb'
class SemanticFunctionParser < Racc::Parser

module_eval(<<'...end SemanticFunctionParser.y/module_eval...', 'SemanticFunctionParser.y', 66)

def parse(str)
  orig_str = str
  str = str.gsub(" ", "").gsub("\n", "").gsub("\r", "")
  @yydebug = true
  @q = []
  until str.empty?
    append = ""
    case str
      when /\A(if)/
        @q.push [:IF, $1]
      when /\A(else)/
        @q.push [:ELSE, $1]
      when /\A(while)/
        @q.push [:WHILE, $1]
      when /\A(&&|\|\||\^\^)/
        @q.push [:BINCOND, $1]
      when /\A(&|\||\^|<<|>>|-|\+|\/|\*)/
        @q.push [:BINOP, $1]
      when /\A(==|!=|<=|<|>=|>)/
        @q.push [:BINCOMP, $1]
      when /\A([\~!])/
        @q.push [:UNIOP, $1]
      when /\A(a)\]/
        @q.push [:STRING, $1]
        append = "]"
      when /\A(^[a-zA-Z][a-zA-Z0-9]*)\(/
        @q.push [:FUNC, $1]
        append = '('
      when /\A(@?[a-zA-Z_][a-zA-Z0-9_]*)/
        @q.push [:VAR, $1]
      when /\A0x([0-9a-fA-F])+/
        @q.push [:HEX_NUMBER, $&.to_i(16)]
      when /\A\d+/
        @q.push [:NUMBER, $&.to_i]
      when /\A.|\n/o
        s = $&
        @q.push [s, s]
#     # when /\A([\+\-\*\/]|<<|>>|&)/
#     #   @q.push [:BINOP, $1]
    end
    str = append + $'
  end
  @q.push [false, '$end']
#  begin
    do_parse
#  rescue
#    return SemanticFunctionAST.error("Error parsing: --#{orig_str}--")
#  end
end

 def next_token
  @q.shift
 end

 def on_error(t, val, vstack)
   raise ParseError, sprintf("\nparse error on value %s (%s)",
                             val.inspect, token_to_str(t) || '?')
 end

...end SemanticFunctionParser.y/module_eval...
##### State transition tables begin ###

racc_action_table = [
     7,     7,     8,     8,    53,    52,     2,     2,    12,    11,
    51,     9,     9,     7,     7,     8,     8,     7,    17,     8,
    10,    10,    18,     2,     9,     9,    53,    52,     9,     7,
     7,     8,     8,    10,    10,     2,     2,    10,    19,    47,
     9,     9,    29,    20,     9,    28,    62,    21,    33,    10,
    10,    34,    35,    10,    39,    47,     9,    37,    53,    52,
    33,    22,    62,    34,    35,    10,    39,    23,     9,    37,
    24,    24,    33,    53,    52,    34,    35,    10,    39,    58,
     9,    37,    47,    50,    33,    53,    52,    34,    35,    10,
    29,    67,     9,    28,    47,    59,    33,    60,    47,    34,
    35,    10,    29,    63,     9,    28,    47,    70,    33,    53,
   nil,    34,    35,    10,    39,   nil,     9,    37,   nil,   nil,
    33,   nil,   nil,    34,    35,    10,    39,   nil,     9,    37,
   nil,   nil,    33,   nil,   nil,    34,    35,    10,    29,   nil,
     9,    28,   nil,   nil,    33,   nil,   nil,    34,    35,    10,
    39,   nil,     9,    37,   nil,   nil,    33,   nil,   nil,    34,
    35,    10,    39,   nil,     9,    37,   nil,   nil,    33,   nil,
   nil,    34,    35,    10,    39,   nil,     9,    37,   nil,   nil,
    33,   nil,   nil,    34,    35,    10,    47,   -26,   -26 ]

racc_action_check = [
     0,     2,     0,     2,    36,    36,     0,     2,     2,     1,
    36,     0,     2,    16,    24,    16,    24,    51,     5,    51,
     0,     2,     7,    51,    16,    24,    44,    44,    51,    58,
    70,    58,    70,    16,    24,    58,    70,    51,     8,    49,
    58,    70,    17,     9,    17,    17,    49,    11,    17,    58,
    70,    17,    17,    17,    18,    56,    18,    18,    55,    55,
    18,    13,    56,    18,    18,    18,    19,    14,    19,    19,
    15,    25,    19,    41,    41,    19,    19,    19,    20,    41,
    20,    20,    27,    33,    20,    57,    57,    20,    20,    20,
    28,    57,    28,    28,    38,    42,    28,    45,    48,    28,
    28,    28,    29,    50,    29,    29,    54,    64,    29,    65,
   nil,    29,    29,    29,    37,   nil,    37,    37,   nil,   nil,
    37,   nil,   nil,    37,    37,    37,    39,   nil,    39,    39,
   nil,   nil,    39,   nil,   nil,    39,    39,    39,    47,   nil,
    47,    47,   nil,   nil,    47,   nil,   nil,    47,    47,    47,
    52,   nil,    52,    52,   nil,   nil,    52,   nil,   nil,    52,
    52,    52,    53,   nil,    53,    53,   nil,   nil,    53,   nil,
   nil,    53,    53,    53,    60,   nil,    60,    60,   nil,   nil,
    60,   nil,   nil,    60,    60,    60,    43,    43,    43 ]

racc_action_pointer = [
    -3,     9,    -2,   nil,   nil,     7,   nil,    10,    26,    31,
   nil,    47,   nil,    51,    57,    53,    10,    30,    42,    54,
    66,   nil,   nil,   nil,    11,    54,   nil,    76,    78,    90,
   nil,   nil,   nil,    64,   nil,   nil,    -3,   102,    88,   114,
   nil,    66,    82,   180,    19,    81,   nil,   126,    92,    33,
    83,    14,   138,   150,   100,    51,    49,    78,    26,   nil,
   162,   nil,   nil,   nil,   103,   102,   nil,   nil,   nil,   nil,
    27,   nil ]

racc_action_default = [
   -37,   -37,   -37,    -4,    -5,   -37,    -7,   -37,   -37,   -37,
   -36,   -37,    -1,   -37,   -37,    -4,    -5,   -37,   -37,   -37,
   -21,    72,    -2,    -3,   -30,   -31,   -29,    -6,   -37,   -37,
   -15,   -16,   -32,   -37,   -34,   -35,   -37,   -37,   -26,   -37,
   -16,   -37,   -37,   -17,   -18,   -20,   -28,   -37,   -12,   -37,
   -37,   -37,   -37,   -37,   -12,   -25,   -26,   -37,   -37,   -11,
   -21,   -13,   -14,   -33,    -9,   -23,   -24,   -22,   -10,   -19,
   -37,    -8 ]

racc_goto_table = [
     1,     5,    13,     5,     6,    42,     6,    27,   nil,   nil,
    43,    31,    36,    41,   nil,   nil,    14,     5,    48,    49,
     6,    15,    31,    31,   nil,     5,    16,    54,     6,    56,
    26,    55,   nil,    57,   nil,    25,   nil,    61,    46,   nil,
    16,    31,   nil,    25,   nil,    69,    65,    66,    16,   nil,
    43,    64,     5,   nil,   nil,     6,   nil,   nil,    68,     5,
   nil,   nil,     6,   nil,   nil,   nil,   nil,   nil,   nil,   nil,
    71,     5,   nil,   nil,     6 ]

racc_goto_check = [
     1,     5,     1,     5,     7,     9,     7,     6,   nil,   nil,
     6,    10,     8,     8,   nil,   nil,     2,     5,     6,     6,
     7,     3,    10,    10,   nil,     5,     4,     6,     7,     6,
     2,     8,   nil,     8,   nil,     3,   nil,     6,     2,   nil,
     4,    10,   nil,     3,   nil,     9,     8,     8,     4,   nil,
     6,     1,     5,   nil,   nil,     7,   nil,   nil,     1,     5,
   nil,   nil,     7,   nil,   nil,   nil,   nil,   nil,   nil,   nil,
     1,     5,   nil,   nil,     7 ]

racc_goto_pointer = [
   nil,     0,    14,    19,    24,     1,   -10,     4,    -6,   -15,
    -6,   nil ]

racc_goto_default = [
   nil,   nil,   nil,     3,     4,    32,    38,    30,    44,   nil,
    40,    45 ]

racc_reduce_table = [
  0, 0, :racc_error,
  2, 25, :_reduce_1,
  3, 25, :_reduce_2,
  3, 25, :_reduce_3,
  1, 25, :_reduce_4,
  1, 27, :_reduce_5,
  3, 27, :_reduce_6,
  1, 27, :_reduce_7,
  7, 28, :_reduce_8,
  5, 28, :_reduce_9,
  5, 28, :_reduce_10,
  4, 31, :_reduce_11,
  2, 30, :_reduce_12,
  3, 30, :_reduce_13,
  3, 30, :_reduce_14,
  1, 30, :_reduce_15,
  1, 30, :_reduce_16,
  1, 35, :_reduce_17,
  1, 35, :_reduce_18,
  3, 33, :_reduce_19,
  1, 33, :_reduce_20,
  0, 33, :_reduce_21,
  3, 32, :_reduce_22,
  3, 32, :_reduce_23,
  3, 32, :_reduce_24,
  2, 32, :_reduce_25,
  1, 32, :_reduce_26,
  1, 32, :_reduce_27,
  3, 26, :_reduce_28,
  2, 26, :_reduce_29,
  2, 26, :_reduce_30,
  1, 26, :_reduce_31,
  1, 34, :_reduce_32,
  3, 34, :_reduce_33,
  1, 34, :_reduce_34,
  1, 34, :_reduce_35,
  1, 29, :_reduce_36 ]

racc_reduce_n = 37

racc_shift_n = 72

racc_token_table = {
  false => 0,
  :error => 1,
  :UMINUS => 2,
  :IF => 3,
  :ELSE => 4,
  :WHILE => 5,
  :BINOP => 6,
  :BINCOMP => 7,
  :BINCOND => 8,
  "{" => 9,
  "}" => 10,
  "=" => 11,
  "(" => 12,
  ")" => 13,
  :FUNC => 14,
  :UNIOP => 15,
  "," => 16,
  ";" => 17,
  "[" => 18,
  :STRING => 19,
  "]" => 20,
  :NUMBER => 21,
  :HEX_NUMBER => 22,
  :VAR => 23 }

racc_nt_base = 24

racc_use_result_var = true

Racc_arg = [
  racc_action_table,
  racc_action_check,
  racc_action_default,
  racc_action_pointer,
  racc_goto_table,
  racc_goto_check,
  racc_goto_default,
  racc_goto_pointer,
  racc_nt_base,
  racc_reduce_table,
  racc_token_table,
  racc_shift_n,
  racc_reduce_n,
  racc_use_result_var ]

Racc_token_to_s_table = [
  "$end",
  "error",
  "UMINUS",
  "IF",
  "ELSE",
  "WHILE",
  "BINOP",
  "BINCOMP",
  "BINCOND",
  "\"{\"",
  "\"}\"",
  "\"=\"",
  "\"(\"",
  "\")\"",
  "FUNC",
  "UNIOP",
  "\",\"",
  "\";\"",
  "\"[\"",
  "STRING",
  "\"]\"",
  "NUMBER",
  "HEX_NUMBER",
  "VAR",
  "$start",
  "block",
  "stmt_list",
  "stmt",
  "block_stmt",
  "var",
  "expr",
  "func",
  "cond",
  "func_args",
  "leaf",
  "arg" ]

Racc_debug_parser = false

##### State transition tables end #####

# reduce 0 omitted

module_eval(<<'.,.,', 'SemanticFunctionParser.y', 12)
  def _reduce_1(val, _values, result)
     return SemanticFunctionAST.new({ type: :block, list: SemanticFunctionAST.nothing })
    result
  end
.,.,

module_eval(<<'.,.,', 'SemanticFunctionParser.y', 13)
  def _reduce_2(val, _values, result)
     return val[1]
    result
  end
.,.,

module_eval(<<'.,.,', 'SemanticFunctionParser.y', 14)
  def _reduce_3(val, _values, result)
     return SemanticFunctionAST.new({ type: :block, list: val[1] })
    result
  end
.,.,

module_eval(<<'.,.,', 'SemanticFunctionParser.y', 15)
  def _reduce_4(val, _values, result)
     return SemanticFunctionAST.new({ type: :block, list: SemanticFunctionAST.new({ type: :stmt_list, head: val[0], tail: SemanticFunctionAST.nothing }) })
    result
  end
.,.,

module_eval(<<'.,.,', 'SemanticFunctionParser.y', 17)
  def _reduce_5(val, _values, result)
     return val[0]
    result
  end
.,.,

module_eval(<<'.,.,', 'SemanticFunctionParser.y', 18)
  def _reduce_6(val, _values, result)
     return SemanticFunctionAST.new({ type: :assign, lhs: val[0], rhs: val[2] })
    result
  end
.,.,

module_eval(<<'.,.,', 'SemanticFunctionParser.y', 19)
  def _reduce_7(val, _values, result)
     return val[0]
    result
  end
.,.,

module_eval(<<'.,.,', 'SemanticFunctionParser.y', 21)
  def _reduce_8(val, _values, result)
     return SemanticFunctionAST.new({ type: :if, cond: val[2], then: val[4], else: val[6] })
    result
  end
.,.,

module_eval(<<'.,.,', 'SemanticFunctionParser.y', 22)
  def _reduce_9(val, _values, result)
     return SemanticFunctionAST.new({ type: :if, cond: val[2], then: val[4], else: SemanticFunctionAST.nothing })
    result
  end
.,.,

module_eval(<<'.,.,', 'SemanticFunctionParser.y', 23)
  def _reduce_10(val, _values, result)
     return SemanticFunctionAST.new({ type: :while, cond: val[2], loop: val[4] })
    result
  end
.,.,

module_eval(<<'.,.,', 'SemanticFunctionParser.y', 25)
  def _reduce_11(val, _values, result)
     return SemanticFunctionAST.new({ type: :func, name: val[0], args: val[2] })
    result
  end
.,.,

module_eval(<<'.,.,', 'SemanticFunctionParser.y', 27)
  def _reduce_12(val, _values, result)
     return SemanticFunctionAST.new({ type: :uniop, name: val[0], rhs: val[1] })
    result
  end
.,.,

module_eval(<<'.,.,', 'SemanticFunctionParser.y', 28)
  def _reduce_13(val, _values, result)
     return SemanticFunctionAST.new({ type: :binop, name: val[1], lhs: val[0], rhs: val[2] })
    result
  end
.,.,

module_eval(<<'.,.,', 'SemanticFunctionParser.y', 29)
  def _reduce_14(val, _values, result)
     return val[1]
    result
  end
.,.,

module_eval(<<'.,.,', 'SemanticFunctionParser.y', 30)
  def _reduce_15(val, _values, result)
     return val[0]
    result
  end
.,.,

module_eval(<<'.,.,', 'SemanticFunctionParser.y', 31)
  def _reduce_16(val, _values, result)
     return val[0]
    result
  end
.,.,

module_eval(<<'.,.,', 'SemanticFunctionParser.y', 33)
  def _reduce_17(val, _values, result)
    val[0]
    result
  end
.,.,

module_eval(<<'.,.,', 'SemanticFunctionParser.y', 34)
  def _reduce_18(val, _values, result)
    val[0]
    result
  end
.,.,

module_eval(<<'.,.,', 'SemanticFunctionParser.y', 37)
  def _reduce_19(val, _values, result)
     return [val[0]] + val[2]
    result
  end
.,.,

module_eval(<<'.,.,', 'SemanticFunctionParser.y', 38)
  def _reduce_20(val, _values, result)
     return [val[0]]
    result
  end
.,.,

module_eval(<<'.,.,', 'SemanticFunctionParser.y', 39)
  def _reduce_21(val, _values, result)
     return []
    result
  end
.,.,

module_eval(<<'.,.,', 'SemanticFunctionParser.y', 41)
  def _reduce_22(val, _values, result)
     return val[1]
    result
  end
.,.,

module_eval(<<'.,.,', 'SemanticFunctionParser.y', 42)
  def _reduce_23(val, _values, result)
     return SemanticFunctionAST.new({ type: :bincond, name: val[1], lhs: val[0], rhs: val[2] })
    result
  end
.,.,

module_eval(<<'.,.,', 'SemanticFunctionParser.y', 43)
  def _reduce_24(val, _values, result)
     return SemanticFunctionAST.new({ type: :bincond, name: val[1], lhs: val[0], rhs: val[2] })
    result
  end
.,.,

module_eval(<<'.,.,', 'SemanticFunctionParser.y', 44)
  def _reduce_25(val, _values, result)
     return SemanticFunctionAST.new({ type: :unicond, name: val[0], rhs: val[1] })
    result
  end
.,.,

module_eval(<<'.,.,', 'SemanticFunctionParser.y', 45)
  def _reduce_26(val, _values, result)
     val[0]
    result
  end
.,.,

module_eval(<<'.,.,', 'SemanticFunctionParser.y', 46)
  def _reduce_27(val, _values, result)
     val[0]
    result
  end
.,.,

module_eval(<<'.,.,', 'SemanticFunctionParser.y', 50)
  def _reduce_28(val, _values, result)
     return SemanticFunctionAST.new({ type: :stmt_list, head: val[0], tail: val[2]})
    result
  end
.,.,

module_eval(<<'.,.,', 'SemanticFunctionParser.y', 51)
  def _reduce_29(val, _values, result)
     return SemanticFunctionAST.new({ type: :stmt_list, head: val[0], tail: val[1]})
    result
  end
.,.,

module_eval(<<'.,.,', 'SemanticFunctionParser.y', 52)
  def _reduce_30(val, _values, result)
     return SemanticFunctionAST.new({ type: :stmt_list, head: val[0], tail: SemanticFunctionAST.nothing })
    result
  end
.,.,

module_eval(<<'.,.,', 'SemanticFunctionParser.y', 53)
  def _reduce_31(val, _values, result)
     return SemanticFunctionAST.new({ type: :stmt_list, head: val[0], tail: SemanticFunctionAST.nothing })
    result
  end
.,.,

module_eval(<<'.,.,', 'SemanticFunctionParser.y', 55)
  def _reduce_32(val, _values, result)
     return val[0]
    result
  end
.,.,

module_eval(<<'.,.,', 'SemanticFunctionParser.y', 56)
  def _reduce_33(val, _values, result)
     return SemanticFunctionAST.new(type: :string, value: val[0])
    result
  end
.,.,

module_eval(<<'.,.,', 'SemanticFunctionParser.y', 57)
  def _reduce_34(val, _values, result)
     return SemanticFunctionAST.new(type: :number, number: val[0])
    result
  end
.,.,

module_eval(<<'.,.,', 'SemanticFunctionParser.y', 58)
  def _reduce_35(val, _values, result)
     return SemanticFunctionAST.new(type: :number, number: val[0])
    result
  end
.,.,

module_eval(<<'.,.,', 'SemanticFunctionParser.y', 60)
  def _reduce_36(val, _values, result)
     return SemanticFunctionAST.new(type: :var, name: val[0])
    result
  end
.,.,

def _reduce_none(val, _values, result)
  val[0]
end

end   # class SemanticFunctionParser