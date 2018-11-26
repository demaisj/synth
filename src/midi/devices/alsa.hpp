#pragma once

#include <cstring>
#include <alsa/asoundlib.h>

#include "../types.hpp"
#include "base.hpp"

namespace midi {

class alsa_device : public device_base
{
public:

  const std::string string() const
  {
    return "midi::alsa_device()";
  }

  const std::string name() const
  {
    return "ALSA RawMIDI: ";
  }

  void open()
  {

  }

  void close()
  {

  }

  static void probe(prober_results &results)
  {
    int card = -1;

    while (snd_card_next(&card) >= 0 && card >= 0) {

      char name[6];
      sprintf(name, "hw:%d", card);

      snd_ctl_t *handle;
      if (snd_ctl_open(&handle, name, 0) != 0) {
        continue;
      }

      snd_ctl_card_info_t *info;
      if (snd_ctl_card_info_malloc(&info) != 0) {
        snd_ctl_close(handle);
        continue;
      }

      if (snd_ctl_card_info(handle, info) != 0) {
        snd_ctl_card_info_free(info);
        snd_ctl_close(handle);
        continue;
      }        printf("Card #%d: id=%s, driver=%s, name=%s, longname=%s, mixername=%s, components=%s\n",
                snd_ctl_card_info_get_card(info),
                snd_ctl_card_info_get_id(info),
                snd_ctl_card_info_get_driver(info),
                snd_ctl_card_info_get_name(info),
                snd_ctl_card_info_get_longname(info),
                snd_ctl_card_info_get_mixername(info),
                snd_ctl_card_info_get_components(info));

      snd_ctl_card_info_free(info);

      snd_ctl_elem_list_t *list;
      if (snd_ctl_elem_list_malloc(&list) != 0) {
        snd_ctl_close(handle);
        continue;
      }

      if (snd_ctl_elem_list(handle, list) != 0) {
        snd_ctl_elem_list_free(list);
        snd_ctl_close(handle);
        continue;
      }

                unsigned int used = snd_ctl_elem_list_get_used(list);
                unsigned int count = snd_ctl_elem_list_get_count(list);
                printf("\tElement used = %d, count = %d.  Allocating space for %d entries...\n", used, count, count);

      if (snd_ctl_elem_list_alloc_space(list, count) != 0) {
        snd_ctl_elem_list_free(list);
        snd_ctl_close(handle);
      }

      if (snd_ctl_elem_list(handle, list) != 0) {
        snd_ctl_elem_list_free(list);
        snd_ctl_close(handle);
        continue;
      }

                used = snd_ctl_elem_list_get_used(list);
                count = snd_ctl_elem_list_get_count(list);
                printf("\tElement used = %d, count = %d\n", used, count);

      for (unsigned int i = 0; i < used; i++) {
        printf("\tElement #%d: numid=%d, interface=%s, device=%d, subdevice=%d, name=%s, index=%d, elem_id follows:\n",
                i,
                snd_ctl_elem_list_get_numid(list, i),
                snd_ctl_elem_iface_name(snd_ctl_elem_list_get_interface(list, i)),
                snd_ctl_elem_list_get_device(list, i),
                snd_ctl_elem_list_get_subdevice(list, i),
                snd_ctl_elem_list_get_name(list, i),
                snd_ctl_elem_list_get_index(list, i));
snd_ctl_elem_id_t *id;
        if (snd_ctl_elem_id_malloc(&id))
        {
                printf("Error allocating snd_ctl_elem_id_t, aborting\n");
                return;
        }
        snd_ctl_elem_list_get_id(list, i, id);
                printf("\t\telem_id: numid=%d, interface=%s, device=%d, subdevice=%d, name=%s, index=%d\n",
                snd_ctl_elem_id_get_numid(id),
                snd_ctl_elem_iface_name(snd_ctl_elem_id_get_interface(id)),
                snd_ctl_elem_id_get_device(id),
                snd_ctl_elem_id_get_subdevice(id),
                snd_ctl_elem_id_get_name(id),
                snd_ctl_elem_id_get_index(id));
        snd_ctl_elem_id_free(id);
      }

      snd_ctl_elem_list_free_space(list);
      snd_ctl_elem_list_free(list);

      snd_ctl_close(handle);

      printf("\n");

      /*char *name;
      snd_card_get_name(card, &name);
      char *longname;
      snd_card_get_longname(card, &longname);
      std::cout << name << ", " << longname << std::endl;
      free(name);
      free(longname);*/
    }
  }

};

}