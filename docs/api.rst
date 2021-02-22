=================
API dokumentacija
=================

.. toctree::

U ovom odjeljku su prikazane funkcije koje se koriste za interfejs sa programima
koji koriste ovu biblioteku.

Globalni simboli
================

.. doxygenfile:: devlib_global.h
   :project: devlib

.. admonition:: Napomena

   Simbol ``DEVLIB_EXPORT`` je potrebno staviti ispred deklaracije svake klase i
   funkcije kako bi se biblioteka ispravno kompajlirala i mogla koristiti.

Klasa ``ValueSpec``
===================

.. rubric:: ``#include "devlib/value.h"``

|startovw|

.. image:: _build/doxygen/html/classValueSpec__coll__graph.svg
   :align: center

|endcollapse|

.. tabs::

   .. tab:: Sažetak

      .. doxygenclass:: ValueSpec
         :project: devlib
         :outline:

   .. tab:: Detalji

      .. doxygenclass:: ValueSpec
         :project: devlib

Klasa ``Data``
==============

.. rubric:: ``#include "devlib/data.h"``

|startovw|

.. image:: _build/doxygen/html/classData__coll__graph.svg
   :align: center

|endcollapse|

.. tabs::

   .. tab:: Sažetak

      .. doxygenclass:: Data
         :project: devlib
         :outline:

   .. tab:: Detalji

      .. doxygenclass:: Data
         :project: devlib


Struktura ``Condition``
=======================

.. rubric:: ``#include "devlib/function.h"``

|startovw|

.. rubric:: **Dijagram klasa**
.. image:: _build/doxygen/html/classCondition__coll__graph.svg
   :align: center

|endcollapse|

.. tabs::

   .. tab:: Sažetak

      .. doxygenstruct:: Condition
         :project: devlib
         :outline:

   .. tab:: Detalji

      .. doxygenstruct:: Condition
         :project: devlib

Klasa ``Function`` i podklase
=============================

.. rubric:: ``#include "devlib/function.h"``

|startovw|

.. rubric:: Dijagram klasa
.. image:: _build/doxygen/html/classFunction__inherit__graph.svg
   :align: center

|endcollapse|

.. tabs::

   .. tab:: Sažetak

      .. doxygenclass:: Function
         :project: devlib
         :outline:

   .. tab:: Detalji

      .. doxygenclass:: Function
         :project: devlib
|startovw|

.. image:: _build/doxygen/html/classSingleFunction__coll__graph.svg
   :align: center

|endcollapse|

.. tabs::

   .. tab:: Sažetak

      .. doxygenclass:: SingleFunction
         :project: devlib
         :outline:

   .. tab:: Detalji

      .. doxygenclass:: SingleFunction
         :project: devlib

|startovw|

.. image:: _build/doxygen/html/classMultiFunction__coll__graph.svg
   :align: center

|endcollapse|

.. tabs::

   .. tab:: Sažetak

      .. doxygenclass:: MultiFunction
         :project: devlib
         :outline:

   .. tab:: Detalji

      .. doxygenclass:: MultiFunction
         :project: devlib

Klasa ``Device``
================

.. rubric:: ``#include "devlib/device.h"``

|startovw|

.. image:: _build/doxygen/html/classDevice__coll__graph.svg
   :align: center

|endcollapse|

.. tabs::

   .. tab:: Sažetak

      .. doxygenclass:: Device
         :project: devlib
         :outline:

   .. tab:: Detalji

      .. doxygenclass:: Device
         :project: devlib

Funkcije za rad sa JSON
=======================

.. rubric:: ``#include "devlib/json.h"``

.. tabs::

   .. tab:: Sažetak

      .. doxygenfile:: json.h
         :project: devlib
         :outline:

   .. tab:: Detalji

      .. doxygenfile:: json.h
         :project: devlib
