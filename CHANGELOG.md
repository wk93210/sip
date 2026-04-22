# Changelog

All notable changes to this project will be documented in this file.

## [2.0.0] - 2025

### Added
- SIM7600E-H full support and optimization
- Modern Asterisk compatibility (18.x, 20.x, 22.x)
- Improved PCM write retry logic with usleep delays
- Enhanced error messages with errno details
- Proper glibc/GCC compatibility for modern Linux systems
- VOICE CALL: BEGIN handling for SIM7600

### Fixed
- PCM write errors causing continuous "Write error!" messages
- UL audio not working due to mixb_attach conditional
- AT^CVOICE timeout on SIM7600 (now skipped)
- AT+COPS=0,0 timeout on SIM7600 (now handled gracefully)
- AT^DDSETEX not supported on SIM7600 (now skipped)

### Changed
- Updated build system for modern compilers
- Improved preinclude.h for glibc compatibility
- Cleaned up build artifacts and temporary files
- Enhanced documentation with SIM7600-specific instructions

### Removed
- Legacy build file support
- Temporary/backup files (.bak, .o, test files)

## [1.0.0] - Original Release

### Features
- Initial chan_dongle release
- Huawei modem support (original focus)
- Voice calls, SMS, USSD support
- Asterisk 1.8-13 compatibility
