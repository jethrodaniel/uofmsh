Vagrant.configure("2") do |config|
  config.vm.box = "bento/ubuntu-18.04"

  config.vm.provider "virtualbox" do |vb|
    vb.memory = "1024"
  end

  config.vm.provision "shell", privileged: false, inline: <<-SHELL
    # Update the package manager
    sudo apt-get update

    # Install git
    sudo apt-get install -y git

    # Clone the project repo and its submodules
    git clone --recurse-submodules https://github.com/jethrodaniel/uofmsh.git

    # Install RVM
    gpg --keyserver hkp://keys.gnupg.net --recv-keys 409B6B1796C275462A1703113804BB82D39DC0E3 7D2BAF1CF37B13E2069D6956105BD0E739499BDB
    \\curl -sSL https://get.rvm.io | bash -s

    # Use RVM to install Ruby
    ~/.rvm/bin/rvm --quiet-curl install ruby-2.5.1

    # Move into the project directory
    cd uofmsh

    echo -e "All finished!\nNow run the following commands to finish the setup\n"
    echo "./vagrant ssh"
    echo "cd uofmsh"
    echo "gem install bundle"
    echo "bundle"
  SHELL
end
