#pragma once

#include <string>
#include <alsa/asoundlib.h>

#include "../types.hpp"
#include "base.hpp"

namespace midi {

class alsa_device : public device_base
{
public:
  alsa_device(int client_id, int port_id, const char *name)
  : _client_id(client_id), _port_id(port_id), _name(name)
  {}

  const std::string string() const
  {
    return "midi::alsa_device(client_id=" + std::to_string(_client_id) + ", port_id=" + std::to_string(_port_id) + ", name=" + _name + ")";
  }

  const std::string name() const
  {
    return "ALSA: " + _name;
  }

  void open()
  {

  }

  void close()
  {

  }

  size_t read(unsigned char data[])
  {
    return 0;
  }

  static void probe(prober_results &results)
  {
    snd_seq_t *seq;

    /* open sequencer */
    if (snd_seq_open(&seq, "default", SND_SEQ_OPEN_DUPLEX, 0) < 0)
      return;

    /* set our client's name */
    if (snd_seq_set_client_name(seq, "synth") < 0)
      return;

    snd_seq_client_info_t *cinfo;
    snd_seq_port_info_t *pinfo;

    snd_seq_client_info_alloca(&cinfo);
    snd_seq_port_info_alloca(&pinfo);

    snd_seq_client_info_set_client(cinfo, -1);
    while (snd_seq_query_next_client(seq, cinfo) >= 0) {
      int client = snd_seq_client_info_get_client(cinfo);

      snd_seq_port_info_set_client(pinfo, client);
      snd_seq_port_info_set_port(pinfo, -1);
      while (snd_seq_query_next_port(seq, pinfo) >= 0) {
        /* we need both READ and SUBS_READ */
        if ((snd_seq_port_info_get_capability(pinfo)
             & (SND_SEQ_PORT_CAP_READ | SND_SEQ_PORT_CAP_SUBS_READ))
            != (SND_SEQ_PORT_CAP_READ | SND_SEQ_PORT_CAP_SUBS_READ))
                continue;
        results.push_back(std::make_unique<alsa_device>(
          snd_seq_port_info_get_client(pinfo),
          snd_seq_port_info_get_port(pinfo),
          snd_seq_port_info_get_name(pinfo)
        ));
      }
    }
  }

private:
  int _client_id;
  int _port_id;
  std::string _name;

};

}