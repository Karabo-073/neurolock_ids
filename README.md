
<h1>NeuroLock IDS – Real-Time Intrusion Detection System</h1>

<h2>Project Structure</h2>
<pre>
NeuroLock_IDS/
├── project_documentation.md
├── tests/
│   └── test_localhost.sh
└── README.md
</pre>

<h2>Overview</h2>
<p>
NeuroLock IDS is a real-time Intrusion Detection System developed in C++ using libpcap.
It monitors network traffic and detects threats such as port scans, ICMP floods, and suspicious payloads.
All operations are conducted safely in a controlled environment.
</p>

<h2>Key Features</h2>
<ul>
<li>Real-time packet capture using libpcap</li>
<li>Port scan detection across multiple TCP ports</li>
<li>ICMP flood detection (DoS behavior)</li>
<li>Payload inspection for suspicious keywords</li>
<li>Safe Mode for localhost testing</li>
<li>Lightweight and high-performance C++ implementation</li>
</ul>

<h2>How It Works</h2>

<h3>1. Packet Capture</h3>
<p>Captures live network traffic from the interface using libpcap.</p>

<h3>2. Packet Parsing</h3>
<ul>
<li>Ethernet Header – Validates IP traffic</li>
<li>IP Header – Extracts source and destination IP addresses</li>
<li>TCP/ICMP Headers – Identifies protocol and port information</li>
</ul>

<h3>3. Detection Engine</h3>
<ul>
<li>Port Scan Detection – Detects repeated connections across multiple ports</li>
<li>ICMP Flood Detection – Flags sources exceeding a threshold of ICMP packets</li>
<li>Suspicious Payload Analysis – Flags sensitive keywords like "admin" or "password"</li>
</ul>

<h2>Testing & Results</h2>
<table>
<tr>
<th>Test</th>
<th>Command</th>
<th>Result</th>
</tr>

<tr>
<td>Port Scan</td>
<td><code>nmap -sT -p 1-9000 127.0.0.1</code></td>
<td>Alert triggered for multi-port scanning</td>
</tr>

<tr>
<td>ICMP Flood</td>
<td><code>ping -i 0.002 -f 127.0.0.1</code></td>
<td>High-frequency ICMP traffic detected</td>
</tr>

<tr>
<td>Payload Attack</td>
<td><code>curl -X POST http://127.0.0.1:8080 -d "username=admin&password=123"</code></td>
<td>Suspicious payload flagged</td>
</tr>
</table>

<h3>Testing Notes</h3>
<ul>
<li>All tests conducted in Safe Mode (localhost only)</li>
<li>Real-time detection across network and application layers</li>
<li>Alerts include source IP, destination IP, and threat type</li>
</ul>

<h2>Live Detection Example</h2>
<div class="terminal">
[INFO] Monitoring started...<br>
[ALERT] Port Scan detected from 127.0.0.1<br>
[ALERT] ICMP Flood detected<br>
[ALERT] Suspicious Payload detected: "password"<br>
</div>

<h2>How to Run</h2>
<pre>
# Clone the repository
git clone https://github.com/yourusername/NeuroLock_IDS.git

# Navigate into project
cd NeuroLock_IDS

# Compile the program
g++ main.cpp -lpcap -o neurolock

# Run (requires root)
sudo ./neurolock
</pre>

<h2>Conclusion</h2>
<p>
NeuroLock IDS is a fully functional real-time IDS demonstrating strong expertise in:
</p>
<ul>
<li>C++ systems programming</li>
<li>Network packet analysis</li>
<li>Cybersecurity monitoring</li>
</ul>

</div>
</body>
</html>
