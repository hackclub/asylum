# cyrilli's weather station submission

<div align="center">
    <img src="https://cloud-axpfu2g0e-hack-club-bot.vercel.app/12024-12-22t15_10_49_729298641-06_00.png" width="53%" height="auto" />
    &nbsp;
    &nbsp;
    <img src="https://cloud-axpfu2g0e-hack-club-bot.vercel.app/02024-12-22t15_10_22_281533985-06_00.png" width="40%" height="auto" />
</div>

## BOM

- 1x Wemos/Lolin ESP32-C3 board
- 1x 1.8 inch TFT display
- 2x ELM3052 Triac
    - C142300
- 1x 75 Ohm 0603 Resistor
    - C4275
- 1x 10 Ohm 1206 Resistor
    - C17903
- 3x 2x8P 2.54mm Female Header
    - C5160823
- 8x M3 25mm Double-ended Standoff
- 2x M3 16mm Double-ended Standoff
- 4x M3 50mm Screw
- 2x M3 16mm Screw

## Planned Use

I plan to use this as a small display for agenda items or connect it to my computer to use as a status panel. I will also run wires to our garage door to act as a smart door opener.

## Design Process

The design was inspired by 龙少's stacked homebrew CPU design. Since the minimum order for PCBs is 5, I used the extra boards to sandwich the main board, acting as a case without needing extra 3D printed components. The PCB is perfectly square so that two layers can be rotated and stacked for the bottome case, covering all the drill holes and cutouts of each other. Pin connections between the LCD and the ESP32 was chosen to permit visually pleasing routing on a single layer.

## Case

I am planning to stack some unpopulated PCBs vertically for a homebrew-cpu-like "case" instead of using 3D printed parts.

## Firmware

Written in CircuitPython, will be expanded once I have hardware to test on.
