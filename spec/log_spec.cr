require "./spec_helper"

describe Ometa::Log do
  pending "#level" do
    Ometa::Log.level.should eq(Logger::ERROR)
  end

  pending "#level=" do
    Ometa::Log.level.should eq(Logger::ERROR)
    Ometa::Log.level = Logger::DEBUG
    Ometa::Log.level.should eq(Logger::DEBUG)
  end

  # Error: can't include dynamically
  pending "log" do
    #   include Ometa::Log
    #   log.info "testing, 1,2,3..."
  end
end
