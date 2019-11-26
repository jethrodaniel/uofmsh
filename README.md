# vodka

![](https://github.com/jethrodaniel/vodka/workflows/build/badge.svg)

a stupid simple shell.

## Install

Assuming you have crystal installed

```
git clone https://github.com/jethrodaniel/vodka
cd vodka
make build
./bin/vodka
```

### What it do


pipes (like normal)

```
fortune | cowsay
```

file descriptors (like normal)

```
fortune | cowsay 2>errors >cow
```

interpolation of commands (like ruby)

```
vim "notes_#{date +%Y%m%d%H%M%S}.txt"
```

simple quotes _without_ interpolation (like ruby)

```
echo '#{yeet}'
```

command chaining (like normal)

```
which crystall || echo "pls install crystal first. kthnxbye."
which crystall && echo "you got crystal? kool."
```

yaml PATH configuration

```
# ~/.config/vodka/config.yml

path:
  - some/path
```

### What it **doesn't** do

- job control (backgrounding processes, etc.. just use tmux)
- conditionals (besides the one-line command chaining)
- functions
- `$(())` arithmetic, use `"#{bc <<< "(1 + 2) * 2 ^ 2"}` 
- `${}`
- globs, `.*`, and `.?` matching

## Development

To run the tests

```
make
```

To run a specfic test

```
crystal spec spec/lexer_spec.cr:122
```

To set the logging level

```
VODKA_LOG=debug ./bin/vodka # info, warn, etc
```

## License

[MIT](LICENSE).

## References

- POSIX shell specifications: https://pubs.opengroup.org/onlinepubs/9699919799/

A big thanks to the following

- https://weblog.jamisbuck.org/2015/7/30/writing-a-simple-recursive-descent-parser.html
- http://www.craftinginterpreters.com/
- http://parsingintro.sourceforge.net/

Etc

- https://pastebin.com/qpsK4TF6
