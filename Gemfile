# frozen_string_literal: true

source 'https://rubygems.org'

group :test, :development do
  # Work around a bug caused by both Minitest (5.1.3) and Aruba (0.14.4).
  #
  # Aruba's deprecated api defines a `run` command, which Minitest needs to
  # set up any tests.
  #
  # Ideally, both of these libraries could **not** pollute the test namespace
  # with methods **not** intended for user-consumption - looking at you,
  # Minitest.
  #
  # ¯\_(ツ)_/¯
  #
  gem 'aruba', git: 'https://github.com/cucumber/aruba', branch: 'master'
  gem 'minitest', '~> 5.11'
  gem 'minitest-reporters', '~> 1.3'

  # An excellent debugger. Just add `binding.pry`.
  gem 'pry-byebug', '~> 3.7'

  # For compilation and build tasks
  gem 'rake', '~> 12.3'
  gem 'thor', '~> 0.20.0'
end

gem "activesupport", "~> 6.0"
