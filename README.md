<!-- Cybersecurity Portfolio README -->

<div align="center" style="font-family: Arial, sans-serif; line-height: 1.6;">

<u><h1>NeuroLock IDS – Real-Time Network Intrusion Detection System</h1></u>

<br>

This project demonstrates a **real-time Intrusion Detection System (IDS)** built in C++ using libpcap. NeuroLock monitors network traffic, detects port scans, ICMP floods, and suspicious payloads, all in a **safe, controlled environment**. The project showcases professional skills in network security, C++ programming, and practical IDS development for cybersecurity portfolios.

<br><br>

<u><h2>Project Structure (Tree Diagram)</h2></u>

<pre>
NeuroLock_IDS/

│     ├── project_documentation.md
│     └── screenshots/
│          ├── port_scan_alert.png
│          ├── icmp_flood_alert.png
│          └── suspicious_payload_alert.png
│
     ├── tests/
         │     └── test_localhost.sh 
               │
                  └── README.md                    
</pre>

<br>

<u><h2>Key Features</h2></u>

| Feature | Description |
| --- | --- |
| Real-Time Packet Capture | Continuously captures TCP/ICMP packets using libpcap for inspection |
| Port Scan Detection | Alerts when a single IP scans multiple TCP ports in a short time |
| ICMP Flood Detection | Detects high-frequency ICMP traffic indicating potential DoS |
| Payload Inspection | Flags TCP payloads with suspicious keywords (e.g., "admin", "password") |
| Safe Testing (Safe Mode) | Monitors only localhost or selected IPs to avoid scanning external networks |
| Lightweight & Fast | Efficient C++ implementation using maps and sets for low-latency processing |

<br>

<u><h2>How It Works</h2></u>

This IDS monitors network traffic in real-time through three main stages:

<ol>
    <li><strong>Packet Capture:</strong> libpcap captures live TCP/ICMP packets from the network interface.</li>
    <li><strong>Packet Parsing:</strong> 
        <ul>
            <li>Ethernet Header – Checks if the packet is IP traffic</li>
            <li>IP Header – Extracts source/destination IP addresses</li>
            <li>TCP/ICMP Header – Identifies traffic type and port numbers</li>
        </ul>
    </li>
    <li><strong>Detection Logic:</strong>
        <ul>
            <li>Port Scan – Detects repeated connections across multiple ports</li>
            <li>ICMP Flood – Flags sources exceeding a threshold of ICMP packets</li>
            <li>Suspicious Payload – Identifies login or SQL injection-like payloads</li>
        </ul>
    </li>
</ol>

<br>

<u><h2>Testing & Results</h2></u>

| Test Type | Setup / Command | Observed Behavior |
| --- | --- | --- |
| Port Scan Detection | nmap -sT -p 1-9000 127.0.0.1 | IDS triggered alert when multiple ports were accessed |
| ICMP Flood Detection | ping -i 0.002 -f 127.0.0.1 | IDS flagged high-frequency ICMP traffic |
| Suspicious Payload Detection | curl -X POST http://127.0.0.1:8080 -d "username=admin&password=123" | IDS detected suspicious POST payload with username/password |

**Testing Notes:**  
- All tests conducted in **Safe Mode** (localhost only)  
- Demonstrates real-time detection of network and application-layer attacks  
- Alerts include source IP, destination IP, and type of threat  

<br>

<u><h2>Conclusion</h2></u>

NeuroLock IDS is a **fully functional, real-time intrusion detection system** optimized for local safe testing.  
It effectively detects:

1. Port scans  
2. ICMP floods  
3. Suspicious application-layer payloads  

This project demonstrates strong **C++ programming skills, network traffic analysis, and practical cybersecurity expertise**.  
It is a professional portfolio-ready project suitable for **LinkedIn, GitHub, and technical interviews**, showcasing hands-on IDS development and security monitoring.

</div>
