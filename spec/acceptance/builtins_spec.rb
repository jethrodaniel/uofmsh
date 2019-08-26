# Why, Aruba, why can't you freeze your strings?
#
# frozen_string_literal: false

require 'spec_helper'

desc 'Built-in commands' do
  describe 'exit' do
    it 'exits the shell' do
      type 'exit'
      last_command_started.output.must_equal "vodka> "
    end
  end

  describe 'pwd' do
    it 'prints the current working directory' do
      type 'pwd'
      last_command_started.output.must_equal "vodka> #{Dir.pwd}/tmp/aruba\n"
    end
  end
end

desc 'Common *nix commands' do
  describe 'ls' do
    let(:user) { ENV['HOME'].gsub '/home/', '' }

    it 'shows the contents of a directory' do
      type 'ls -lah'
      last_command_started.output.must_equal <<~SH
        vodka> total 8.0K
        drwxr-xr-x 2 #{user} #{user} 4.0K #{Time.now.strftime '%b %e %H:%M'} .
        drwxr-xr-x 3 #{user} #{user} 4.0K #{Time.now.strftime '%b %e %H:%M'} ..
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

# desc 'Redirection' do

# Feature: Redirection
#
#   Background:
#     When I run `./vodka` interactively
#
#   Scenario: <
#     Given a file named "cow" with:
#     """
#      ^__^
#      (oo)\_______
#      (__)\       )\/\
#          ||----w |
#          ||     ||
#     """
#     And  I type "cat < cow"
#     Then the output should contain exactly:
#     """
#     vodka>  ^__^
#      (oo)\_______
#      (__)\       )\/\
#          ||----w |
#          ||     ||
#     """
#
#   Scenario: >
#     Given a file named "hello.txt" does not exist
#     And  I type "echo hello > hello.txt"
#     Then a file named "hello.txt" should contain "hello"
#
#   Scenario: |
#     Given a file named "sqlite.txt" with:
#     """
#     May you do good and not evil.
#     May you find forgiveness for yourself and forgive others.
#     May you share freely, never taking more than you give.
#     """
#     And  I type "cat sqlite.txt | wc -m"
#     Then the output should contain exactly "vodka> 142"
# end
