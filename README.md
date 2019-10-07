# Team9 - Hedwig

## Hedwig went undefeated in competition!

This repository is contains all of the work that Team 9 (Alex Carbo, Maxwell Yang, Kausik Krishnakumar, Sarvan Gill) produced throughout their summer, with the main focus being on building a fully autonomous robot for a robot competition in August 2019. 

The **ENPH257/** folder contains MATLAB scripts (including data), to investigate thermal waves through the heating of an alumninium rod.

All other folders are pertaining to the robot.

## Robot
Link to the rules and structure of the competition: https://docs.google.com/document/d/1WXgxAmkSgfv2YprMDtSkUyIwbtqzgsT3AemDqi9obIw/edit

Link to news clip on the competition:
https://www.facebook.com/BTCityNewsVAN/videos/583404632190468/

### Microcontrollers
We used 2 STM-32 microcontrollers, giving us a single master controller and a single slave controller. The master handled the navigation aspect of the competition, while the slave controlled the arm movements. The master ran the **robot_test_code/** folder and the slave ran the **slave_code/** folder. 

### CAD
All CAD is in the **Solidworks/** folder. The main assembly is **Robot_V1.SLDASM**. When opening this file it may ask for the loaction of the other files, in which case just point to the correct files. Do not move the files after it has opened. 

The .dxf are the files used to cut the parts using either a laser jet cutter or a water jet cutter. The main purpose of the CAD, was to produce these files for cutting and measurment purposes, so in almost all cases these files were just exported from their respective Solidworks part.


#### Team9 - Beares of The Mandate of Heaven

Explore. Create. Innovate. That is all we know.

The world is our canvas. We are Picasso, Monet, Van Gogh, and Dali.

We gave the other teams a chance to surrender.


They refused.

#### Alea iacta est.
