# ADR-002: NFC NDEF approach with PN532

**Status:** Accepted

**Date:** 2022-11-03

**Context:**  
TapTune must allow a phone to receive an NDEF record that opens Bluetooth settings. The PN532 can work as a reader or as an emulated tag.

**Options considered:**

1. **PN532 as reader** – the nearby phone is read, but NDEF cannot be sent.
2. **PN532 as emulated target (passive tag)** – the chip responds with a predefined NDEF when a reader (phone) interrogates it.

**Decision:**  
We use the **emulated target** mode of the PN532.  
Benefits:
- The user does nothing: they tap their phone and receive the link to Bluetooth settings.
- No interaction with the phone's NFC app is required beyond the automatic read.

**Consequences:**
- The firmware must configure the PN532 in target mode and keep polling to detect when a reader has read the tag, then generate the `NfcTapped` event.
- Greater initialization complexity, but once working it is robust.
