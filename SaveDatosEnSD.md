# Cuadro para CADENA EN SD
| Num  | Rango | Descripción                                                    |
|------|-------|----------------------------------------------------------------|
| 1    | 0-7   | Recorder Type Indicator (string)                               |
| 2-5  | 0-31  | Timestamp Start of Text (STX)                                  |
| 6-9  | 0-31  | Timestamp End of Text (ETN)                                    |
| 10-11| 0-15  | Record size                                                    |
| 12   | 0-7   | Least significant 8 bits of the record checksum                |
| 13-19| 0-55  | Temperature sensing - MAX31865                                 |
| 20-24| 0-39  | INA219 - Measurement of load voltage                           |
| 25-31| 0-55  | INA219 - Measurement of consumption current Heater power supply system |
| 32-38| 0-55  | x-axis acceleration sensing - BNO055                           |
| 39-45| 0-55  | y-axis acceleration sensing - BNO055                           |
| 46-52| 0-55  | z-axis acceleration sensing - BNO055                           |
| 53-59| 0-55  | Gyroscope sensing in the x-axis - BNO055                       |
| 60-66| 0-55  | Gyroscope sensing in the y-axis - MPU6050                      |
| 67-73| 0-55  | Gyroscope sensing in the z-axis - MPU6050                      |
| 74-80| 0-55  | Temperature of BME280                                          |
| 81-87| 0-55  | Humidity of BME280                                             |
| 88-94| 0-55  | Pressure of BME280                                             |
| 95-101| 0-55 | x-axis acceleration sensing - BNO055                           |
| 102-108| 0-55| y-axis acceleration sensing - BNO055                           |
| 109-115| 0-55| z-axis acceleration sensing - BNO055                           |
| 116-122| 0-55| Gyroscope sensing in the x-axis - BNO055                       |
| 123-129| 0-55| Gyroscope sensing in the y-axis - BNO055                       |
| 130-136| 0-55| Gyroscope sensing in the z-axis - BNO055                       |
| 137-143| 0-55| x-axis magnetometer sensing - BNO055                           |
| 144-150| 0-55| y-axis magnetometer sensing - BNO055                           |
| 151-157| 0-55| z-axis magnetometer sensing - BNO055                           |
| 158-164| 0-55| Values orientation in the x-axis - BNO055                      |
| 165-171| 0-55| Values orientation in the x-axis - BNO055                      |
| 172-178| 0-55| Values orientation in the x-axis - BNO055                      |
| 179-185| 0-55| x-axis gravity vector value - BNO055                           |
| 186-192| 0-55| y-axis gravity vector value - BNO055                           |
| 193-199| 0-55| z-axis gravity vector value - BNO055                           |
| 200-201| 0-13| General system calibration level - BNO055                      |
| 202-210| 0-71| GPS - Latitude module GPS-6mv2                                 |
| 211-219| 0-71| GPS - module longitude GPS-6mv2                                |
| 220-227| 0-63| GPS - module altitude GPS-6mv2                                 |
| 228-236| 0-71| GPS - module time in GPS-6mv2                                  |
| 237-245| 0-71| GPS - module date                                              |
| 246-251| 0-47| Temperature sensing – Thermistor NTC                           |
| 252-257| 0-47| Temperature sensing – Thermistor NTC                           |
| 258-263| 0-47| Temperature sensing – Thermistor NTC                           |
| 264-269| 0-47| Temperature sensing – Thermistor NTC                           |
| 270-275| 0-47| Temperature sensing – Thermistor NTC                           |
| 276-281| 0-47| Temperature sensing – Thermistor NTC                           |
| 282-287| 0-47| Temperature sensing – Thermistor NTC                           |
| 288-393| 0-47| Temperature sensing – Thermistor NTC                           |
