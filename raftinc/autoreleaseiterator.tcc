/**
 * autoreleaseiterator.tcc - 
 * @author: Jonathan Beard
 * @version: Thu Jul  2 12:26:23 2020
 * 
 * Copyright 2020 Jonathan Beard
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef AUTORELEASEITERATOR_TCC
#define AUTORELEASEITERATOR_TCC  1

#include <iterator>

//TODO, add enable_if to sensure AUTORELEASE object inherits from 
//autorelease


/**
 * PLAN: 
 * constructor takes in: FIFO object, queue, 
 * n_items, basically most of the things that
 * the autorelease object has, we can't use the
 * [] overload b/c of the exception, but...
 * we can use the rest of the info directly. 
 * 
 * NOTE: we'll also need to pass through 
 * a way to keep the queue tied up while
 * the iterators still exist, i.e., we can't
 * recycle till we destruct these, meaning
 * they extend the ref-count of the parent
 * autorelease object.
 * 
 * Iterator ret val will be a std::pair, 
 * the first value must be the q value
 * the second is the signal so it'll work
 * with things like std::sort for in-place
 * sort. We'll also need to figure out how
 * to return a std::pair ref :). 
 */

template < class T > class autorelease_iterator : 
    public std::iterator< std::forward_iterator_tag, AUTORELASE_OBJECT::self_type >
{

public:
   explicit autorelease_iterator( ) 
   
   autorelease_iterator( portmap_t * port_map, std::size_t index );

   autorelease_iterator& operator++() ;
   
   bool operator==(const autorelease_iterator& rhs) const; 
   bool operator!=(const autorelease_iterator& rhs) const;
   
   FIFO& operator*() const;
   
   const std::string& name() const;

private:
   using map_iterator_type = std::decay_t<decltype(begin(portmap_t::map))>;

};

#endif /* END AUTORELEASEITERATOR_TCC */
