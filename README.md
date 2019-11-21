# vodka

![](https://github.com/jethrodaniel/vodka/workflows/build/badge.svg)

## Install

Assuming you have crystal installed

```
git clone https://github.com/jethrodaniel/vodka
cd vodka
make build
./bin/vodka
```

## Development

To run all tests

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

## History

This was originally a homework project - see the [assignment](docs/assignment.pdf), which is in C++, and has a git tag.

## References

- POSIX shell specifications: https://pubs.opengroup.org/onlinepubs/9699919799/

A big thanks to the following

- https://weblog.jamisbuck.org/2015/7/30/writing-a-simple-recursive-descent-parser.html
- http://www.craftinginterpreters.com/
- http://parsingintro.sourceforge.net/

Etc

- https://pastebin.com/qpsK4TF6
