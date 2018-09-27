Vagrant.configure('2') do |config|
  config.vm.box = 'bento/ubuntu-18.04'

  config.vm.provider 'virtualbox' do |vb|
    vb.memory = '1024'
  end

  config.vm.provision 'shell', privileged: false, inline: <<-SHELL
    sudo apt-get update
    sudo apt-get install -y git g++ make

    git clone --recurse-submodules https://github.com/jethrodaniel/uofmsh.git

    gpg --keyserver hkp://pgp.mit.edu --recv-keys 409B6B1796C275462A1703113804BB82D39DC0E3 7D2BAF1CF37B13E2069D6956105BD0E739499BDB
    curl -sSL https://get.rvm.io | bash -sl stable --ruby=ruby-2.5.1 --gems=bundler

    echo -e 'Next steps:\n'
    echo -e '\t./vagrant ssh'
    echo -e '\tcd uofmsh'
  SHELL
end
