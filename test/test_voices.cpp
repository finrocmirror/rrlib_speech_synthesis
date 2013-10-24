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
/*!\file    rrlib/speech_synthesis/test/test_voices.cpp
 *
 * \author  Tobias Föhst
 *
 * \date    2013-07-15
 *
 */
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// External includes (system with <>, local with "")
//----------------------------------------------------------------------

#include <string>
#include <thread>
#include <unistd.h>

//----------------------------------------------------------------------
// Internal includes with ""
//----------------------------------------------------------------------
#include "rrlib/speech_synthesis/voices.h"

//----------------------------------------------------------------------
// Debugging
//----------------------------------------------------------------------
#include <cassert>

//----------------------------------------------------------------------
// Namespace usage
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Forward declarations / typedefs / enums
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Const values
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Implementation
//----------------------------------------------------------------------


void Run()
{
  rrlib::speech_synthesis::tVoice *espeak_default = rrlib::speech_synthesis::tVoiceFactory::Instance().Create("espeak", "default");
  for (unsigned int i = 1; i < 10; ++i)
  {
    std::string text = "Speaking from thread 2: line number " + std::to_string(i);
    espeak_default->Say(text);
    sleep(1);
  }
}


int main(int argc, char* argv[])
{

  rrlib::speech_synthesis::tVoice *festival_kal = rrlib::speech_synthesis::tVoiceFactory::Instance().Create("festival", "kal_diphone");
  rrlib::speech_synthesis::tVoice *festival_don = rrlib::speech_synthesis::tVoiceFactory::Instance().Create("festival", "don_diphone");
  rrlib::speech_synthesis::tVoice *espeak_mb_en1 = rrlib::speech_synthesis::tVoiceFactory::Instance().Create("espeak", "mb-en1");

  std::thread thread2(Run);

  for (unsigned int i = 1; i < 10; ++i)
  {
    std::string text = "Speaking from thread 1: line number " + std::to_string(i);
    festival_kal->Say(text);
    festival_don->Say(text);
    espeak_mb_en1->Say(text);
    sleep(1);
  }

  thread2.join();

  sleep(30);

  return 0;
}
