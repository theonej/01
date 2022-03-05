# appendage table

The appendage table (appendage_table) stores information about the appendages that have been attached to the body.  The appendage table lives on the body and starts at address 0x100000.

The appendage table:

| appendage | address   |
|-----------|-----------|
|a1         |0x100000   |
|a2         |0x101000   |
|a3         |0x102000   |
|a4         |0x104000   |

#

Each entry in the appendage table has the following format:

| name  | mac   | memory size   | public key    | command table address | event table address | command list |
|-------|-------|---------------|---------------|-----------------------|---------------------|--------------|
| 4 b   | 6b    | 4b            | 4096b         | 4b                    | 4b                  | 400b         |

memory size defaults to 4gb, but should be set by the appendage that is registering itself to the body, as different appendages may require different memory sizes.

#

## registering an appendage

An appendage registers itself when it is intialized by sending a packet with the following format:

| body public key    | check sum | name  | mac   | memory size   | command list  | appendage public key |
|--------------------|-----------|-------|-------|---------------|---------------|----------------------|
| 4096b              | 414b      | 4b    | 6b    | 4b            | 400b          | 4096b                |

The body public key is provided as part of the **[appendage OS generation process](/appendage/appendage-os-generation-process)**