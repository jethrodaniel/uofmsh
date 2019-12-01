# default: build
default: clean run
# default: spec

spec: clean build
	crystal spec

run: build
	OMETA_LOG=debug ./bin/ometa

build: lint
	shards build --error-trace

lint:
	crystal tool format

clean:
	rm -rf ./bin
