require "./vodka"

puts <<-SH
              ^__^
      _______/(oo)
  /\\/(       /(__)🚬    vodka.
     ||w----||
     ||     ||
SH

Vodka::Shell.new("$ ").repl!
