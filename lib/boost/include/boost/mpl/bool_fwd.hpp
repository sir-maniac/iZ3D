
#ifndef BOOST_MPL_BOOL_FWD_HPP_INCLUDED
#define BOOST_MPL_BOOL_FWD_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id: bool_fwd.hpp 49267 2008-10-11 06:19:02Z agurtovoy $
// $Date: 2008-10-11 10:19:02 +0400 (Ñá, 11 îêò 2008) $
// $Revision: 49267 $

#include <boost/mpl/aux_/adl_barrier.hpp>

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN

template< bool C_ > struct bool_;

// shorcuts
typedef bool_<true> true_;
typedef bool_<false> false_;

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE

BOOST_MPL_AUX_ADL_BARRIER_DECL(bool_)
BOOST_MPL_AUX_ADL_BARRIER_DECL(true_)
BOOST_MPL_AUX_ADL_BARRIER_DECL(false_)

#endif // BOOST_MPL_BOOL_FWD_HPP_INCLUDED
