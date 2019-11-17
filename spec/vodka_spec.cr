require "./spec_helper"

describe Vodka do
  it "has a version" do
    Vodka::VERSION.should eq("0.2.0")
  end
end

describe Vodka::Log do
  it "#level" do
    Vodka::Log.level.should eq(0)
  end

  it "#level=" do
    Vodka::Log.level.should eq(0)
    Vodka::Log.level = 9_001
    Vodka::Log.level.should eq(9_001)
  end

  # Error: can't include dynamically
  pending "log" do
    #   include Vodka::Log
    #   log.info "testing, 1,2,3..."
  end
end

describe Vodka::Token do
  it ".to_s" do
    token = Vodka::Token.new \
      line: 0,
      column: 0,
      type: Vodka::Token::Types::BANG,
      text: "!"

    token.to_s.should eq("[1:1] BANG `!`")
  end
end

macro create_lexer_spec(name, command, expected)
  describe Vodka::Lexer do
    it {{name}} do
      lexer = Vodka::Lexer.new {{command}}
      lexer.to_s.should eq {{expected}}
    end
  end
end

create_lexer_spec "or", "fortune || cowsay", <<-LEX
[1:1] WORD `fortune`
[1:9] OR_IF `||`
[1:12] WORD `cowsay`
LEX

create_lexer_spec "pipe", "fortune | cowsay", <<-LEX
[1:1] WORD `fortune`
[1:9] PIPE `|`
[1:11] WORD `cowsay`
LEX

create_lexer_spec "and", "fortune && cowsay", <<-LEX
[1:1] WORD `fortune`
[1:9] AND_IF `&&`
[1:12] WORD `cowsay`
LEX

create_lexer_spec "bg", "fortune &", <<-LEX
[1:1] WORD `fortune`
[1:9] AND `&`
LEX

create_lexer_spec "parenthesis", "(cat file)", <<-LEX
[1:1] LEFT_PAREN `(`
[1:2] WORD `cat`
[1:6] WORD `file`
[1:10] RIGHT_PAREN `)`
LEX

create_lexer_spec "braces", "{cat file}", <<-LEX
[1:1] LEFT_BRACE `{`
[1:2] WORD `cat`
[1:6] WORD `file`
[1:10] RIGHT_BRACE `}`
LEX

create_lexer_spec "semi-colon", "date;", <<-LEX
[1:1] WORD `date`
[1:5] SEMI `;`
LEX

create_lexer_spec "comments", <<-SH, <<-LEX
# ignore me
cal # also me
SH
[1:13] WORD `cal`
LEX
