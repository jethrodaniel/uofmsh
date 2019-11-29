require "./spec_helper"

describe Ometa do
  it "has a version" do
    Ometa::VERSION.should match(/\d\.\d\.\d/)
  end
end

# describe PEG do
#  it "do" do
#    p = PEG::Parser.new
#    out = p.parse "1 + 1"
#    # out.should eq({:wow => [] of Hash | Array})
#    out.should eq({:wow => [] of String})
#  end
# end
#
# describe PEG::Slice do
#  it "do" do
#    s = PEG::Slice.new 0, 0, 0, ""
#
#    s.size.should eq(0)
#    # s.match(//).should be_true
#  end
# end
