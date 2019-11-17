require "./log"

module Vodka
  class Shell
    property prompt

    property log : Logger = Logger.new(STDOUT, level: Logger::DEBUG)
    # delegate log, to: @log

    BANNER = <<-COW
                  ^__^
          _______/(oo)
      /\\/(       /(__)🚬    vodka.
         ||w----||
         ||     ||
    COW

    def initialize(@prompt : String)
      @log.info "starting shell..."
      @prompt ||= "λ"
    end

    # Run the interactive shell, i.e, the REPL
    def repl!(banner = false, fortune = false)
      puts BANNER if banner

      puts %x{fortune} if fortune

      loop do
        print "#{@prompt}"
        eval! gets.not_nil!.chomp
      end
    end

    # Run a single line of input
    def eval!(input : String)
      begin
        Interpreter.new input
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
