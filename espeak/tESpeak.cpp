//
// You received this file as part of RRLib
// Robotics Research Library
//
// Copyright (C) Finroc GbR (finroc.org)
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//
//----------------------------------------------------------------------
/*!\file    rrlib/speech_synthesis/espeak/tESpeak.cpp
 *
 * \author  Tobias Föhst
 *
 * \date    2013-07-26
 *
 */
//----------------------------------------------------------------------
#define __rrlib__speech_synthesis__include_guard__
#include "rrlib/speech_synthesis/espeak/tESpeak.h"

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------
#include <map>
#include <tuple>
#include <stdexcept>

#include <speak_lib.h>

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
namespace espeak
{

//----------------------------------------------------------------------
// Forward declarations / typedefs / enums
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Const values
//----------------------------------------------------------------------
const int cBUFFER_LENGTH = 500;

//----------------------------------------------------------------------
// Implementation
//----------------------------------------------------------------------

namespace
{

//----------------------------------------------------------------------
// InititalizeIfNeeded
//----------------------------------------------------------------------
void InititalizeIfNeeded()
{
  static bool initialized = false;
  if (initialized)
  {
    return;
  }

  LOG_PRINT(DEBUG, "Initializing espeak");

  int result = espeak_Initialize(AUDIO_OUTPUT_SYNCH_PLAYBACK, cBUFFER_LENGTH, NULL, 0);

  if (result < 0)
  {
    throw std::runtime_error("Could not initialize espeak speech synthesis");
  }

  LOG_PRINT(DEBUG, "Initialized espeak with sample rate: ", result, " Hz");
  initialized = true;
}

}

//----------------------------------------------------------------------
// tESpeak constructors
//----------------------------------------------------------------------
tESpeak::tESpeak(const std::string &voice) :
  voice(voice)
{}

//----------------------------------------------------------------------
// tESpeak OutputText
//----------------------------------------------------------------------
void tESpeak::OutputText(const std::string &text)
{
  InititalizeIfNeeded();
  espeak_ERROR error = espeak_SetVoiceByName(this->voice.c_str());
  if (error == EE_OK)
  {
    espeak_Synth(text.c_str(), text.length() + 1, 0, POS_CHARACTER, 0, espeakCHARS_AUTO, NULL, NULL);
  }

  switch (error)
  {
  case EE_OK:
    break;
  case EE_INTERNAL_ERROR:
    LOG_PRINT(ERROR, "Speech synthesis failed: internal error");
    break;
  case EE_BUFFER_FULL:
    LOG_PRINT(ERROR, "Speech synthesis failed: buffer full");
    break;
  case EE_NOT_FOUND:
    LOG_PRINT(ERROR, "Speech synthesis failed: not found");
    break;
  }
}

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}
}
