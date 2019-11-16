require "./spec_helper"

describe Vodka do
  it "has a version" do
    Vodka::VERSION.should eq("0.2.0")
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

describe Vodka::Lexer do
  it ".to_s" do
    lexer = Vodka::Lexer.new "fortune | cowsay"

    expected = <<-STR
    [1:1] WORD `fortune`
    [1:9] PIPE `|`
    [1:11] WORD `cowsay`
    STR

    lexer.to_s.should eq expected
  end

  context "multiple examples" do
    it "or" do
      lexer = Vodka::Lexer.new "fortune || cowsay"

      expected = <<-STR
      [1:1] WORD `fortune`
      [1:9] OR_IF `||`
      [1:12] WORD `cowsay`
      STR

      lexer.to_s.should eq expected
    end
  end
end
