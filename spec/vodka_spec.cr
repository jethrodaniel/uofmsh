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

create_lexer_spec "colon", ":", <<-LEX
[1:1] COLON `:`
LEX

create_lexer_spec "hyphen", "-", <<-LEX
[1:1] HYPHEN `-`
LEX

create_lexer_spec "backslash", "\\", <<-LEX
[1:1] BACKSLASH `\\`
LEX

create_lexer_spec "new lines", <<-LEX, <<-SH



vim
LEX
[1:1] NEWLINE `\n`
[2:1] NEWLINE `\n`
[3:1] NEWLINE `\n`
[4:1] WORD `vim`
SH

create_lexer_spec "whitespace", <<-LEX, <<-SH
        date
	cal
				date
LEX
[1:9] WORD `date`
[1:13] NEWLINE `\n`
[2:2] WORD `cal`
[2:5] NEWLINE `\n`
[3:5] WORD `date`
SH

create_lexer_spec "redirect input", "cat < file", <<-LEX
[1:1] WORD `cat`
[1:5] REDIRECT_LEFT `<`
[1:7] WORD `file`
LEX

create_lexer_spec "here-docs", "cat <<here\nhere", <<-LEX
[1:1] WORD `cat`
[1:5] HEREDOC `<<here`
[1:11] NEWLINE `\n`
[2:1] WORD `here`
LEX
