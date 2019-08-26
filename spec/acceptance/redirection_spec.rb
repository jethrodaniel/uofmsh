# Why, Aruba, why can't you freeze your strings?
#
# frozen_string_literal: false

require 'spec_helper'

desc 'Redirection' do
  describe '>' do
    it 'redirects std out to a file'
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
