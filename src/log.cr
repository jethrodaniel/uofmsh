require "logger"

module Vodka
  module Log
    def log
      log = Logger.new STDOUT
      log.level = Logger::INFO
      log
    end
  end
end