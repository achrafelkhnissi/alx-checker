#!/usr/bin/env bash

declare -x IS_42_STUDENT=1
declare -x INSTALLATION_PATH=~/goinfre
declare -x SHELL_CONFIG_FILE=~/.zshrc
declare -x BREW_PATH=$INSTALLATION_PATH/.brew
declare -x BREW=$BREW_PATH/bin/brew
declare -x BREW_ENV

# Install Homebrew
if test ! "$(command -v brew)"; then
  echo "Installing Homebrew..."


fi

function is_42_student() {
   if [ ! -d ~/goinfre ]; then
     IS_42_STUDENT 0
   else
     IS_42_STUDENT 1
   fi
}

# Check if the ~/goinfre directory exists
if [ ! -d ~/goinfre ]; then
  IS_42_STUDENT=0
  INSTALLATION_PATH=~
fi

if [ -f ~/.zshrc ]; then
  SHELL_CONFIG_FILE=~/.zshrc
elif [ -f ~/.bashrc ]; then
  SHELL_CONFIG_FILE=~/.bashrc
fi

# Install Homebrew
if test ! "$(command -v brew)"; then

  git clone https://github.com/Homebrew/brew $BREW_PATH

# Set brew's environment variables
  for line in $BREW_ENV; do
    if [[ $line == "export" ]]; then
      continue
    fi
    echo "$line"
  done

fi # End of Homebrew installation

# Update Homebrew recipes
brew update --force --quiet

# Change permissions
chmod -R go-w "$(brew --prefix)/share/zsh"

#done!
