# CFG-RATE (0x06,0x08) packet (without header 0xB5,0x62)
# payload length - 6 (little endian format), update rate 200ms, cycles - 1, reference - UTC (0)

packet = [0x06,0x00,
          0x14,0x00,
          0x01,  0x00,  0x00,0x00,  0xC0,0x08,0x00,0x00,
          0x00,0xC2,0x01,0x00,    0x07,0x00,     0x03,0x00,
          0x00,0x00,     0x00,0x00]

# 0xB0, 0x7E

CK_A,CK_B = 0, 0
for i in range(len(packet)):
  CK_A = CK_A + packet[i]
  CK_B = CK_B + CK_A
# ensure unsigned byte range
CK_A = CK_A & 0xFF
CK_B = CK_B & 0xFF

print "UBX packet checksum:", ("0x%02X,0x%02X" % (CK_A,CK_B))