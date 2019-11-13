module Vodka
  class Shell
    include Vodka::Log

    property prompt

    BANNER = <<-COW
                  ^__^
          _______/(oo)
      /\\/(       /(__)🚬    vodka.
         ||w----||
         ||     ||
    COW

    def initialize(@prompt : String)
      log.info "starting shell..."
      @prompt ||= "λ"
      # @interpreter ||= Interpreter.new ""
    end

    # Run the interactive shell, i.e, the REPL
    def repl!(banner = false, fortune = false)
      puts BANNER if banner

      puts %x{fortune} if fortune

      loop do
        print "#{@prompt}"
        input = gets.not_nil!.chomp || ""

        # TODO cleanup
        interpreter = Interpreter.new input

        interpreter.interpret!
      end
    end

    # Run a single line of input
    def eval!(input : String)
      # # TODO: dont handle builtins differently, just check if builtin first
      # if input == "q" || input == "exit"
      #   puts "bye! <3"
      #   exit 1
      # end
    end

    def to_s
      "[vodka shell] #{@prompt}"
    end
  end
end
