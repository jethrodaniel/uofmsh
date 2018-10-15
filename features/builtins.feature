# For aruba documentation, see https://relishapp.com/cucumber/aruba/docs/

Feature: Built-in commands

  Background:
    When I run `uofmsh` interactively

  Scenario: exit
    And  I type "exit"
    Then the output should contain exactly "uofmsh> "

  Scenario: pwd
    And  I type "pwd"
    Then the output should contain "tmp/aruba"

