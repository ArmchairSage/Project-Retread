# Project RETREAD
Personal side project based on measuring and analysing data directly from the friction between road tyres and terrain.

RETREAD is an acronym for **R**ain-or-shine **E**lectronic **T**y**RE** **A**dhesion **D**etector 
<br/>_(thanks to https://acronymify.com/ for helping come up with that one)_<br/><br/>

## Needed Context and Expositional Information
>[!IMPORTANT]
>***This project is based off of automotive manufacturer Nissan's _ATTESA_ four-wheel drive system, particularly the ATTESA E-TS variant. This is not meant to be an attempt at "forging" Nissan's work, rather this is just a personal side project learning from what Nissan has developed. Think of it as a tribute to Nissan and their contributions in technology and engineering.***
><br/>_Read for further information since I am not a qualified mechanic with the proper knowledge, nor do I own and have experience using an ATTESA-fitted vehicle: https://en.wikipedia.org/wiki/ATTESA_

<br/>ATTESA is a four-wheel drive system used in some Nissan cars. It stands for ***<ins>A</ins>dvanced <ins>T</ins>otal <ins>T</ins>raction <ins>E</ins>ngineering <ins>S</ins>ystem for <ins>A</ins>ll-Terrain***, with the E-TS version referring to ***<ins>E</ins>lectronic <ins>T</ins>orque <ins>S</ins>plit***.

The original ATTESA is a **permanent** four-wheel drive system. When you press down on the throttle, all four wheels on the car will turn.
<br/>The E-TS variant is an interesting case where only the ***rear wheels*** are constantly driven, and the front wheels only drive ***when one of the rear wheels starts to lose grip***. It is a sort of "conditional" four-wheel drive system.
>[!NOTE]
>A later update to the original ATTESA system made it so that the **front wheels** are constantly driven, while the rear wheels only drive when said front wheels lose grip. It is essentially an inverse of the E-TS variant's layout.

Mechanically, this is done through the use of a multi-plate wet clutch inside a transfer case, however for this project I am more interested with how the ATTESA E-TS system is controlled **from a software engineering perspective**.

Said system is controlled by a 16-bit computer that measures the speed of each wheel via the <ins>A</ins>nti-lock <ins>B</ins>rake <ins>S</ins>ystem (ABS) sensors. A G-Sensor also feeds lateral and longitudinal inputs, which controls both the ABS and ATTESA E-TS system.

When slip is detected on one of the rear wheels, the ATTESA system directs some of the car's torque to the front wheels through an open differential, adjusting to different torque ratios ranging from 0:100 to 50:50. 

As an example:
- 0:100 torque ratio - only the rear wheels are being driven.
- 30:70 split - 30% of the engine's power drives the front wheels, whilst 70% drives the rear wheels.
- 50:50 split - half of the engine's power drives the front wheels and another half drives the rear wheels, leading to an even distribution on all four wheels being driven.

In practice, a vehicle that has ATTESA E-TS performs like a rear wheel drive vehicle in normal conditions, but can also recover control when conditions aren't as optimal.

## Project Intentions
To be clear, ***I'm not going to build a four-wheel drive system from scratch.*** That would require **WAY** too much time and resources on my part, not to mention my lack of experience in Mechanical Engineering.

Rather, I'm focusing on ***how*** you detect a loss of tyre grip, rather than ***what*** you do to mitigate it.

Earlier it was mentioned that:
>Said system is controlled by a 16-bit computer that measures the speed of each wheel via the <ins>A</ins>nti-lock <ins>B</ins>rake <ins>S</ins>ystem (ABS) sensors. A G-Sensor also feeds lateral and longitudinal inputs, which controls both the ABS and ATTESA E-TS system.

This is where part of the inspiration lies, along with [this article about directly measuring the friction between your tyres and the road](https://polyn.ai/gaining-precision-in-tire-road-grip-measurement/), particularly this section of text:
>To address this gap, new emerging technologies are exploring direct sensing methods. These include <ins>***tire-embedded sensors that monitor vibration at the contact patch, along with edge AI chips that interpret data from accelerometers of standard TPMS nodes in tires***</ins>. Such innovations aim to give vehicles the ability to sense road conditions more like a human driver, through feel rather than inference.

Thus the main goal of this project is to design software that can... 
- Determine how much grip a tyre has in various circumstances <ins>by directly measuring the friction between the road and the tyre in real-time</ins>.
- Collect and store the data obtained from the above measurements.
- Display this data in an understandable way for analysis, monitoring, safety etc.

Once finished, the idea is to test the software within the tyre(s) of an actual car, exposed to different weather and terrain conditions within a certain time period.
This may be achieved using an [STM32](https://en.wikipedia.org/wiki/STM32) microcontroller paired with an MEMS (<ins>M</ins>icro-<ins>E</ins>lectro-<ins>M</ins>echanical <ins>S</ins>ystem) such as the [IIS3DWB](https://www.st.com/en/mems-and-sensors/iis3dwb.html) or the [LSM6DSV320X](https://www.st.com/en/mems-and-sensors/lsm6dsv320x.html).
But we'll cross that bridge when we get there.

<!-- STM32 picks:
* STM32H743 - top pick
    - Cortex-M7 @ 480 MHz, 1 MB SRAM, TCM (zero-wait-state access for DSP)
    - 3× 16-bit ADCs (2.4 MSPS each, 7.2 MSPS combined in interleaved mode)
    - Specifically called out in ST's own ecosystem as the board of choice for "high-performance vibration or signal analysis" and "predictive-maintenance vibration classifier"
    - Handles 50+ kSPS triaxial acquisition with headroom for real-time FFT and even on-device ML anomaly detection
    - 10/100 Ethernet + CAN-FD for vehicle integration
    - Overkill for simple logging, but the right ceiling for production

* STM32G474 - best ADC per £
    - Cortex-M4 @ 170 MHz, 320 KB SRAM
    - 3 independent 12-bit ADCs — the standout feature. Each can run up to 5 MSPS (tested at ~11 MSPS overclocked), and they can be interleaved for 10+ MSPS combined
    - Community consensus: "the fastest ADC I've found comparing to F4 / F7 / H7" in single-ADC mode
    - Cheaper and lower power than H7, ideal if you're driving 3 MEMS accelerometer channels via analog front end
    - Good if you want high sampling rate without jumping to the H7 price tier

* STM32F407 / STM32F446 - best for prototyping
    - Cortex-M4 @ 180 MHz, 320 KB SRAM
    - 3× 12-bit ADCs at 3.6 MSPS (up to ~6 MSPS in triple interleaved)
    - The NUCLEO-F446RE is the most commonly referenced dev board for vibration monitoring nodes in ST's own application notes 
    - Massive community, easiest to get running in a day with CubeMX
    - Sufficient for 10–20 kSPS triaxial with FFT — covers road texture and basic bearing fault detection
    - The natural "start here" before stepping up to G4/H7

Alternative ESP32 picks:

| Variant | Core / Clock | ADC Max Rate | DNL / INL | Notes |
|---------|-------------|-------------|-----------|-------|
| **ESP32 (original)** | 2× LX6 @ 240 MHz | **2 Msps** (DIG) | ±7 / ±12 | Fastest ADC in the family, but worst linearity. 2× 8-bit DAC (unique). TWAI/CAN available. |
| **ESP32-S3** | 2× LX7 @ 240 MHz | 100 kSPS | ±4 / ±8 | Better ADC accuracy, SIMD for DSP, USB OTG, up to 8 MB PSRAM. No DAC. |
| **ESP32-C3** | 1× RISC-V @ 160 MHz | 100 kSPS | ±7 / ±12 | Only 6 ADC channels, 22 GPIO, no PSRAM. Cheapest. |
| **ESP32-C5** | 1× RISC-V @ 160 MHz | 2 Msps | ±2 / ±4 | Newer. Best ADC accuracy in the family at high speed, but single-core. |
| **ESP32-P4** | 2× RISC-V @ 400 MHz | High | Good | Newest high-performance part, but overkill for this use. |

-->
