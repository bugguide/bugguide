-- SUMMARY --

The Extensible BBCode provides a BBCode parser that can be extended
with custom tag macros. If you install it on your Drupal site, 
it will create a text format 
named "BBCode" that can generate HTML out of user-entered text markup like this:

    This text is [b]bold[/b] and [i]italic[/i].

Activating the "Basic" submodule will add the most commonly available 
markup tags. Beyond that, it is also possible to create new tags
that either generate static output or use PHP code to determine how
the tag is rendered.

-- REQUIREMENTS --

None. However, the core PHP module must be enabled in order to create
tags that use PHP code.
