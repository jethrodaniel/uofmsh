# For aruba documentation, see https://relishapp.com/cucumber/aruba/docs/

@vodka
Feature: Commands

  Background:
    When I run `./vodka` interactively

  Scenario: ls
    And  I type "ls -ah"
    Then the output should contain ".."

  Scenario: touch
    Given an empty file named "example.c"
    And  I type "touch example.c"
    Then the output should contain exactly "vodka> "
    And a file named "example.c" should exist

  Scenario: cp
    Given a file named "a.txt" with:
    """
    zeppelin
    """
    And a file named "b.txt" does not exist
    And  I type "cp a.txt b.txt"
    Then the output should contain exactly "vodka> "
    And the file named "a.txt" should contain:
    """
    zeppelin
    """
    And a file named "b.txt" should contain:
    """
    zeppelin
    """

  Scenario: rm
    Given an empty file named "notes.txt"
    And  I type "rm notes.txt"
    Then the output should contain exactly "vodka> "
    And the file "notes.txt" should not exist
