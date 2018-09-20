Feature: Built-in commands
  As a shell user
  I want to run builtin commands
  So that I can interact with the shell

  # @announce-output
  Scenario: Exiting the shell
    When I run `uofmsh` interactively
    And  I type "exit"
    Then it should pass with "exit"
    And the output should contain exactly:
    """
    uofmsh> exit
    """
