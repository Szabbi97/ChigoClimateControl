#!/usr/bin/env python3
"""
Script to convert web files to C++ header files for embedding in Arduino sketch
"""

import os
import re

def file_to_cpp_string(filepath, varname):
    """Convert a file to a C++ string literal"""
    with open(filepath, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # Use raw string literal which is much simpler
    cpp_content = f'const char {varname}[] PROGMEM = R"rawliteral(\n{content}\n)rawliteral";\n\n'
    
    return cpp_content

def process_directory(input_dir, output_file):
    """Process all files in directory and create header file"""
    
    header_content = """#pragma once
// Auto-generated file containing web resources
// Generated from ui/ directory

"""
    
    files_to_process = [
        ('index.html', 'MAIN_HTML'),
        ('scripts/main.js', 'MAIN_JS'),
        ('scripts/api.js', 'API_JS'),
        ('scripts/localization.js', 'LOCALIZATION_JS'),
        ('scripts/status.js', 'STATUS_JS'),
        ('scripts/temperature.js', 'TEMPERATURE_JS'),
        ('scripts/theme.js', 'THEME_JS'),
        ('scripts/uiState.js', 'UISTATE_JS'),
        ('scripts/weather.js', 'WEATHER_JS'),
        ('scripts/cloud.js', 'CLOUD_JS'),
        ('styles/main.css', 'MAIN_CSS'),
        ('styles/base.css', 'BASE_CSS'),
        ('styles/animations.css', 'ANIMATIONS_CSS'),
        ('styles/buttons.css', 'BUTTONS_CSS'),
        ('styles/clouds.css', 'CLOUDS_CSS'),
        ('styles/control-buttons.css', 'CONTROL_BUTTONS_CSS'),
        ('styles/dark-mode.css', 'DARK_MODE_CSS'),
        ('styles/language-switcher.css', 'LANGUAGE_SWITCHER_CSS'),
        ('styles/power-buttons.css', 'POWER_BUTTONS_CSS'),
        ('styles/responsive.css', 'RESPONSIVE_CSS'),
        ('styles/sliders.css', 'SLIDERS_CSS'),
        ('styles/status.css', 'STATUS_CSS'),
        ('styles/theme-switcher.css', 'THEME_SWITCHER_CSS'),
        ('styles/weather-bg.css', 'WEATHER_BG_CSS'),
        ('styles/weather-effects.css', 'WEATHER_EFFECTS_CSS'),
    ]
    
    for filepath, varname in files_to_process:
        full_path = os.path.join(input_dir, filepath)
        if os.path.exists(full_path):
            print(f"Processing {filepath}...")
            header_content += file_to_cpp_string(full_path, varname)
        else:
            print(f"Warning: File not found: {full_path}")
    
    # Write header file
    with open(output_file, 'w', encoding='utf-8') as f:
        f.write(header_content)
    
    print(f"Generated {output_file}")

if __name__ == "__main__":
    input_directory = "../ui"
    output_header = "../climatecontrol/WebResources.h"
    
    process_directory(input_directory, output_header)
