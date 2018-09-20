ENV['PATH'] = "#{ENV['PATH']}:#{%x[pwd].chomp}"
