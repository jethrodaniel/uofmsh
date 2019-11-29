require "./spec_helper"

describe Ometa::Lexer do
  it "do" do
    lex = Ometa::Lexer.new "ometa ExpRecognizer"
    # lex.line_number.should eq(1)
    # lex.column_number.should eq(1)

    # lex.lex!
    lex.to_s.should eq <<-LEX
      wow
    LEX
  end
end

# macro lex_spec(name, command, expected)
#   describe Ometa::Lexer do
#     it {{name}} do
#       lexer = Ometa::Lexer.new {{command}}
#       puts "lexer: #{lexer.to_s}"
#       lexer.to_s.should eq {{expected}}
#     end
#   end
# end
#
# # macro lex_spec_fail(name, command, failure)
# #   describe Ometa::Lexer do
# #     it {{name}} do
# #       expect_raises Ometa::Lexer::Error, {{failure}} do
# #         lexer = Ometa::Lexer.new {{command}}
# #       end
# #     end
# #   end
# # end
#
# lex_spec "test", <<-OMETA, <<-LEX
# ometa ExpRecognizer
# OMETA
# [1:3] WORD `\\`
# LEX

# lex_spec "test", <<-OMETA, <<-LEX
# ometa ExpRecognizer {
#   dig = ’0’ | ... | ’9’,
#   num = dig+,
#   fac = fac ’*’ num| fac ’/’ num| num,
#   exp = exp ’+’ fac| exp ’-’ fac| fac
# }
# OMETA
# [1:3] WORD `\\`
# [1:3] NEWLINE `\n`
# [2:1] WORD `echo`
# [2:8] WORD `$`
# [2:8] WORD `HOME`
# [2:12] NEWLINE `\n`
# LEX
