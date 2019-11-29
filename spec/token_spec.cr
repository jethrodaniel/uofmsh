require "./spec_helper"

describe Ometa::Token do
  it ".to_s" do
    token = Ometa::Token.new \
      line: 0,
      column: 0,
      type: Ometa::Token::Types::BANG,
      text: "!"

    token.to_s.should eq("[1:1] BANG `!`")
  end

  it "==" do
    a = Ometa::Token.new \
      line: 1,
      column: 1,
      type: Ometa::Token::Types::BANG,
      text: "!"

    b = Ometa::Token.new \
      line: 1,
      column: 1,
      type: Ometa::Token::Types::BANG,
      text: "!"

    c = Ometa::Token.new \
      line: 2,
      column: 1,
      type: Ometa::Token::Types::WORD,
      text: "cowsay"

    a.should eq(b)
    b.should eq(a)
    a.should_not eq(c)
    b.should_not eq(c)
    c.should_not eq(a)
    c.should_not eq(b)
  end
end
