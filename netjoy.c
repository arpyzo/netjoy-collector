#include <stdio.h>
#include <pcap.h>

char error_buffer[PCAP_ERRBUF_SIZE];

void packet_handler(unsigned char *param, const struct pcap_pkthdr *header, const unsigned char *pkt_data) {
    printf("Processed packet\n");
}

int main() {
    pcap_if_t *nic_list;
    pcap_if_t *nic;
    pcap_t *nic_handle;

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
    
    if ((nic_handle = pcap_create("eth0", error_buffer)) == NULL) {
        printf("Unable to open network adapter!");
        return 1;
    }
    pcap_set_promisc(nic_handle, 1);
    // TODO: set minimum size for capture
    pcap_set_snaplen(nic_handle, 1000);
    pcap_activate(nic_handle);
    
    pcap_loop(nic_handle, -1, packet_handler, NULL);

    return 0;
}