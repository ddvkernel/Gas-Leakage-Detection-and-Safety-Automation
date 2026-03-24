## Gas-Leakage-Detection-and-Safety-Automation
Developed a microcontroller-based LPG leakage detection system using an MQ-2 sensor. Implemented automated safety actions including circuit isolation, forced ventilation, and solenoid valve shutoff. Integrated SIM800L GSM module for real-time SMS alerts and remote monitoring.


## Problem Statement
Gas leakage can lead to fire hazards, explosions, and serious health risks in homes and industries. Manual detection is unreliable and often too late. This project aims at providing an automated system that detects gas leaks in real time and immediately triggers safety mechanisms and alerts. 


## System Diagram
![System Diagram](assets/block_diagram_gas.png)


## How to Run

1. Connect MQ-2 gas sensor to Arduino (A0 pin)
2. Connect relay module, motor, solenoid valve, and LED as per circuit
3. Connect GSM module (SIM800L) using TX/RX pins
4. Update phone number in the 22nd line of the code
5. Power the system
6. Connect the Arduino Board to the laptop
7. Upload the code using the upload button in Arduino IDE
8. Monitor Serial output and SMS alerts


## Documented Report
Full report available in /report/project-report.pdf
