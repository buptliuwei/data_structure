#！/bin/bash
if [ -z "$1" ]; then
    echo "usage: ./install.sh go-package.tar"
    exit
fi

if [ -d "/usr/local/go" ]; then
    echo "Uninstalling old version..."
    sudo rm -rf /usr/local/go
fi

echo "Installing..."
sudo tar -C /usr/local -xzf $1
echo "Done"