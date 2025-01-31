#pragma once

/**
  * Floating-point precision defaults to single but can be made double via
    <tt><b>#define _float_t double</b></tt> before <tt>#include <tinyekf.h></tt>
  */
#ifndef _float_t
#define _float_t float
#endif