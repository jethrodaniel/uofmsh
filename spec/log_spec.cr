require "./spec_helper"

describe Vodka::Log do
  it "#level" do
    Vodka::Log.level.should eq(0)
  end

  it "#level=" do
    Vodka::Log.level.should eq(0)
    Vodka::Log.level = 9_001
    Vodka::Log.level.should eq(9_001)
  end

  # Error: can't include dynamically
  pending "log" do
    #   include Vodka::Log
    #   log.info "testing, 1,2,3..."
  end
end
