# Tests for chan_dongle

noinst_PROGRAMS = test_at_parse

test_at_parse_SOURCES = \
	test_at_parse.c \
	$(top_srcdir)/at_parse.c \
	$(top_srcdir)/char_conv.c \
	$(top_srcdir)/pdu.c \
	$(top_srcdir)/memmem.c

test_at_parse_CFLAGS = \
	-O2 -g -Wall -std=gnu11 \
	-D_GNU_SOURCE \
	-DHAVE_CONFIG_H \
	-DAST_MODULE_SELF_SYM=__internal_test_self \
	-I$(top_srcdir) \
	-include $(top_srcdir)/preinclude.h \
	$(SQLITE3_CFLAGS) \
	-idirafter $(ASTERISK_INCLUDE_DIR)/asterisk

test_at_parse_LDADD = \
	$(SQLITE3_LIBS) \
	-lpthread

# Test target
check: test_at_parse
	./test_at_parse

.PHONY: test
test: check
