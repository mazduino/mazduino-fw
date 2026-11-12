#pragma once

#include <cstdint>

// Sets the pins of Speeduino board preset `index` (see speeduino_presets.cpp).
// Returns false when there is no such preset.
bool applySpeeduinoPreset(uint16_t index);
