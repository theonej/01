# body info

The body maintains a **body info** table that contains information **appendages** can use to join the body.

The format of the body info table is as follows:

| name  | mac   | join certificate  | join certificate public key   |
|-------|-------|-------------------|-------------------------------|
| 4b    | 6b    | 4096b             | 4096b                         |

The join certificate and join certificate public key are embedded within the OS when the OS binary is generated.

## adding an appendage

When the body is put into pairing mode, it listens for incoming connections that contain the join certificate public key.

The connection body should contain the following packet format:

| body public key    | check sum | name  | mac   | memory size   | command list  | appendage public key |
|--------------------|-----------|-------|-------|---------------|---------------|----------------------|
| 4096b              | 414b      | 4b    | 6b    | 4b            | 400b          | 4096b                |

The check sum for the packet should be generated by appending the name, mac, memorysize, and command list and encrypting them using the provided public key.

The body will first check to ensure that the join certificate public key in the body info table is a match for the provided body public key, and then will attempt to decrypt the check sum using the join certificate (private key).  The resulting infromation will then be checked against the provided packaet information.  If an exact match is identified, the appendage will be registered in the **[appendage table](/appendage/appendage-table)** at the next available address.

