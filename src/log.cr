require "logger"

# TODO: use this, set log level based on env
#
# Currently we're just using this:
#
# ```
# class Example
#   property log : Logger = Logger.new(STDOUT, level: Logger::INFO)
#
#   def foo
#     log.info "bar"
#   end
# end
# ```
#
module Vodka
  # DEBUG
  # ERROR
  # FATAL
  # INFO
  # UNKNOWN
  # WARN
  class Log
    #     property level : Logger::Severity = Logger::ERROR
    #     forward_missing_to @logger
    #     def initialize
    #       update_logger!
    #     end
    #     def level=(n)
    #       @level = n
    #       update_logger!
    #     end
    #     private def update_logger!
    #       @logger = Logger.new(STDOUT, level: level)
    #     end
  end
end
