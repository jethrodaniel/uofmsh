require "./log"
require "./parser"

module Vodka
  class Shell
    BANNER = <<-COW
                  ^__^
          _______/(oo)
      /\\/(       /(__)🚬    vodka.
         ||w----||
         ||     ||
    COW

    property prompt : String = "λ"

    # property parser : Vodka::Parser

    property log : Logger = Logger.new(STDOUT, level: Logger::DEBUG)

    def initialize(@prompt : String)
      @log.info "starting shell..."
    end

    # Run the interactive shell, i.e, the REPL
    #
    # ```
    # Vodka::Shell.new.repl banner: true, fortune: true
    # ```
    def repl(banner = false, fortune = false)
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
    # sh = Vodka::Shell.new
    # sh.eval "crystal run src/main.rc"
    # ```
    def eval(input : String)
      begin
        parser = Parser.new input
        puts parser.lexer.to_s if parser.lexer.tokens.size > 0
      rescue e : Vodka::Lexer::Error | Vodka::Parser::Error
        puts "#{e.class}: #{e.message}"
      end

      # # TODO: dont handle builtins differently, just check if builtin first
      if input == "exit"
        puts "bye! <3"
        exit 1
      end
    end

    def to_s
      "[vodka shell] #{@prompt}"
    end
  end
end
