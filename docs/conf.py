# -- Project information -----------------------------------------------------

project = 'devlib'
copyright = '2021, Haris Gušić, Anes Hadžić, Džana Aldžić, Medina Gračo'
author = 'Haris Gušić, Anes Hadžić, Džana Aldžić, Medina Gračo'

# -- General configuration ---------------------------------------------------

extensions = [
        'sphinx.ext.todo', 'breathe'
]

breathe_projects = { "devlib": "_build/doxygen/xml/" }
breathe_default_project = "devlib"
breathe_default_members = ('members', 'protected-members', 'undoc-members')

primary_domain = 'cpp'
highlight_language = 'cpp'

# Add any paths that contain templates here, relative to this directory.
templates_path = ['_templates']

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']

todo_include_todos = True

# -- Options for HTML output -------------------------------------------------

html_theme = 'sphinx_rtd_theme'

html_static_path = ['_static']
