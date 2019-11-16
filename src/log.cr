require "logger"

module Vodka
  module Log
    # TODO
    # property level

    def log
      log = Logger.new STDOUT
      log.level = Logger::INFO
      log
    end
  end
end
