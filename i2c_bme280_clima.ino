void init_bme280()
{  
    boolean status = bme_clima.begin(BME280_ADDR);  
    // You can also pass in a Wire library object like &Wire2
    // status = bme.begin(0x76, &Wire2)
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        Serial.print("SensorID was: 0x"); Serial.println(bme_clima.sensorID(),16);
        Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
        Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
        Serial.print("        ID of 0x60 represents a BME 280.\n");
        Serial.print("        ID of 0x61 represents a BME 680.\n");
    } else
    {
      
    
    Serial.print("Temperature = ");
    Serial.print(bme_clima.readTemperature());
    Serial.println(" *C");

    Serial.print("Pressure = ");

    Serial.print(bme_clima.readPressure() / 100.0F);
    Serial.println(" hPa");

    Serial.print("Approx. Altitude = ");
    Serial.print(bme_clima.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println(" m");

    Serial.print("Humidity = ");
    Serial.print(bme_clima.readHumidity());
    Serial.println(" %");

    Serial.println();
    
    }
}
