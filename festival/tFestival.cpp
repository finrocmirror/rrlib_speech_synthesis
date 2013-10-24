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
/*!\file    rrlib/speech_synthesis/festival/tFestival.cpp
 *
 * \author  Tobias Föhst
 *
 * \date    2013-07-26
 *
 */
//----------------------------------------------------------------------
#define __rrlib__speech_synthesis__include_guard__
#include "rrlib/speech_synthesis/festival/tFestival.h"

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------
#include <map>
#include <tuple>

#include <festival.h>

//----------------------------------------------------------------------
// Internal includes with ""
//----------------------------------------------------------------------
#include "rrlib/speech_synthesis/base/log_messages.h"

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
namespace festival
{

//----------------------------------------------------------------------
// Forward declarations / typedefs / enums
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Const values
//----------------------------------------------------------------------
const int cHEAP_SIZE = 2100000;

//----------------------------------------------------------------------
// Implementation
//----------------------------------------------------------------------

namespace
{

//----------------------------------------------------------------------
// InititalizeFestival
//----------------------------------------------------------------------
void InititalizeIfNeeded()
{
  static bool initialized = false;
  if (initialized)
  {
    return;
  }

  LOG_PRINT(DEBUG, "Initializing festival");

  festival_initialize(1, cHEAP_SIZE);
  initialized = true;
}

}

//----------------------------------------------------------------------
// tFestival constructors
//----------------------------------------------------------------------
tFestival::tFestival(const std::string &voice) :
  voice_command("(voice_" + voice + ")")
{}

//----------------------------------------------------------------------
// tFestival OutputText
//----------------------------------------------------------------------
void tFestival::OutputText(const std::string &text)
{
  InititalizeIfNeeded();
  if (!festival_eval_command(this->voice_command.c_str()))
  {
    LOG_PRINT(ERROR, "Could not evaluate voice command '", voice_command, "'");
    return;
  }
  if (!festival_say_text(text.c_str()))
  {
    LOG_PRINT(ERROR, "Speech synthesis failed.");
  }
}

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}
}
