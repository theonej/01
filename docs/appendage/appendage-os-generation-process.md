# appendage OS generation process

When a new appendage is to be added to a body, an **appendage OS** binary must be generated which contains the necessary certificate information to allow the appendage to join a body.

When the body OS is generated, a public/private keypair are embedded within the binary and stored in the **[body info table](/body/body-info)**.  The body public key must be provided to the OS generation process for the appendage to ensure that only authorized appendages can communicate with the host body.

The body OS contains a command for getting the embedded public key, which can then be provided when generating the appendage OS, ensuring cryptographic pairing between the body and appendage.

the appendage OS generation process also generates a unique public/private key pair for the appendage which can be used to authenticate messages from the body to the appendage