EXT_NAME = ferret-syntax-theme
EXT_VERSION = 1.0.0
VSIX_FILE = $(EXT_NAME)-$(EXT_VERSION).vsix

.PHONY: all clean build install rebuild

# Default target: build and install
all: build install

# Remove existing .vsix file
clean:
	rm -f $(VSIX_FILE)

# Build the .vsix package using vsce
build: clean
	vsce package

# Install the .vsix package into VS Code
install:
	cursor --install-extension $(VSIX_FILE)

# Clean, build, and install in one go
rebuild: clean build install
