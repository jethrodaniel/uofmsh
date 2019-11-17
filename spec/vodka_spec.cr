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

create_lexer_spec "or", "fortune || cowsay", <<-STR
[1:1] WORD `fortune`
[1:9] OR_IF `||`
[1:12] WORD `cowsay`
STR

create_lexer_spec "pipe", "fortune | cowsay", <<-STR
[1:1] WORD `fortune`
[1:9] PIPE `|`
[1:11] WORD `cowsay`
STR

create_lexer_spec "and", "fortune && cowsay", <<-STR
[1:1] WORD `fortune`
[1:9] AND_IF `&&`
[1:12] WORD `cowsay`
STR

create_lexer_spec "bg", "fortune &", <<-STR
[1:1] WORD `fortune`
[1:9] AND `&`
STR
