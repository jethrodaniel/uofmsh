$LOAD_PATH.unshift File.expand_path('../test', __FILE__)

require 'test_helper'
require 'minitest/autorun'
require 'aruba/api'

class FirstRun < Minitest::Test
  include Aruba::Api

  def setup
    aruba_setup
  end
end
