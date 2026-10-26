Slot-die coating is a widely used technique for the precise and uniform deposition of
thin films in manufacturing industries such as electronics, batteries, and biomedical de
vices. However, maintaining consistent coating quality depends on two key factors: sta
ble conveyor speed and precise temperature control during drying. Inconsistent drying
temperatures can affect solvent evaporation, film adhesion, and overall coating perfor
mance, while even small variations in motor speed can result in uneven film thickness
andimperfections. To address these issues, a closed-loop control system is implemented
using an Arduino Uno harnessing a Proportional-Integral (PI) controller. An infrared
(IR) sensor measures the stepper motor’s speed in real time, and the controller adjusts
the pulse delay dynamically to maintain the desired speed. This approach ensures stable
motor operation, minimizes speed fluctuations.
To ensure a consistent heat distribution during the drying process, we employ ther
mocouples, solid-state relays (SSRs), infrared heating elements and a PID temperature
controller.
By ensuring both precise speed control and stable temperature regulation, this sys
tem minimizes coating inconsistencies and enhances film quality. This method im
proves the scalability, dependability, and suitability of the slot-die coating process for
high-precision applications.
