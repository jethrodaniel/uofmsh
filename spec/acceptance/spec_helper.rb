# frozen_string_literal: true

require 'bundler/setup'

require 'minitest/spec'
require 'minitest/autorun'

require 'minitest/reporters'
Minitest::Reporters.use! Minitest::Reporters::SpecReporter.new

require 'aruba/api'

require 'date'

module MiniTest
  class Spec
    class << self
      alias_method :context, :describe
    end
  end
end

# Shared test methods, setup, teardown, etc.
class ShellTest < Minitest::Test
  include Aruba::Api
  extend Minitest::Spec::DSL

  def setup
    super
    setup_aruba
    start_shell
  end

  def teardown
    super
    terminate_all_commands
  end

  # Set `VODKA_SPEC_SHELL` to the full path to your shell, to test against
  # another shell.
  def shell
    cmd = ENV['VODKA_SPEC_SHELL']&.strip
    cmd = (Pathname.new(Dir.pwd) + 'vodka').realpath.to_s if cmd.nil?
    cmd
  end

  def start_shell
    run_command shell
  end
end

# Creates a new subclass of our test class.
#
# Used to consolidate shared spec methods, setup, teardown etc while still
# using the spec syntax.
def desc description, &block
  Class.new ShellTest do
    instance_eval(&block)
  end
end
