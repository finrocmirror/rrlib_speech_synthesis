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
/*!\file    rrlib/speech_synthesis/base/tVoice.cpp
 *
 * \author  Tobias Föhst
 *
 * \date    2013-07-26
 *
 */
//----------------------------------------------------------------------
#define __rrlib__speech_synthesis__include_guard__
#include "rrlib/speech_synthesis/base/tVoice.h"

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------
#include "rrlib/logging/messages.h"

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
const unsigned int cMESSAGE_BUFFER_LENGTH = 64;

//----------------------------------------------------------------------
// Implementation
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// tVoice destructor
//----------------------------------------------------------------------
tVoice::~tVoice()
{}

//----------------------------------------------------------------------
// tVoice Say
//----------------------------------------------------------------------
void tVoice::Say(const std::string &text)
{
  tMessageProcessor::Instance().AddMessage(this, text);
}

//----------------------------------------------------------------------
// tVoice::tMessageProcessorImplementation constructors
//----------------------------------------------------------------------
tVoice::tMessageProcessorImplementation::tMessageProcessorImplementation() :
  message_buffer(cMESSAGE_BUFFER_LENGTH),
  writer(message_buffer.begin()),
  reader(writer),
  message_buffer_overrun_on_next_write(false),
  run_processing_thread(true),
  processing_thread(ProcessMessages, this)
{
  RRLIB_LOG_PRINT(DEBUG, "Started thread");
}

//----------------------------------------------------------------------
// tVoice::tMessageProcessorImplementation destructor
//----------------------------------------------------------------------
tVoice::tMessageProcessorImplementation::~tMessageProcessorImplementation()
{
  RRLIB_LOG_PRINT(DEBUG, "Stopping thread");
  this->run_processing_thread = false;
  this->message_buffer_empty.notify_all();
  this->processing_thread.join();
}

//----------------------------------------------------------------------
// tVoice::tMessageProcessorImplementation AddMessage
//----------------------------------------------------------------------
void tVoice::tMessageProcessorImplementation::AddMessage(tVoice *voice, const std::string &text)
{
  RRLIB_LOG_PRINT(DEBUG_VERBOSE_3, "Trying to acquiring lock");
  std::unique_lock<std::mutex> message_buffer_lock(this->message_buffer_mutex);
  RRLIB_LOG_PRINT(DEBUG_VERBOSE_3, "Acquired lock");

  tMessage message{voice, text};
  if (this->message_buffer_overrun_on_next_write)
  {
    message.text = "Lost messages";
  }

  RRLIB_LOG_PRINT(DEBUG_VERBOSE_1, "Adding '", text, "' to message buffer");
  *this->writer = message;
  std::advance(this->writer, 1);
  if (this->writer == this->message_buffer.end())
  {
    this->writer = this->message_buffer.begin();
  }
  if (this->writer == this->reader)
  {
    this->message_buffer_overrun_on_next_write = true;
  }

  RRLIB_LOG_PRINT(DEBUG_VERBOSE_2, "Notifying processing thread");
  this->message_buffer_empty.notify_all();

  RRLIB_LOG_PRINT(DEBUG_VERBOSE_3, "Yielding");
  std::this_thread::yield();
}

//----------------------------------------------------------------------
// tVoice::tMessageProcessorImplementation ProcessMessages
//----------------------------------------------------------------------
void tVoice::tMessageProcessorImplementation::ProcessMessages(tMessageProcessorImplementation *processor)
{
  while (processor->run_processing_thread)
  {
    tMessage message;

    {
      RRLIB_LOG_PRINT(DEBUG_VERBOSE_3, "Trying to acquiring lock");
      std::unique_lock<std::mutex> message_buffer_lock(processor->message_buffer_mutex);
      RRLIB_LOG_PRINT(DEBUG_VERBOSE_3, "Acquired lock");
      while (processor->run_processing_thread && processor->reader == processor->writer)
      {
        RRLIB_LOG_PRINT(DEBUG_VERBOSE_2, "Buffer empty -> going to sleep");
        processor->message_buffer_empty.wait(message_buffer_lock);
        RRLIB_LOG_PRINT(DEBUG_VERBOSE_2, "Waking up");
      }

      if (!processor->run_processing_thread)
      {
        continue;
      }

      RRLIB_LOG_PRINT(DEBUG_VERBOSE_2, "Found message");
      message = *processor->reader;
      std::advance(processor->reader, 1);
      if (processor->reader == processor->message_buffer.end())
      {
        processor->reader = processor->message_buffer.begin();
      }
      processor->message_buffer_overrun_on_next_write = false;

      RRLIB_LOG_PRINT(DEBUG_VERBOSE_3, "Releasing lock");
    }

    RRLIB_LOG_PRINT(DEBUG_VERBOSE_1, "Saying '", message.text, "'");
    message.voice->OutputText(message.text);

    RRLIB_LOG_PRINT(DEBUG_VERBOSE_3, "Yielding");
    std::this_thread::yield();
  }
}


//----------------------------------------------------------------------
// End of namespace declaration
//----------------------------------------------------------------------
}
}
