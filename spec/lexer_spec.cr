require "./spec_helper"

macro passes(name, command, expected)
  describe Ometa::Lexer do
    it {{name}} do
      lex = Ometa::Lexer.new {{command}}
      puts "lex: #{lex.to_s}"
      lex.to_s.should eq {{expected}}
    end
  end
end

macro fails(name, command, failure)
  describe Ometa::Lexer do
    it {{name}} do
      expect_raises Ometa::Lexer::Error, {{failure}} do
        Ometa::Lexer.new {{command}}
      end
    end
  end
end

passes "example", <<-OMETA, <<-LEX
ometa Exp {
  foo = '0'
}
OMETA
[1:1-5] RULE `ometa`
[1:7-9] RULE `Exp`
[1:11-11] LEFT_BRACE `{`
[1:12-12] NEWLINE `\n`
[2:3-5] RULE `foo`
[2:7-7] EQUALS `=`
[2:11-11] LITERAL `0`
[2:12-12] NEWLINE `\n`
[3:1-1] RIGHT_BRACE `}`
LEX

fails "unterminated single quotes", <<-OMETA, <<-LEX
foo = '0
OMETA
unterminated literal single qoute at [1:8]
LEX

fails "single quoting nothing", <<-OMETA, <<-LEX
foo = ''
OMETA
blank literal is meaningless at [1:8]
LEX
