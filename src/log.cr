require "logger"

module Vodka
  # Basic logging module that provides `log`.
  #
  # Set the `VODKA_LOG` environment variable to change this, defaults to `info`.
  #
  # NOTE: The result must be one of the following, matched case-insensitive:
  #  - debug
  #  - error
  #  - fatal
  #  - info
  #  - unknown
  #  - warn
  module Log
    # logs something.
    # TODO: colorize output
    def log
      level = if ENV.has_key? "VODKA_LOG"
                case ENV["VODKA_LOG"]
                when .match(/debug/m)   then Logger::DEBUG
                when .match(/error/m)   then Logger::ERROR
                when .match(/fatal/m)   then Logger::FATAL
                when .match(/info/m)    then Logger::INFO
                when .match(/unknown/m) then Logger::UNKNOWN
                when .match(/warn/m)    then Logger::WARN
                else                         Logger::INFO
                end
              else
                Logger::INFO
              end
      Logger.new(STDOUT, level: level)
    end
  end
end
