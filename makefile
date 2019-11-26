# default: build
default: run

spec: clean
	crystal spec

run: build
	./bin/vodka

build: lint
	shards build --error-trace

lint:
	crystal tool format

clean:
	rm -rf ./bin
