# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

# Directories
SRCDIR = src
INCDIR = include
BUILDDIR = build
BINDIR = bin

# Target executable names
TARGET_DEBUG = $(BINDIR)/wifi_simulator_debug
TARGET_RELEASE = $(BINDIR)/wifi_simulator_release

# Source files
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SRCS))

# Default target
all: debug release

# Debug build
debug: CXXFLAGS += -g
debug: $(TARGET_DEBUG)

# Release build
release: CXXFLAGS += -O3
release: $(TARGET_RELEASE)

# Create build and bin directories if they don't exist
$(BUILDDIR):
	@if not exist $(BUILDDIR) mkdir $(BUILDDIR)

$(BINDIR):
	@if not exist $(BINDIR) mkdir $(BINDIR)

# Compile each source file into an object file
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link object files into the debug executable
$(TARGET_DEBUG): $(OBJS) | $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Link object files into the release executable
$(TARGET_RELEASE): $(OBJS) | $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Clean build and binary files
clean:
	@if exist $(BUILDDIR) rmdir /s /q $(BUILDDIR)
	@if exist $(BINDIR) rmdir /s /q $(BINDIR)

# Rebuild everything
rebuild: clean all
