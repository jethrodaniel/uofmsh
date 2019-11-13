require "./vodka"

Vodka::Shell.new("$ ").repl! banner: true, fortune: true
