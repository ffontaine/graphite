/*  GRAPHITE2 LICENSING

    Copyright 2011, SIL International
    All rights reserved.

    This library is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published
    by the Free Software Foundation; either version 2.1 of License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should also have received a copy of the GNU Lesser General Public
    License along with this library in the file named "LICENSE".
    If not, write to the Free Software Foundation, 51 Franklin Street,
    Suite 500, Boston, MA 02110-1335, USA or visit their web page on the
    internet at http://www.fsf.org/licenses/lgpl.html.

Alternatively, the contents of this file may be used under the terms of the
Mozilla Public License (http://mozilla.org/MPL) or the GNU General Public
License, as published by the Free Software Foundation, either version 2
of the License or (at your option) any later version.
*/

#pragma once

#include "inc/Code.h"
#include "inc/SlotMap.h"

namespace graphite2 {

class json;

struct Rule {
  const vm::Machine::Code * constraint,
                 * action;
  unsigned short   sort;
  byte             preContext;
#ifndef NDEBUG
  uint16           rule_idx;
#endif

  Rule();
  ~Rule() {}

  CLASS_NEW_DELETE;

private:
  Rule(const Rule &);
  Rule & operator = (const Rule &);
};

inline
Rule::Rule()
: constraint(0),
  action(0),
  sort(0),
  preContext(0)
{
#ifndef NDEBUG
  rule_idx = 0;
#endif
}


struct RuleEntry
{
  const Rule   * rule;

  inline
  bool operator < (const RuleEntry &r) const
  {
    const unsigned short lsort = rule->sort, rsort = r.rule->sort;
    return lsort > rsort || (lsort == rsort && rule < r.rule);
  }

  inline
  bool operator == (const RuleEntry &r) const
  {
    return rule == r.rule;
  }
};


} // namespace graphite2
