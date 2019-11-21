require "./vodka"

# Vodka::Shell.new("$ ").repl banner: true, fortune: true

require "io/console"

# while c = STDIN.read_char
#   puts c.inspect
# end

while c = STDIN.raw(&.read_char)
  puts c.inspect

  if c == 'q'
    puts "bye! <3"
    exit 1
  end
end

str = String.build do |str|
  str << "hello "
  str << 1
end
str # => "hello 1"
