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
/*!\file    rrlib/speech_synthesis/base/tVoiceFactory.h
 *
 * \author  Tobias Föhst
 *
 * \date    2013-07-26
 *
 * \brief   Contains tVoiceFactory
 *
 * \b tVoiceFactory
 *
 * Get a concrete voice object from a string describing the text-to-speech system and voice configuration.
 *
 */
//----------------------------------------------------------------------
#ifndef __rrlib__speech_synthesis__include_guard__
#error Invalid include directive. Try #include "rrlib/speech_synthesis/voices.h" instead.
#endif

#ifndef __rrlib__speech_synthesis__base__tVoiceFactory_h__
#define __rrlib__speech_synthesis__base__tVoiceFactory_h__

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------
#include "rrlib/design_patterns/factory.h"
#include "rrlib/design_patterns/singleton.h"

//----------------------------------------------------------------------
// Internal includes with ""
//----------------------------------------------------------------------
#include "rrlib/speech_synthesis/base/tVoice.h"

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
class tVoiceFactoryImplementation;
typedef design_patterns::tSingletonHolder<tVoiceFactoryImplementation> tVoiceFactory;

//----------------------------------------------------------------------
// Class declaration
//----------------------------------------------------------------------
//! SHORT_DESCRIPTION
/*!
 * Get a concrete voice object from a string describing the text-to-speech system and voice configuration.
 */
class tVoiceFactoryImplementation : public design_patterns::tFactory<tVoice, std::string, std::function<tVoice*(const std::string&)>>
{

//----------------------------------------------------------------------
// Public methods and typedefs
//----------------------------------------------------------------------
public:

  ~tVoiceFactoryImplementation();

  tVoice *Create(const std::string &id, const std::string &voice);

//----------------------------------------------------------------------
// Private fields and methods
//----------------------------------------------------------------------
private:

  std::map<std::tuple<std::string, std::string>, tVoice *> voice_registry;

};

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}


#endif
