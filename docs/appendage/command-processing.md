# command processing

the appendage OS runs an infinite command loop that determines what commands need to be executed. 

#

command table format:

| command id    | command byte |
|---------------|--------------|
| 4b            | 1b           |

command byte format:
0 - unused
1 - unused
2 - unused
3 - unused
4 - unused
5 - unused
6 - cancelled
7 - processed

if all bits are set high(0xff), it indicates the end of the command table

# 
the command loop starts at the beginning of the command table, which has a starting address of 0x200000 and grow downwards, and examines each entry to see if the lowermost bit processed byte is on and the second lowermost bit (the cancelled bit) is also set low.  If the lowermost bit of the command byte is not on, the command is processed (see [command processing](/appendage/command-processing) for details) and the lowermost bit of the command byte is set high.

the execution loop continues until the end of the command table is reached (indicated by a command byte value of 0xff).  the loop then starts at the beginning of the table again.  in this way, commands can be queued up and processing in a FiFo manner to ensure correct sequencing.