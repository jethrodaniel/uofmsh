default: build
	crystal spec

run: build
	./bin/vodka

build: lint
	shards build --error-trace

lint:
	crystal tool format
