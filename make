#!/usr/bin/env ruby
# frozen_string_literal: true

# Thor command line program to build and manage the project.
#
# Run `./make` to for help.

require 'rake'
require 'thor'

# Load everyting in the `rakefile`
load 'rakefile'

class BuildSystemCLI < Thor
  include Thor::Actions
  include FileUtils

  PROJECT_DIR = __dir__

  desc 'build', 'Builds the project'
  def build
    inside(PROJECT_DIR) { rake 'build' }
  end

  desc PROGRAM_NAME, 'Builds and runs the project'
  define_method PROGRAM_NAME.to_s do
    inside PROJECT_DIR do
      rake 'build'
      exec "./#{PROGRAM_NAME}"
    end
  end

  desc 'cucumber', 'Runs the aruba/cucumber tests'
  def cucumber
    invoke :build
    inside PROJECT_DIR do
      POSIX_SHELLS.keys.each { |shell| rake shell }
      run 'bundle exec cucumber'
    end
  end

  desc 'lint', 'Runs the linter'
  def lint
    inside(PROJECT_DIR) { die 'TODO: add this' }
  end

  desc 'spec', 'Runs the specs'
  def spec
    inside PROJECT_DIR do
      rake 'spec'
      run './.spec.out'
    end
  end

	desc 'clean', 'Removes build files'
  def clean
    inside(PROJECT_DIR) { rake 'clean' }
  end

	desc 'clobber', 'Removes all generated files'
  def clobber
    inside(PROJECT_DIR) { rake 'clobber' }
  end

  private

  def rake cmd = nil
    run "bundle exec rake #{cmd}"
  end

  def die cmd
    say cmd, :red
  end
end

BuildSystemCLI.start ARGV
