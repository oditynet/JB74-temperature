# JB74-temperature
Suzuki jimny JB74 temperature 
Arduino nano + OLED дисплей 0.96" 128x64 I2C + MCP2515 TJA1050 CAN Bus
CAN :

https://can.starline.ru/0/38/8629#connections

<table>
  <tr>
    <td><img src="https://github.com/oditynet/JB74-temperature/blob/main/res1.jpg" width="300" height="auto" /></td>
    <td><img src="https://github.com/oditynet/JB74-temperature/blob/main/res2.jpg" width="300" height="auto" /></td>
  </tr>
</table>

STL Model

<img src="https://github.com/oditynet/JB74-temperature/blob/main/res3.png" width="300" height="auto" />


<h2>Подключение LCD I2C к Arduino Nano</h2>
<table border="1" cellpadding="5" cellspacing="0">
  <tr>
    <th>LCD I2C модуль</th>
    <th>Arduino Nano</th>
    <th>Примечание</th>
  </tr>
  <tr>
    <td>GND</td>
    <td><b>GND</b></td>
    <td>Общий провод</td>
  </tr>
  <tr>
    <td>VCC</td>
    <td><b>5V</b></td>
    <td>Питание дисплея</td>
  </tr>
  <tr>
    <td>SDA</td>
    <td><b>A4</b></td>
    <td>Линия данных I2C</td>
  </tr>
  <tr>
    <td>SCL</td>
    <td><b>A5</b></td>
    <td>Линия тактового сигнала I2C</td>
  </tr>
</table>

<h2>Подключение CAN модуля MCP2515 к Arduino Nano</h2>
<table border="1" cellpadding="5" cellspacing="0">
  <tr>
    <th>MCP2515 модуль</th>
    <th>Arduino Nano</th>
    <th>Примечание</th>
  </tr>
  <tr>
    <td>VCC</td>
    <td><b>5V</b></td>
    <td>Питание модуля</td>
  </tr>
  <tr>
    <td>GND</td>
    <td><b>GND</b></td>
    <td>Общий провод</td>
  </tr>
  <tr>
    <td>CS</td>
    <td><b>D8</b></td>
    <td>Chip Select (как в коде)</td>
  </tr>
  <tr>
    <td>MOSI</td>
    <td><b>D11</b></td>
    <td>SPI данные</td>
  </tr>
  <tr>
    <td>MISO</td>
    <td><b>D12</b></td>
    <td>SPI данные</td>
  </tr>
  <tr>
    <td>SCK</td>
    <td><b>D13</b></td>
    <td>SPI тактовый сигнал</td>
  </tr>
  <tr>
    <td>INT</td>
    <td><i>не используется</i></td>
    <td>Пин прерывания</td>
  </tr>
</table>
