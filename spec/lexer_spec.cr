require "./spec_helper"

macro lex_spec(name, command, expected)
  describe Vodka::Lexer do
    it {{name}} do
      lexer = Vodka::Lexer.new {{command}}
      lexer.to_s.should eq {{expected}}
    end
  end
end

lex_spec "or", "fortune || cowsay", <<-LEX
[1:1] WORD `fortune`
[1:9] OR_IF `||`
[1:12] WORD `cowsay`
LEX

lex_spec "pipe", "fortune | cowsay", <<-LEX
[1:1] WORD `fortune`
[1:9] PIPE `|`
[1:11] WORD `cowsay`
LEX

lex_spec "and", "fortune && cowsay", <<-LEX
[1:1] WORD `fortune`
[1:9] AND_IF `&&`
[1:12] WORD `cowsay`
LEX

lex_spec "bg", "fortune &", <<-LEX
[1:1] WORD `fortune`
[1:9] AND `&`
LEX

lex_spec "parenthesis", "(cat file)", <<-LEX
[1:1] LEFT_PAREN `(`
[1:2] WORD `cat`
[1:6] WORD `file`
[1:10] RIGHT_PAREN `)`
LEX

lex_spec "braces", "{cat file}", <<-LEX
[1:1] LEFT_BRACE `{`
[1:2] WORD `cat`
[1:6] WORD `file`
[1:10] RIGHT_BRACE `}`
LEX

lex_spec "semi-colon", "date;", <<-LEX
[1:1] WORD `date`
[1:5] SEMI `;`
LEX

lex_spec "comments", <<-SH, <<-LEX
# ignore me
cal # also me
SH
[1:13] WORD `cal`
LEX

lex_spec "colon", ":", <<-LEX
[1:1] COLON `:`
LEX

lex_spec "hyphen", "-", <<-LEX
[1:1] HYPHEN `-`
LEX

lex_spec "backslash", "\\", <<-LEX
[1:1] BACKSLASH `\\`
LEX

lex_spec "new lines", <<-LEX, <<-SH



vim
LEX
[1:1] NEWLINE `\n`
[2:1] NEWLINE `\n`
[3:1] NEWLINE `\n`
[4:1] WORD `vim`
SH

lex_spec "whitespace", <<-LEX, <<-SH
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

lex_spec "redirect input", "cat < file", <<-LEX
[1:1] WORD `cat`
[1:5] REDIRECT_LEFT `<`
[1:7] WORD `file`
LEX

lex_spec "here-docs", <<-SH, <<-LEX
cat <<here
  wow!
here
SH
[1:1] WORD `cat`
[1:5] HEREDOC `<<here`
[1:11] NEWLINE `\n`
[2:3] WORD `wow`
[2:6] BANG `!`
[2:7] NEWLINE `\n`
[3:1] WORD `here`
LEX
