# Build Success - Asterisk 20 Compatibility

## Problem Solved
Successfully compiled chan_dongle with SIM7600 PCM write fixes for Asterisk 20.

## Build Process

### Working Makefile
Used `Makefile.fix_headers` which includes:
- Header compatibility fixes for glibc/GCC
- Proper include order with `preinclude.h`
- `-idirafter` flag to avoid header shadowing issues
- Asterisk 20 version defines

### Build Commands
```bash
cd /home/lunanli/sip/chan_dongle-src
make -f Makefile.fix_headers clean
make -f Makefile.fix_headers
sudo cp chan_dongle.so /usr/lib/asterisk/modules/
sudo chmod 644 /usr/lib/asterisk/modules/chan_dongle.so
```

## Fixes Included in Build

### 1. PCM Write Fix (channel.c:iov_write)
- Increased retry count from 10 to 100
- Added usleep(1000) between retries for buffer drain
- Reset retry count after successful writes
- Enhanced error messages with errno details

### 2. SIM7600 Compatibility
- Skipped AT^CVOICE check (Huawei-specific)
- Skipped AT^DDSETEX commands
- Added VOICE CALL: BEGIN handling
- Unconditional mixb_attach for UL audio

## Verification
```bash
# Verify fix is in module
strings /usr/lib/asterisk/modules/chan_dongle.so | grep "Deadlock avoided"
# Output: [%s] Deadlock avoided for write! (retried 100 times, errno=%d)

strings /usr/lib/asterisk/modules/chan_dongle.so | grep "Write error"
# Output: [%s] Write error! Expected %d, wrote %zd (errno=%d: %s)
```

## Files Modified
- channel.c - PCM write retry logic
- at_command.c - Skip Huawei-specific commands for SIMCOM
- at_response.c - SIMCOM detection and VOICE CALL: BEGIN handling

## Next Steps to Test
1. Restart Asterisk: `sudo systemctl restart asterisk`
2. Load module: `sudo asterisk -rx "module load chan_dongle"`
3. Check device: `sudo asterisk -rx "dongle show devices"`
4. Make a test call and monitor logs:
   ```bash
   sudo tail -f /var/log/asterisk/full | grep -E "Write error|Deadlock avoided|DONGLE-UL"
   ```
