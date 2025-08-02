#include "WebServerControl.h"
#include "WebResources.h"  // Generated header with embedded files

WebServerControl::WebServerControl(ESP8266WebServer &server, ChigoIRControl &chigoIR, WiFiControl &wifi)
    : server(server), chigoIR(chigoIR), wifi(wifi) {}

void WebServerControl::begin()
{
    wifi.connect();
    Serial.println("[WebServerControl] Registering HTTP handlers...");
    
    // Main routes
    server.on("/", std::bind(&WebServerControl::handleRoot, this));
    server.on("/status", std::bind(&WebServerControl::handleStatus, this));
    server.on("/on", std::bind(&WebServerControl::handleOn, this));
    server.on("/off", std::bind(&WebServerControl::handleOff, this));
    server.on("/set", std::bind(&WebServerControl::handleSet, this));
    server.on("/setmode", std::bind(&WebServerControl::handleSetMode, this));
    server.on("/setairflow", std::bind(&WebServerControl::handleSetAirflow, this));
    server.on("/setfan", std::bind(&WebServerControl::handleSetFan, this));
    
    // Static file routes
    server.on("/scripts/main.js", [this]() { server.send_P(200, "application/javascript", MAIN_JS); });
    server.on("/scripts/api.js", [this]() { server.send_P(200, "application/javascript", API_JS); });
    server.on("/scripts/localization.js", [this]() { server.send_P(200, "application/javascript", LOCALIZATION_JS); });
    server.on("/scripts/status.js", [this]() { server.send_P(200, "application/javascript", STATUS_JS); });
    server.on("/scripts/temperature.js", [this]() { server.send_P(200, "application/javascript", TEMPERATURE_JS); });
    server.on("/scripts/theme.js", [this]() { server.send_P(200, "application/javascript", THEME_JS); });
    server.on("/scripts/uiState.js", [this]() { server.send_P(200, "application/javascript", UISTATE_JS); });
    server.on("/scripts/weather.js", [this]() { server.send_P(200, "application/javascript", WEATHER_JS); });
    server.on("/scripts/cloud.js", [this]() { server.send_P(200, "application/javascript", CLOUD_JS); });
    
    server.on("/styles/main.css", [this]() { server.send_P(200, "text/css", MAIN_CSS); });
    server.on("/styles/base.css", [this]() { server.send_P(200, "text/css", BASE_CSS); });
    server.on("/styles/animations.css", [this]() { server.send_P(200, "text/css", ANIMATIONS_CSS); });
    server.on("/styles/buttons.css", [this]() { server.send_P(200, "text/css", BUTTONS_CSS); });
    server.on("/styles/clouds.css", [this]() { server.send_P(200, "text/css", CLOUDS_CSS); });
    server.on("/styles/control-buttons.css", [this]() { server.send_P(200, "text/css", CONTROL_BUTTONS_CSS); });
    server.on("/styles/dark-mode.css", [this]() { server.send_P(200, "text/css", DARK_MODE_CSS); });
    server.on("/styles/language-switcher.css", [this]() { server.send_P(200, "text/css", LANGUAGE_SWITCHER_CSS); });
    server.on("/styles/power-buttons.css", [this]() { server.send_P(200, "text/css", POWER_BUTTONS_CSS); });
    server.on("/styles/responsive.css", [this]() { server.send_P(200, "text/css", RESPONSIVE_CSS); });
    server.on("/styles/sliders.css", [this]() { server.send_P(200, "text/css", SLIDERS_CSS); });
    server.on("/styles/status.css", [this]() { server.send_P(200, "text/css", STATUS_CSS); });
    server.on("/styles/theme-switcher.css", [this]() { server.send_P(200, "text/css", THEME_SWITCHER_CSS); });
    server.on("/styles/weather-bg.css", [this]() { server.send_P(200, "text/css", WEATHER_BG_CSS); });
    server.on("/styles/weather-effects.css", [this]() { server.send_P(200, "text/css", WEATHER_EFFECTS_CSS); });
    
    server.begin();
    Serial.println("[WebServerControl] HTTP server started.");
}

void WebServerControl::handleClient()
{
    server.handleClient();
}

void WebServerControl::handleRoot()
{
    Serial.println("[WebServerControl] handleRoot() called, serving embedded HTML");
    server.send_P(200, "text/html; charset=UTF-8", MAIN_HTML);
}

void WebServerControl::handleStatus()
{
    server.send(200, "application/json", "{\"status\":\"online\",\"device\":\"ESP8266\"}");
}

void WebServerControl::handleOn()
{
    chigoIR.powerOn();
    server.send(200, "text/html; charset=UTF-8", "Turned on");
}

void WebServerControl::handleOff()
{
    chigoIR.powerOff();
    server.send(200, "text/html; charset=UTF-8", "Turned off");
}

void WebServerControl::handleSet()
{
    if (server.hasArg("temp"))
    {
        int temp = server.arg("temp").toInt();
        if (temp >= 18 && temp <= 30)
        {
            chigoIR.setTemperature(temp);
            server.send(200, "text/html; charset=UTF-8", "Temperature set");
        }
        else
        {
            server.send(400, "text/html; charset=UTF-8", "Invalid temperature");
        }
    }
    else
    {
        server.send(400, "text/html; charset=UTF-8", "Missing parameter");
    }
}

void WebServerControl::handleSetMode()
{
    if (server.hasArg("mode"))
    {
        int mode = server.arg("mode").toInt();
        if (mode >= 1 && mode <= 4)
        {
            chigoIR.setMode(mode);
            server.send(200, "text/html; charset=UTF-8", "Mode set");
        }
        else
        {
            server.send(400, "text/html; charset=UTF-8", "Invalid mode");
        }
    }
    else
    {
        server.send(400, "text/html; charset=UTF-8", "Missing parameter");
    }
}

void WebServerControl::handleSetAirflow()
{
    if (server.hasArg("airflow"))
    {
        int airflow = server.arg("airflow").toInt();
        if (airflow >= 0 && airflow <= 2)
        {
            chigoIR.setAirflow(airflow);
            server.send(200, "text/html; charset=UTF-8", "Airflow set");
        }
        else
        {
            server.send(400, "text/html; charset=UTF-8", "Invalid airflow");
        }
    }
    else
    {
        server.send(400, "text/html; charset=UTF-8", "Missing parameter");
    }
}

void WebServerControl::handleSetFan()
{
    if (server.hasArg("fan"))
    {
        int fan = server.arg("fan").toInt();
        if (fan >= 0 && fan <= 3)
        {
            chigoIR.setFanSpeed(fan);
            server.send(200, "text/html; charset=UTF-8", "Fan speed set");
        }
        else
        {
            server.send(400, "text/html; charset=UTF-8", "Invalid fan speed");
        }
    }
    else
    {
        server.send(400, "text/html; charset=UTF-8", "Missing parameter");
    }
}
