CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Isrc
TARGET   = lab
SRCDIR   = src
BUILDDIR = build
SOURCES  = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS  = $(addprefix $(BUILDDIR)/, $(notdir $(SOURCES:.cpp=.o)))

$(TARGET): $(OBJECTS) | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILDDIR):
	mkdir -p $@

clean:
	rm -rf $(BUILDDIR) $(TARGET)

.PHONY: clean

TEST_DIR = tests
TEST_FILES = $(wildcard $(TEST_DIR)/*.txt)

.PHONY: test
test: $(TARGET)
	@for file in $(TEST_FILES); do \
		echo "=== $$(basename $$file) ==="; \
		./$(TARGET) $$file; \
		echo "Exit code: $$?"; \
		echo; \
	done
