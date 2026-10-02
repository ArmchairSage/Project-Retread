# Project RETREAD
Personal side project based on measuring and analysing data on tyre-road grip.

RETREAD is an acronym for **R**ain-or-shine **E**lectronic **T**y**RE** **A**dhesion **D**etector 
<br/>_(thanks to https://acronymify.com/ for helping come up with that one)_<br/><br/>

## Needed Context and Expositional Information
>[!IMPORTANT]
>***This project is based off of automotive manufacturer Nissan's _ATTESA_ system, particularly the ATTESA E-TS variant. This is not meant to be an attempt at "forging" Nissan's work, rather this is just a personal side project learning from what Nissan has developed. Think of it as a tribute to Nissan's technological works.***
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

## Project Intention(s)
***Too be clear, I'm not going to build a four-wheel drive system from scratch.*** That would require **WAY** too much time and resources on my part, not to mention my lack of experience in Mechanical Engineering.

Rather, I'm focusing on ***how*** you detect a loss of tyre grip, rather than ***what*** you do to mitigate it.

Earlier it was mentioned that:
>Said system is controlled by a 16-bit computer that measures the speed of each wheel via the <ins>A</ins>nti-lock <ins>B</ins>rake <ins>S</ins>ystem (ABS) sensors. A G-Sensor also feeds lateral and longitudinal inputs, which controls both the ABS and ATTESA E-TS system.

This is where part of the inspiration lies, along with [this article about directly measuring the friction between your tyres and the road](https://polyn.ai/gaining-precision-in-tire-road-grip-measurement/).

Thus the main goal of this project is to ***design software that can be used to detect how much grip a tyre has in various circumstances***, and being able to ***read, interpret and analyse the data collected.*** 
<br/>_Perhaps it may be used in testing an ATTESA-like system? That might be far-fetched and too ambitious at the moment._
