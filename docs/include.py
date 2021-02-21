
# Replace |br| with line break
rst_prolog = r'''
.. |br| raw:: html

   <br/>
'''
# Start overview (collapsible section with the summary 'Overview')
rst_prolog += r'''
.. |startovw| raw:: html

   <details><summary><a><b> Pregled </b></a></summary><br/>
'''
# Start example (collapsible section with the summary 'Example')
rst_prolog += r'''
.. |startexample| raw:: html

   <details><summary><a><b> Primjer </b></a></summary><br/>
'''
# End collapsible section
rst_prolog += r'''
.. |endcollapse| raw:: html

   </details>
'''
