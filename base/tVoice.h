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
/*!\file    rrlib/speech_synthesis/base/tVoice.h
 *
 * \author  Tobias Föhst
 *
 * \date    2013-07-26
 *
 * \brief   Contains tVoice
 *
 * \b tVoice
 *
 * Abstract class for voices. Voices are basically the interfaces to specific text-to-speech-libraries.
 *
 */
//----------------------------------------------------------------------
#ifndef __rrlib__speech_synthesis__include_guard__
#error Invalid include directive. Try #include "rrlib/speech_synthesis/voices.h" instead.
#endif

#ifndef __rrlib__speech_synthesis__base__tVoice_h__
#define __rrlib__speech_synthesis__base__tVoice_h__

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "rrlib/design_patterns/singleton.h"

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

//----------------------------------------------------------------------
// Class declaration
//----------------------------------------------------------------------
//! SHORT_DESCRIPTION
/*!
 * Abstract class for voices. Voices are basically the interfaces to specific text-to-speech-libraries.
 */
class tVoice
{

  struct tMessageProcessorImplementation
  {
    struct tMessage
    {
      tVoice *voice;
      std::string text;
    };

    tMessageProcessorImplementation();

    ~tMessageProcessorImplementation();

    std::vector<tMessage> message_buffer;
    std::vector<tMessage>::iterator writer;
    std::vector<tMessage>::const_iterator reader;
    bool message_buffer_overrun_on_next_write;

    std::mutex message_buffer_mutex;
    std::condition_variable message_buffer_empty;

    bool run_processing_thread;
    std::thread processing_thread;

    void AddMessage(tVoice *voice, const std::string &text);
    static void ProcessMessages(tMessageProcessorImplementation *processor);
  };

  typedef design_patterns::tSingletonHolder<tMessageProcessorImplementation, design_patterns::singleton::Longevity> tMessageProcessor;
  friend unsigned int GetLongevity(tMessageProcessorImplementation *);

//----------------------------------------------------------------------
// Public methods and typedefs
//----------------------------------------------------------------------
public:

  virtual ~tVoice();

  void Say(const std::string &text);

//----------------------------------------------------------------------
// Private fields and methods
//----------------------------------------------------------------------
private:

  virtual void OutputText(const std::string &text) = 0;

};

//----------------------------------------------------------------------
// Function declarations
//----------------------------------------------------------------------
inline unsigned int GetLongevity(tVoice::tMessageProcessorImplementation *)
{
  return 0xFFFFFFFF;
}

//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}


#endif
