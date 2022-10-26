
#ifndef PACKAGE_H
#define PACKAGE_H

#define ESP32DEBUGGING
#define DEBUG_LOG
/////////////////////////////////////////////////////////////////////
//                                                                 //
//                          CHOOSE HARDWARE                        //
//                                                                 //
/////////////////////////////////////////////////////////////////////

//#define HARDWARE_M5STACK
#define HARDWARE_TYPE_SLIM_GW
//#define HARDWARE_TYPE_FIAMMA 										// - NA
//#define HARDWARE_TYPE_MODULE_IO 								// - NA
//#define HARDWARE_TYPE_HOMEHEALTH 								// - NA
//#define HARDWARE_TYPE_IRHUB  										// - NA
//#define HARDWARE_TYPE_ETHERNET_GW 							// - NA
//#define HARDWARE_TYPE_ENERGY_ANALYZER 					// - NA
//#define HARDWARE_TYPE_MULTI_ENERGY_ANALYZER
//#define HARDWARE_TYPE_SMART_MOTION							// - NA

// uncomment the uProcessor which you are using
#define HARDWARE_TYPE_ESP32_CORE


/////////////////////////////////////////////////////////////////////
//                                                                 //
// DO NOT CHANGE BELOW LINES UNLESS YOU KNOW WHAT YOU'RE DOING 		 //
//                                                                 //
/////////////////////////////////////////////////////////////////////

#ifdef HARDWARE_TYPE_ESP32_CORE
	#define PACKAGE_VERSION        			 	"0.0.1"
	#define PACKAGE_PREFIX								"esp32/freeRTOS"
#endif

/////////////////////////////////////////////////////////////////////
//                                                                 //
//                         CHOOSE DEPLOYMENT                       //
//                                                                 //
/////////////////////////////////////////////////////////////////////

// --- Developer ---
#define DEVELOPING
#define DEPLOY_DEVELOPMENT_VODAFONE_GPRS


/////////////////////////////////////////////////////////////////////
//                                                                 //
//                 CHOOSE ADDITIONAL STUFF (OPTIONAL)              //
//                                                                 //
/////////////////////////////////////////////////////////////////////

#if defined HARDWARE_M5STACK

	#define PACKAGE_MODEL 200

	#define ENABLE_WIFI

	#ifdef ENABLE_WIFI
		#define WIFI_MQTT_ENABLE
	#endif

	#define ENABLE_LCD
	#define LCD_M5STACK_ENABLE

#elif defined HARDWARE_TYPE_SLIM_GW

	#define PACKAGE_MODEL 40

	#define ENABLE_LTE 			// This module is responsible for creating a GPRS connection (if also defined in settings), discarding the use of the wireless connection.
	#define SETTINGS_LTE_MODE						MODEM_GPRS  			// GPRS mode

	//#define WIFI_SYNC_TIME // timestamp gets corrupted very fast
	#define GPRS_SYNC_TIME

	/*
	#define ENABLE_WIFI
	#ifdef ENABLE_WIFI
		#define WIFI_MQTT_ENABLE // timestamp gets corrupted after a while
	#endif
	*/
	#define ENABLE_RS485
	#define ENABLE_TIMESTAMP

	#define ENABLE_LED

	#define ENABLE_BATTERY

	#define DIGITAL_COUNTERS
	#define ANDON

	#define ADS1015 // Compatible with all boards

	#define BG95
	#define PWRKEY 4

	//#define ENABLE_BLE
#elif defined HARDWARE_TYPE_FIAMMA

	#define PACKAGE_MODEL 80

	#define ENABLE_LTE 			// This module is responsible for creating a GPRS connection (if also defined in settings), discarding the use of the wireless connection.
	#define SETTINGS_LTE_MODE						MODEM_GPRS  			// GPRS mode

	#define SETTINGS_WIFI_MODE					WIFI_DEACTIVATED  // deactive
	#define ENABLE_LED

	#define ENABLE_RS485
	#define ENABLE_TIMESTAMP
	#define ENABLE_GICAR

	#define SIM800C
	#define PWRKEY 12

#elif defined HARDWARE_TYPE_MODULE_IO

	#define PACKAGE_MODEL 70

	#define ENABLE_LTE 			// This module is responsible for creating a GPRS connection (if also defined in settings), discarding the use of the wireless connection.
	#define SETTINGS_LTE_MODE						MODEM_GPRS  // GPRS and GSM disabled

	#define SETTINGS_WIFI_MODE					WIFI_DEACTIVATED  // client mode
	//#define SETTINGS_WIFI_MODE					NONE  // client mode

	#define ENABLE_LCD
	#define ENABLE_RS485
	#define ENABLE_TIMESTAMP
	//#define ENABLE_BLE
	#define ENABLE_LED
	#define DIGITAL_COUNTERS
	#define ANDON

	#define BG95
	#define PWRKEY 12
#elif defined HARDWARE_TYPE_HOMEHEALTH

	#define PACKAGE_MODEL 60

	#define ENABLE_LTE 			// This module is responsible for creating a GPRS connection (if also defined in settings), discarding the use of the wireless connection.
	#define SETTINGS_LTE_MODE						MODEM_GPRS  			// GPRS mode

	#define SETTINGS_WIFI_MODE					WIFI_DEACTIVATED  // disabled

	#define ENABLE_TIMESTAMP
	#define ENABLE_MYSIGNALS
	#define ENABLE_BME680
	#define ENABLE_LED

	//#define GDS_VODAFONE
	#define SIM800C
	#define PWRKEY 4

#elif defined HARDWARE_TYPE_IRHUB

	#define PACKAGE_MODEL  50

	#define SETTINGS_LTE_MODE						MODEM_DEACTIVATED  // GPRS and GSM disabled

	#define SETTINGS_WIFI_MODE					WIFI_DEACTIVATED  // deactive

	#define ENABLE_TIMESTAMP
	#define ENABLE_BME680
	#define ENABLE_INFRARED
	#define ENABLE_LED
  //#define ENABLE_RCWL_0516

#elif defined HARDWARE_TYPE_ETHERNET_GW
	#define PACKAGE_MODEL 100

	#define ENABLE_LTE 			// This module is responsible for creating a GPRS connection (if also defined in settings), discarding the use of the wireless connection.
	#define SETTINGS_LTE_MODE						MODEM_GSM  			// GPRS mode

	#define SETTINGS_WIFI_MODE					WIFI_CLIENT  // deactive

	#define ENABLE_TIMESTAMP
	#define ENABLE_RS485
	#define ENABLE_ETHERNET
	#define ENABLE_LED

	#define ENABLE_BATTERY

	#define SIM800C
	#define PWRKEY 4

#elif defined HARDWARE_TYPE_ENERGY_ANALYZER
	#define PACKAGE_MODEL 90

	#define ENABLE_LTE 			// This module is responsible for creating a GPRS connection (if also defined in settings), discarding the use of the wireless connection.
	#define SETTINGS_LTE_MODE						MODEM_GPRS  			// GPRS mode

	#define SETTINGS_WIFI_MODE					WIFI_DEACTIVATED  // deactive

	#define ENABLE_ENERGY_ANALYZER
	#define ENABLE_TIMESTAMP
	#define ENABLE_RS485
	#define ENABLE_LED

	#define ENABLE_BATTERY

	#define SIM800C
	#define PWRKEY 4

#elif defined HARDWARE_TYPE_MULTI_ENERGY_ANALYZER
	#define PACKAGE_MODEL 120

	#define ENABLE_LTE 			// This module is responsible for creating a GPRS connection (if also defined in settings), discarding the use of the wireless connection.
	#define SETTINGS_LTE_MODE						MODEM_GPRS  			// GPRS mode

	//#define WIFI_SYNC_TIME // timestamp gets corrupted very fast
	#define GPRS_SYNC_TIME

	/*
	#define ENABLE_WIFI
	#ifdef ENABLE_WIFI
		#define WIFI_MQTT_ENABLE  // it is corrupting timestamp
	#endif
	*/
	#define ENABLE_MULTI_ENERGY_ANALYZER
	#define ENABLE_TIMESTAMP
	#define ENABLE_RS485

	#define ENABLE_LCD
	#define ENABLE_LCD_ILI9341
	#define ENABLE_LED

	#define ENABLE_BATTERY
	#define ENABLE_RTC

	#define BG95
	#define PWRKEY 4

#elif defined HARDWARE_TYPE_SMART_MOTION
	#define PACKAGE_MODEL 110

	#define ENABLE_LTE 			// This module is responsible for creating a GPRS connection (if also defined in settings), discarding the use of the wireless connection.
	#define SETTINGS_LTE_MODE						MODEM_GPRS  			// GPRS mode
	//#define SETTINGS_LTE_MODE						MODEM_DEACTIVATED  			// GPRS mode

	#define SETTINGS_WIFI_MODE					WIFI_DEACTIVATED  // deactive
	//#define SETTINGS_WIFI_MODE					WIFI_CLIENT  // deactive

	#define ENABLE_ENERGY_ANALYZER
	#define ENABLE_TIMESTAMP
	//#define ENABLE_RS485
	#define ENABLE_LED

	#define BG95
	#define PWRKEY 2

#endif

/////////////////////////////////////////////////////////////////////
//                                                                 //
//                 Nothing more to configure				               //
//									you are ready to go ;)                         //
//																					                       //
/////////////////////////////////////////////////////////////////////

#if defined DEPLOY_DEVELOPMENT_NOS_NB
	#define SETTINGS_NB_APN         						"tdtnb"
	#define SETTINGS_NB_USERNAME    						""
	#define SETTINGS_NB_PASSWORD    						""
	#define SETTINGS_NB_BAND		    						20
	#define SETTINGS_NB_COPS		    						26803
	#define SETTINGS_SERVER_HOST 		  					"192.168.0.41"
	#define SETTINGS_SERVER_PORT   							5684
#elif defined DEPLOY_DEVELOPMENT_VODAFONE_NB
	//#define SETTINGS_NB_APN         						"m2m.vodafone.pt"
	#define SETTINGS_NB_APN         						"nbiot1.vodafone.pt"  //
	//#define SETTINGS_NB_APN         						"nbiot2.vodafone.pt"  // 12 hours sleep mode
	//#define SETTINGS_NB_APN         						"nbiot3.vodafone.pt"  // 12 hours sleep mode
	#define SETTINGS_NB_USERNAME    						""
	#define SETTINGS_NB_PASSWORD    						""
	#define SETTINGS_NB_BAND		    						20
	#define SETTINGS_NB_COPS		    						26801
	#define SETTINGS_SERVER_HOST 		  					"83.240.189.154"
	#define SETTINGS_SERVER_PORT   							5684
#elif defined DEPLOY_PRODUCTION_VODAFONE_NB
	//#define SETTINGS_NB_APN         						"m2m.vodafone.pt"
	#define SETTINGS_NB_APN         						"nbiot1.vodafone.pt"  //
	//#define SETTINGS_NB_APN         						"nbiot2.vodafone.pt"  // 12 hours sleep mode
	//#define SETTINGS_NB_APN         						"nbiot3.vodafone.pt"  // 12 hours sleep mode
	#define SETTINGS_NB_USERNAME    						""
	#define SETTINGS_NB_PASSWORD    						""
	#define SETTINGS_NB_BAND		    						20
	#define SETTINGS_NB_COPS		    						26801
	#define SETTINGS_SERVER_HOST 		  					"83.240.189.154"
	#define SETTINGS_SERVER_PORT   							19987
#elif defined DEPLOY_DEVELOPMENT_NOS_GPRS
	#define SETTINGS_GPRS_APN         					"ocnetjws.prtop"
	#define SETTINGS_GPRS_USERNAME    					""
	#define SETTINGS_GPRS_PASSWORD    					""
	#define SETTINGS_GPRS_BAND		    					0
	#define SETTINGS_GPRS_COPS		    					0
	#define SETTINGS_SERVER_HOST   							"83.240.189.154"  // change it
#elif defined DEPLOY_DEVELOPMENT_VODAFONE_GPRS
	#define SETTINGS_NB_APN         						"m2m.vodafone.pt"
	//#define SETTINGS_NB_APN         						"nbiot1.vodafone.pt"  //
	//#define SETTINGS_NB_APN         						"nbiot2.vodafone.pt"  // 12 hours sleep mode
	//#define SETTINGS_NB_APN         						"nbiot3.vodafone.pt"  // 12 hours sleep mode
	#define SETTINGS_NB_USERNAME    						""
	#define SETTINGS_NB_PASSWORD    						""
	#define SETTINGS_NB_BAND		    						20
	#define SETTINGS_NB_COPS		    						26801

	#define SETTINGS_GPRS_APN         					"m2m.vodafone.pt"
	#define SETTINGS_GPRS_USERNAME    					"vodafone"
	#define SETTINGS_GPRS_PASSWORD    					""
	#define SETTINGS_GPRS_BAND		    					20
	#define SETTINGS_GPRS_COPS		    					26801

	#define SETTINGS_SERVER_PORT   							19987
	#define SETTINGS_SERVER_HOST			   				"dev.cc.dourogas.thinkdigital.pt"  // change it
	#define SETTINGS_SERVER_PATH			   				"/equipment/types/config/kLEPuH"  // change it
	#define SETTINGS_SERVER_TCPMODBUS_PORT 			5684			  // change it
#endif

#define SETTINGS_MQTT_USERNAME 								"admin"
#define SETTINGS_MQTT_PASS		 								"thinkdigital"
#define SETTINGS_MQTT_HOST		 								"83.240.189.154"
//#define SETTINGS_MQTT_HOST		 								"192.168.0.101"
#define SETTINGS_MQTT_TCP			 								1883
#define SETTINGS_MQTT_TLS			 								8883

#define SETTINGS_FOTA_HOST		 								"office.thinkdigital.pt"
#define SETTINGS_FOTA_ADDRESS									"/deployments/devices/firmwares/download/stm32l4xx_v0.6.bin"
#define SETTINGS_FOTA_PORT			 							80
#define SETTINGS_FOTA_TLS			 								8883

#define SECRET_SSID 													"THINKDIGITAL-IoT" // Network SSID (name).
//#define SECRET_SSID 													"THINKDIGITAL-IoT-2" // Network SSID (name).
//#define SECRET_SSID 													"Vodafone-rocks" // Network SSID (name).
//#define SECRET_SSID 													"TD" // Network SSID (name).
#define SECRET_PASS 													"td-iot-1234567890" // WPA password or WEP key.
//#define SECRET_PASS 													"famelgasilva" // WPA password or WEP key.
//#define SECRET_PASS 													"TDAveiro2015" // WPA password or WEP key.

#define LOW 0
#define HIGH 1

#endif
