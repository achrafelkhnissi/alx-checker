
read -p "Install GitHub CLI? [y/N] " -n 1 -r

function generate_ssh_key() {
  read -p "Please enter your email address: " -r

  ssh-keygen -t ed25519 -C "$REPLY"

  # Start the ssh-agent in the background
  eval "$(ssh-agent -s)"

  echo "Host github.com" >> ~/.ssh/config
  echo "  AddKeysToAgent yes" >> ~/.ssh/config
  echo "  UseKeychain yes" >> ~/.ssh/config
  echo "  IdentityFile ~/.ssh/id_ed25519" >> ~/.ssh/config
  echo "" >> ~/.ssh/config

  # Add your SSH private key to the ssh-agent
  ssh-add ~/.ssh/id_ed25519

  pbcopy < ~/.ssh/id_ed25519.pub
  echo "Your SSH key has been copied to your clipboard."
}

function setup_github_cli() {
#  read -p "Please the path to your SSH key: " -r
  # Authenticate with GitHub
  gh auth login --hostname github.com --git-protocol ssh

  # Test your connection
  ssh -T git@github.com

}

if [[ $REPLY =~ ^[Yy]$ ]]; then
#  echo "Installing GitHub CLI..."
#  brew install gh

#  printf "\n\nGenerating SSH key...\n"
#  generate_ssh_key

  printf "\n\nSetting up GitHub CLI...\n"
  setup_github_cli

  printf "\n\nDone!\n"

fi








#if [[ $REPLY =~ ^[Yy]$ ]]; then
#  echo "Installing GitHub CLI..."
#  brew install gh
#  gh auth login --with-ssh-key --hostname github.com
#fi
#
#brew install gh
#
#gh auth login --with-ssh-key --hostname github.com

