/* ES40 emulator.
 * Copyright (C) 2007-2008 by the ES40 Emulator Project
 *
 * WWW    : http://www.es40.org
 * E-mail : camiel@es40.org
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
 * USA.
 *
 * Although this is not required, the author would appreciate being notified of,
 * and receiving any modifications you may make to the source code that might
 * serve the general public.
 *
 * Parts of this file based upon the Poco C++ Libraries, which is Copyright (C)
 * 2004-2006, Applied Informatics Software Engineering GmbH. and Contributors.
 */

/**
 * $Id: ErrorHandler.cpp,v 1.1 2008/05/31 15:47:20 iamcamiel Exp $
 *
 * X-1.1        Camiel Vanderhoeven                             31-MAY-2008
 *      Initial version for ES40 emulator.
 **/

//
// ErrorHandler.cpp
//
// $Id: ErrorHandler.cpp,v 1.1 2008/05/31 15:47:20 iamcamiel Exp $
//
// Library: Foundation
// Package: Threading
// Module:  ErrorHandler
//
// Copyright (c) 2005-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//

#include "ErrorHandler.h"
#include "SingletonHolder.h"

CErrorHandler *CErrorHandler::_pHandler = CErrorHandler::defaultHandler();
CFastMutex CErrorHandler::_mutex;

CErrorHandler::CErrorHandler() {}

CErrorHandler::~CErrorHandler() {}

void CErrorHandler::exception(const CException &exc) {
  poco_debugger_msg(exc.what());
}

void CErrorHandler::exception(const std::exception &exc) {
  poco_debugger_msg(exc.what());
}

void CErrorHandler::exception() { poco_debugger_msg("unknown exception"); }

void CErrorHandler::handle(const CException &exc) {
  CFastMutex::CScopedLock lock(&_mutex);
  try {
    _pHandler->exception(exc);
  } catch (...) {
  }
}

void CErrorHandler::handle(const std::exception &exc) {
  CFastMutex::CScopedLock lock(&_mutex);
  try {
    _pHandler->exception(exc);
  } catch (...) {
  }
}

void CErrorHandler::handle() {
  CFastMutex::CScopedLock lock(&_mutex);
  try {
    _pHandler->exception();
  } catch (...) {
  }
}

CErrorHandler *CErrorHandler::set(CErrorHandler *pHandler) {
  poco_check_ptr(pHandler);

  CFastMutex::CScopedLock lock(&_mutex);
  CErrorHandler *pOld = _pHandler;
  _pHandler = pHandler;
  return pOld;
}

CErrorHandler *CErrorHandler::defaultHandler() {
  static CSingletonHolder<CErrorHandler> sh;
  return sh.get();
}