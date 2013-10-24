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
/*!\file    rrlib/speech_synthesis/festival/tFestival.h
 *
 * \author  Tobias Föhst
 *
 * \date    2013-07-26
 *
 * \brief   Contains tFestival
 *
 * \b tFestival
 *
 * Interface to the festival text-to-speech library
 *
 */
//----------------------------------------------------------------------
#ifndef __rrlib__speech_synthesis__include_guard__
#error Invalid include directive. Try #include "rrlib/speech_synthesis/voices.h" instead.
#endif

#ifndef __rrlib__speech_synthesis__festival__tFestival_h__
#define __rrlib__speech_synthesis__festival__tFestival_h__

#include "rrlib/speech_synthesis/base/tVoice.h"

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------

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
namespace festival
{

//----------------------------------------------------------------------
// Forward declarations / typedefs / enums
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Class declaration
//----------------------------------------------------------------------
//! SHORT_DESCRIPTION
/*!
 * Interface to the festival text-to-speech library
 *
 */
class tFestival : public tVoice
{

//----------------------------------------------------------------------
// Public methods and typedefs
//----------------------------------------------------------------------
public:

  tFestival(const std::string &voice);

  //----------------------------------------------------------------------
// Private fields and methods
//----------------------------------------------------------------------
private:

  const std::string voice_command;

  virtual void OutputText(const std::string &text);

};

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}
}


#endif
