#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "nvs_flash.h"
#include "dht.h"
#include "wifi_app.h"



void DHT_reader_task(void *pvParameter)
{
		setDHTgpio(GPIO_NUM_4);

	while(1) {
	
		printf("Lendo Sensores do Terrario\n" );
		int ret = readDHT();
		
		errorHandler(ret);

		printf("Umidade %.2f %%\n", getHumidity());
		printf("Temperatura %.2f ºC\n\n", getTemperature());
		
		vTaskDelay(2000 / portTICK_RATE_MS);
	}
}

void app_main(void)
{

	esp_err_t ret = nvs_flash_init();
	if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
	{
		ESP_ERROR_CHECK(nvs_flash_erase());
		ret = nvs_flash_init();
	}
	ESP_ERROR_CHECK(ret);

	http_server_start();

	wifi_app_start();
    vTaskDelay(2000 / portTICK_RATE_MS);
	xTaskCreate(&DHT_reader_task, "DHT_reader_task", 2048, NULL, 5, NULL );
		
}
