require "./spec_helper"

describe Vodka::Log do
  pending "#level" do
    Vodka::Log.level.should eq(Logger::ERROR)
  end

  pending "#level=" do
    Vodka::Log.level.should eq(Logger::ERROR)
    Vodka::Log.level = Logger::DEBUG
    Vodka::Log.level.should eq(Logger::DEBUG)
  end

  # Error: can't include dynamically
  pending "log" do
    #   include Vodka::Log
    #   log.info "testing, 1,2,3..."
  end
end
