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
/*!\file    rrlib/speech_synthesis/voices.cpp
 *
 * \author  Tobias Föhst
 *
 * \date    2013-07-26
 *
 */
//----------------------------------------------------------------------
#include "rrlib/speech_synthesis/voices.h"

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Internal includes with ""
//----------------------------------------------------------------------

#define __rrlib__speech_synthesis__include_guard__

#ifdef _LIB_RRLIB_SPEECH_SYNTHESIS_FESTIVAL_PRESENT_
#include "rrlib/speech_synthesis/festival/tFestival.h"
#endif

#ifdef _LIB_RRLIB_SPEECH_SYNTHESIS_ESPEAK_PRESENT_
#include "rrlib/speech_synthesis/espeak/tESpeak.h"
#endif

//----------------------------------------------------------------------
// Debugging
//----------------------------------------------------------------------
#include <cassert>

//----------------------------------------------------------------------
// Namespace usage
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

//----------------------------------------------------------------------
// Const values
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Implementation
//----------------------------------------------------------------------

namespace
{

int RegisterVoices()
{

#ifdef _LIB_RRLIB_SPEECH_SYNTHESIS_FESTIVAL_PRESENT_
  tVoiceFactory::Instance().Register<festival::tFestival>("festival");
#endif

#ifdef _LIB_RRLIB_SPEECH_SYNTHESIS_ESPEAK_PRESENT_
  tVoiceFactory::Instance().Register<espeak::tESpeak>("espeak");
#endif

  return 0;
}
int cVOICES(RegisterVoices());

}

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}
