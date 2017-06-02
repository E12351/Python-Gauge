/*********************************************
Filename: Main.c
Project : SB Board
Product : Battery Charger / Monitor
Date    : 06/14/2016
Contents: Main Control Loop
***********************************************/

#include "global.h"

void main(void)
{
    init_devices();
    while(1)
    {
        if (Data_Recieved == 'Y')
        {
            if ((HOST_INBUFF[0] == 'R') || (HOST_INBUFF[0] == 'r'))
            {
                Command_1 = 'R';

                if ((HOST_INBUFF[1] == 'B') || (HOST_INBUFF[1] == 'b'))
                {
                    Command_2 = 'B';
                    Valid_Command = 'Y';
                }
                else
                {
                    Error = 1;
                    Error_Routine();
                    Command_1 = Command_2 = Command_3 = 0;
                    Valid_Command = 'N';
                }
            }
            else
            {
                Error = 1;
                Error_Routine();
                Command_1 = Command_2 = Command_3 = 0;
                Valid_Command = 'N';
            }
        }

        if (Valid_Command == 'Y')
        {

            temp = &HOST_INBUFF[2];
            Command_3 = atoi(temp);

            if ((Command_3 < 1) || (Command_3 > 8))
            {
                Error = 2;
                Error_Routine();
                Command_1 = Command_2 = Command_3 = 0;
            }
            else
            {
                if ((Command_1 == 'R') && (Command_2 == 'B'))
                {
                    switch(Command_3)
                    {
                        case 1:
                        {
                            NOP();
                            Voltage = 12.11;
                            Current = 1.11;
                            break;
                        }
                        case 2:
                        {
                            NOP();
                            Voltage = 12.22;
                            Current = 2.22;
                            break;
                        }
                        case 3:
                        {
                            NOP();
                            Voltage = 12.33;
                            Current = 3.33;
                            break;
                        }
                        case 4:
                        {
                            NOP();
                            Voltage = 12.44;
                            Current = 4.44;
                            break;
                        }
                        case 5:
                        {
                            NOP();
                            Voltage = 12.55;
                            Current = 5.55;
                            break;
                        }
                        case 6:
                        {
                            NOP();
                            Voltage = 12.66;
                            Current = 6.66;
                            break;
                        }
                        case 7:
                        {
                            NOP();
                            Voltage = 12.77;
                            Current = 7.77;
                            break;
                        }
                        case 8:
                        {
                            NOP();
                            Voltage = 12.88;
                            Current = 8.88;
                            break;
                        }
                        default:
                        {
                            NOP();
                            Voltage = 0;
                            break;
                        }
                        break;
                        } // end of switch(Command_3)
                    if (Current == 0)
                    {
                        HOST_OUTBUFF[15] = '0';
                        HOST_OUTBUFF[17] = '0';
                        HOST_OUTBUFF[18] = '0';
                    }
                    else
                    {
                        current_integer_1 = floorf(Current);
                        current_remainder = (Current - current_integer_1);
                        HOST_OUTBUFF[15] = (current_integer_1 + 48);
                        current_remainder_1 = (current_remainder * 10);
                        current_integer_2 = floorf(current_remainder_1);
                        current_remainder_2 = ((current_remainder_1 - current_integer_2) * 10);
                        current_integer_3 = floorf(current_remainder_2);
                        HOST_OUTBUFF[17] = (current_integer_2 + 48);
                        HOST_OUTBUFF[18] = (current_integer_3 + 48);
                    }

                    if (Voltage == 0)
                    {
                        HOST_OUTBUFF[9] = (0 + 48);
                        HOST_OUTBUFF[10] = (0 + 48);
                        volt_integer_2 = volt_integer_3 = 0;
                    }
                    else
                    {
                        // if Voltage is 12.34 then the comments are correct
                        volt_integer_1 = floorf(Voltage);                                   // gets integer portion  is 12
                        volt_remainder = (Voltage - volt_integer_1);                        // gets stuff after decimal point  is .34
                        if (volt_integer_1 < 10)
                        {
                            HOST_OUTBUFF[9] = (0 + 48);
                            HOST_OUTBUFF[10] = (volt_integer_1 + 48);
                        }
                        else
                        {
                            HOST_OUTBUFF[9] = (1 + 48);
                            HOST_OUTBUFF[10] = ((volt_integer_1 - 10) + 48);
                        }
                        volt_remainder_1 = (volt_remainder * 10);                           // 3.4
                        volt_integer_2 = floorf(volt_remainder_1);                          // 3
                        volt_remainder_2 = ((volt_remainder_1 - volt_integer_2) * 10);      // .4
                        volt_integer_3 = floorf(volt_remainder_2);                          // 4
                    }

                    HOST_OUTBUFF[0] = 'B';
                    HOST_OUTBUFF[1] = 'A';
                    HOST_OUTBUFF[2] = 'T';
                    HOST_OUTBUFF[3] = 'T';
                    HOST_OUTBUFF[4] = 'E';
                    HOST_OUTBUFF[5] = 'R';
                    HOST_OUTBUFF[6] = 'Y';
                    HOST_OUTBUFF[7] = (Command_3 + 48);
                    HOST_OUTBUFF[8] = '=';
                    HOST_OUTBUFF[11] = '.';
                    HOST_OUTBUFF[12] = (volt_integer_2 + 48);
                    HOST_OUTBUFF[13] = (volt_integer_3 + 48);
                    HOST_OUTBUFF[14] = ' ';
                    HOST_OUTBUFF[16] = '.';
                    HOST_OUTBUFF[19] = CR;
                    HOST_OUTBUFF[20] = LF;
                    HOST_OUTBUFF[21] = EOT;

                    Data_Recieved = 'N';
                    HOST_DATASEND();
                    for (q1 = 0; q1 < 24; q1++)
                    {
                        HOST_INBUFF[q1] = 0;
                    }
                    Command_1 = Command_2 = Command_3 = 0;
                    Valid_Command = 'N';
                } // end of if ((Command_1 == 'R') && (Command_2 == 'B'))
            } // end of else
        } // end of if (Valid_Command == 'Y')
/*
        if (Second_Passed == 'Y')
        {
            HOST_OUTBUFF[0] = 'T'; HOST_OUTBUFF[1] = 'I';
            HOST_OUTBUFF[2] = 'M'; HOST_OUTBUFF[3] = 'E';
            HOST_OUTBUFF[4] = CR;  HOST_OUTBUFF[5] = LF;
            HOST_OUTBUFF[6] = EOT;
            HOST_DATASEND();
            Second_Passed = 'N';
        }
*/
	    if (COMMUN_STATUS & HOST_RECVD)  //NEW HOST MESSAGE
	    {
	        if (HOST_INBUFF[1] == BELL)
			{
			    if (!(COMMUN_STATUS & SLAVE_TX_BUSY))
				{
				    COMMUN_STATUS &= ~HOST_RECVD;
				    COMMUN_STATUS &= ~HOST_RX_BUSY;
				}
			}
			else
			{
			    if (!(COMMUN_STATUS & SLAVE_TX_BUSY))
				{
				    COMMUN_STATUS |= SLAVE_TX_BUSY;
					COMMUN_STATUS &= ~HOST_RX_BUSY; //NOT BUSY
					COMMUN_STATUS &= ~HOST_RECVD;
				}
			}
	    }  //END HOST RECVD
    }  //END while
} //END MAIN

void Error_Routine(void)
{
    Data_Recieved = 'N';
    for (q1 = 0; q1 < 24; q1++)
    {
        HOST_INBUFF[q1] = 0;
    }
    if (Error == 2)
    {
        HOST_OUTBUFF[0] = 'V'; HOST_OUTBUFF[1] = 'A';
        HOST_OUTBUFF[2] = 'L'; HOST_OUTBUFF[3] = 'U';
        HOST_OUTBUFF[4] = 'E'; HOST_OUTBUFF[5] = ' ';
        HOST_OUTBUFF[6] = 'N'; HOST_OUTBUFF[7] = 'O';
        HOST_OUTBUFF[8] = ' '; HOST_OUTBUFF[9] = 'G';
        HOST_OUTBUFF[10] = 'O'; HOST_OUTBUFF[11] = 'O';
        HOST_OUTBUFF[12] = 'D';
        HOST_OUTBUFF[13] = CR;  HOST_OUTBUFF[14] = LF;
        HOST_OUTBUFF[15] = EOT;
    }
    if (Error == 1)
    {
        HOST_OUTBUFF[0] = 'B'; HOST_OUTBUFF[1] = 'A';
        HOST_OUTBUFF[2] = 'D'; HOST_OUTBUFF[3] = ' ';
        HOST_OUTBUFF[4] = 'C'; HOST_OUTBUFF[5] = 'O';
        HOST_OUTBUFF[6] = 'M'; HOST_OUTBUFF[7] = 'M';
        HOST_OUTBUFF[8] = 'A'; HOST_OUTBUFF[9] = 'N';
        HOST_OUTBUFF[10] = 'D';
        HOST_OUTBUFF[11] = CR;  HOST_OUTBUFF[12] = LF;
        HOST_OUTBUFF[13] = EOT;
    }
    HOST_DATASEND();
    Error = 0;
    Valid_Command = 'N';
    return;
}



