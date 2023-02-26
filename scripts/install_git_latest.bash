
declare -x GIT_VERSION=$(git --version | cut -d ' ' -f 3)

echo "GIT_VERSION: $GIT_VERSION"
# Install git

# Install git
#brew install git
#
#brew upgrade git # Upgrade git

#GIT_NEW_VERSTION = $(curl -s https://api.github.com/repos/git/git/releases/latest | grep tag_name | cut -d '"' -f 4)
GIT_NEW_VERSTION=$(git --version | cut -d ' ' -f 3)

# Check if the current git version is equal to the new version
if [ "$GIT_VERSION" != "$GIT_NEW_VERSTION" ]; then
  echo "Unlink and relink git..."
  brew unlink git
  brew link --force git
  echo "git $GIT_NEW_VERSTION installed!"
else
  echo "git $GIT_NEW_VERSTION is already installed!"
fi
