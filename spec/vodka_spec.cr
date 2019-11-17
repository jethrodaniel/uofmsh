require "./spec_helper"

describe Vodka do
  it "has a version" do
    Vodka::VERSION.should eq("0.2.0")
  end
end
