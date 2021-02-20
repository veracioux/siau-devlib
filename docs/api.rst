=================
API dokumentacija
=================

.. toctree::

Globalni simboli
================

.. doxygenfile:: devlib_global.h
   :project: devlib

.. admonition:: Napomena

   Simbol ``DEVLIB_EXPORT`` je potrebno staviti ispred deklaracije svake klase i
   funkcije kako bi se biblioteka ispravno kompajlirala i mogla koristiti.

Klasa ``ValueSpec``
===================

.. doxygenclass:: ValueSpec
   :project: devlib

Klasa ``Data``
==============

.. include:: /inc/startov.rst
.. image:: _build/doxygen/html/classData__coll__graph.svg
   :align: center

.. include:: /inc/enddetails.rst
.. raw:: html

   <br>

.. doxygenclass:: Data
   :project: devlib

Klasa ``Condition``
===================

.. doxygenclass:: Condition
   :project: devlib

Klasa ``Function``
==================


.. include:: /inc/startov.rst
.. image:: /_build/doxygen/html/classFunction__inh.svg
   :align: center

.. include:: /inc/enddetails.rst
.. raw:: html

   <br>

.. doxygenclass:: Function
   :project: devlib

.. doxygenclass:: SingleFunction
   :project: devlib

.. doxygenclass:: MultiFunction
   :project: devlib

Klasa ``Device``
================

.. doxygenclass:: Device
   :project: devlib

Funkcije za rad sa JSON
=======================

.. doxygenfile:: json.h
   :project: devlib
