EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:ESP8266
LIBS:Weather-Station-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L NodeMCU1.0(ESP-12E) U1
U 1 1 5A58E7F1
P 5700 3350
F 0 "U1" H 5700 4200 60  0000 C CNN
F 1 "NodeMCU1.0(ESP-12E)" H 5700 2500 60  0000 C CNN
F 2 "ESP8266_l2:NodeMCU1.0(12-E)" H 5100 2500 60  0001 C CNN
F 3 "" H 5100 2500 60  0000 C CNN
	1    5700 3350
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x02 J6
U 1 1 5A58E867
P 8150 3050
F 0 "J6" H 8150 3150 50  0000 C CNN
F 1 "Anamometro" H 8150 2850 50  0000 C CNN
F 2 "Terminal_Blocks:TerminalBlock_Pheonix_MPT-2.54mm_2pol" H 8150 3050 50  0001 C CNN
F 3 "" H 8150 3050 50  0001 C CNN
	1    8150 3050
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x02 J5
U 1 1 5A58E986
P 8150 2550
F 0 "J5" H 8150 2650 50  0000 C CNN
F 1 "Pluviometro" H 8150 2350 50  0000 C CNN
F 2 "Terminal_Blocks:TerminalBlock_Pheonix_MPT-2.54mm_2pol" H 8150 2550 50  0001 C CNN
F 3 "" H 8150 2550 50  0001 C CNN
	1    8150 2550
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x02 J1
U 1 1 5A58E9CB
P 3800 2750
F 0 "J1" H 3800 2850 50  0000 C CNN
F 1 "Biruta" H 3800 2550 50  0000 C CNN
F 2 "Terminal_Blocks:TerminalBlock_Pheonix_MPT-2.54mm_2pol" H 3800 2750 50  0001 C CNN
F 3 "" H 3800 2750 50  0001 C CNN
	1    3800 2750
	-1   0    0    1   
$EndComp
$Comp
L Conn_01x05 J3
U 1 1 5A58EAD3
P 8150 1200
F 0 "J3" H 8150 1500 50  0000 C CNN
F 1 "BH1750-FVI" H 8150 900 50  0000 C CNN
F 2 "Terminal_Blocks:TerminalBlock_Pheonix_MPT-2.54mm_5pol" H 8150 1200 50  0001 C CNN
F 3 "" H 8150 1200 50  0001 C CNN
	1    8150 1200
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x02 J2
U 1 1 5A58EC49
P 3800 4050
F 0 "J2" H 3800 4150 50  0000 C CNN
F 1 "Power" H 3800 3850 50  0000 C CNN
F 2 "Terminal_Blocks:TerminalBlock_Pheonix_MPT-2.54mm_2pol" H 3800 4050 50  0001 C CNN
F 3 "" H 3800 4050 50  0001 C CNN
	1    3800 4050
	-1   0    0    1   
$EndComp
$Comp
L Conn_01x06 J4
U 1 1 5A58EA66
P 8150 1900
F 0 "J4" H 8150 2200 50  0000 C CNN
F 1 "BME280" H 8150 1500 50  0000 C CNN
F 2 "Terminal_Blocks:TerminalBlock_Pheonix_MPT-2.54mm_6pol" H 8150 1900 50  0001 C CNN
F 3 "" H 8150 1900 50  0001 C CNN
	1    8150 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 3650 4250 3650
Wire Wire Line
	4250 3650 4250 2750
Wire Wire Line
	4250 2750 4000 2750
Wire Wire Line
	4000 2650 4900 2650
Wire Wire Line
	4550 2800 4550 2650
Connection ~ 4550 2650
Wire Wire Line
	6700 4050 6500 4050
Wire Wire Line
	6500 3350 7000 3350
Wire Wire Line
	6500 3450 7100 3450
Wire Wire Line
	6600 3950 6500 3950
Wire Wire Line
	6600 1400 6600 3950
Wire Wire Line
	6600 2950 7350 2950
Wire Wire Line
	7350 3450 7350 3550
Wire Wire Line
	7350 3550 6600 3550
Connection ~ 6600 3550
Wire Wire Line
	6700 1000 6700 4050
Wire Wire Line
	6700 2550 7950 2550
Wire Wire Line
	7950 3050 6700 3050
Connection ~ 6700 3050
Wire Wire Line
	7950 1800 6600 1800
Connection ~ 6600 2950
Wire Wire Line
	7950 1700 6700 1700
Connection ~ 6700 2550
Wire Wire Line
	7950 2100 6700 2100
Connection ~ 6700 2100
Wire Wire Line
	7950 2200 6700 2200
Connection ~ 6700 2200
Wire Wire Line
	7950 1900 6800 1900
Wire Wire Line
	6800 1100 6800 2750
Wire Wire Line
	6800 2750 6500 2750
Wire Wire Line
	7950 2000 6900 2000
Wire Wire Line
	6900 1200 6900 2850
Wire Wire Line
	6900 2850 6500 2850
Wire Wire Line
	7000 3350 7000 2650
Wire Wire Line
	7100 3450 7100 3150
Wire Wire Line
	7950 1000 6700 1000
Connection ~ 6700 1700
Wire Wire Line
	7950 1100 6800 1100
Connection ~ 6800 1900
Wire Wire Line
	7950 1200 6900 1200
Connection ~ 6900 2000
Wire Wire Line
	7950 1400 6600 1400
Connection ~ 6600 1800
NoConn ~ 7950 1300
Wire Wire Line
	4550 3100 4550 3550
Wire Wire Line
	4550 3550 4900 3550
NoConn ~ 4900 2750
NoConn ~ 4900 2850
NoConn ~ 4900 2950
NoConn ~ 4900 3050
NoConn ~ 4900 3150
NoConn ~ 4900 3250
NoConn ~ 4900 3350
NoConn ~ 4900 3450
NoConn ~ 4900 3750
NoConn ~ 4900 3850
NoConn ~ 6500 2650
NoConn ~ 6500 2950
NoConn ~ 6500 3050
NoConn ~ 6500 3150
NoConn ~ 6500 3250
NoConn ~ 6500 3550
NoConn ~ 6500 3650
NoConn ~ 6500 3750
NoConn ~ 6500 3850
$Comp
L PWR_FLAG #FLG01
U 1 1 5A5912D8
P 4350 3950
F 0 "#FLG01" H 4350 4025 50  0001 C CNN
F 1 "PWR_FLAG" H 4350 4100 50  0000 C CNN
F 2 "" H 4350 3950 50  0001 C CNN
F 3 "" H 4350 3950 50  0001 C CNN
	1    4350 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 3950 4900 3950
Connection ~ 4350 3950
$Comp
L PWR_FLAG #FLG02
U 1 1 5A5913B0
P 4350 4050
F 0 "#FLG02" H 4350 4125 50  0001 C CNN
F 1 "PWR_FLAG" H 4350 4200 50  0000 C CNN
F 2 "" H 4350 4050 50  0001 C CNN
F 3 "" H 4350 4050 50  0001 C CNN
	1    4350 4050
	-1   0    0    1   
$EndComp
Wire Wire Line
	4000 4050 4900 4050
Connection ~ 4350 4050
$Comp
L R R1
U 1 1 5A5918F9
P 4550 2950
F 0 "R1" V 4630 2950 50  0000 C CNN
F 1 "10K" V 4550 2950 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 4480 2950 50  0001 C CNN
F 3 "" H 4550 2950 50  0001 C CNN
	1    4550 2950
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 5A591980
P 7350 2800
F 0 "R2" V 7430 2800 50  0000 C CNN
F 1 "10K" V 7350 2800 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 7280 2800 50  0001 C CNN
F 3 "" H 7350 2800 50  0001 C CNN
	1    7350 2800
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 5A5919D5
P 7350 3300
F 0 "R3" V 7430 3300 50  0000 C CNN
F 1 "10K" V 7350 3300 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 7280 3300 50  0001 C CNN
F 3 "" H 7350 3300 50  0001 C CNN
	1    7350 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 2650 7950 2650
Wire Wire Line
	7100 3150 7950 3150
Connection ~ 7350 3150
Connection ~ 7350 2650
$EndSCHEMATC
