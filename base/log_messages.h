//
// You received this file as part of RRLib
// Robotics Research Library
//
// Copyright (C) Finroc GbR (finroc.org)
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//
//----------------------------------------------------------------------
/*!\file    rrlib/speech_synthesis/log_messages.h
 *
 * \author  Tobias Föhst
 *
 * \date    2013-08-07
 *
 * As this speech synthesis library itself is used by rrlib-logging, it
 * can not use the normal RRLIB_LOG_ macros. The declarations would be
 * valid, but as the logging sink for speech synthesis must be linked
 * via the central rrlib_logging library, a cyclic dependency would be
 * created. As long as this is invalid, rrlib_logging can not be used.
 *
 * Instead, a simplified variant of the rrlib_logging macros is provided
 * for internal use, without domains and with compile-time hardcoded max
 * logging level.
 *
 * However, that way debugging the speech system via itself is stricly
 * avoided.
 *
 */
//----------------------------------------------------------------------
#ifndef __rrlib__speech_synthesis__include_guard__
#error Invalid include directive. Try #include "rrlib/speech_synthesis/voices.h" instead.
#endif

#ifndef __rrlib__speech_synthesis__base__log_messages_h__
#define __rrlib__speech_synthesis__base__log_messages_h__

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------
#include <iostream>

#define __rrlib__logging__include_guard__

#include "rrlib/logging/log_levels.h"

#undef __rrlib__logging__include_guard__

//----------------------------------------------------------------------
// Internal includes with ""
//----------------------------------------------------------------------


//----------------------------------------------------------------------
// Namespace declaration
//----------------------------------------------------------------------
namespace rrlib
{
namespace speech_synthesis
{

//----------------------------------------------------------------------
// Forward declarations / typedefs / enums
//----------------------------------------------------------------------

#ifdef RRLIB_LOGGING_LESS_OUTPUT
#define MAX_MESSAGE_LEVEL DEBUG
#else
#define MAX_MESSAGE_LEVEL WARNING
#endif

namespace logging
{

template <typename THead>
void SendDataToStream(std::ostream &stream, const THead &head)
{
  stream << head;
}

template <typename THead, typename ... TTail>
void SendDataToStream(std::ostream &stream, const THead &head, const TTail &... tail)
{
  stream << head;
  SendDataToStream(stream, tail...);
}

}

//----------------------------------------------------------------------
// Macros for internal use
//----------------------------------------------------------------------
#define __EXPAND_LEVEL__(level) rrlib::logging::tLogLevel::level

#define __LOG_PRINT__(level, args...) \
  do \
  { \
    if ((level) <= __EXPAND_LEVEL__(MAX_MESSAGE_LEVEL)) \
    { \
      std::cout << "speech_synthesis" << "::" << __FUNCTION__ << " [" << __FILE__ << ":" << __LINE__ << "] >> "; \
      rrlib::speech_synthesis::logging::SendDataToStream(std::cout, args); \
      std::cout << std::endl; \
    } \
  } while(0) \
     
//----------------------------------------------------------------------
// Simple variant of the rrlib_logging macro interface
//----------------------------------------------------------------------
#ifdef RRLIB_LOGGING_LESS_OUTPUT

/*! Macro to print messages using stream semantics
 *
 * \param level    The level of the message
 * \param args     The data to be put into the underlying stream
 */
#define LOG_PRINT(level, args...) \
  do \
  { \
    if ((__EXPAND_LEVEL__(level)) <= rrlib::logging::tLogLevel::DEBUG) \
    { \
      __LOG_PRINT__(__EXPAND_LEVEL__(level), args); \
    } \
  } while (0) \
     
#else

/*! Macro to print messages using stream semantics
 *
 * \param level    The level of the message
 * \param args     The data to be put into the underlying stream
 */
#define LOG_PRINT(level, args...) \
  __LOG_PRINT__(__EXPAND_LEVEL__(level), args) \
   
#endif

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}


#endif
