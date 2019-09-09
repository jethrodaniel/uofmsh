# Why, Aruba, why can't you freeze your strings?
#
# frozen_string_literal: false

require 'spec_helper'

describe 'Built-in commands' do
  describe 'exit' do
    it 'exits the shell' do
      type 'exit'
      last_command_started.output.must_equal ""
    end
  end

  describe 'pwd' do
    it 'prints the current working directory' do
      type 'pwd'
      last_command_started.output.must_equal "#{Dir.pwd}/tmp/aruba\n"
    end
  end
end
