/*
    File: executables.h
*/

/*
Copyright (c) 2014, Christian E. Schafmeister
 
CLASP is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public
License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.
 
See directory 'clasp/licenses' for full details.
 
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
/* -^- */
#ifndef _core_executables_H //(
#define _core_executables_H

#include <stdio.h>
#include <string>
#include <vector>
#include <set>
#include <clasp/core/foundation.h>
#include <clasp/core/object.h>
//#i n c l u d e "macro.h"
#include <clasp/core/cons.h>
#include <clasp/core/symbol.h>
#include <clasp/core/str.fwd.h>
#include <clasp/core/activationFrame.fwd.h>
#include <clasp/core/package.fwd.h>
#include <clasp/core/evaluator.fwd.h>
#include <clasp/core/lambdaListHandler.fwd.h>
#include <clasp/core/lispDefinitions.h>

namespace core {
extern void handleArgumentHandlingExceptions(Closure_sp);
};


template <>
struct gctools::GCInfo<core::CompiledFunction_O> {
  static bool constexpr NeedsInitialization = false;
  static bool constexpr NeedsFinalization = false;
  static GCInfo_policy constexpr Policy = normal;
};

namespace core {
  SMART(LambdaListHandler);
  SMART(Function);
  class CompiledFunction_O : public Closure_O {
    LISP_CLASS(core, ClPkg, CompiledFunction_O, "CompiledFunction",Closure_O);

#if defined(XML_ARCHIVE)
    void archiveBase(ArchiveP node);
#endif // defined(XML_ARCHIVE)
  public:
  CompiledFunction_O(T_sp name) : Base(name){};
    virtual ~CompiledFunction_O(){};

  public:
#if 0
    static CompiledFunction_sp make(Closure_sp c) {
      GC_ALLOCATE(CompiledFunction_O, f);
      ASSERT(c.generalp());
      f->closure = c;
    //            printf("%s:%d Returning CompiledFunction_sp func=%p &f=%p\n", __FILE__, __LINE__, f.px_ref(), &f);
      return f;
    }
#endif
  public:
  };
};
TRANSLATE(core::CompiledFunction_O);

#endif //)
