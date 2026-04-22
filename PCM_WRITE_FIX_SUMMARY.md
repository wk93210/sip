# SIM7600 PCM Write Error - Fix Summary

## Problem
The SIM7600 module shows continuous "Write error!" messages when trying to write audio to `/dev/ttyUSB5`. The write completes with less than 320 bytes (FRAME_SIZE).

## Root Causes Identified

### 1. O_NONBLOCK Causing EAGAIN Errors
The PCM device is opened with O_NONBLOCK flag (line 222 in chan_dongle.c), and when `writev()` is called, the device buffer may be full, causing `EAGAIN` errors.

**Current behavior:**
- Retry count: 10 attempts
- No delay between retries
- After 10 failures, logs "Write error!" and continues

**Fix Applied in channel.c:iov_write()** (lines 494-545):
```c
// Increased retry count from 10 to 100
int count = 100;

// Added usleep(1000) between retries to allow buffer drain
if(count != 0) {
    /* Add small delay to allow device buffer to drain - SIM7600 needs this */
    usleep(1000);
    goto again;
}

// Improved error messages with errno details
ast_debug (1, "[%s] Deadlock avoided for write! (retried 100 times, errno=%d)\n", PVT_ID(pvt), errno);

// Reset retry count after successful writes
count = 100;  /* Reset retry count after successful write */

// Enhanced write error message
ast_debug (1, "[%s] Write error! Expected %d, wrote %zd (errno=%d: %s)\n",
    PVT_ID(pvt), FRAME_SIZE, done, errno, strerror(errno));
```

### 2. Device Verification
- `/dev/ttyUSB-PCM` is a symlink pointing to `/dev/ttyUSB5` - CORRECT
- The device is mapped to the SIM7600 USB interface - VERIFIED
- Kernel logs confirm device attachment: `GSM modem (1-port) converter now attached to ttyUSB5`

### 3. SIM7600-Specific PCM Configuration
The SIM7600 does NOT require special PCM configuration AT commands:
- Unlike Huawei modems (AT^CVOICE, AT^DDSETEX), SIM7600 enables PCM automatically
- Audio format: 8kHz, 16-bit signed linear (slin) - 320 bytes per 20ms frame
- The PCM interface switches to voice mode automatically when a call is active

## Testing Recommendations

1. **Monitor the write errors with improved logging:**
   ```bash
   sudo tail -f /var/log/asterisk/full | grep -E "Write error|Deadlock avoided|DONGLE-UL"
   ```

2. **Check if the retry fix helps:**
   - With the usleep(1000) between retries, the device buffer should have time to drain
   - The increased retry count (100 vs 10) provides more chances for success

3. **If write errors persist, consider:**
   - Removing O_NONBLOCK from the PCM device open flags (chan_dongle.c:222)
   - This would make writes blocking, but may cause other issues with Asterisk's event loop

4. **Verify PCM data flow:**
   ```bash
   # Check if audio is actually being received from the device
   sudo asterisk -rx "dongle show device dongle0"
   ```

## Additional Notes

- The UL (uplink) audio path fix (unconditional mixb_attach) is already in place
- The SIM7600 compatibility changes (skipping Huawei-specific AT commands) are working
- The VOICE CALL: BEGIN event handler is properly detecting call connection

## Build Issues

The module cannot be easily recompiled for Asterisk 20 due to API changes. The codebase was originally written for Asterisk 1.8-13. To use these fixes:

1. Apply the fixes to a codebase compatible with Asterisk 20
2. Or use the chan_dongle fork that supports modern Asterisk versions

## References

- iov_write() function: channel.c:494
- PCM device opening: chan_dongle.c:222, 691
- FRAME_SIZE definition: cpvt.h:16 (320 bytes = 20ms @ 8kHz 16-bit)
