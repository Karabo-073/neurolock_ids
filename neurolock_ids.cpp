#include <pcap.h>
#include <iostream>
#include <arpa/inet.h>        // For inet_ntoa, inet_addr
#include <netinet/ip.h>       // For IP header
#include <netinet/tcp.h>      // For TCP header
#include <netinet/if_ether.h> // For Ethernet header
#include <map>
#include <set>
#include <fstream>
#include <cstring>

// ===== GLOBAL STRUCTURES =====
std::map<std::string, std::set<int>> portScanTracker;
std::map<std::string, int> icmpTracker;
std::ofstream logFile("alerts.log");

// ===== ALERT FUNCTION =====
void logAlert(const std::string& msg) {
    std::cout << msg << std::endl;
    logFile << msg << std::endl;
}

// ===== PORT SCAN DETECTION =====
void detectPortScan(const std::string& srcIP, int port) {
    portScanTracker[srcIP].insert(port);
    if (portScanTracker[srcIP].size() > 10) {
        logAlert("[ALERT] Port scan detected from " + srcIP);
    }
}

// ===== ICMP FLOOD DETECTION =====
void detectICMP(const std::string& srcIP) {
    icmpTracker[srcIP]++;
    if (icmpTracker[srcIP] > 50) {
        logAlert("[ALERT] ICMP Flood detected from " + srcIP);
    }
}

// ===== PAYLOAD INSPECTION =====
void inspectPayload(const u_char* payload, int size) {
    std::string data((char*)payload, size);
    if (data.find("password") != std::string::npos ||
        data.find("admin") != std::string::npos ||
        data.find("SELECT") != std::string::npos) {
        logAlert("[ALERT] Suspicious payload detected!");
    }
}

// ===== PACKET HANDLER =====
void packetHandler(u_char *, const struct pcap_pkthdr *pkthdr, const u_char *packet) {

    if (pkthdr->len < sizeof(struct ether_header))
        return;

    struct ether_header *eth = (struct ether_header *)packet;

    if (ntohs(eth->ether_type) != ETHERTYPE_IP)
        return;

    struct ip *ipHeader = (struct ip*)(packet + sizeof(struct ether_header));

    std::string srcIP = inet_ntoa(ipHeader->ip_src);
    std::string dstIP = inet_ntoa(ipHeader->ip_dst);

    std::cout << "[+] " << srcIP << " -> " << dstIP << std::endl;

    // TCP packets
    if (ipHeader->ip_p == IPPROTO_TCP) {
        int ipHeaderLen = ipHeader->ip_hl * 4;
        struct tcphdr *tcpHeader = (struct tcphdr*)(packet + sizeof(struct ether_header) + ipHeaderLen);
        int destPort = ntohs(tcpHeader->dest);

        detectPortScan(srcIP, destPort);

        int tcpHeaderLen = tcpHeader->doff * 4;
        const u_char *payload = packet + sizeof(struct ether_header) + ipHeaderLen + tcpHeaderLen;
        int payloadSize = pkthdr->len - (sizeof(struct ether_header) + ipHeaderLen + tcpHeaderLen);

        if (payloadSize > 0) {
            inspectPayload(payload, payloadSize);
        }
    }

    // ICMP packets
    else if (ipHeader->ip_p == IPPROTO_ICMP) {
        detectICMP(srcIP);
    }
}

// ===== MAIN =====
int main() {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_if_t *alldevs;

    if (pcap_findalldevs(&alldevs, errbuf) == -1) {
        std::cerr << "Error finding devices: " << errbuf << std::endl;
        return 1;
    }

    pcap_if_t *device = alldevs;
    std::cout << "Using device: " << device->name << std::endl;

    pcap_t *handle = pcap_open_live(device->name, 65536, 1, 1000, errbuf);
    if (!handle) {
        std::cerr << "Could not open device: " << errbuf << std::endl;
        return 1;
    }

    struct bpf_program filter;
    bpf_u_int32 net = 0;

    if (pcap_compile(handle, &filter, "tcp or icmp", 0, net) == -1) {
        std::cerr << "Error compiling filter" << std::endl;
        return 1;
    }
    if (pcap_setfilter(handle, &filter) == -1) {
        std::cerr << "Error setting filter" << std::endl;
        return 1;
    }

    std::cout << "[*] NeuroLock IDS Running...\n";
    pcap_loop(handle, 0, packetHandler, nullptr);

    pcap_close(handle);
    logFile.close();
    return 0;
}