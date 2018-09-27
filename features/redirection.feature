# For aruba documentation, see https://relishapp.com/cucumber/aruba/docs/

Feature: Redirection

  Background:
    # When I run `bash` interactively
    When I run `uofmsh` interactively

  Scenario: <
    Given a file named "cow" with:
    """
     ^__^
     (oo)\_______
     (__)\       )\/\
         ||----w |
         ||     ||
    """
    And  I type "cat < cow"
    Then the output should contain exactly:
    """
     ^__^
     (oo)\_______
     (__)\       )\/\
         ||----w |
         ||     ||
    """

  Scenario: >
    Given a file named "hello.txt" does not exist
    And  I type "echo 'hello' > hello.txt"
    Then a file named "hello.txt" should contain "hello"

  Scenario: |
    Given a file named "sqlite.txt" with:
    """
    May you do good and not evil.
    May you find forgiveness for yourself and forgive others.
    May you share freely, never taking more than you give.
    """
    And  I type "cat sqlite.txt | wc -m"
    Then the output should contain exactly "142"
