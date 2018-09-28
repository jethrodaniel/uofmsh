Vagrant.configure('2') do |config|
  config.vm.box = 'bento/ubuntu-18.04'

  config.vm.provider 'virtualbox' do |vb|
    vb.memory = '1024'
  end

  config.vm.provision 'shell', privileged: false, inline: <<-SHELL
    sudo apt-get update
    sudo apt-add-repository -y ppa:rael-gc/rvm
    sudo apt-get install -y git g++ make rvm
    rvm install "ruby-2.5.1"

    git clone --recurse-submodules https://github.com/jethrodaniel/uofmsh.git

    echo -e 'Next steps:\n'
    echo -e '\tvagrant ssh'
    echo -e '\tcd uofmsh'
  SHELL
end
