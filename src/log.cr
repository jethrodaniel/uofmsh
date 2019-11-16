require "logger"

module Vodka
  module Log
    @@level = 0

    def self.level=(n)
      @@level = n
    end

    def self.level
      @@level
    end

    def log
      log = Logger.new STDOUT
      log.level = Logger::INFO
      log
    end
  end
end
