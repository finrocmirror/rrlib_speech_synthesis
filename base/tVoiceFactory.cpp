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
/*!\file    rrlib/speech_synthesis/base/tVoiceFactory.cpp
 *
 * \author  Tobias Föhst
 *
 * \date    2013-07-26
 *
 */
//----------------------------------------------------------------------
#define __rrlib__speech_synthesis__include_guard__
#include "rrlib/speech_synthesis/base/tVoiceFactory.h"

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Internal includes with ""
//----------------------------------------------------------------------

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

//----------------------------------------------------------------------
// tVoiceFactoryImplementation destructor
//----------------------------------------------------------------------
tVoiceFactoryImplementation::~tVoiceFactoryImplementation()
{
  for (auto it = this->voice_registry.begin(); it != this->voice_registry.end(); ++it)
  {
    delete it->second;
  }
}

//----------------------------------------------------------------------
// tVoiceFactoryImplementation Create
//----------------------------------------------------------------------
tVoice *tVoiceFactoryImplementation::Create(const std::string &id, const std::string &voice)
{
  auto key = std::make_tuple(id, voice);
  if (voice_registry.find(key) == voice_registry.end())
  {
    voice_registry.insert(std::make_pair(key, tFactory::Create(id, voice)));
  }
  return voice_registry.find(key)->second;
}

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}
