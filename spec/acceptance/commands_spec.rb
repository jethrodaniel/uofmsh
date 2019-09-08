# Why, Aruba, why can't you freeze your strings?
#
# frozen_string_literal: false

require 'spec_helper'

describe 'Common *nix commands' do
  describe 'ls' do
    let(:user) { ENV['HOME'].gsub '/home/', '' }

    it 'shows the contents of a directory' do
      type 'ls -a'
      last_command_started.output.must_include <<~SH
      vodka> .
      ..
      SH
    end
  end

  # Scenario: touch
  #   Given an empty file named "example.c"
  #   And  I type "touch example.c"
  #   Then the output should contain exactly "vodka> "
  #   And a file named "example.c" should exist

  # Scenario: cp
  #   Given a file named "a.txt" with:
  #   """
  #   zeppelin
  #   """
  #   And a file named "b.txt" does not exist
  #   And  I type "cp a.txt b.txt"
  #   Then the output should contain exactly "vodka> "
  #   And the file named "a.txt" should contain:
  #   """
  #   zeppelin
  #   """
  #   And a file named "b.txt" should contain:
  #   """
  #   zeppelin
  #   """

  # Scenario: rm
  #   Given an empty file named "notes.txt"
  #   And  I type "rm notes.txt"
  #   Then the output should contain exactly "vodka> "
  #   And the file "notes.txt" should not exist
end
