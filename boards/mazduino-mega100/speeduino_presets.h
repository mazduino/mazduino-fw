#pragma once

#include <cstdint>

// Sets the pins of Speeduino board preset `index` (see speeduino_presets.cpp).
// Returns false when there is no such preset.
bool applySpeeduinoPreset(uint16_t index);

// Index of the Speeduino v0.4 preset, the board default.
constexpr uint16_t SPEEDUINO_PRESET_V04 = 2;
