#!/usr/bin/env ruby
# frozen_string_literal: true

# Thor command line program to build and manage the project.
#
# Run `./make` to for help.
#
# Divided into a build system with Rake and a command line interface with Thor.

require 'thor'
require 'thor/rake_compat'
require 'rake/clean'

PROGRAM_NAME = 'vodka'

class BuildSystemRake
  include Rake::DSL

  SPEC_NAME = '.spec.out'
  SPEC_OBJECT = '.spec.o'

  CPP = 'g++-8'

  CPP_FLAGS = %w[
    -std=c++17
    -g
    -pedantic
    -Wall
    -Wextra
    -Werror
  ].join ' '

  SPEC_FLAGS = %w[
    -std=c++17
    -Wall
    -I./third_party/Catch2
  ].join ' '
  SPEC_SETUP = './spec/setup.cpp'

  SOURCE_FILES = Rake::FileList['src/**/*.cpp']
  SPEC_FILES = Rake::FileList.new 'spec/**/*.cpp' do |fl|
    fl.exclude 'spec/setup.cpp'
  end

  CLEAN << SPEC_NAME
  CLEAN << SPEC_OBJECT
  CLOBBER << PROGRAM_NAME

  def initialize
    file PROGRAM_NAME do
      sh "#{CPP} #{CPP_FLAGS} #{SOURCE_FILES} -o #{PROGRAM_NAME}"
    end

    desc "builds the executable, `#{PROGRAM_NAME}`"
    task build: PROGRAM_NAME

    file SPEC_NAME => SPEC_OBJECT do
      sh "#{CPP} #{SPEC_FLAGS} #{SPEC_OBJECT} #{SPEC_FILES} -o #{SPEC_NAME}"
    end

    file SPEC_OBJECT do
      sh "#{CPP} #{SPEC_FLAGS} -c #{SPEC_SETUP} -o #{SPEC_OBJECT}"
    end

    desc 'builds the spec program'
    task spec: SPEC_NAME

    desc 'show some build configuration settings'
    task :config do
      puts <<~MSG
        SPEC_FILES: #{SPEC_FILES.inspect}
        CLEAN: #{CLEAN.inspect}
        CLOBBER: #{CLOBBER.inspect}
      MSG
    end

    task default: :build
  end
end

class BuildSystemCLI < Thor
  include Thor::Actions
  include Thor::RakeCompat
  include FileUtils

  BuildSystemRake.new

  PROJECT_DIR = __dir__

  desc 'build', 'Builds the project'
  def build
    inside(PROJECT_DIR) { rake :build }
  end

  desc PROGRAM_NAME, 'Builds and runs the project'
  define_method PROGRAM_NAME.to_s do
    inside PROJECT_DIR do
      rake :build
      exec "./#{PROGRAM_NAME}"
    end
  end

  desc 'lint', 'Runs the linter'
  def lint
    inside(PROJECT_DIR) { die 'TODO: add this' }
  end

  desc 'spec', 'Runs the specs'
  option :acceptance, type: :boolean
  def spec
    rake :build

    inside PROJECT_DIR do
      if options[:acceptance]
        puts cmd = <<~SH
          for file in spec/**/*_spec.rb
          do
            ruby -I spec/acceptance/ $file
          done
        SH
        exec cmd
      else
        rake :spec
        run './.spec.out'
      end
    end
  end

  desc 'clean', 'Removes build files'
  def clean
    inside(PROJECT_DIR) { rake :clean }
  end

  desc 'clobber', 'Removes all generated files'
  def clobber
    inside(PROJECT_DIR) { rake :clobber }
  end

  private

  def rake cmd = :default
    Rake::Task[cmd].invoke
  end

  def die cmd
    say cmd, :red
  end
end

BuildSystemCLI.start ARGV
