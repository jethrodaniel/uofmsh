require "./log"
require "./parser"

module Ometa
  class Shell
    include Ometa::Log

    BANNER = <<-COW
                  ^__^
          _______/(oo)
      /\\/(       /(__)🚬    ometa.
         ||w----||
         ||     ||
    COW

    property prompt : String = "λ"

    def initialize(@prompt : String)
      log.info "starting shell..."
    end

    # Run the interactive shell
    #
    # ```
    # Ometa::Shell.new.repl banner: true, fortune: true
    # ```
    def repl(banner = false, fortune = false)
      @input = STDIN

      puts BANNER if banner

      puts %x{fortune} if fortune

      loop do
        print @prompt
        eval gets.not_nil!.chomp
      end
    end

    # Run a string of input
    #
    # ```
    # sh = Ometa::Shell.new
    # sh.eval "crystal run src/main.rc"
    # ```
    # def eval(input : String)
    #   begin
    #     parser = Parser.new input
    #     puts parser.lexer.to_s if parser.lexer.tokens.size > 0
    #   rescue e : Ometa::Lexer::Error | Ometa::Parser::Error
    #     puts "#{e.class}: #{e.message}"
    #   end

    #   # # TODO: dont handle builtins differently, just check if builtin first
    #   if input == "exit"
    #     puts "bye! <3"
    #     exit 1
    #   end
    # end

    def to_s
      "[ometa shell] #{@prompt}"
    end
  end
end
