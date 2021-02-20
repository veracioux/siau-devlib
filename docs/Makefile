
SPHINXOPTS    ?=
SPHINXBUILD   ?= sphinx-build
SOURCEDIR     = .
BUILDDIR      = _build

# Put it first so that "make" without argument is like "make help".
help:
	@$(SPHINXBUILD) -M help "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

.PHONY: help doxygen

html: doxygen
	@$(SPHINXBUILD) -M $@ "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

doxygen:
	mkdir -p _build/doxygen
	@doxygen
	@for file in _build/doxygen/html/class*__inherit__graph.svg; do \
		cp "$$file" "$$(echo "$$file" | sed 's/inherit__graph/inh/')"; \
	done

clean:
	rm -rf _build/
