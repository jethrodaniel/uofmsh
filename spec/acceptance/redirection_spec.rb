# Why, Aruba, why can't you freeze your strings?
#
# frozen_string_literal: false

require 'spec_helper'

describe 'redirection' do
  describe '>' do
    it 'redirects output to a file'
  end

  describe '<' do
    let :cow do
      <<~'STR'
        ^__^
        (oo)\_______
        (__)\       )\/\
            ||----w |
            ||     ||
      STR
    end

    before do
      write_file 'cow.txt', cow
    end

    it 'redirects input to a file' do
      type 'cat < cow.txt'
      # @todo remove prompt
      last_command_started.output.must_equal cow
    end
  end

  describe '>>' do
    it 'appends output to a file'
  end

  describe '<<' do
    it 'appends input to a file'
  end
end

describe 'the shell prompt' do
  context 'when not running interactively' do
    it "doesn't print the prompt"
  end

  context 'when running interactively' do
    it 'prints to the terminal (tty)'
  end
end

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
