require "./ometa"

if STDIN.tty?
  print "\nometa> "
  line = [] of Char

  while c = ARGF.read_char
    print c.inspect, '\n'

    case c
    when 'q'
      puts "bye! <3"
      exit 1
    when '\n'
      puts
      puts "> #{line.join.to_s}"
      puts Ometa::Lexer.new(line.join).to_s
      print "\nometa> "
      line = [] of Char
    else
      line << c
    end
  end
else
  puts Ometa::Lexer.new(ARGF.gets_to_end).to_s
end
