#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "nvs_flash.h"
#include "dht.h"
#include "wifi_app.h"

void app_main(void)
{
    // Initialize NVS
	esp_err_t ret = nvs_flash_init();
	if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
	{
		ESP_ERROR_CHECK(nvs_flash_erase());
		ret = nvs_flash_init();
	}
	ESP_ERROR_CHECK(ret);

	http_server_start();
	// Start Wifi
	wifi_app_start();

	while(1){
		//Start DTH11 Sensor task
		printf("A temperatura é %d \n", DHT11_read().temperature);
		printf("A humidade é %d\n", DHT11_read().humidity);
		printf("Status %d\n", DHT11_read().status);
		waitSeconds(1);
	}
	

}
