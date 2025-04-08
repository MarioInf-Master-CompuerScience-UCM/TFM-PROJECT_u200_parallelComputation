SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PARENT_DIR="$(dirname "$SCRIPT_DIR")"
ENV_NAME="venv"
ENV_PATH="$PARENT_DIR/$ENV_NAME"

delete_environment() {
    echo "Deleting the existing environment at '$ENV_PATH'..."
    rm -rf "$ENV_PATH"
}


if [ -d "$ENV_PATH" ]; then
    echo "A Python environment already exists at '$ENV_PATH'."
    read -p "Do you want to overwrite the current environment? (y/n): " response
    case "$response" in
        [yY][eE][sS]|[yY])
            delete_environment
            python3 -m venv "$ENV_PATH"
            ;;
        *)
            echo "The environment was not overwritten. Exiting the script."
            exit 0
            ;;
    esac
fi

source "$ENV_PATH/bin/activate"
pip install matplotlib pandas
echo "Python environment created at '$ENV_PATH' and the libraries 'matplotlib' and 'pandas' have been installed."



#INSTALL SUPERUSER DEPENDENCIES
#sudo apt-get update
#sudo apt-get install -y libjsoncpp-dev
#sudo apt-get install -y python3 python3-pip
#sudo apt-get install -y python3-pip
