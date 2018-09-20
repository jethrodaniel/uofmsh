Feature: Built-in commands

  Scenario: Exiting the shell
    When I run `uofmsh` interactively
    And  I type "exit"
    Then the output should contain exactly ""
