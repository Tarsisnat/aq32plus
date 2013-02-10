/*
  October 2012

  aq32Plus Rev -

  Copyright (c) 2012 John Ihlein.  All rights reserved.

  Open Source STM32 Based Multicopter Controller Software

  Includes code and/or ideas from:

  1)AeroQuad
  2)BaseFlight
  3)CH Robotics
  4)MultiWii
  5)S.O.H. Madgwick
  6)UAVX

  Designed to run on the AQ32 Flight Control Board

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

///////////////////////////////////////////////////////////////////////////////

#include "board.h"

///////////////////////////////////////////////////////////////////////////////
// MAX7456 CLI
///////////////////////////////////////////////////////////////////////////////

void max7456CLI()
{
    uint8_t  max7456query;
    uint8_t  validQuery = false;

    cliBusy = true;

    usbPrint("\nEntering MAX7456 CLI....\n\n");

    if (eepromConfig.osdInstalled)
    {
    	resetMax7456();

        while(true)
        {
			usbPrint("MAX7456 CLI -> ");

			while ((usbAvailable() == false) && (validQuery == false));

			if (validQuery == false)
			    max7456query = usbRead();

			usbPrint("\n");

			switch(max7456query)
			{
                ///////////////////////

                case 'a': // OSD Configuration
                    usbPrint("\nOSD Installed:               ");
                    if (eepromConfig.osdInstalled)
                    	usbPrint("True\n");
                    else
                	    usbPrint("False\n");

                    if (eepromConfig.osdInstalled)
                    {
		        	    usbPrint("OSD Default Video Standard:  ");
                        if (eepromConfig.defaultVideoStandard)
                    	    usbPrint("PAL\n");
                        else
                    	    usbPrint("NTSC\n");

                        usbPrint("OSD Display Units:           ");
                        if (eepromConfig.metricUnits)
                    	    usbPrint("Metric\n");
                        else
                    	    usbPrint("English\n");

                        usbPrint("OSD Altitude:                ");
                        if (eepromConfig.osdDisplayAlt)
                    	    usbPrint("On\n");
                        else
                    	    usbPrint("Off\n");

                        usbPrint("OSD Artifical Horizon:       ");
                        if (eepromConfig.osdDisplayAH)
                    	    usbPrint("On\n");
                        else
                    	    usbPrint("Off\n");

                        usbPrint("OSD Attitude:                ");
                        if (eepromConfig.osdDisplayAtt)
                    	    usbPrint("On\n");
                        else
                    	    usbPrint("Off\n");

                        usbPrint("OSD Heading:                 ");
                        if (eepromConfig.osdDisplayHdg)
                    	    usbPrint("On\n");
                        else
                    	    usbPrint("Off\n");
		            }

                    usbPrint("\n");
                    validQuery = false;
                    break;

                ///////////////////////

                case 'b': // Enable OSD Altitude Display
                    eepromConfig.osdDisplayAlt  = true;
                    usbPrint( "\nAltitude Display On....\n\n" );

                    max7456query = 'a';
                    validQuery = true;
                    break;

                ///////////////////////

                case 'c': // Enable OSD Artifical Horizon Display
                    eepromConfig.osdDisplayAH  = true;
                    eepromConfig.osdDisplayAtt = false;
                    usbPrint( "\nArtificial Horizon On, Attitude Off....\n\n" );

                    max7456query = 'a';
                    validQuery = true;
                    break;

                ///////////////////////

                case 'd': // Enable OSD Attitude Display
                    eepromConfig.osdDisplayAtt = true;
                    eepromConfig.osdDisplayAH  = false;
                    usbPrint( "\nAttitude On, Artificial Horizon Off....\n\n" );

                    max7456query = 'a';
                    validQuery = true;
                    break;

                ///////////////////////

                case 'e': // Enable OSD Heading Display
                    eepromConfig.osdDisplayHdg = true;
                    usbPrint( "\nHeading On....\n\n" );

                    max7456query = 'a';
                    validQuery = true;
                    break;

                ///////////////////////

                case 'q': // Set English Display Units
                    eepromConfig.metricUnits = false;
                    usbPrint( "\nUnits Changed to English....\n\n" );

                    max7456query = 'a';
                    validQuery = true;
                    break;

                ///////////////////////

                case 'r': // reset
                    resetMax7456();
                    usbPrint("\nMAX7456 Reset....\n\n");
                    break;

                ///////////////////////

                case 's': // show charset
                    showMax7456Font();
                    usbPrint("\nMAX7456 Character Set Displayed....\n\n");
                    break;

                ///////////////////////

                case 't': // download font
                    downloadMax7456Font();
                    break;

                ///////////////////////

                case 'u': // change OSD status to uninstalled
                    eepromConfig.osdInstalled = false;
                    usbPrint("\nOSD State Changed to Uninstalled....\n");
                    usbPrint("\nSystem Resetting....\n\n");
                    delay(100);
                    writeEEPROM();
                    systemReset(false);
                    break;

    			///////////////////////

    		    case 'v': // change default video standard
    			    if (eepromConfig.defaultVideoStandard)         // If  PAL
    			        eepromConfig.defaultVideoStandard = NTSC;  // Set NTSC
    			    else                                           // If  NTSC
    			        eepromConfig.defaultVideoStandard = PAL;   // Set PAL

                    usbPrint("\nDefault Video Standard Changed to ");
                    if (eepromConfig.defaultVideoStandard)
                        usbPrint("PAL....\n");
                    else
                        usbPrint("NTSC....\n");

                    usbPrint("\nSystem Resetting....\n\n");
    			    delay(100);
    				writeEEPROM();
    				systemReset(false);
    				break;

    		    ///////////////////////

    			case 'x':
    			    usbPrint("\nExiting MAX7456 CLI....\n\n");
    			    cliBusy = false;
    			    return;
    			    break;

                ///////////////////////

                case 'B': // Disable OSD Altitude Display
                    eepromConfig.osdDisplayAlt = false;
                    usbPrint( "\nAltitude Off....\n\n" );

                    max7456query = 'a';
                    validQuery = true;
                    break;

                ///////////////////////

                case 'C': // Disable OSD Artifical Horizon Display
                    eepromConfig.osdDisplayAH = false;
                    usbPrint( "\nArtifical Horizon Off....\n\n" );

                    max7456query = 'a';
                    validQuery = true;
                    break;

                ///////////////////////

                case 'D': // Disable OSD Attitude Display
                    eepromConfig.osdDisplayAtt = false;
                    usbPrint( "\nAttitude Off....\n\n" );

                    max7456query = 'a';
                    validQuery = true;
                    break;

                ///////////////////////

                case 'E': // Disable OSD Heading Display
                    eepromConfig.osdDisplayHdg = false;
                    usbPrint( "\nHeading Off....\n\n" );

                    max7456query = 'a';
                    validQuery = true;
                    break;

               ///////////////////////

               case 'Q': // Set Metric Display Units
                    eepromConfig.metricUnits = true;
                    usbPrint( "\nUnits Changed to Metric....\n\n" );

                    max7456query = 'a';
                    validQuery = true;
                    break;

                ///////////////////////////

                case 'W': // Write EEPROM Parameters
                    usbPrint("\nWriting EEPROM Parameters....\n\n");
                    writeEEPROM();
                    break;

				///////////////////////

				case '?':
				   	usbPrint("\n");
				   	usbPrint("'a' OSD Configuration\n");
				    usbPrint("'b' Enable OSD Artificial Horizon Display  'B' Disable OSD Artificial Horizon Display\n");
				   	usbPrint("'c' Enable OSD Artificial Horizon Display  'C' Disable OSD Artificial Horizon Display\n");
				   	usbPrint("'d' Enable OSD Attitude Display            'D' Disable OSD Attitude Display\n");
				   	usbPrint("'e' Enable OSD Heading Display             'E' Disable OSD Heading Display\n");
				   	usbPrint("'q' Set English Display Units              'Q' Set Metric Display Units\n");
				    usbPrint("'r' Reset MAX7456\n");
				   	usbPrint("'s' Display MAX7456 Character Set\n");
				   	usbPrint("'t' Download Font to MAX7456\n");
				   	usbPrint("'u' Change OSD State to Uninstalled\n");
				   	usbPrint("'v' Change Default Video Standard\n");
				   	usbPrint("'x' Exit Sensor CLI                        'W' Write EEPROM Parameters\n");
				   	usbPrint("\n");
   		    	    break;

   		    	///////////////////////
		    }
	    }
	}
	else
	{
		while(true)
		{
			usbPrint("MAX7456 CLI -> ");

		    while (usbAvailable() == false);

			max7456query = usbRead();

			usbPrint("\n");

			switch(max7456query)
			{
                ///////////////////////

                case 'i': // change OSD status to installed
            	    eepromConfig.osdInstalled = true;
            	    usbPrint("\nOSD State Changed to Installed....\n");
            	    usbPrint("\nSystem Resetting....\n\n");
            	    writeEEPROM();
            	    delay(100);
            	    systemReset(false);
            	    break;

				///////////////////////

				case 'x':
				    usbPrint("\nExiting MAX7456 CLI....\n\n");
				    cliBusy = false;
				    return;
				    break;

				///////////////////////

				case '?':
					usbPrint("\n");
				    usbPrint("'i' Change OSD State to Installed\n");
				   	usbPrint("'x' Exit MAX7456 CLI\n");
				   	usbPrint("\n");
				   	break;

				///////////////////////
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// Mixer CLI
///////////////////////////////////////////////////////////////////////////////

void mixerCLI()
{
    float    tempFloat;

    uint8_t  index;
    uint8_t  rows, columns;

    uint8_t  mixerQuery;
    uint8_t  validQuery = false;

    cliBusy = true;

    usbPrint("\nEntering Mixer CLI....\n\n");

    while(true)
    {
        usbPrint("Mixer CLI -> ");

		while ((usbAvailable() == false) && (validQuery == false));

		if (validQuery == false)
		    mixerQuery = usbRead();

		usbPrint("\n");

		switch(mixerQuery)
		{
            ///////////////////////////

            case 'a': // Mixer Configuration
                usbPrint("\nMixer Configuration:            ");
                switch (eepromConfig.mixerConfiguration)
                {
                    case MIXERTYPE_GIMBAL:
                    	usbPrint("MIXERTYPE GIMBAL\n");
                    	break;

                    ///////////////////////

                    case MIXERTYPE_FLYING_WING:
                    	usbPrint("MIXERTYPE FLYING WING\n");
                    	break;

                    ///////////////////////

                    case MIXERTYPE_BI:
                        usbPrint("MIXERTYPE BICOPTER\n");
                        break;

                    ///////////////////////

                    case MIXERTYPE_TRI:
                        usbPrint("MIXERTYPE TRICOPTER\n");
                        break;

                    ///////////////////////

                    case MIXERTYPE_QUADP:
                        usbPrint("MIXERTYPE QUAD PLUS\n");
                        break;

                    case MIXERTYPE_QUADX:
                        usbPrint("MIXERTYPE QUAD X\n");
                        break;

                    case MIXERTYPE_VTAIL4_NO_COMP:
                    	usbPrint("MULTITYPE VTAIL NO COMP\n");
                    	break;

                    case MIXERTYPE_VTAIL4_Y_COMP:
                    	usbPrint("MULTITYPE VTAIL Y COMP\n");
                    	break;

                    case MIXERTYPE_VTAIL4_RY_COMP:
                    	usbPrint("MULTITYPE VTAIL RY COMP\n");
                    	break;

                    case MIXERTYPE_VTAIL4_PY_COMP:
                    	usbPrint("MULTITYPE VTAIL PY COMP\n");
                    	break;

                    case MIXERTYPE_VTAIL4_RP_COMP:
                    	usbPrint("MULTITYPE VTAIL RP COMP\n");
                    	break;

                    case MIXERTYPE_VTAIL4_RPY_COMP:
                    	usbPrint("MULTITYPE VTAIL RPY COMP\n");
                    	break;

                    case MIXERTYPE_Y4:
                    	usbPrint("MIXERTYPE Y4\n");
                    	break;

                    ///////////////////////

                    case MIXERTYPE_HEX6P:
                        usbPrint("MIXERTYPE HEX PLUS\n");
                        break;

                    case MIXERTYPE_HEX6X:
                        usbPrint("MIXERTYPE HEX X\n");
                        break;

                    case MIXERTYPE_Y6:
                        usbPrint("MIXERTYPE Y6\n");
                        break;

                    ///////////////////////

                    case MIXERTYPE_OCTOF8P:
                        usbPrint("MIXERTYPE FLAT OCTO PLUS\n");
                        break;

                    case MIXERTYPE_OCTOF8X:
                        usbPrint("MIXERTYPE FLAT OCTO X\n");
                        break;

                    case MIXERTYPE_OCTOX8P:
                        usbPrint("MIXERTYPE COAXIAL OCTO PLUS\n");
                        break;

                    case MIXERTYPE_OCTOX8X:
                        usbPrint("MIXERTYPE COAXIAL OCTO X\n");
                        break;

                    ///////////////////////

                    case MIXERTYPE_FREEMIX:
                    	usbPrint("MIXERTYPE FREE MIX\n");
                    	break;
                }

                usbPrint("Number of Motors:               ");
                itoa(numberMotor,                         numberString, 10); usbPrint(numberString); usbPrint("\n");

                usbPrint("ESC PWM Rate:                   ");
                itoa((uint16_t)eepromConfig.escPwmRate,   numberString, 10); usbPrint(numberString); usbPrint("\n");

                usbPrint("Servo PWM Rate:                 ");
                itoa((uint16_t)eepromConfig.servoPwmRate, numberString, 10); usbPrint(numberString); usbPrint("\n");

                if ( eepromConfig.mixerConfiguration == MIXERTYPE_BI )
                {
                    usbPrint("BiCopter Left Servo Min:        ");
                    itoa((uint16_t)eepromConfig.biLeftServoMin,  numberString, 10); usbPrint(numberString); usbPrint("\n");
                    usbPrint("BiCopter Left Servo Mid:        ");
                    itoa((uint16_t)eepromConfig.biLeftServoMid,  numberString, 10); usbPrint(numberString); usbPrint("\n");
                    usbPrint("BiCopter Left Servo Max:        ");
                    itoa((uint16_t)eepromConfig.biLeftServoMax,  numberString, 10); usbPrint(numberString); usbPrint("\n");
                    usbPrint("BiCopter Right Servo Min:       ");
                    itoa((uint16_t)eepromConfig.biRightServoMin, numberString, 10); usbPrint(numberString); usbPrint("\n");
                    usbPrint("BiCopter Right Servo Mid:       ");
                    itoa((uint16_t)eepromConfig.biRightServoMid, numberString, 10); usbPrint(numberString); usbPrint("\n");
                    usbPrint("BiCopter Right Servo Max:       ");
                    itoa((uint16_t)eepromConfig.biRightServoMax, numberString, 10); usbPrint(numberString); usbPrint("\n");
                }

                if ( eepromConfig.mixerConfiguration == MIXERTYPE_FLYING_WING )
                {
                    usbPrint("Roll Direction Left:            ");
                    itoa((uint16_t)eepromConfig.rollDirectionLeft,   numberString, 10); usbPrint(numberString); usbPrint("\n");
                    usbPrint("Roll Direction Right:           ");
                    itoa((uint16_t)eepromConfig.rollDirectionRight,  numberString, 10); usbPrint(numberString); usbPrint("\n");
                    usbPrint("Pitch Direction Left:           ");
                    itoa((uint16_t)eepromConfig.pitchDirectionLeft,  numberString, 10); usbPrint(numberString); usbPrint("\n");
                    usbPrint("Pitch Direction Right:          ");
                    itoa((uint16_t)eepromConfig.pitchDirectionRight, numberString, 10); usbPrint(numberString); usbPrint("\n");
                    usbPrint("Wing Left Minimum:              ");
                    itoa((uint16_t)eepromConfig.wingLeftMinimum,     numberString, 10); usbPrint(numberString); usbPrint("\n");
                    usbPrint("Wing Left Maximum:              ");
                    itoa((uint16_t)eepromConfig.wingLeftMaximum,     numberString, 10); usbPrint(numberString); usbPrint("\n");
                    usbPrint("Wing Right Minimum:             ");
                    itoa((uint16_t)eepromConfig.wingRightMinimum,    numberString, 10); usbPrint(numberString); usbPrint("\n");
                    usbPrint("Wing Right Maximum:             ");
                    itoa((uint16_t)eepromConfig.wingRightMaximum,    numberString, 10); usbPrint(numberString); usbPrint("\n");
                }

                if ( eepromConfig.mixerConfiguration == MIXERTYPE_GIMBAL )
                {
                    usbPrint("Gimbal Roll Servo Min:          ");
                    itoa((uint16_t)eepromConfig.gimbalRollServoMin,  numberString, 10); usbPrint(numberString); usbPrint("\n");
                    usbPrint("Gimbal Roll Servo Mid:          ");
                    itoa((uint16_t)eepromConfig.gimbalRollServoMid,  numberString, 10); usbPrint(numberString); usbPrint("\n");
                    usbPrint("Gimbal Roll Servo Max:          ");
                    itoa((uint16_t)eepromConfig.gimbalRollServoMax,  numberString, 10); usbPrint(numberString); usbPrint("\n");
                    usbPrint("Gimbal Roll Servo Gain:        ");
                    ftoa(eepromConfig.gimbalRollServoGain, numberString);               usbPrint(numberString); usbPrint("\n");
                    usbPrint("Gimbal Pitch Servo Min:         ");
                    itoa((uint16_t)eepromConfig.gimbalPitchServoMin, numberString, 10); usbPrint(numberString); usbPrint("\n");
                    usbPrint("Gimbal Pitch Servo Mid:         ");
                    itoa((uint16_t)eepromConfig.gimbalPitchServoMid, numberString, 10); usbPrint(numberString); usbPrint("\n");
                    usbPrint("Gimbal Pitch Servo Max:         ");
                    itoa((uint16_t)eepromConfig.gimbalPitchServoMax, numberString, 10); usbPrint(numberString); usbPrint("\n");
                    usbPrint("Gimbal Pitch Servo Gain:       ");
                    ftoa(eepromConfig.gimbalPitchServoGain, numberString);              usbPrint(numberString); usbPrint("\n");
                }

                if ( eepromConfig.mixerConfiguration == MIXERTYPE_TRI )
                {
                    usbPrint("TriCopter Yaw Servo Min:        ");
                    itoa((uint16_t)eepromConfig.triYawServoMin, numberString, 10); usbPrint(numberString); usbPrint("\n");
                    usbPrint("TriCopter Yaw Servo Mid:        ");
                    itoa((uint16_t)eepromConfig.triYawServoMid, numberString, 10); usbPrint(numberString); usbPrint("\n");
                    usbPrint("TriCopter Yaw Servo Max:        ");
                    itoa((uint16_t)eepromConfig.triYawServoMax, numberString, 10); usbPrint(numberString); usbPrint("\n");
                }

                if (eepromConfig.mixerConfiguration == MIXERTYPE_VTAIL4_Y_COMP  ||
                    eepromConfig.mixerConfiguration == MIXERTYPE_VTAIL4_RY_COMP ||
                    eepromConfig.mixerConfiguration == MIXERTYPE_VTAIL4_PY_COMP ||
                    eepromConfig.mixerConfiguration == MIXERTYPE_VTAIL4_RP_COMP ||
                    eepromConfig.mixerConfiguration == MIXERTYPE_VTAIL4_RPY_COMP)
                {
                    usbPrint("V Tail Angle                   ");
                    ftoa(eepromConfig.vTailAngle, numberString); usbPrint(numberString); usbPrint("\n");
    			}

                usbPrint("Yaw Direction:                  ");
                itoa((int8_t)eepromConfig.yawDirection,   numberString, 10); usbPrint(numberString); usbPrint("\n\n");

                validQuery = false;
                break;

            ///////////////////////////

            case 'b': // Free Mix Matrix
        	    usbPrint("\nNumber of Free Mixer Motors:  ");
        	    itoa( eepromConfig.freeMixMotors, numberString, 10 ); usbPrint( numberString ); usbPrint("\n\n");
                usbPrint("         Roll    Pitch   Yaw\n");

        	    for ( index = 0; index < eepromConfig.freeMixMotors; index++ )
        	    {
        	    	usbPrint("Motor"); itoa(index, numberString, 10);       usbPrint(numberString); usbPrint("  ");
        	    	ftoa(eepromConfig.freeMix[index][ROLL ], numberString); usbPrint(numberString); usbPrint("  ");
        	    	ftoa(eepromConfig.freeMix[index][PITCH], numberString); usbPrint(numberString); usbPrint("  ");
        	    	ftoa(eepromConfig.freeMix[index][YAW  ], numberString); usbPrint(numberString); usbPrint("\n");
        	    }

        	    usbPrint("\n");
        	    validQuery = false;
        	    break;

            ///////////////////////////

			case 'x':
			    usbPrint("\nExiting Mixer CLI....\n\n");
			    cliBusy = false;
			    return;
			    break;

            ///////////////////////////

            case 'A': // Read Mixer Configuration
                eepromConfig.mixerConfiguration = (uint8_t)readFloatUsb();
                usbPrint( "\nMixer Configuration Received....\n\n" );
        	    initMixer();

        	    mixerQuery = 'a';
                validQuery = true;
		        break;

            ///////////////////////////

            case 'B': // Read ESC and Servo PWM Update Rates
                eepromConfig.escPwmRate   = (uint16_t)readFloatUsb();
                eepromConfig.servoPwmRate = (uint16_t)readFloatUsb();
                usbPrint( "\nPWM Update Rates Received....\n\n");

                pwmEscInit(eepromConfig.escPwmRate);
                pwmServoInit(eepromConfig.servoPwmRate);

                mixerQuery = 'a';
                validQuery = true;
        	    break;

            ///////////////////////////

            case 'C': // Read BiCopter Left Servo Parameters
           	    eepromConfig.biLeftServoMin = readFloatUsb();
           	    eepromConfig.biLeftServoMid = readFloatUsb();
           	    eepromConfig.biLeftServoMax = readFloatUsb();
           	    usbPrint( "\nBiCopter Left Servo Parameters Received....\n\n");

           	    mixerQuery = 'a';
                validQuery = true;
                break;

            ///////////////////////////

            case 'D': // Read BiCopter Right Servo Parameters
           	    eepromConfig.biRightServoMin = readFloatUsb();
           	    eepromConfig.biRightServoMid = readFloatUsb();
           	    eepromConfig.biRightServoMax = readFloatUsb();
           	    usbPrint( "\nBiCopter Right Servo Parameters Received....\n\n");

           	    mixerQuery = 'a';
                validQuery = true;
                break;

            ///////////////////////////

            case 'E': // Read Flying Wing Servo Directions
                eepromConfig.rollDirectionLeft   = readFloatUsb();
                eepromConfig.rollDirectionRight  = readFloatUsb();
                eepromConfig.pitchDirectionLeft  = readFloatUsb();
                eepromConfig.pitchDirectionRight = readFloatUsb();
          	    usbPrint( "\nFlying Wing Servo Directions Received....\n\n");

         	    mixerQuery = 'a';
                validQuery = true;
                break;

            ///////////////////////////

            case 'F': // Read Flying Wing Servo Limits
           	    eepromConfig.wingLeftMinimum  = readFloatUsb();
           	    eepromConfig.wingLeftMaximum  = readFloatUsb();
           	    eepromConfig.wingRightMinimum = readFloatUsb();
           	    eepromConfig.wingRightMaximum = readFloatUsb();
           	    usbPrint( "\nFlying Wing Servo Limits Received....\n\n");

                mixerQuery = 'a';
                validQuery = true;
                break;

            ///////////////////////////

            case 'G': // Read Free Mix Motor Number
           	    eepromConfig.freeMixMotors = (uint8_t)readFloatUsb();
           	    usbPrint( "\nFree Mix Motor Number Received....\n\n");
           	    initMixer();

           	    mixerQuery = 'b';
                validQuery = true;
                break;

            ///////////////////////////

            case 'H': // Read Free Mix Matrix Element
                rows    = (uint8_t)readFloatUsb();
                columns = (uint8_t)readFloatUsb();
                eepromConfig.freeMix[rows][columns] = readFloatUsb();
                usbPrint( "\nFree Mix Value Received....\n\n");

                mixerQuery = 'b';
                validQuery = true;
                break;

            ///////////////////////////

            case 'I': // Read Gimbal Roll Servo Parameters
         	    eepromConfig.gimbalRollServoMin  = readFloatUsb();
           	    eepromConfig.gimbalRollServoMid  = readFloatUsb();
           	    eepromConfig.gimbalRollServoMax  = readFloatUsb();
           	    eepromConfig.gimbalRollServoGain = readFloatUsb();
           	    usbPrint( "\nGimbal Roll Servo Parameters Received....\n\n");

           	    mixerQuery = 'a';
                validQuery = true;
                break;

            ///////////////////////////

            case 'J': // Read Gimbal Pitch Servo Parameters
           	    eepromConfig.gimbalPitchServoMin  = readFloatUsb();
           	    eepromConfig.gimbalPitchServoMid  = readFloatUsb();
           	    eepromConfig.gimbalPitchServoMax  = readFloatUsb();
           	    eepromConfig.gimbalPitchServoGain = readFloatUsb();
           	    usbPrint( "\nGimbal Pitch Servo Parameters Received....\n\n");

           	    mixerQuery = 'a';
                validQuery = true;
                break;

            ///////////////////////////

            case 'K': // Read TriCopter YawServo Parameters
        	    eepromConfig.triYawServoMin = readFloatUsb();
           	    eepromConfig.triYawServoMid = readFloatUsb();
           	    eepromConfig.triYawServoMax = readFloatUsb();
           	    usbPrint( "\nTriCopter Yaw Servo Parameters Received....\n\n");

           	    mixerQuery = 'a';
                validQuery = true;
                break;

            ///////////////////////////

            case 'L': // Read V Tail Angle
        	    eepromConfig.vTailAngle = readFloatUsb();
        	    usbPrint("\nV Tail Angle Received....\n\n");

        	    mixerQuery = 'a';
                validQuery = true;
                break;

            ///////////////////////////

            case 'M': // Read yaw direction
                tempFloat = readFloatUsb();
                if (tempFloat >= 0.0)
                    tempFloat = 1.0;
                else
                	tempFloat = -1.0;

                eepromConfig.yawDirection = tempFloat;
                usbPrint("\nYaw Direction Received....\n\n");

                mixerQuery = 'a';
                validQuery = true;
                break;

            ///////////////////////////

            case 'W': // Write EEPROM Parameters
                usbPrint("\nWriting EEPROM Parameters....\n\n");
                writeEEPROM();
                break;

			///////////////////////////

			case '?':
			   	usbPrint("\n");
			   	usbPrint("'a' Mixer Configuration Data               'A' Set Mixer Configuration              A1 thru 21, see aq32Plus.h\n");
   		        usbPrint("'b' Free Mixer Configuration               'B' Set PWM Rates                        BESC;Servo\n");
			   	usbPrint("                                           'C' Set BiCopter Left Servo Parameters   CMin;Mid;Max\n");
			   	usbPrint("                                           'D' Set BiCopter Right Servo Parameters  DMin;Mid;Max\n");
			   	usbPrint("                                           'E' Set Flying Wing Servo Directions     ERollLeft;RollRight;PitchLeft;PitchRight\n");
			   	usbPrint("                                           'F' Set Flying Wing Servo Limits         FLeftMin;LeftMax;RightMin;RightMax\n");
   		        usbPrint("                                           'G' Set Number of FreeMix Motors         GNumber\n");
   		        usbPrint("                                           'H' Set FreeMix Matrix Element           HRow;Column;Element\n");
   		        usbPrint("                                           'I' Set Gimbal Roll Servo Parameters     IMin;Mid;Max;Gain\n");
   		        usbPrint("                                           'J' Set Gimbal Pitch Servo Parameters    JMin;Mid;Max;Gain\n");
   		        usbPrint("                                           'K' Set TriCopter Servo Parameters       KMin;Mid;Max\n");
   		        usbPrint("                                           'L' Set V Tail Angle                     LAngle\n");
   		        usbPrint("                                           'M' Set Yaw Direction                    M1 or $-1\n");
   		        usbPrint("'x' Exit Mixer CLI                         'W' Write EEPROM Parameters\n");
			   	usbPrint("\n");
	    	    break;

	    	///////////////////////////
	    }
	}

}

///////////////////////////////////////////////////////////////////////////////
// Receiver CLI
///////////////////////////////////////////////////////////////////////////////

void receiverCLI()
{
    char     rcOrderString[9];
    uint8_t  index;
    uint8_t  receiverQuery;
    uint8_t  validQuery = false;

    cliBusy = true;

    usbPrint("\nEntering Receiver CLI....\n\n");

    while(true)
    {
        usbPrint("Receiver CLI -> ");

		while ((usbAvailable() == false) && (validQuery == false));

		if (validQuery == false)
		    receiverQuery = usbRead();

		usbPrint("\n");

		switch(receiverQuery)
		{
            ///////////////////////////

            case 'a': // Receiver Configuration
                usbPrint("\nReceiver Type:                  ");
                switch(eepromConfig.receiverType)
                {
                    case PARALLEL_PWM:
                        usbPrint("Parallel\n");
                        break;
                    case SERIAL_PWM:
                        usbPrint("Serial\n");
                        break;
                    case SPEKTRUM:
                        usbPrint("Spektrum\n");
                        break;
		        }

                usbPrint("Current RC Channel Assignment:  ");
                for (index = 0; index < 8; index++)
                    rcOrderString[eepromConfig.rcMap[index]] = rcChannelLetters[index];

                rcOrderString[index] = '\0';

                usbPrint(rcOrderString);  usbPrint("\n");

                usbPrint("Spektrum Resolution:            ");
                if (eepromConfig.spektrumHires)
				    usbPrint("11 Bit Mode\n");
				else
				    usbPrint("10 Bit Mode\n");

				usbPrint("Number of Spektrum Channels:    ");
				itoa(eepromConfig.spektrumChannels, numberString,10); usbPrint(numberString); usbPrint("\n");

                usbPrint("Mid Command:                    ");
				itoa((uint16_t)eepromConfig.midCommand,   numberString, 10); usbPrint(numberString); usbPrint("\n");

				usbPrint("Min Check:                      ");
				itoa((uint16_t)eepromConfig.minCheck,     numberString, 10); usbPrint(numberString); usbPrint("\n");

				usbPrint("Max Check:                      ");
				itoa((uint16_t)eepromConfig.maxCheck,     numberString, 10); usbPrint(numberString); usbPrint("\n");

				usbPrint("Min Throttle:                   ");
				itoa((uint16_t)eepromConfig.minThrottle,  numberString, 10); usbPrint(numberString); usbPrint("\n");

				usbPrint("Max Thottle:                    ");
				itoa((uint16_t)eepromConfig.maxThrottle,  numberString, 10); usbPrint(numberString); usbPrint("\n\n");

                validQuery = false;
                break;

            ///////////////////////////

			case 'x':
			    usbPrint("\nExiting Receiver CLI....\n\n");
			    cliBusy = false;
			    return;
			    break;

            ///////////////////////////

            case 'A': // Read RX Input Type
                eepromConfig.receiverType = (uint8_t)readFloatUsb();
			    usbPrint( "\nReceiver Type Received....\n");

			    usbPrint("\nSystem Reseting....\n");
			    delay(100);
			    writeEEPROM();
			    systemReset(false);

		        break;

            ///////////////////////////

            case 'B': // Read RC Control Order
                readStringUsb( rcOrderString, 8 );
                usbPrint( "\nRC Channel Order Received...." );
                usbPrint( rcOrderString );
                usbPrint("\n\n");
                parseRcChannels( rcOrderString );

          	    receiverQuery = 'a';
                validQuery = true;
        	    break;

            ///////////////////////////

            case 'C': // Read Spektrum Resolution
                eepromConfig.spektrumHires = (uint8_t)readFloatUsb();
                usbPrint("\nSpektrum Resolution Received....\n\n");

                receiverQuery = 'a';
                validQuery = true;
                break;

            ///////////////////////////

            case 'D': // Read Number of Spektrum Channels
                eepromConfig.spektrumChannels = (uint8_t)readFloatUsb();
                usbPrint("\nSpektrum Channels Received....\n\n");

                receiverQuery = 'a';
                validQuery = true;
                break;

            ///////////////////////////

            case 'E': // Read RC Control Points
                eepromConfig.midCommand   = readFloatUsb();
    	        eepromConfig.minCheck     = readFloatUsb();
    		    eepromConfig.maxCheck     = readFloatUsb();
    		    eepromConfig.minThrottle  = readFloatUsb();
    		    eepromConfig.maxThrottle  = readFloatUsb();
                usbPrint( "\nRC Control Points Received....\n\n" );

                receiverQuery = 'a';
                validQuery = true;
                break;

            ///////////////////////////

            case 'W': // Write EEPROM Parameters
                usbPrint("\nWriting EEPROM Parameters....\n\n");
                writeEEPROM();
                break;

			///////////////////////////

			case '?':
			   	usbPrint("\n");
			   	usbPrint("'a' Receiver Configuration Data            'A' Set RX Input Type                    AX, 1=Parallel, 2=Serial, 3=Spektrum\n");
   		        usbPrint("                                           'B' Set RC Control Order                 BTAER1234\n");
			   	usbPrint("                                           'C' Set Spektrum Resolution              C0 or C1\n");
			   	usbPrint("                                           'D' Set Number of Spektrum Channels      D6 thru D12\n");
			   	usbPrint("                                           'E' Set RC Control Points                EMidCmd;minChk;MaxChk;MinThrot;MaxThrot\n");
			   	usbPrint("'x' Exit Receiver CLI                      'W' Write EEPROM Parameters\n");
			   	usbPrint("\n");
	    	    break;

	    	///////////////////////////
	    }
	}

}

///////////////////////////////////////////////////////////////////////////////
// Sensor CLI
///////////////////////////////////////////////////////////////////////////////

void sensorCLI()
{
    uint8_t  sensorQuery;
    uint8_t  tempInt;
    uint8_t  validQuery = false;

    cliBusy = true;

    usbPrint("\nEntering Sensor CLI....\n\n");

    while(true)
    {
        usbPrint("Sensor CLI -> ");

		while ((usbAvailable() == false) && (validQuery == false));

		if (validQuery == false)
		    sensorQuery = usbRead();

		usbPrint("\n");

		switch(sensorQuery)
		{
            ///////////////////////////

            case 'a': // Sensor Data
                usbPrint("\n");

                usbPrint("Accel One G:               ");
                ftoa(accelOneG,                                numberString); usbPrint(numberString); usbPrint("\n");

                usbPrint("Accel Temp Comp Slope:     ");
                ftoa(eepromConfig.accelTCBiasSlope[XAXIS],     numberString); usbPrint(numberString); usbPrint(", ");
                ftoa(eepromConfig.accelTCBiasSlope[YAXIS],     numberString); usbPrint(numberString); usbPrint(", ");
                ftoa(eepromConfig.accelTCBiasSlope[ZAXIS],     numberString); usbPrint(numberString); usbPrint("\n");

                usbPrint("Accel Temp Comp Bias:      ");
                ftoa(eepromConfig.accelTCBiasIntercept[XAXIS], numberString); usbPrint(numberString); usbPrint(", ");
                ftoa(eepromConfig.accelTCBiasIntercept[YAXIS], numberString); usbPrint(numberString); usbPrint(", ");
                ftoa(eepromConfig.accelTCBiasIntercept[ZAXIS], numberString); usbPrint(numberString); usbPrint("\n");

                usbPrint("Gyro Temp Comp Slope:      ");
                ftoa(eepromConfig.gyroTCBiasSlope[ROLL ],      numberString); usbPrint(numberString); usbPrint(", ");
                ftoa(eepromConfig.gyroTCBiasSlope[PITCH],      numberString); usbPrint(numberString); usbPrint(", ");
                ftoa(eepromConfig.gyroTCBiasSlope[YAW  ],      numberString); usbPrint(numberString); usbPrint("\n");

                usbPrint("Gyro Temp Comp Intercept:  ");
                ftoa(eepromConfig.gyroTCBiasIntercept[ROLL ],  numberString); usbPrint(numberString); usbPrint(", ");
                ftoa(eepromConfig.gyroTCBiasIntercept[PITCH],  numberString); usbPrint(numberString); usbPrint(", ");
                ftoa(eepromConfig.gyroTCBiasIntercept[YAW  ],  numberString); usbPrint(numberString); usbPrint("\n");

                usbPrint("Mag Bias:                  ");
                ftoa(eepromConfig.magBias[XAXIS],              numberString); usbPrint(numberString); usbPrint(", ");
                ftoa(eepromConfig.magBias[YAXIS],              numberString); usbPrint(numberString); usbPrint(", ");
                ftoa(eepromConfig.magBias[ZAXIS],              numberString); usbPrint(numberString); usbPrint("\n");

                usbPrint("Accel Cutoff:              ");
                ftoa(eepromConfig.accelCutoff,                 numberString); usbPrint(numberString); usbPrint("\n");

                usbPrint("KpAcc (MARG):              ");
                ftoa(eepromConfig.KpAcc,                       numberString); usbPrint(numberString); usbPrint("\n");

                usbPrint("KiAcc (MARG):              ");
                ftoa(eepromConfig.KiAcc,                       numberString); usbPrint(numberString); usbPrint("\n");

                usbPrint("KpMag (MARG):              ");
                ftoa(eepromConfig.KpMag,                       numberString); usbPrint(numberString); usbPrint("\n");

                usbPrint("KiMag (MARG):              ");
                ftoa(eepromConfig.KiMag,                       numberString); usbPrint(numberString); usbPrint("\n");

                usbPrint("hdot est/h est Comp Fil A: ");
                ftoa(eepromConfig.compFilterA,                 numberString); usbPrint(numberString); usbPrint("\n");

                usbPrint("hdot est/h est Comp Fil B: ");
                ftoa(eepromConfig.compFilterB,                 numberString); usbPrint(numberString); usbPrint("\n");

                usbPrint("MPU6000 DLPF:               ");
                switch(eepromConfig.dlpfSetting)
                {
                    case DLPF_256HZ:
                        usbPrint("256 Hz\n\n");
                        break;
                    case DLPF_188HZ:
                        usbPrint("188 Hz\n\n");
                        break;
                    case DLPF_98HZ:
                        usbPrint("98 Hz\n\n");
                        break;
                    case DLPF_42HZ:
                        usbPrint("42 Hz\n\n");
                        break;
                }

                validQuery = false;
                break;

            ///////////////////////////

            case 'b': // MPU6000 Calibration
                mpu6000Calibration();

                sensorQuery = 'a';
                validQuery = true;
                break;

            ///////////////////////////

            case 'c': // Magnetometer Calibration
                magCalibration(HMC5883L_I2C);

                sensorQuery = 'a';
                validQuery = true;
                break;

			///////////////////////////

			case 'x':
			    usbPrint("\nExiting Sensor CLI....\n\n");
			    cliBusy = false;
			    return;
			    break;

            ///////////////////////////

            case 'A': // Set MPU6000 Digital Low Pass Filter
                tempInt = (uint8_t)readFloatUsb();

                switch(tempInt)
                {
                    case DLPF_256HZ:
                        eepromConfig.dlpfSetting = BITS_DLPF_CFG_256HZ;
                        break;

                    case DLPF_188HZ:
                    	eepromConfig.dlpfSetting = BITS_DLPF_CFG_188HZ;
                    	break;

                    case DLPF_98HZ:
                    	eepromConfig.dlpfSetting = BITS_DLPF_CFG_98HZ;
                    	break;

                    case DLPF_42HZ:
                    	eepromConfig.dlpfSetting = BITS_DLPF_CFG_42HZ;
                     	break;
                }

                usbPrint("\nMPU6000 DLPF Configuration Received....\n\n");

                setSPIdivisor(MPU6000_SPI, 64);  // 0.65625 MHz SPI clock (within 20 +/- 10%)

                GPIO_ResetBits(MPU6000_CS_GPIO, MPU6000_CS_PIN);
			    spiTransfer(MPU6000_SPI, MPU6000_CONFIG);
			    spiTransfer(MPU6000_SPI, eepromConfig.dlpfSetting);
			    GPIO_SetBits(MPU6000_CS_GPIO, MPU6000_CS_PIN);

                setSPIdivisor(MPU6000_SPI, 2);  // 21 MHz SPI clock (within 20 +/- 10%)

                sensorQuery = 'a';
                validQuery = true;
                break;

            ///////////////////////////

            case 'B': // Accel Cutoff
                eepromConfig.accelCutoff = readFloatUsb();
                usbPrint( "\nAccel Cutoff Received....\n\n" );

                sensorQuery = 'a';
                validQuery = true;
        	    break;

            ///////////////////////////

            case 'C': // kpAcc, kiAcc
                eepromConfig.KpAcc = readFloatUsb();
                eepromConfig.KiAcc = readFloatUsb();
                usbPrint("\nkpAcc and kiAcc Received....\n\n");

                sensorQuery = 'a';
                validQuery = true;
                break;

            ///////////////////////////

            case 'D': // kpMag, kiMag
                eepromConfig.KpMag = readFloatUsb();
                eepromConfig.KiMag = readFloatUsb();
                usbPrint("\nkpMag and kiMag Received....\n\n");

                sensorQuery = 'a';
                validQuery = true;
                break;

            ///////////////////////////

            case 'E': // h dot est/h est Comp Filter A/B
                eepromConfig.compFilterA = readFloatUsb();
                eepromConfig.compFilterB = readFloatUsb();
                usbPrint("\nh dot est/h est Comp Filter A/B Received....\n\n");

                sensorQuery = 'a';
                validQuery = true;
                break;

            ///////////////////////////

            case 'W': // Write EEPROM Parameters
                usbPrint("\nWriting EEPROM Parameters....\n");
                writeEEPROM();
                break;

			///////////////////////////

			case '?':
			   	usbPrint("\n");
			   	usbPrint("'a' Display Sensor Data                    'A' Set MPU6000 DLPF                     A0 thru 3, see aq32Plus.h\n");
			   	usbPrint("'b' MPU6000 Calibration                    'B' Set Accel Cutoff                     BAccelCutoff\n");
			   	usbPrint("'c' Magnetometer Calibration               'C' Set kpAcc/kiAcc                      CKpAcc;KiAcc\n");
			   	usbPrint("                                           'D' Set kpMag/kiMag                      @KpMag;KiMag\n");
			   	usbPrint("                                           'E' Set h dot est/h est Comp Filter A/B  A;B\n");
			   	usbPrint("'x' Exit Sensor CLI                        'W' Write EEPROM Parameters\n");
			   	usbPrint("\n");
	    	    break;

	    	///////////////////////////
	    }
	}

}

///////////////////////////////////////////////////////////////////////////////
