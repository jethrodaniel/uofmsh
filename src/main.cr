require "./ometa"

# Ometa::Shell.new("$ ").repl banner: true, fortune: true

while line = gets
  puts line.inspect

  if line == 'q'
    puts "bye! <3"
    exit 1
  end

  puts Ometa::Lexer.new(line).to_s
end
