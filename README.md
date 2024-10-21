# esphome-hcpbridge

[![GitHub](https://img.shields.io/github/license/mapero/esphome-hcpbridge)](https://github.com/mapero/esphome-hcpbridge/blob/main/LICENSE)
[![GitHub issues](https://img.shields.io/github/issues/mapero/esphome-hcpbridge)](https://github.com/mapero/esphome-hcpbridge)
[![GitHub Sponsors](https://img.shields.io/github/sponsors/mapero)](https://github.com/sponsors/mapero)
![GitHub Workflow Status](https://img.shields.io/github/actions/workflow/status/mapero/esphome-hcpbridge/build.yaml)


This is a esphome-based adaption of the HCPBridge. Credits for the initial development of the HCPBridge go to [Gifford47](https://github.com/Gifford47/HCPBridgeMqtt), [hkiam](https://github.com/hkiam/HCPBridge) and all the other guys contributed.

## Usage

### Example esphome configuration

```YAML
esphome:
  name: hcpbridge
  libraries:
    - emelianov/modbus-esp8266 # Required for communication with the modbus
  platformio_options:
    board_build.f_cpu: 240000000L
    board_build.flash_mode: qio
    monitor_speed: 9600
    monitor_filters: esp32_exception_decoder
    lib_ldf_mode: deep+
    # board_build.f_flash: 40000000L

external_components:
    source: github://14yannick/esphome-hcpbridge
    refresh: 0s # Ensure you always get the latest version

esp32:
  board: #adafruit_feather_esp32s3 #set your board
  framework:
    type: arduino

hcpbridge:
  id: hcpbridge_id
  rx_pin: 18 # optional, default=18
  tx_pin: 17 # optional, default=17
  #rts_pin : 1 # optional RTS pin to use if hardware automatic control flow is not available.

cover:
  - platform: hcpbridge
    name: Garage Door
    device_class: garage
    id: garagedoor_cover

binary_sensor:
  - platform: hcpbridge
    is_connected:
      name: "HCPBridge Connected"
      id: sensor_connected
    relay_state:
      name: "Garage Door Relay state"
      id: sensor_relay
      #on_state:
      #create your automation based on Garage Door Relay state

output:
  - platform: hcpbridge
    id: output_light

light:
  - platform: hcpbridge
    id: gd_light
    output: output_light
    name: Garage Door Light

# API to communicate with home assistant
api:
  encryption:
    key: !secret api_key
  services:
    - service: go_to_open
      then:
        - lambda: |-
            id(garagedoor_cover).on_go_to_open();
    - service: go_to_close
      then:
        - lambda: |-
            id(garagedoor_cover).on_go_to_close();
    - service: go_to_half
      then:
        - lambda: |-
            id(garagedoor_cover).on_go_to_half();
    - service: go_to_vent
      then:
        - lambda: |-
            id(garagedoor_cover).on_go_to_vent();
    - service: toggle
      then:
        - cover.toggle: garagedoor_cover

# Enable OTA updates
ota:
  - platform: esphome
    safe_mode: true
```

### Home Assistant

![Home Assistant Device Overview](docs/device_overview.png)

### Cover

The component provides a cover component to control the garage door.

### Light

The component provides a Light component to turn the light off and on.

### Binary_Sensor

The component provides you two sensor.

- `is_connected`: Who indicated if there is a valid connection with the door.
- `relay_state`: Give the status of the option relay (Menu 30) of the HCP.

### Text_sensor

This component provide you a detailed current state of the door. This text can be changed using the substitute functionality.
```YAML
text_sensor:
  - platform: hcpbridge
    id: sensor_templ_state
    name: "Garage Door State"
    filters:
      - substitute:
        - "Opening -> your text"
        - "Move venting -> your text"
        - "Move half -> your text"
        - "Closing -> your text"
        - "Open -> your text"
        - "Closed -> your text"
        - "Stopped -> your text"
        - "Half open -> your text"
        - "Venting -> your text"
        - "Unknown -> your text"
```

### Additional Components

There is also a simple button and switch component for convenience for Automation.
Check out the [example_hcpbridge.yaml](./example_hcpbridge.yaml) for some implementations.


### Services

Additionally, when using the cover component, you can use the following services:

- `esphome.hcpbridge_go_to_close`: To close the garage door
- `esphome.hcpbridge_go_to_half`: To move the garage door to half position
- `esphome.hcpbridge_go_to_vent`: To move the garage door to the vent position
- `esphome.hcpbridge_go_to_open`: To open the garage door
- `esphome.hcpbridge_toggle`: Send an Impulse command to the door

# Project

- HCPBridge from `Tysonpower` on an `Hörmann Promatic 4`

You can find more information on the project here: [Hörmann garage door via MQTT](https://community.home-assistant.io/t/hormann-garage-door-via-mqtt/279938/340)

# ToDo

- [x] Initial working version
- [ ] Use esphome modbus component instead of own code
- [ ] Map additional functions to esphome
- [ ] Use callbacks instead of pollingComponent
- [x] Expert options for the HCPBridge component (GPIOs ...)

# Contribute

I am open for contribution. Just get in contact with me.

# License

```
MIT License

Copyright (c) 2023 Jochen Scheib

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```
