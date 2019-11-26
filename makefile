# default: build
#	crystal spec
default: run

run: build
	./bin/vodka

build: lint
	shards build --error-trace

lint:
	crystal tool format

clean:
	rm -rf ./bin
