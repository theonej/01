# command/control map table

The **body** contains a command/control map table that maps control inputs (i.e. human interface device inputs) to commands supported by an appendage.  When a control input is received (e.g. a keystroke is entered), a lookup is performed against the command/control map table to determine if a command should be dispatched to an appendage.

the format of the command/control map table is as follows:

| control address   | command address   |
|-------------------|-------------------|
| 4b                | 4b                |
