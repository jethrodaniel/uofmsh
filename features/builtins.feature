# For aruba documentation, see https://relishapp.com/cucumber/aruba/docs/

@vodka
Feature: Built-in commands

  Background:
    When I run `./vodka` interactively

  Scenario: exit
    And  I type "exit"
    Then the output should contain exactly "vodka> "

  Scenario: pwd
    And  I type "pwd"
    Then the output should contain "tmp/aruba"

