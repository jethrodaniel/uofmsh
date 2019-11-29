# default: build
# default: run
default: spec

spec: clean build
	crystal spec

run: build
	./bin/ometa

build: lint
	shards build --error-trace

lint:
	crystal tool format

clean:
	rm -rf ./bin
