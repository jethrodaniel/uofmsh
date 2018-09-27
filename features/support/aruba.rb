require 'aruba/cucumber'

Aruba.configure do |config|
  # Fail a command if it takes longer than a second
  config.exit_timeout = 1
end
