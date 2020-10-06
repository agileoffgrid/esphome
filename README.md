# ESPHome

This is the real ESPHome device configuration I run in our home.

## Things & Devices

In the roof of the reposity is a `.config.yaml` file for each *thing* in our ESPHome network. These *things* represent the individual devices.

Each *thing* is a type of device, and inherits standardized config from a device in the `./devices/` folder. For example, `./devices/sonoff-s31.yaml` contains the base configuration for a Sonoff S31.

Configuration common to all devices is contained within the `./common/` folder.

## Substitutions

Each *thing* requires substitutions which are inserted as variables in the included configuration files. These are:

Name | Required | Note
---|---|---
`hostname` | Yes | A hostname for the device on the network (domain is automatically appended)
`friendly_name` | Yes | A human-readable name for the *thing*
`light_name` | For `sonoff-sv-light` | A name for the light itself

For example:

```yaml
substitutions:
  hostname: bedroom-lights
  friendly_name: Bedroom Lights
  light_name: Bedroom
```

## Secrets

The configuration relies on a file called `secrets.yaml` that should be placed in the root of this repository. It contains the following keys:

Key | Note
---|---
`WIFI_SSID` | SSID of the WiFi network to connect to
`WIFI_PASSWORD` | Password for the WiFi network
`WIFI_DOMAIN` | Domain for devices on the network with preceding period, e.g. `.local`

For example:

```yaml
WIFI_SSID: MyWiFiNetwork
WIFI_PASSWORD: MySuperSecureWiFiPassword
WIFI_DOMAIN: .local
```
