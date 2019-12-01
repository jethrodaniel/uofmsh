# ometa

![](https://github.com/jethrodaniel/vodka/workflows/build/badge.svg)

An implementation of Alessandro Warth's OMeta system in Crystal.

## Install

Assuming you have crystal installed

```
git clone https://github.com/jethrodaniel/ometa
cd ometa
make
```

### What it do


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
OMETA_LOG=debug ./bin/ometa # info, warn, etc
```

## License

[MIT](LICENSE).

# Links:

- [OMeta website](http://tinlizzie.org/ometa/)
- [js version](https://github.com/alexwarth/ometa-js)
- [the 2008 paper](http://www.vpri.org/pdf/tr2008003_experimenting.pdf)
- [some article about OMeta](http://www.moserware.com/2008/06/ometa-who-what-when-where-why.html)
- [Pegged, a PEG generator in D](https://github.com/PhilippeSigaud/Pegged/wiki/PEG-Basics)
- [ometa in C#](https://github.com/kulibali/ironmeta)
- [handling left-recursion in PEGs](https://arxiv.org/pdf/1207.0443.pdf)
