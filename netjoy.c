#include <stdio.h>
#include <pcap.h>

char error_buffer[PCAP_ERRBUF_SIZE];

int main() {
    pcap_if_t *nic_list;
    pcap_if_t *nic;

    if (pcap_findalldevs(&nic_list, error_buffer) == -1) {
        printf("Failed to retrieve network card list!\n");
        return 1;
    }

    for (nic = nic_list; nic; nic = nic->next) {
        if (nic->name) {
            printf("NIC name: %s\n", nic->name);
        }
        if (nic->description) {
            printf("NIC description: %s\n", nic->description);
        }
    }

    pcap_freealldevs(nic_list);
}
