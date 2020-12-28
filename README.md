# Key Duplicator
Simple Dallas key duplicator based on arduino. 
Supports keys/buttons:
 * RW-1990.1 
 * RW-1990.2 

# Device operation
1. After power on, the GREEN LED starts blinking, waiting for the read source key. 
2. Connect the source key to the socket.
    
    2.1. In case the device failed to read the key, a long beep will be reproduced. GREEN LED will continue blinking, giving a chance to try again.  
    
    2.2. If the key recognized and successfully read, a short beep will be reproduced and the GREEN LED will light up constantly. The device is ready for the next action (button to be pressed)
3. As soon as the button will be pressed, a short beep will be reproduced and 
RED LED will start blinking awaiting for RW key (a new one). 
4. Connect the RW key to the socket and the process of writing will be started. 
   
    4.1. In case of successful key duplication, a short beep will be reproduced, 
   
    4.2. Otherwise a long beep will be reproduced.
    
    Regardless of duplication results, RED LED becomes OFF, the GREEN LED will stay ON, changing the device available for the new attempt of duplication (step 3).
Press the button again and make a new attempt.

Holding the button for more then 3 seconds you will reboot the device and you can change the source key.

# Sketch

![sketch](sketch.png)

# Requirements
* PlatformIO Core 5+