
#ifndef BOOST_MPL_AS_SEQUENCE_HPP_INCLUDED
#define BOOST_MPL_AS_SEQUENCE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id: as_sequence.hpp 49267 2008-10-11 06:19:02Z agurtovoy $
// $Date: 2008-10-11 10:19:02 +0400 (Ñá, 11 îêò 2008) $
// $Revision: 49267 $

#include <boost/mpl/is_sequence.hpp>
#include <boost/mpl/single_view.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct as_sequence
    : if_< is_sequence<T>, T, single_view<T> >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,as_sequence,(T))
};

BOOST_MPL_AUX_NA_SPEC_NO_ETI(1, as_sequence)

}}

#endif // BOOST_MPL_AS_SEQUENCE_HPP_INCLUDED
