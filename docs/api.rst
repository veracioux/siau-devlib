=================
API dokumentacija
=================

.. toctree::

U ovom odjeljku su prikazane funkcije koje se koriste za interfejs sa programima
koji koriste ovu biblioteku.

Globalni simboli
================

.. rubric:: Datoteka `devlib_global.h`

.. doxygenfile:: devlib_global.h
   :project: devlib

.. admonition:: Napomena

   Simbol ``DEVLIB_EXPORT`` je potrebno staviti ispred deklaracije svake klase i
   funkcije kako bi se biblioteka ispravno kompajlirala i mogla koristiti.

Klasa ``ValueSpec``
===================

.. rubric:: ``#include "data.h"``

.. doxygenclass:: ValueSpec
   :project: devlib

Klasa ``Data``
==============

.. rubric:: ``#include "data.h"``

|startovw|

.. image:: _build/doxygen/html/classData__coll__graph.svg
   :align: center

|endcollapse|

.. doxygenclass:: Data
   :project: devlib

Klasa ``Condition``
===================

.. rubric:: ``#include "function.h"``

|startovw|

.. rubric:: **Dijagram klasa**
.. image:: _build/doxygen/html/classCondition__coll__graph.svg
   :align: center

|endcollapse|

.. doxygenclass:: Condition
   :project: devlib

Klasa ``Function`` i podklase
=============================

.. rubric:: ``#include "function.h"``

|startovw|

.. rubric:: Dijagram klasa
.. image:: _build/doxygen/html/classFunction__inherit__graph.svg
   :align: center

|endcollapse|

.. doxygenclass:: Function
   :project: devlib

|startovw|

.. image:: _build/doxygen/html/classSingleFunction__coll__graph.svg
   :align: center

|endcollapse|

.. doxygenclass:: SingleFunction
   :project: devlib

|startovw|

.. image:: _build/doxygen/html/classMultiFunction__coll__graph.svg
   :align: center

|endcollapse|

.. doxygenclass:: MultiFunction
   :project: devlib

Klasa ``Device``
================

.. rubric:: ``#include "device.h"``

|startovw|

.. image:: _build/doxygen/html/classDevice__coll__graph.svg
   :align: center

|endcollapse|

.. doxygenclass:: Device
   :project: devlib

Funkcije za rad sa JSON
=======================

.. rubric:: ``#include "json.h"``

.. doxygenfile:: json.h
   :project: devlib
