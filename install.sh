#
# @brief  This script install the project
# @usage  sudo sh install
# @author Achraf El Khnissi <achraf.elkhnissi@gmail.com>
# @date   Sunday, 5 March, 2023
#

# declare global variables
declare -x SCRIPT_NAME=$(basename "$0")
declare -x SCRIPT_DIR=$(cd "$(dirname "$0")" && pwd)
declare -x SCRIPT_PATH="$SCRIPT_DIR/$SCRIPT_NAME"
declare -x SCRIPT_VERSION="1.0"

declare -x SCRIPT_ARGS="$@"
declare -x SCRIPT_ARGS_COUNT="$#"
declare -x SCRIPT_ARGS_ARRAY=("$@")
declare -x SCRIPT_ARGS_ARRAY_COUNT="${#SCRIPT_ARGS_ARRAY[@]}"
declare -x SCRIPT_ARGS_ARRAY_FIRST="${SCRIPT_ARGS_ARRAY[0]}"

declare -x ALX_CHECKER_DIR="$HOME/.alx-checker"

declare -x YELLOW="\033[1;93m"
declare -x PURPLE="\033[0;95m"
declare -x RED="\033[31m"
declare -x BLUE='\033[0;34m'
declare -x CYAN='\033[0;36m'
declare -x GREEN="\033[0;92m"
declare -x END="\033[0m" # No Color

# Styles
declare -x BOLD="\033[1m"
declare -x UNDERLINE="\033[4m"
declare -x BLINK="\033[5m"
declare -x REVERSE="\033[7m"
declare -x HIDDEN="\033[8m"
declare -x CROSS="\033[9m"

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
  echo "${RED}ERROR: $1 ${END}"
}

function print_warning() {
  echo "${YELLOW}WARNING: $1 ${END}"
}

function print_info() {
  echo "${PURPLE}INFO: $1 ${END}"
}

function print_success() {
  echo "${GREEN}SUCCESS: $1 ${END}"
}

function print_debug() {
  echo "${BLUE}DEBUG: $1 ${END}"
}

# check if the project is installed
if command -v alx-checker &>/dev/null; then
  print_info "alx-checker is already installed, Please run 'alx-checker --update' to check for updates"
  exit 1
fi

echo ; echo "${CYAN}${BOLD}${UNDERLINE}INSTALLING ALX CHECKER.. ${END}" ; echo

# check if betty is installed
if ! command -v betty &>/dev/null && [ "$EUID" -ne 0 ]; then
  print_error "Please run as root in order to install Betty"
  exit 1
fi

# clone the project
print_info "Cloning the project..."
git clone https://github.com/achrafelkhnissi/alx-checker.git "${ALX_CHECKER_DIR}"

# Check if the project is cloned
if [ ! -d "${ALX_CHECKER_DIR}" ]; then
  print_error "Failed to clone the project"
  exit 1
fi

# check which shell is used
if [ -n "$ZSH_VERSION" ]; then
  SHELL="zsh"
elif [ -n "$BASH_VERSION" ]; then
  SHELL="bash"
else
  print_error "Unsupported shell"
  exit 1
fi

# add project bin to the PATH
print_info "Adding project bin to the PATH..."
echo "export PATH=\$PATH:~/.alx-checker/bin" >>~/.${SHELL}rc

# build the project with cmake
print_info "Building the project..."
if ! cmake -S ~/.alx-checker -B ~/.alx-checker/build; then
  print_error "Failed to build the project"
  exit 1
fi

print_success "The project is installed successfully"
