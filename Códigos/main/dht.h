/*

	DHT11 temperature sensor driver

*/

#ifndef DHT11_H_
#define DHT11_H_

#define SENSOR_TYPE DHT_TYPE_DHT11

#define DHT_GPIO			21

/**
 * Starts DHT11 sensor task
 */

void DHT11_read(void);
int _waitOrTimeout();
int _sendStartSignal();
int _checkResponse();
void DHT11_init();

#endif
