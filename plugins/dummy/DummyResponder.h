/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 * DummyResponder_h
 * The dummy responder is a simple software RDM responder. It's useful for
 * testing RDM controllers.
 * Copyright (C) 2009 Simon Newton
 */

#ifndef PLUGINS_DUMMY_DUMMYRESPONDER_H_
#define PLUGINS_DUMMY_DUMMYRESPONDER_H_

#include <string>
#include "ola/rdm/RDMControllerInterface.h"
#include "ola/rdm/RDMEnums.h"
#include "ola/rdm/UID.h"
#include "DummyRDMDevice.h"

namespace ola {
namespace plugin {
namespace dummy {

class DummyResponder: public ola::rdm::RDMControllerInterface {
  public:
    DummyResponder(const ola::rdm::UID &uid):
      m_start_address(1),
      m_personality(0),
      m_identify_mode(0),
      m_lamp_strikes(0),
      m_uid(uid),
      m_root_device(ROOT_RDM_DEVICE) {}

    void SendRDMRequest(const ola::rdm::RDMRequest *request,
                        ola::rdm::RDMCallback *callback);

    uint16_t StartAddress() const { return m_start_address; }
    uint16_t Footprint() const {
      return PERSONALITIES[m_personality].footprint;
    }

    const ola::rdm::UID &UID() const { return m_uid; }

  private:
    uint16_t m_start_address;
    uint8_t m_personality;
    uint8_t m_identify_mode;
    uint32_t m_lamp_strikes;
    ola::rdm::UID m_uid;
    DummyRDMDevice m_root_device;

    typedef struct {
      uint16_t footprint;
      const char *description;
    } personality_info;

    static const personality_info PERSONALITIES[];
    static const unsigned int PERSONALITY_COUNT;
};
}  // dummy
}  // plugin
}  // ola
#endif  // PLUGINS_DUMMY_DUMMYRESPONDER_H_
