==========
vmod_types
==========

--------------------
Varnish Types Module
--------------------

:Date: 2016-04-05
:Version: 1.0
:Manual section: 3


SYNOPSIS
========

import types;


DESCRIPTION
===========

Implements various object types.


FUNCTIONS
=========

string
------

Prototype
	::

		string(STRING s)
Return value
	OBJECT
Description
	Creates a new string object with value s.
Example
	::

		new str = types.string("This is a string!");

(string).value
--------------

Prototype
	::

		.value()
Return value
	STRING
Description
	Gets the string value of a string object
Example
	::

		new str = types.string("This is a string!");
		set resp.http.X-str = str.value();

(string).length
---------------

Prototype
	::

		.length()
Return value
	INT
Description
	Gets the length of the string objects value
Example
	::

		new str = types.string("This is a string!");
		if (str.length() == 17) {
			//str has a length of 17
		}


USAGE EXAMPLE
=============

In your VCL you could then use this vmod along the following lines::

	import types;

	sub vcl_init {
		new s = types.string("Hello!");
	}

	sub vcl_deliver {
		set resp.http.s = s.value();
		set resp.http.s_len = s.length() + 0;
	}


INSTALLATION
============

The source tree is based on autotools to configure the building, and
does also have the necessary bits in place to do functional unit tests
using the ``varnishtest`` tool.

Building requires the Varnish header files and uses pkg-config to find
the necessary paths.

Pre-requisites::

 sudo apt-get install -y autotools-dev make automake libtool pkg-config libvarnishapi1 libvarnishapi-dev

Usage::

 ./autogen.sh
 ./configure

If you have installed Varnish to a non-standard directory, call
``autogen.sh`` and ``configure`` with ``PKG_CONFIG_PATH`` pointing to
the appropriate path. For types, when varnishd configure was called
with ``--prefix=$PREFIX``, use

 PKG_CONFIG_PATH=${PREFIX}/lib/pkgconfig
 export PKG_CONFIG_PATH

Make targets:

* make - builds the vmod.
* make install - installs your vmod.
* make check - runs the unit tests in ``src/tests/*.vtc``
* make distcheck - run check and prepare a tarball of the vmod.

Installation directories
------------------------

By default, the vmod ``configure`` script installs the built vmod in
the same directory as Varnish, determined via ``pkg-config(1)``. The
vmod installation directory can be overridden by passing the
``VMOD_DIR`` variable to ``configure``.

Other files like man-pages and documentation are installed in the
locations determined by ``configure``, which inherits its default
``--prefix`` setting from Varnish.
