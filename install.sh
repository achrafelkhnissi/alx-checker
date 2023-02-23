#!/usr/bin/env bash

# Install the latest version of the script
#curl -s https://raw.githubusercontent.com/andrewchilds/ssh-alias/master/ssh-alias.sh > /usr/local/bin/ssh-alias

# declare global variables
declare -x SCRIPT_NAME=$(basename "$0")
declare -x SCRIPT_DIR=$(cd "$(dirname "$0")" && pwd)
declare -x SCRIPT_PATH="$SCRIPT_DIR/$SCRIPT_NAME"
declare -x SCRIPT_VERSION="1.0"

declare -x SCRIPT_ARGS="$@"
declare -x SCRIPT_ARGS_COUNT="$#"
declare -x SCRIPT_ARGS_ARRAY=("$@")
declare -x SCRIPT_ARGS_ARRAY_COUNT="${#SCRIPT_ARGS_ARRAY[@]}"
declare -x SCRIPT_ARGS_ARRAY_LAST="${SCRIPT_ARGS_ARRAY[$((SCRIPT_ARGS_ARRAY_COUNT - 1))]}"
declare -x SCRIPT_ARGS_ARRAY_FIRST="${SCRIPT_ARGS_ARRAY[0]}"




echo "SCRIPT_NAME: $SCRIPT_NAME"
echo "SCRIPT_DIR: $SCRIPT_DIR"
echo "SCRIPT_PATH: $SCRIPT_PATH"


# declare colors
#declare -x YELLOW='\033[1;33m'
#declare -x PURPLE='\033[0;35m'
#declare -x RED='\033[0;31m'
#declare -x GREEN='\033[0;32m'
#declare -x NC='\033[0m' # No Color

declare -x YELLOW="\033[1;93m"
declare -x PURPLE="\033[0;95m"
declare -x RED="\033[0;91m"
declare -x BLUE='\033[0;34m'
declare -x CYAN='\033[0;36m'
declare -x GREEN="\033[0;92m"
declare -x END="\033[0m" # No Color

function print_usage() {
  echo "Usage: $SCRIPT_NAME [OPTION]..."
  echo "Install the latest version of the script"
  echo
  echo "Options:"
  echo "  -h, --help     display this help and exit"
  echo "  -v, --version  output version information and exit"
  echo
  echo "Examples:"
  echo "  $SCRIPT_NAME -h"
  echo "  $SCRIPT_NAME -v"
  echo "  $SCRIPT_NAME"
  echo
  echo "Report bugs to: Achraf El Khnissi <achraf.elkhnissi@gmail.com>"
}

function print_version() {
  echo "$SCRIPT_NAME 1.0"
}

function print_error() {
  echo -e "${RED_COLOR}ERROR: $1 ${END}"
}

function print_warning() {
  echo -e "${YELLOW}WARNING: $1 ${END}"
}

function print_info() {
  echo -e "${PURPLE}INFO: $1 ${END}"
}

function print_success() {
  echo -e "${GREEN}SUCCESS: $1 ${END}"
}

function print_debug() {
  echo -e "${BLUE}DEBUG: $1 ${END}"
}

function print_cyan() {
  echo -e "${CYAN}$1${END}"
}

function install_git() {
  printf "do you want to install it? [y/n]: "
  read -r input
  answer=$(echo "$input" | tr '[:upper:]' '[:lower:]')

  answer=${answer:0:1}
  echo "answer: $answer"
  if [ "$answer" = "y" ]; then
    print_info "installing git"
    sudo apt-get install git
  fi
}

function exit_with_error() {
  print_error "$1"
  exit 1
}

# Check if the script is run as root
#if [ "$EUID" -ne 0 ]; then
#  print_error "Please run as root"
#  exit 1
#fi

## Check if the command git is installed
if ! command -v git $> /dev/null; then
  print_warning "git is not installed"
  install_git # install git
fi


# -h, --help
if [ "$1" = "-h" ] || [ "$1" = "--help" ]; then
  print_usage
  exit 0
elif [ "$1" = "-v" ] || [ "$1" = "--version" ]; then
  print_version
  exit 0
fi

# Clone the repository
git clone https://github.com/achrafelkhnissi/alx-checker.git || \
  exit_with_error "Failed to clone the repository"

# cd into the repository
cd alx-checker &> /dev/null || \
  exit_with_error "Failed to cd into the repository"

# Make
if make; then
  print_success "alx-checker installed successfully"
else
  exit_with_error "Failed to install alx-checker"
fi

# Copy the script to /usr/local/bin
sudo cp alx-checker /usr/bin || \
  exit_with_error "Failed to copy the script to /usr/local/bin"






